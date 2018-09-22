#include "clonefrontend.h"
#include "clonebackend.h"
#include "zmqhelper.h"

#include "zlogger.h"
#include "utilsclone.h"

#include <QThread>
#include <QMetaObject>
#include <QUuid>

#include <zmq.h>
#include <unistd.h>

using namespace logging;

#define zUuid(msg) \
    QString("%1 Clone %2 %3").arg(utils::uuid2string(_uuid)).arg(_name).arg(msg)

#define zCat(msg) \
    "clone", zUuid(msg)


CloneFrontend::CloneFrontend(const QString &name, make_backend_t createBackend,
    QObject *parent) : QObject(parent),
    _zmqCtx(zmq_ctx_new()), _uuid(QUuid::createUuid()), _name(name),
    _cloneThread(new QThread), _cloneBackend(createBackend(_zmqCtx, _uuid)),
    _socketInproc(0)
{
    assert_msg(_zmqCtx, "ZMQ context is null");
    assert_msg(!_uuid.isNull(), "UUID is invalid");

    _cloneBackend->moveToThread(_cloneThread);

//    connect(_cloneThread, &QThread::started, [ = ]() {
//        zDebug(zCat("thread started"));
//    });

//    connect(_cloneThread, &QThread::finished, [ = ]() {
//        zDebug(zCat("thread finished"));
//    });

    zDebug(zCat("thread is being started..."));
    _cloneThread->start();
    startBackend();

    createInprocSocket();
}

CloneFrontend::~CloneFrontend()
{
    zDebug(zCat("thread is being stopped..."));

    // Stop backend
    stopBackend();

    _cloneThread->quit();
    _cloneThread->wait();

    delete _cloneBackend;
    delete _cloneThread;

    zInfo(zCat("ZMQ context is now terminated"));

    // close sockets
    deleteInprocSocket();

    zmq_term(_zmqCtx);

    zInfo(zCat("terminated"));
}

QUuid CloneFrontend::uuid() const
{
    return _uuid;
}

void CloneFrontend::createInprocSocket()
{
    // Delete ZMQ inproc socket, if already created.
    deleteInprocSocket();

    _socketInproc = zmq::zmqCreateSocket(_zmqCtx, ZMQ_PAIR);
    assert_msg(_socketInproc, "ZMQ inproc socket creation failed");

    const bool recv_timeo = zmq::zmqSetsockopt<int>(_socketInproc, ZMQ_RCVTIMEO, 15000);
    assert_msg(recv_timeo, "ZMQ inproc socket recv timeout setup failed");

    /// FIXME: inproc endpoint may fail to connect when two backends have the same uuid
    /// On inproc zmq sockets, zmq_bind must be called *before* zmq_connect
    const QString endpoint = QString("inproc://backend-%1").arg(_uuid.toString());
    bool conn;
    int cnt = 0;
    for (;;) {
        conn = zmq::zmqConnectSocket(_socketInproc, qPrintable(endpoint));
        if (conn || errno != ECONNREFUSED)
            break;
        if (++cnt > 15)
            break;
        usleep(100000);
    }
    assert_msg(conn, qPrintable(QString("ZMQ inproc socket connection failed to %1: %2")
        .arg(endpoint).arg(zmq_strerror(errno))));

    zInfo(zCat(QString("inproc socket connected to %1")
        .arg(endpoint)));
}

void CloneFrontend::deleteInprocSocket()
{
    if (_socketInproc) {
        if (zmq::zmqCloseSocket(_socketInproc))
            zDebug(zCat("inproc socket closed"));
        else
            zWarning(zCat("inproc socket could not be closed"));

        _socketInproc = 0;
    }
}

void CloneFrontend::startBackend(int msecs)
{
    QMetaObject::invokeMethod(_cloneBackend, "doWork",
        Qt::QueuedConnection, Q_ARG(int, msecs));
}

void CloneFrontend::stopBackend()
{
    handleInprocCommand("STOP", QList<QByteArray>()
        << zmq::zmqEncodeMessagePart<backend_cmd_t>(BackendCommand::Stop));
}

bool CloneFrontend::handleInprocCommand(const QString &cmdstr, const QList<QByteArray> request,
    std::function<bool (const QList<QByteArray> &)> handleReply)
{
    zInfo(zCat(QString("inproc %1 request")
        .arg(cmdstr)));

    const bool cmd_request = zmq::zmqSendMessage(_socketInproc, request);
    assert_msg(cmd_request, qPrintable(QString("inproc %1 request failed")
        .arg(cmdstr)));

    QList<QByteArray> cmd_reply = zmq::zmqRecvMessage(_socketInproc);
    assert_msg(!cmd_reply.isEmpty(), qPrintable(QString("inproc %1 answer failed")
        .arg(cmdstr)));

    const bool success = zmq::zmqDecodeMessagePart<backend_ret_t>(cmd_reply.at(0));

    if (success && handleReply(cmd_reply)) {
        zInfo(zCat(QString("inproc %1 answer: ok")
            .arg(cmdstr)));
        return true;
    } else {
        zError(zCat(QString("inproc %1 answer: err")
            .arg(cmdstr)));
        return false;
    }
}
