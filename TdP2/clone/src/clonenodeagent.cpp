#include "clonenodeagent.h"
#include "clonetopic.h"
#include "zmqhelper.h"
#include "zlogger.h"
#include "utilsclone.h"

#include <zmq.h>

#include <QStringList>

#include <functional>

using namespace logging;

#define zUuid(msg) \
    QString("%1 Clone %2 %3").arg(utils::uuid2string(_uuid)).arg(_name).arg(msg)

#define zCat(msg) \
    "clone", zUuid(msg)

#define BIND_INPROC(fun) \
    std::bind(&CloneNodeAgent::fun, this, std::placeholders::_1)


CloneNodeAgent::CloneNodeAgent(void *zmqCtx, const QUuid &uuid, QObject *parent) :
    CloneBackend("node agent", zmqCtx, uuid, parent),
    _nodeFsm(StateMachine::FsmIdle), _sequence(0)
{
    // TODO: log network activity with a rate-limited behaviour
}

QList<QByteArray> CloneNodeAgent::handleInprocCommands(const QList<QByteArray> &request)
{
    const NodeAgentCommand cmd = NodeAgentCommand(
        zmq::zmqDecodeMessagePart<backend_cmd_t>(request.at(0)));

    switch (cmd) {
    case NodeAgentCommand::Connect:
        return handleInprocCommand("CONNECT", BIND_INPROC(handleInprocConnect),
            request);

    case NodeAgentCommand::Disconnect:
        return handleInprocCommand("DISCONNECT", BIND_INPROC(handleInprocDisconnect),
            request);

    case NodeAgentCommand::SetSubtree:
        return handleInprocCommand("SET_SUBTREE", BIND_INPROC(handleInprocSetSubtree),
            request);

    case NodeAgentCommand::PostTopic:
        return handleInprocCommand("POST_TOPIC", BIND_INPROC(handleInprocPostTopic),
            request);

    default:
        return CloneBackend::handleInprocCommands(request);
    };
}

QList<QByteArray> CloneNodeAgent::handleInprocConnect(const QList<QByteArray> &request)
{
    // check lenght of request
    if (request.size() != 4) {
        return QList<QByteArray>()
            << zmq::zmqEncodeMessagePart<backend_ret_t>(false);
    }

    _epSnapshot = zmq::zmqDecodeMessagePart<QByteArray>(request.at(1));
    _epUpdate = zmq::zmqDecodeMessagePart<QByteArray>(request.at(2));
    _epCollector = zmq::zmqDecodeMessagePart<QByteArray>(request.at(3));

    return QList<QByteArray>()
        << zmq::zmqEncodeMessagePart<backend_ret_t>(connectNode());
}

QList<QByteArray> CloneNodeAgent::handleInprocDisconnect(const QList<QByteArray> &request)
{
    Q_UNUSED(request);

    return QList<QByteArray>()
        << zmq::zmqEncodeMessagePart<backend_ret_t>(disconnectNode());
}

QList<QByteArray> CloneNodeAgent::handleInprocSetSubtree(const QList<QByteArray> &request)
{
    _subtrees.clear();
    for (int i = 1; i < request.size(); ++i)
        _subtrees.append(zmq::zmqDecodeMessagePart<QByteArray>(request.at(i)));

    return QList<QByteArray>()
        << zmq::zmqEncodeMessagePart<backend_ret_t>(true);
}

QList<QByteArray> CloneNodeAgent::handleInprocPostTopic(const QList<QByteArray> &request)
{
    if (request.size() != 3) {
        return QList<QByteArray>()
            << zmq::zmqEncodeMessagePart<backend_ret_t>(false);
    }

    const QByteArray topic = zmq::zmqDecodeMessagePart<QByteArray>(request.at(1));
    const QByteArray value = zmq::zmqDecodeMessagePart<QByteArray>(request.at(2));

    return QList<QByteArray>()
        << zmq::zmqEncodeMessagePart<backend_ret_t>(postTopic(topic, value));
}

bool CloneNodeAgent::connectNode()
{
    if (openSockets() && subscribeNode()) {
        zInfo(zCat(QString("connection succeeded to %1")
            .arg((QStringList() << _epSnapshot << _epUpdate << _epCollector)
                .join(" "))));

        resetStateMachine();
        emit nodeConnected();
        return true;

    } else {
        zError(zCat(QString("connection failed to %1")
            .arg((QStringList() << _epSnapshot << _epUpdate << _epCollector)
                .join(" "))));

        disconnectNode();
        return false;
    }
}

bool CloneNodeAgent::openSockets()
{
    bool succ = true;

    if (!createCommSocket(_socketSnapshot, ZMQ_DEALER, zmq::zmqConnectSocket,
            QList<QString>() << _epSnapshot, "snapshot")) {

        emit connectionError(_epSnapshot);
        succ = false;
    }

    if (!createCommSocket(_socketUpdate, ZMQ_SUB, zmq::zmqConnectSocket,
            QList<QString>() << _epUpdate, "update")) {

        emit connectionError(_epUpdate);
        succ = false;
    }

    if (!createCommSocket(_socketCollector, ZMQ_PUSH, zmq::zmqConnectSocket,
            QList<QString>() << _epCollector, "collector")) {

        emit connectionError(_epCollector);
        succ = false;
    }

    return succ;
}

bool CloneNodeAgent::disconnectNode()
{
    haltStateMachine();

    if (closeSockets()) {
        emit nodeDisconnected();
        return true;
    } else {
        zWarning(zCat("sockets could not be properly closed"));
        return false;
    }
}

bool CloneNodeAgent::closeSockets()
{
    return true
        && deleteCommSocket(_socketSnapshot, "snapshot")
        && deleteCommSocket(_socketUpdate, "update")
        && deleteCommSocket(_socketCollector, "collector");
}

bool CloneNodeAgent::subscribeNode()
{
    if (!_socketUpdate) {
        zError(zCat("could not subscribe on a null socket"));
        return false;
    }

    // Subscribe to heartbeat messages
    if (!zmq::zmqSubscribeSocket(_socketUpdate, "HUGZ")) {
        zError(zCat("could not subscribe to HUGZ heartbeat messages"));
        return false;
    }

    bool succ = true;

    if (!_subtrees.isEmpty()) {
        foreach (const QByteArray &subtree, _subtrees) {
            if (!zmq::zmqSubscribeSocket(_socketUpdate, subtree)) {
                zError(zCat(QString("could not subscribe to topic %1")
                    .arg(QString(subtree))));
                emit subscriptionError(subtree);
                succ = false;
            }
        }
    } else {
        if (!zmq::zmqSubscribeSocket(_socketUpdate, "")) {
            zError(zCat("could not subscribe to any topic"));
            emit subscriptionError(QString());
            succ = false;
        }
    }

    if (succ) {
        QStringList subtreesTmp;
        foreach (QByteArray subtree, _subtrees) {
            subtreesTmp << QString(subtree);
        }
        zInfo(zCat(QString("subscription succeeded to %1")
            .arg(!_subtrees.isEmpty() ? QString(subtreesTmp.join(" ")) : "everything")));
    }
    else
        emit connectionError(_epUpdate);

    return succ;
}

bool CloneNodeAgent::postTopic(const QByteArray &topic, const QByteArray &value, bool enableFilterOutTopic)
{
    if (!isConnected()) {
        zError(zCat(QString("topic %1 not posted since the node is not connected")
            .arg(QString(topic))));
        return false;
    }

    if (topic.isEmpty()) {
        zError(zCat("could not post an empty topic name"));
        return false;
    }

    if (enableFilterOutTopic && filterOutTopic(topic)) {
        zError(zCat(QString("topic %1 not posted since "
            "it doesn't match any configured filter")
            .arg(QString(topic))));
        return false;
    }

    QList<QByteArray> kvset;
    kvset.append(zmq::zmqEncodeMessagePart<QByteArray>("KVSET"));
    kvset.append(zmq::zmqEncodeMessagePart<quint64>(_sequence));
    kvset.append(zmq::zmqEncodeMessagePart<QUuid>(_uuid));
    kvset.append(zmq::zmqEncodeMessagePart<QByteArray>(topic));
    kvset.append(zmq::zmqEncodeMessagePart<QByteArray>(value));
    // TODO: add one or more properties
    kvset.append(zmq::zmqEncodeMessagePart<QByteArray>(QByteArray()));

    if (zmq::zmqSendMessage(_socketCollector, kvset)) {
        zDebug(zCat(QString("topic %1 posted: %2")
            .arg(QString(topic))
            .arg(QString(zmq::zmqMessageToHex(kvset)))));
        return true;
    } else {
        // TODO: rate limited print
        zError(zCat(QString("could not post topic %1 with value %2")
            .arg(QString(topic).arg(QString(value.toHex())))));
        closeSockets();
        return false;
    }
}

bool CloneNodeAgent::filterOutTopic(const QByteArray &topic) const
{
    if (!_subtrees.isEmpty()) {
        foreach (const QByteArray &st, _subtrees) {
            if (topic.indexOf(st) == 0)
                return false;
        }
        return true;

    } else {
        return false;
    }
}

bool CloneNodeAgent::isConnected() const
{
    return _socketCollector && _socketUpdate && _socketCollector;
}

bool CloneNodeAgent::isFsmActive() const
{
    return _nodeFsm != StateMachine::FsmIdle;
}

void CloneNodeAgent::doBackendStep()
{
    // Run the state machine.
    doFsmStep();

    // Check for connection timeouts
    // TODO: make comm timeout configurable
    if (isFsmActive() && _commTimeout.elapsed() > 5000) {
        zWarning(zCat("connection timeout has expired!"));
        emit connectionTimeout();
        connectNode();
    }
}

void CloneNodeAgent::doFsmStep()
{
    // Check common preconditions
    assert_msg(!isFsmActive() || isConnected(),
        qPrintable(QString("%1 is accessing disconnected sockets").arg(_name)));

    // Run the state machine
    switch (_nodeFsm) {
    case StateMachine::FsmRequestSnapshot:
        doFsmRequestSnapshot();
        break;

    case StateMachine::FsmPullSnapshot:
        doFsmPullSnapshot();
        break;

    case StateMachine::FsmWaitForHugs:
        doFsmWaitForHugz();
        break;

    case StateMachine::FsmListenUpdates:
        doFsmListenUpdates();
        break;

    case StateMachine::FsmIdle:
        // Do nothing
        break;
    };
}

void CloneNodeAgent::resetStateMachine()
{
    zInfo(zCat("connection reset"));
    _commTimeout.start();
    _hugzSync.invalidate();
    _nodeFsm = StateMachine::FsmRequestSnapshot;
}

void CloneNodeAgent::haltStateMachine()
{
    if (isFsmActive()) {
        zInfo(zCat("connection halt"));
        _nodeFsm = StateMachine::FsmIdle;
    }
}

void CloneNodeAgent::doFsmRequestSnapshot()
{
    zInfo(zCat("snapshot remote sync request"));

    QList<QByteArray> snapsync;

    snapsync.append(zmq::zmqEncodeMessagePart<QByteArray>("SNAPSYNC?"));
    snapsync.append(zmq::zmqEncodeMessagePart<QUuid>(_uuid));
    snapsync.append(zmq::zmqEncodeMessagePart<quint64>(_sequence));

    foreach (const QByteArray topic, _subtrees)
        snapsync.append(zmq::zmqEncodeMessagePart<QByteArray>(topic));

    if (zmq::zmqSendMessage(_socketSnapshot, snapsync)) {
        zInfo(zCat("snapshot remote sync pull"));
        _nodeFsm = StateMachine::FsmPullSnapshot;
    } else {
        zError(zCat("could not send snapshot sync request"));
        closeSockets();
    }
}

void CloneNodeAgent::doFsmPullSnapshot()
{
    if (!isSocketReadable(_socketSnapshot))
        return;

    const QList<QByteArray> reply = zmq::zmqRecvMessage(_socketSnapshot);
    bool succ = false;

    if (!reply.isEmpty()) {
        QByteArray snaprep = zmq::zmqDecodeMessagePart<QByteArray>(reply.at(0));

        if (snaprep == "KVSYNC") {
            succ = parseKvsyncReply(reply);
        } else if (snaprep == "SNAPSYNC!") {
            if (parseSnapsyncReply(reply)) {
                zInfo(zCat("listen for any updates"));
                _nodeFsm = StateMachine::FsmWaitForHugs;
                succ = true;
            }
        } else {
            zError(zCat(QString("snapshot reply discarded since it was not recognized: %1")
                .arg(QString(zmq::zmqMessageToHex(reply)))));
        }
    } else {
        zError(zCat("snapshot reply discarded since it's empty"));
    }

    if (succ)
        _commTimeout.start();
    else
        closeSockets();
}

bool CloneNodeAgent::parseKvsyncReply(const QList<QByteArray> &reply)
{
    if (reply.size() != 6) {
        zError(zCat(QString("snapshot reply %1 discarded since its format is invalid: %2")
            .arg(QString(reply.at(0)))
            .arg(QString(zmq::zmqMessageToHex(reply)))));
        return false;
    }

    QList<QByteArray> kvsync = reply.mid(1);

    CloneTopic t;
    t.name = zmq::zmqDecodeMessagePart<QByteArray>(kvsync.takeFirst());
    t.seqn = zmq::zmqDecodeMessagePart<quint64>(kvsync.takeFirst());
    t.uuid = zmq::zmqDecodeMessagePart<QUuid>(kvsync.takeFirst());
    t.props = zmq::zmqDecodeMessagePart<QByteArray>(kvsync.takeFirst());
    t.value = zmq::zmqDecodeMessagePart<QByteArray>(kvsync.takeFirst());

    if (t.name.isEmpty()) {
        zError(zCat(QString("topic sync discarded since its name is empty: %1")
            .arg(QString(zmq::zmqMessageToHex(reply)))));
        return false;
    }

    if (t.uuid.isNull()) {
        zError(zCat(QString("topic sync discarded since its uuid is invalid: %1")
            .arg(QString(zmq::zmqMessageToHex(reply)))));
        return false;
    }

    // take the topic
    acceptTopic(t);

    return true;
}

bool CloneNodeAgent::parseSnapsyncReply(const QList<QByteArray> &reply)
{
    if (reply.size() < 3) {
        zError(zCat(QString("snapshot reply %1 discarded since its format is invalid: %2")
            .arg(QString(reply.at(0)))
            .arg(QString(zmq::zmqMessageToHex(reply)))));
        return false;
    }

    const QUuid uuid = zmq::zmqDecodeMessagePart<QUuid>(reply.at(1));
    _sequence = zmq::zmqDecodeMessagePart<quint64>(reply.at(2));

    zInfo(zCat(QString("snapshot sync completed with broker %1 at seqn %2")
        .arg(utils::uuid2string(uuid)).arg(_sequence)));

    emit snapshotSynced(uuid);

    return true;
}

void CloneNodeAgent::doFsmWaitForHugz()
{
    CloneTopic t;
    if (receiveTopic(&t)) {
        zDebug(zCat("connection ready"));
        _nodeFsm = StateMachine::FsmListenUpdates;
        emit connectionReady();
        acceptTopic(t);
    } else {
        // TODO: make hugz sync timeout configurable
        if (!_hugzSync.isValid() || _hugzSync.elapsed() > 500) {
            _hugzSync.start();
            if (!sendHugzSync()) {
                zError(zCat("could not send hugz sync request"));
                closeSockets();
            }
        }
    }
}

void CloneNodeAgent::doFsmListenUpdates()
{
    CloneTopic t;
    if (receiveTopic(&t))
        acceptTopic(t);
}

bool CloneNodeAgent::receiveTopic(CloneTopic *t)
{
    if (!isSocketReadable(_socketUpdate))
        return false;

    const QList<QByteArray> update = zmq::zmqRecvMessage(_socketUpdate);
    if (update.isEmpty()) {
        zError(zCat("topic update discarded since it's empty"));
        return false;
    }

    QList<QByteArray> kvpub = update;
    if (update.size() != 6) {
        zError(zCat(QString("topic update discarded since its format is invalid: %1")
            .arg(QString(zmq::zmqMessageToHex(update)))));
        return false;
    }

    const QByteArray cmd = zmq::zmqDecodeMessagePart<QByteArray>(kvpub.takeAt(1));
    if (cmd != "KVPUB") {
        zError(zCat(QString("topic update discarded since KVPUB was expected: %1")
            .arg(QString(zmq::zmqMessageToHex(update)))));
        return false;
    }

    Q_ASSERT_X(t, "CloneNodeAgent::receiveTopic", "topic pointer is null");

    t->name = zmq::zmqDecodeMessagePart<QByteArray>(kvpub.takeFirst());
    t->seqn = zmq::zmqDecodeMessagePart<quint64>(kvpub.takeFirst());
    t->uuid = zmq::zmqDecodeMessagePart<QUuid>(kvpub.takeFirst());
    t->props = zmq::zmqDecodeMessagePart<QByteArray>(kvpub.takeFirst());
    t->value = zmq::zmqDecodeMessagePart<QByteArray>(kvpub.takeFirst());

    if (t->name.isEmpty()) {
        zError(zCat(QString("topic update discarded since its name is empty: %1")
            .arg(QString(zmq::zmqMessageToHex(update)))));
        return false;
    }

    if (t->uuid.isNull()) {
        zError(zCat(QString("topic update discarded since its uuid is invalid: %1")
            .arg(QString(zmq::zmqMessageToHex(update)))));
        return false;
    }

    // Reset the connection timer.
    _commTimeout.start();

    return true;
}

bool CloneNodeAgent::sendHugzSync()
{
    QList<QByteArray> hugzsync;

    hugzsync.append(zmq::zmqEncodeMessagePart<QByteArray>("HUGZSYNC?"));
    hugzsync.append(zmq::zmqEncodeMessagePart<QUuid>(_uuid));

    return zmq::zmqSendMessage(_socketSnapshot, hugzsync);
}

bool CloneNodeAgent::acceptTopic(const CloneTopic &t)
{
    if (t.seqn <= _sequence) {
        zDebug(zCat(QString("topic update %1 discarded since "
            "its seqn %2 is not strictly greater than current seqn %3")
            .arg(QString(t.name)).arg(t.seqn).arg(_sequence)));

        return false;
    }

    // Update the sequence number
    _sequence = t.seqn;

    zDebug(zCat(QString("topic update w/ %1")
        .arg(t.toString())));

    emit topicUpdated(t.name, t.value, t.uuid);

    return true;
}
