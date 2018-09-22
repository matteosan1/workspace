#include "clonenodeapp.h"
#include "clonenodeagent.h"
#include "zmqhelper.h"

#include "zlogger.h"
#include "utilsclone.h"

#include <QStringList>

using namespace logging;

#define zUuid(msg) \
    QString("%1 Clone %2 %3").arg(utils::uuid2string(_uuid)).arg(_name).arg(msg)

#define zCat(msg) \
    "clone", zUuid(msg)


CloneNodeApp::CloneNodeApp(QObject *parent) :
    CloneFrontend("node app", [](void * ctx, const QUuid &uuid) {
        return new CloneNodeAgent(ctx, uuid);
    }, parent)
{
    connect(_cloneBackend,
        SIGNAL(nodeConnected()),
        SIGNAL(nodeConnected()),
        Qt::QueuedConnection);

    connect(_cloneBackend,
        SIGNAL(nodeDisconnected()),
        SIGNAL(nodeDisconnected()),
        Qt::QueuedConnection);

    connect(_cloneBackend,
        SIGNAL(connectionError(QString)),
        SIGNAL(connectionError(QString)),
        Qt::QueuedConnection);

    connect(_cloneBackend,
        SIGNAL(connectionTimeout()),
        SIGNAL(connectionTimeout()),
        Qt::QueuedConnection);

    connect(_cloneBackend,
        SIGNAL(connectionReady()),
        SIGNAL(connectionReady()),
        Qt::QueuedConnection);

    connect(_cloneBackend,
        SIGNAL(snapshotSynced(QUuid)),
        SIGNAL(snapshotSynced(QUuid)),
        Qt::QueuedConnection);

    connect(_cloneBackend,
        SIGNAL(topicUpdated(QByteArray, QByteArray, QUuid)),
        SIGNAL(topicUpdated(QByteArray, QByteArray, QUuid)),
        Qt::QueuedConnection);
}

CloneNodeApp * CloneNodeApp::createNode(QObject *parent)
{
    return new CloneNodeApp(parent);
}

bool CloneNodeApp::connectNode(const QString &snapshot, const QString &update,
    const QString &collector)
{
    return handleInprocCommand("CONNECT", QList<QByteArray>()
        << zmq::zmqEncodeMessagePart<backend_cmd_t>(NodeAgentCommand::Connect)
        << zmq::zmqEncodeMessagePart<QByteArray>(snapshot.toLocal8Bit())
        << zmq::zmqEncodeMessagePart<QByteArray>(update.toLocal8Bit())
        << zmq::zmqEncodeMessagePart<QByteArray>(collector.toLocal8Bit()));
}

bool CloneNodeApp::disconnectNode()
{
    return handleInprocCommand("DISCONNECT", QList<QByteArray>()
        << zmq::zmqEncodeMessagePart<backend_cmd_t>(NodeAgentCommand::Disconnect));
}

bool CloneNodeApp::subscribeToSpecificTopics(const QList<QByteArray> &topics)
{
    if (topics.isEmpty()) {
        zError(zCat("could not subscribe to empty topics"));
        return false;
    }

    QList<QByteArray> subtree;
    subtree.append(zmq::zmqEncodeMessagePart<backend_cmd_t>(NodeAgentCommand::SetSubtree));

    foreach (const QString &topic, topics) {
        if (!topic.isEmpty()) {
            subtree.append(zmq::zmqEncodeMessagePart<QByteArray>(topic.toLocal8Bit()));
        } else {
            zError(zCat("could not subscribe to empty topics"));
            return false;
        }
    }

    const bool ok = handleInprocCommand("SET_SUBTREE", subtree);

    QStringList topicsTmp;
    foreach (QByteArray topic, topics) {
        topicsTmp << QString(topic);
    }
    zInfo(zCat(QString("subscription %1 to topics %2")
        .arg(ok ? "set" : "failed")
        .arg(QString(topicsTmp.join(" ")))));

    return ok;
}

bool CloneNodeApp::subscribeToAllTopics()
{
    const bool ok = handleInprocCommand("SET_SUBTREE", QList<QByteArray>()
        << zmq::zmqEncodeMessagePart<backend_cmd_t>(NodeAgentCommand::SetSubtree));

    zInfo(zCat("subscription %1 to all topics")
        .arg(ok ? "set" : "failed"));

    return ok;
}

bool CloneNodeApp::postTopic(const QByteArray &name, const QByteArray &value)
{
    const bool ok = handleInprocCommand("POST_TOPIC", QList<QByteArray>()
        << zmq::zmqEncodeMessagePart<backend_cmd_t>(NodeAgentCommand::PostTopic)
        << zmq::zmqEncodeMessagePart<QByteArray>(name)
        << zmq::zmqEncodeMessagePart<QByteArray>(value));

    if (ok)
        zDebug(zCat(QString("post topic with %1 and %2")
            .arg(!name.isEmpty() ?
                QString("name %1").arg(QString(name)) : "no name")
            .arg(!value.isEmpty() ?
                QString("value %1").arg(QString(value.toHex())) : "no value")));
    else
        zError(zCat(QString("failed to post topic with %1 and %2")
            .arg(!name.isEmpty() ?
                QString("name %1").arg(QString(name)) : "no name")
            .arg(!value.isEmpty() ?
                QString("value %1").arg(QString(value.toHex())) : "no value")));

    return ok;
}
