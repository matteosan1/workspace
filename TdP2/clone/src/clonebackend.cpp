#include "clonenodeagent.h"
#include "zmqhelper.h"
#include "utilsclone.h"

#include <zmq.h>

#include <QStringList>

#include <functional>

#define zUuid(msg) \
    QString("%1 Clone %2 %3").arg(utils::uuid2string(_uuid)).arg(_name).arg(msg)

#define zCat(msg) \
    "clone", zUuid(msg)

#define BIND_INPROC(fun) \
    std::bind(&CloneBackend::fun, this, std::placeholders::_1)


CloneBackend::CloneBackend(const QString &name, void *zmqCtx, const QUuid &uuid,
    QObject *parent) : QObject(parent),
    _zmqCtx(zmqCtx), _uuid(uuid), _name(name),
    _socketInproc(0), _socketSnapshot(0), _socketUpdate(0), _socketCollector(0),
    _stopped(false)
{
    assert_msg(_zmqCtx, "ZMQ context is null");
    assert_msg(!_uuid.isNull(), "UUID is invalid");
}

CloneBackend::~CloneBackend()
{
}

void CloneBackend::doWork(int msecs)
{
    zInfo(zCat(QString("started for %1")
        .arg(msecs >= 0 ? QString("%1 msecs").arg(msecs) : "unlimited time")));

    _stopped = false;

    emit started();

    std::function<bool (void)> maxTimeExpired;
    if (msecs >= 0) {
        maxTimeExpired = [ = ]() {
            static const int t0 = utils::uptime();
            return utils::uptime() - t0 >= (unsigned long) msecs;
        };
    } else {
        maxTimeExpired = []() {
            return false;
        };
    }

    // Create ZMQ inproc socket
    const bool inproc_conn = createCommSocket(_socketInproc, ZMQ_PAIR, zmq::zmqBindSocket,
        QList<QString>() << QString("inproc://backend-%1").arg(_uuid.toString()), "inproc");
    assert_msg(inproc_conn, "ZMQ backend inproc socket creation failed");

    // Run main backend loop
    while (!maxTimeExpired() && !_stopped) {
        if (isSocketReadable(_socketInproc))
            handleInprocCommands();

        doBackendStep();
    }

    // Delete ZMQ sockets
    deleteCommSocket(_socketInproc, "inproc");
    deleteCommSocket(_socketSnapshot, "snapshot");
    deleteCommSocket(_socketUpdate, "update");
    deleteCommSocket(_socketCollector, "collector");

    //zInfo(zCat("finished"));
    emit finished();
}

void CloneBackend::doBackendStep()
{
    // Do nothing
}

bool CloneBackend::createCommSocket(void * &socket, int type,
    std::function<bool (void *, const char *)> connectSocket,
    const QList<QString> &endpoints, const QString &descr)
{
    if (!connectSocket) {
        zError(zCat(QString("%1 socket could not be created: connection function is null")
            .arg(descr)));
        return false;
    }

    // Delete the socket, if already created
    deleteCommSocket(socket, descr);

    socket = zmq::zmqCreateSocket(_zmqCtx, type);
    if (!socket) {
        zError(zCat(QString("%1 socket could not be created: %2")
            .arg(descr).arg(zmq_strerror(errno))));
        return false;
    }

    // Detect the type of action
    bool (* const * ptr)(void *, const char *) =
        connectSocket.target<bool(*)(void*, const char *)>();

    QString action;
    if (ptr && *ptr == zmq::zmqConnectSocket)
        action = "connected";
    else if (ptr && *ptr == zmq::zmqBindSocket)
        action = "bound";
    else
        action = "associated";

    if (endpoints.isEmpty()) {
        zError(zCat(QString("%1 socket could not be %2 to an empty endpoint")
            .arg(descr).arg(action)));

        deleteCommSocket(socket, descr);
        return false;
    }

    foreach (const QString &endpoint, endpoints) {
        if (endpoint.isEmpty() || !connectSocket(socket, qPrintable(endpoint))) {
            zError(zCat(QString("%1 socket could not be %2 to %3")
                .arg(descr).arg(action)
                .arg(!endpoint.isEmpty() ? endpoint : "an empty endpoint")));

            deleteCommSocket(socket, descr);
            return false;
        }
    }

    QStringList endpointsTmp = (QStringList)endpoints;
    zInfo(zCat(QString("%1 socket %2 to %3")
        .arg(descr).arg(action).arg(endpointsTmp.join(" "))));

    return true;
}

bool CloneBackend::deleteCommSocket(void * &socket, const QString &descr)
{
    if (socket) {
        const bool succ = zmq::zmqCloseSocket(socket);
        socket = 0;

        if (succ) {
            zDebug(zCat(QString("%1 socket closed").arg(descr)));
            return true;

        } else {
            zWarning(zCat("%1 socket could not be closed"));
            return false;
        }
    }

    return false;
}

bool CloneBackend::isSocketReadable(void * socket, int msecs) const
{
    if (!socket)
        return false;

    zmq_pollitem_t fds[] =
    {
        {socket, 0, ZMQ_POLLIN, 0},
    };

    const bool poll = zmq::zmqPoll(fds, countof(fds), msecs);
    assert_msg(poll, qPrintable(QString("ZMQ poll failed: %1")
        .arg(zmq_strerror(errno))));

    return fds[0].revents & ZMQ_POLLIN;
}

void CloneBackend::handleInprocCommands()
{
    QList<QByteArray> request = zmq::zmqRecvMessage(_socketInproc);
    assert_msg(!request.isEmpty(), "ZMQ backend inproc request is null");

    const QList<QByteArray> reply = handleInprocCommands(request);
    assert_msg(!reply.isEmpty(), "ZMQ backend inproc reply is null");

    const bool answer_reply = zmq::zmqSendMessage(_socketInproc, reply);
    assert_msg(answer_reply, "ZMQ backend inproc answer failed");
}

QList<QByteArray> CloneBackend::handleInprocCommands(const QList<QByteArray> &request)
{
    const BackendCommand cmd = BackendCommand(
        zmq::zmqDecodeMessagePart<backend_cmd_t>(request.at(0)));

    switch (cmd) {
    case BackendCommand::Stop:
        return handleInprocCommand("STOP", BIND_INPROC(handleInprocStop),
            request);

    default:
        QList<QByteArray> ko = handleInprocCommand("UNKNOWN", BIND_INPROC(handleInprocUnknown),
            request);

        zError(zCat(QString("inproc unknown request %1")
            .arg(QString(zmq::zmqMessageToHex(request)))));

        return ko;
    };
}

QList<QByteArray> CloneBackend::handleInprocCommand(const QString &cmdstr,
    std::function<QList<QByteArray> (const QList<QByteArray> &)> cmdfun,
    const QList<QByteArray> &request)
{
    zDebug(zCat(QString("inproc %1 request %2")
        .arg(cmdstr).arg(QString(zmq::zmqMessageToHex(request)))));

    const QList<QByteArray> reply = cmdfun(request);

    zDebug(zCat(QString("inproc %1 answer %2")
        .arg(cmdstr).arg(QString(zmq::zmqMessageToHex(reply)))));

    return reply;
}

QList<QByteArray> CloneBackend::handleInprocUnknown(const QList<QByteArray> &request)
{
    Q_UNUSED(request);

    return QList<QByteArray>()
        << zmq::zmqEncodeMessagePart<backend_ret_t>(false);
}

QList<QByteArray> CloneBackend::handleInprocStop(const QList<QByteArray> &request)
{
    Q_UNUSED(request);

    _stopped = true;

    return QList<QByteArray>()
        << zmq::zmqEncodeMessagePart<backend_ret_t>(true);
}
