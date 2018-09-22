#include "clonebrokeragent.h"
#include "zmqhelper.h"

#include "zlogger.h"
#include "utilsclone.h"

#include <zmq.h>
#include <algorithm>

#include <QStringList>

using namespace logging;

#define zUuid(msg) \
    QString("%1 Clone %2 %3").arg(utils::uuid2string(_uuid)).arg(_name).arg(msg)

#define zCat(msg) \
    "clone", zUuid(msg)

#define BIND_INPROC(fun) \
    std::bind(&CloneBrokerAgent::fun, this, std::placeholders::_1)


CloneBrokerAgent::CloneBrokerAgent(void *zmqCtx, const QUuid &uuid, QObject *parent) :
    CloneBackend("broker agent", zmqCtx, uuid, parent),
    _sequence(0)
{
}

QList<QByteArray> CloneBrokerAgent::handleInprocCommands(const QList<QByteArray> &request)
{
    const BrokerAgentCommand cmd = BrokerAgentCommand(
        zmq::zmqDecodeMessagePart<backend_cmd_t>(request.at(0)));

    switch (cmd) {
    case BrokerAgentCommand::Bind:
        return handleInprocCommand("BIND", BIND_INPROC(handleInprocBind),
            request);

    case BrokerAgentCommand::Unbind:
        return handleInprocCommand("UNBIND", BIND_INPROC(handleInprocUnbind),
            request);

    default:
        return CloneBackend::handleInprocCommands(request);
    };
}

QList<QByteArray> CloneBrokerAgent::handleInprocBind(const QList<QByteArray> &request)
{
    /**
     * The command format must be as follow:
     * <[BIND] [SNAP1] .. [SNAPN] [] [UPD1] .. [UPDN] [] [COLL1] .. [COLLN]>
     */
    QList<QByteArray> parts = request.mid(1);
    QList<QString> snapshot, update, collector;
    foreach (QList<QString> *list, QList<QList<QString> *>()
        << &snapshot << &update << &collector)
    {
        while (!parts.isEmpty()) {
            const QByteArray endpoint = parts.takeFirst();
            if (!endpoint.isEmpty())
                list->append(endpoint);
            else
                break;
        }
    }

    auto bindfn = std::bind(zmq::zmqBindSocketTryReuseaddr,
        std::placeholders::_1, std::placeholders::_2, 1000);

    if (createCommSocket(_socketSnapshot, ZMQ_ROUTER, bindfn, snapshot, "snapshot") &&
        createCommSocket(_socketUpdate, ZMQ_PUB, bindfn, update, "update") &&
        createCommSocket(_socketCollector, ZMQ_PULL, bindfn, collector, "collector"))
    {
        return QList<QByteArray>()
            << zmq::zmqEncodeMessagePart<backend_ret_t>(true);
    } else {
        return QList<QByteArray>()
            << zmq::zmqEncodeMessagePart<backend_ret_t>(false);
    }
}

QList<QByteArray> CloneBrokerAgent::handleInprocUnbind(const QList<QByteArray> &request)
{
    Q_UNUSED(request);

    const bool succ = deleteCommSocket(_socketSnapshot, "snapshot") &&
        deleteCommSocket(_socketUpdate, "update") &&
        deleteCommSocket(_socketCollector, "collector");

    return QList<QByteArray>()
        << zmq::zmqEncodeMessagePart<backend_ret_t>(succ);
}

bool CloneBrokerAgent::isBound() const
{
    return _socketSnapshot && _socketUpdate && _socketCollector;
}

void CloneBrokerAgent::doBackendStep()
{
    if (!isBound())
        return;

    if (isSocketReadable(_socketSnapshot))
        handleSnapshotRequest();

    if (isSocketReadable(_socketCollector))
        publishTopic(storeTopic());

    // TODO: make hugz timeout configurable
    if (!_hugzTimeout.isValid() || _hugzTimeout.elapsed() > 2000) {
        _hugzTimeout.start();
        publishTopic(makeHugzTopic());
    }
}

void CloneBrokerAgent::handleSnapshotRequest()
{
    QList<QByteArray> request = zmq::zmqRecvMessage(_socketSnapshot);
    assert_msg(!request.isEmpty(), qPrintable(QString("ZMQ %1 snapshot request is null")
        .arg(_name)));

    const QByteArray identity = request.takeFirst();
    if (request.isEmpty()) {
        zError(zCat("snapshot request discarded since it's empty"));
        return;
    }

    const QByteArray snapreq = zmq::zmqDecodeMessagePart<QByteArray>(request.at(0));

    if (snapreq == "SNAPSYNC?") {
        replyToSnapshotSync(identity, request);
    } else if (snapreq == "HUGZSYNC?") {
        replyToHugzSync(identity, request);
    } else {
        zError(zCat(QString("snapshot request discarded since "
            "SNAPSYNC? or HUGZSYN? was expected: %1")
            .arg(QString(zmq::zmqMessageToHex(request)))));
    }
}

void CloneBrokerAgent::replyToSnapshotSync(const QByteArray &identity, const QList<QByteArray> &request)
{
    if (request.size() < 3) {
        zError(zCat(QString("snapshot sync request discarded since its format is invalid: %1")
            .arg(QString(zmq::zmqMessageToHex(request)))));
        return;
    }

    const QUuid uuid = zmq::zmqDecodeMessagePart<QUuid>(request.at(1));
    const quint64 seqn = zmq::zmqDecodeMessagePart<quint64>(request.at(2));

    zDebug(zCat(QString("snapshot sync request %1")
        .arg(QString(zmq::zmqMessageToHex(request)))));

    QList<QByteArray> topics;
    for (int i = 3; i < request.size(); ++i)
        topics.append(zmq::zmqDecodeMessagePart<QByteArray>(request.at(i)));

    // send state
    if (!replyWithSnapshotTopics(identity, topics, seqn))
        return;

    QList<QByteArray> reply;
    reply.append(zmq::zmqEncodeMessagePart<QByteArray>("SNAPSYNC!"));
    reply.append(zmq::zmqEncodeMessagePart<QUuid>(_uuid));
    reply.append(zmq::zmqEncodeMessagePart<quint64>(_sequence));

    if (zmq::zmqSendMessage(_socketSnapshot, QList<QByteArray>() << identity << reply))
        zDebug(zCat(QString("snapshot sync reply sent: %1")
            .arg(QString(zmq::zmqMessageToHex(reply)))));
    else
        zError(zCat(QString("could not send snapshot sync reply: %1")
            .arg(QString(zmq::zmqMessageToHex(reply)))));

    emit snapshotSynced(uuid);
}

bool CloneBrokerAgent::replyWithSnapshotTopics(const QByteArray &identity, const QList<QByteArray> topics, quint64 sequence) const
{
    QStringList topicsTmp;
    foreach(QByteArray topic, topics) {
        topicsTmp << QString("topic");
    }

    zInfo(zCat(QString("snapshot sync of %1 with sequence higher than %2")
        .arg(topics.isEmpty() ? "any topic" : QString("topics %1")
            .arg(QString(topicsTmp.join(" "))))
        .arg(sequence)));

    // order items
    QList<const CloneTopic *> ordlist;
    for (auto i = _store.constBegin(); i != _store.constEnd(); ++i) {
        const CloneTopic &item = i.value();

        if (item.seqn <= sequence)
            continue;

        if (filterOutTopic(item.name, topics))
            continue;

        ordlist.insert(std::lower_bound(ordlist.begin(), ordlist.end(), &i.value(),
            [](const CloneTopic *t1, const CloneTopic *t2) {
                return t1->seqn < t2->seqn;
            }), &i.value());
    }

    // send items
    foreach (const CloneTopic *t, ordlist) {
        const QList<QByteArray> kvsync = QList<QByteArray>()
            << zmq::zmqEncodeMessagePart<QByteArray>("KVSYNC")
            << zmq::zmqEncodeMessagePart<QByteArray>(t->name)
            << zmq::zmqEncodeMessagePart<quint64>(t->seqn)
            << zmq::zmqEncodeMessagePart<QUuid>(t->uuid)
            << zmq::zmqEncodeMessagePart<QByteArray>(t->props)
            << zmq::zmqEncodeMessagePart<QByteArray>(t->value);

        if (zmq::zmqSendMessage(_socketSnapshot, QList<QByteArray>() << identity << kvsync)) {
            zDebug(zCat(QString("topic synced w/ %1")
                .arg(t->toString())));
        } else {
            zError(zCat(QString("could not sync topic w/ %1")
                .arg(t->toString())));
            return false;
        }
    }

    return true;
}

void CloneBrokerAgent::replyToHugzSync(const QByteArray &identity, const QList<QByteArray> &request)
{
    Q_UNUSED(identity);
    Q_UNUSED(request);

    _hugzTimeout.invalidate();
}

CloneTopic CloneBrokerAgent::storeTopic()
{
    const QList<QByteArray> request = zmq::zmqRecvMessage(_socketCollector);
    if (request.isEmpty()) {
        zError(zCat("topic update discarded since it's empty"));
        return CloneTopic();
    }

    QList<QByteArray> kvset = request;
    if (kvset.size() != 6) {
        zError(zCat(QString("topic update discarded since its format is invalid: %1")
            .arg(QString(zmq::zmqMessageToHex(request)))));
        return CloneTopic();
    }

    const QByteArray cmd = zmq::zmqDecodeMessagePart<QByteArray>(kvset.takeFirst());
    if (cmd != "KVSET") {
        zError(zCat(QString("topic update discarded since KVSET was expected: %1")
            .arg(QString(zmq::zmqMessageToHex(request)))));
        return CloneTopic();
    }

    CloneTopic t;
    t.seqn = zmq::zmqDecodeMessagePart<quint64>(kvset.takeFirst());
    t.uuid = zmq::zmqDecodeMessagePart<QUuid>(kvset.takeFirst());
    t.name = zmq::zmqDecodeMessagePart<QByteArray>(kvset.takeFirst());
    t.value = zmq::zmqDecodeMessagePart<QByteArray>(kvset.takeFirst());
    t.props = zmq::zmqDecodeMessagePart<QByteArray>(kvset.takeFirst());

    if (t.name.isEmpty()) {
        zError(zCat(QString("topic update discarded since its name is empty: %1")
            .arg(QString(zmq::zmqMessageToHex(request)))));
        return CloneTopic();
    }

    if (t.uuid.isNull()) {
        zError(zCat(QString("topic update discarded since its uuid is invalid: %1")
            .arg(QString(zmq::zmqMessageToHex(request)))));
        return CloneTopic();
    }

    // Increment sequence number
    t.seqn = ++_sequence;

    if (t.name.startsWith("/state")) {
        _store.insert(t.name, t);

        zDebug(zCat(QString("topic update stored w/ %1")
            .arg(t.toString())));
    }

    return t;
}

CloneTopic CloneBrokerAgent::makeHugzTopic() const
{
    CloneTopic t;
    t.uuid = _uuid;
    t.name = "HUGZ";

    return t;
}

void CloneBrokerAgent::publishTopic(const CloneTopic &t)
{
    if (t.isNull()) {
        zError(zCat("topic update not published since it's invalid"));
        return;
    }

    if (!_socketUpdate) {
        zError(zCat("topic update not published since ZMQ socket is not bound"));
        return;
    }

    const QList<QByteArray> kvpub = QList<QByteArray>()
        << zmq::zmqEncodeMessagePart<QByteArray>(t.name)
        << zmq::zmqEncodeMessagePart<QByteArray>("KVPUB")
        << zmq::zmqEncodeMessagePart<quint64>(t.seqn)
        << zmq::zmqEncodeMessagePart<QUuid>(t.uuid)
        << zmq::zmqEncodeMessagePart<QByteArray>(t.props)
        << zmq::zmqEncodeMessagePart<QByteArray>(t.value);

    if (zmq::zmqSendMessage(_socketUpdate, kvpub))
        zDebug(zCat(QString("topic update published w/ %1")
            .arg(t.toString())));
    else
        // TODO: rate limited print
        zError(zCat(QString("could not publish topic w/ %1")
            .arg(t.toString())));
}

bool CloneBrokerAgent::filterOutTopic(const QByteArray &topic, const QList<QByteArray> &filters) const
{
    if (!filters.isEmpty()) {
        foreach (const QByteArray &st, filters) {
            if (topic.indexOf(st) == 0)
                return false;
        }
        return true;

    } else {
        return false;
    }
}
