#include "clonebrokerapp.h"
#include "clonebrokeragent.h"
#include "zmqhelper.h"

#include "zlogger.h"
#include "utilsclone.h"


#define zUuid(msg) \
    QString("%1 Clone %2 %3").arg(utils::uuid2string(_uuid)).arg(_name).arg(msg)

#define zCat(msg) \
    "clone", msg

using namespace logging;

CloneBrokerApp::CloneBrokerApp(QObject *parent) :
    CloneFrontend("broker app", [](void * ctx, const QUuid &uuid) {
        return new CloneBrokerAgent(ctx, uuid);
    }, parent)
{
    connect(_cloneBackend,
        SIGNAL(snapshotSynced(QUuid)),
        SIGNAL(snapshotSynced(QUuid)),
        Qt::QueuedConnection);
}

CloneBrokerApp * CloneBrokerApp::createBroker(QObject *parent)
{
    return new CloneBrokerApp(parent);
}

bool CloneBrokerApp::bindBroker(const QList<QString> &snapshot, const QList<QString> &update,
    const QList<QString> &collector)
{
    QList<QByteArray> request;
    request.append(zmq::zmqEncodeMessagePart<backend_cmd_t>(BrokerAgentCommand::Bind));

    foreach (const QList<QString> *list, QList<const QList<QString>*>()
        << &snapshot << &update << &collector)
    {
        foreach (const QString &endpoint, *list)
            request.append(zmq::zmqEncodeMessagePart<QByteArray>(endpoint.toLocal8Bit()));

        request.append(zmq::zmqEncodeMessagePart<QByteArray>(QByteArray()));
    }

    return handleInprocCommand("BIND", request);
}

bool CloneBrokerApp::unbindBroker()
{
    return handleInprocCommand("UNBIND", QList<QByteArray>()
        << zmq::zmqEncodeMessagePart<backend_cmd_t>(BrokerAgentCommand::Unbind));
}
