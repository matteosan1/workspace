#include "clonetestsuite.h"
#include "clonebrokerapp.h"
#include "clonenodeapp.h"
#include "zmqhelper.h"
#include "zlogger.h"
#include "common/testutils.h"

#include <QCoreApplication>
#include <QtTest/QtTest>
#include <QThread>
#include <QMetaObject>
#include <QSignalSpy>
#include <QElapsedTimer>
#include <QUuid>

#define SOCK_SNAP_ADDR  "ipc:///tmp/_sock_clone_snap"
#define SOCK_UPDT_ADDR  "ipc:///tmp/_sock_clone_updt"
#define SOCK_COLL_ADDR  "ipc:///tmp/_sock_clone_coll"

using namespace test::utils;
using namespace logging;

Q_DECLARE_METATYPE(QList<QString>)
Q_DECLARE_METATYPE(QList<QByteArray>)
Q_DECLARE_METATYPE(QUuid)

void CloneTestSuite::deleteObjects(QList<QObject *> objects, int timeoutMsec)
{
    zInfo(QString("Deleting %1 objects...")
        .arg(objects.size()));

    foreach (QObject *o, objects) {
        zDebug("Deleting object...");
        delete o;
        zDebug("Object deleted!");
    }

    zInfo("Objects deleted!");
}

void CloneTestSuite::initTestCase()
{
    zInfo("TEST SUITE BEGIN");

    qRegisterMetaType<QList<QString> >();
    qRegisterMetaType<QList<QByteArray> >();
    qRegisterMetaType<QUuid>();

    QUuid uuid = QUuid::createUuid();
    QVariant var;
    var.setValue(uuid);
    QUuid uuid2 = var.value<QUuid>();
    if (uuid != uuid2)
    {
        qDebug() << "ERROR !!!";
    }
}

void CloneTestSuite::cleanupTestCase()
{
    zInfo("TEST SUITE END");
}

void CloneTestSuite::init()
{
    zInfo(QString("TEST CASE BEGIN: %1 %2")
        .arg(QTest::currentTestFunction())
        .arg(QTest::currentDataTag()));
}

void CloneTestSuite::cleanup()
{
    if (!QTest::currentTestFailed())
        zInfo(QString("TEST CASE END: %1 %2 (SUCCESS)")
            .arg(QTest::currentTestFunction())
            .arg(QTest::currentDataTag()));
    else
        zFatal(QString("TEST CASE END: %1 %2 (FAIL)")
            .arg(QTest::currentTestFunction())
            .arg(QTest::currentDataTag()));
}

void CloneTestSuite::testNodeSimpleStart_data()
{
    QTest::addColumn<int>("n_nodes");

    QTest::newRow("One node creation") << 1;
    QTest::newRow("Two nodes creation") << 2;
    QTest::newRow("Four nodes creation") << 4;
}

void CloneTestSuite::testNodeSimpleStart()
{
    QFETCH(int, n_nodes);

    QList<QObject *> obj;
    for (int i = 0; i < n_nodes; ++i)
        obj.append(CloneNodeApp::createNode());

    deleteObjects(obj);
}

void CloneTestSuite::testNodeConnectionTimeout()
{
    CloneNodeApp *node = CloneNodeApp::createNode();

    bool test_ret = node->connectNode(SOCK_SNAP_ADDR, SOCK_UPDT_ADDR, SOCK_COLL_ADDR);
    QCOMPARE(test_ret, true);

    // TODO: perform test with different timeouts
    QVERIFY(waitForSignal(node, SIGNAL(connectionTimeout()), 5500));

    deleteObjects(QList<QObject *>() << node);
}

void CloneTestSuite::testNodeConnectionHeartbeat()
{
    CloneNodeApp *node = CloneNodeApp::createNode();
    CloneBrokerApp *broker = CloneBrokerApp::createBroker();

    QVERIFY(node->connectNode(SOCK_SNAP_ADDR, SOCK_UPDT_ADDR, SOCK_COLL_ADDR));
    QVERIFY(broker->bindBroker({SOCK_SNAP_ADDR}, {SOCK_UPDT_ADDR}, {SOCK_COLL_ADDR}));

    // TODO: perform test with different timeouts
    QTest::qSleep(5500);

    QVERIFY(waitForSignal(node, SIGNAL(connectionTimeout()), 1, 0));

    deleteObjects(QList<QObject *>() << node << broker);
}

void CloneTestSuite::testNodeConnectionHeartbeatWithTopics()
{
    CloneNodeApp *node1 = CloneNodeApp::createNode();
    CloneNodeApp *node2 = CloneNodeApp::createNode();
    CloneBrokerApp *broker = CloneBrokerApp::createBroker();

    // TODO: perform tests with different timeouts
    const int timeout = 5500;

    QVERIFY(node1->subscribeToSpecificTopics({"/topic1"}));
    QVERIFY(node1->connectNode(SOCK_SNAP_ADDR, SOCK_UPDT_ADDR, SOCK_COLL_ADDR));
    QVERIFY(node2->subscribeToSpecificTopics({"/topic2"}));
    QVERIFY(node2->connectNode(SOCK_SNAP_ADDR, SOCK_UPDT_ADDR, SOCK_COLL_ADDR));
    QVERIFY(broker->bindBroker({SOCK_SNAP_ADDR}, {SOCK_UPDT_ADDR}, {SOCK_COLL_ADDR}));

    QElapsedTimer t;
    t.start();

    while (t.elapsed() < timeout) {
        QTest::qSleep(1000);
        QVERIFY(node1->postTopic("/topic1", QByteArray::fromHex("aa")));
    }

    QVERIFY(waitForSignal(node2, SIGNAL(connectionTimeout()), 1, 0));

    deleteObjects({node1, node2, broker});
}

void CloneTestSuite::testNodeConnectNoMaster_data()
{
    QTest::addColumn<QString>("snapshot");
    QTest::addColumn<QString>("update");
    QTest::addColumn<QString>("collector");
    QTest::addColumn<int>("wait_ms");
    QTest::addColumn<QList<QString>>("errlist");
    QTest::addColumn<bool>("success");

    QTest::newRow("Connect three empty endpoints")
        << "" << "" << ""
        << 1 << (QList<QString>() << "" << "" << "")
        << false;
    QTest::newRow("Connect two empty endpoints")
        << "tcp://127.0.0.1:35121" << "" << ""
        << 1 << (QList<QString>() << "" << "")
        << false;
    QTest::newRow("Connect one empty endpoint")
        << "tcp://127.0.0.1:35121" << "tcp://127.0.0.1:35122" << ""
        << 1 << (QList<QString>() << "")
        << false;
    QTest::newRow("Connect one invalid endpoint")
        << "xxx://" << "" << ""
        << 1 << (QList<QString>() << "xxx://" << "" << "")
        << false;
    QTest::newRow("Connect two invalid endpoints")
        << "xxx://" << "yyy://" << ""
        << 1 << (QList<QString>() << "xxx://" << "yyy://" << "")
        << false;
    QTest::newRow("Connect three invalid endpoints")
        << "xxx://" << "yyy://" << "zzz://"
        << 1 << (QList<QString>() << "xxx://" << "yyy://" << "zzz://")
        << false;
    QTest::newRow("Connect to all valid endpoints")
        << "tcp://127.0.0.1:35121" << "tcp://127.0.0.1:35122" << "tcp://127.0.0.1:35123"
        << 1 << QList<QString>()
        << true;
    QTest::newRow("Connect to all valid endpoints (no reconnection)")
        << "tcp://127.0.0.1:35121" << "tcp://127.0.0.1:35122" << "tcp://127.0.0.1:35123"
        << 5500 << QList<QString>()
        << true;
    QTest::newRow("Connect one invalid endpoint (no reconnection)")
        << "xxx://" << "" << ""
        << 5500 << (QList<QString>() << "xxx://" << "" << "")
        << false;
}

void CloneTestSuite::testNodeConnectNoMaster()
{
    QFETCH(QString, snapshot);
    QFETCH(QString, update);
    QFETCH(QString, collector);
    QFETCH(int, wait_ms);
    QFETCH(QList<QString>, errlist);
    QFETCH(bool, success);

    QList<QList<QVariant>> errargs;
    foreach (const QString &endpoint, errlist)
        errargs.append(QList<QVariant>() << qVariantFromValue(endpoint));

    CloneNodeApp *node = CloneNodeApp::createNode();

    bool test_ret = node->connectNode(snapshot, update, collector);
    QCOMPARE(test_ret, success);

    QTest::qSleep(wait_ms);

    QVERIFY(waitForSignal(node, SIGNAL(connectionError(QString)), 1000,
        errlist.size(), errargs));

    deleteObjects(QList<QObject *>() << node);
}

void CloneTestSuite::testNodeDisconnect_data()
{
    QTest::addColumn<QString>("snapshot");
    QTest::addColumn<QString>("update");
    QTest::addColumn<QString>("collector");
    QTest::addColumn<bool>("success");

    QTest::newRow("Disconnection without connection")
        << "" << "" << ""
        << false;
    QTest::newRow("Disconnection with partial connection #1")
        << "tcp://127.0.0.1:35121" << "" << ""
        << false;
    QTest::newRow("Disconnection with partial connection #2")
        << "tcp://127.0.0.1:35121" << "tcp://127.0.0.1:35122" << ""
        << false;
    QTest::newRow("Disconnection with full connection")
        << "tcp://127.0.0.1:35121" << "tcp://127.0.0.1:35122" << "tcp://127.0.0.1:35123"
        << true;
}

void CloneTestSuite::testNodeDisconnect()
{
    QFETCH(QString, snapshot);
    QFETCH(QString, update);
    QFETCH(QString, collector);
    QFETCH(bool, success);

    CloneNodeApp *node = CloneNodeApp::createNode();

    bool conn_ok = node->connectNode(snapshot, update, collector);
    QCOMPARE(conn_ok, success);
    QVERIFY(waitForSignal(node, SIGNAL(nodeConnected()), 500, !!success));

    bool disconn_ok = node->disconnectNode();
    QCOMPARE(disconn_ok, success);
    QVERIFY(waitForSignal(node, SIGNAL(nodeDisconnected()), 500, !!success));

    deleteObjects(QList<QObject *>() << node);
}

void CloneTestSuite::testNodeConnectDisconnect()
{
    CloneNodeApp *node = CloneNodeApp::createNode();

    QVERIFY(node->connectNode(SOCK_SNAP_ADDR, SOCK_UPDT_ADDR, SOCK_COLL_ADDR));
    QVERIFY(waitForSignal(node, SIGNAL(nodeConnected()), 500));

    QVERIFY(node->disconnectNode());
    QVERIFY(waitForSignal(node, SIGNAL(nodeDisconnected()), 500));

    QVERIFY(node->connectNode(SOCK_SNAP_ADDR, SOCK_UPDT_ADDR, SOCK_COLL_ADDR));
    QVERIFY(waitForSignal(node, SIGNAL(nodeConnected()), 500));

    QVERIFY(node->disconnectNode());
    QVERIFY(waitForSignal(node, SIGNAL(nodeDisconnected()), 500));

    deleteObjects(QList<QObject *>() << node);
}

void CloneTestSuite::testBrokerSimpleStart_data()
{
    QTest::addColumn<int>("n_nodes");

    QTest::newRow("One broker creation") << 1;
}

void CloneTestSuite::testBrokerSimpleStart()
{
    QFETCH(int, n_nodes);

    QList<QObject *> obj;
    for (int i = 0; i < n_nodes; ++i)
        obj.append(CloneBrokerApp::createBroker());

    deleteObjects(obj);
}

void CloneTestSuite::testBrokerBind_data()
{
    QTest::addColumn<QList<QString>>("snapshot");
    QTest::addColumn<QList<QString>>("update");
    QTest::addColumn<QList<QString>>("collector");
    QTest::addColumn<bool>("success");

    QTest::newRow("Bind three empty endpoints")
        << QList<QString>()
        << QList<QString>()
        << QList<QString>()
        << false;
    QTest::newRow("Bind two empty endpoints")
        << (QList<QString>() << "tcp://127.0.0.1:35121")
        << QList<QString>()
        << QList<QString>()
        << false;
    QTest::newRow("Bind one empty endpoint")
        << (QList<QString>() << "tcp://127.0.0.1:35121")
        << (QList<QString>() << "tcp://127.0.0.1:35221")
        << QList<QString>()
        << false;
    QTest::newRow("Bind valid endpoints")
        << (QList<QString>() << "tcp://127.0.0.1:35121")
        << (QList<QString>() << "tcp://127.0.0.1:35221")
        << (QList<QString>() << "tcp://127.0.0.1:35321")
        << true;
    QTest::newRow("Bind two valid snapshot endpoints")
        << (QList<QString>() << "tcp://127.0.0.1:35121" << "tcp://127.0.0.1:35122")
        << (QList<QString>() << "tcp://127.0.0.1:35221")
        << (QList<QString>() << "tcp://127.0.0.1:35321")
        << true;
    QTest::newRow("Bind two valid update endpoints")
        << (QList<QString>() << "tcp://127.0.0.1:35121")
        << (QList<QString>() << "tcp://127.0.0.1:35221" << "tcp://127.0.0.1:35222")
        << (QList<QString>() << "tcp://127.0.0.1:35321")
        << true;
    QTest::newRow("Bind two valid collector endpoints")
        << (QList<QString>() << "tcp://127.0.0.1:35121")
        << (QList<QString>() << "tcp://127.0.0.1:35221")
        << (QList<QString>() << "tcp://127.0.0.1:35321" << "tcp://127.0.0.1:35322")
        << true;
    QTest::newRow("Bind three valid snapshot endpoints")
        << (QList<QString>() << "tcp://127.0.0.1:35121" << "tcp://127.0.0.1:35122" << "tcp://127.0.0.1:35123")
        << (QList<QString>() << "tcp://127.0.0.1:35221")
        << (QList<QString>() << "tcp://127.0.0.1:35321")
        << true;
    QTest::newRow("Bind three valid update endpoints")
        << (QList<QString>() << "tcp://127.0.0.1:35121")
        << (QList<QString>() << "tcp://127.0.0.1:35221" << "tcp://127.0.0.1:35222" << "tcp://127.0.0.1:35223")
        << (QList<QString>() << "tcp://127.0.0.1:35321")
        << true;
    QTest::newRow("Bind three valid collector endpoints")
        << (QList<QString>() << "tcp://127.0.0.1:35121")
        << (QList<QString>() << "tcp://127.0.0.1:35221")
        << (QList<QString>() << "tcp://127.0.0.1:35321" << "tcp://127.0.0.1:35322" << "tcp://127.0.0.1:35323")
        << true;
}

void CloneTestSuite::testBrokerBind()
{
    QFETCH(QList<QString>, snapshot);
    QFETCH(QList<QString>, update);
    QFETCH(QList<QString>, collector);
    QFETCH(bool, success);

    CloneBrokerApp *broker = CloneBrokerApp::createBroker();

    bool test_ret = broker->bindBroker(snapshot, update, collector);
    QCOMPARE(test_ret, success);

    deleteObjects(QList<QObject *>() << broker);
}

void CloneTestSuite::testBrokerUnbind_data()
{
    QTest::addColumn<QList<QString>>("snapshot");
    QTest::addColumn<QList<QString>>("update");
    QTest::addColumn<QList<QString>>("collector");
    QTest::addColumn<bool>("success");

    QTest::newRow("Disconnection without connection")
        << QList<QString>()
        << QList<QString>()
        << QList<QString>()
        << false;
    QTest::newRow("Disconnection with partial connection #1")
        << (QList<QString>() << SOCK_SNAP_ADDR)
        << QList<QString>()
        << QList<QString>()
        << false;
    QTest::newRow("Disconnection with partial connection #2")
        << (QList<QString>() << SOCK_SNAP_ADDR)
        << (QList<QString>() << SOCK_UPDT_ADDR)
        << QList<QString>()
        << false;
    QTest::newRow("Disconnection with full connection")
        << (QList<QString>() << SOCK_SNAP_ADDR)
        << (QList<QString>() << SOCK_UPDT_ADDR)
        << (QList<QString>() << SOCK_COLL_ADDR)
        << true;
}

void CloneTestSuite::testBrokerUnbind()
{
    QFETCH(QList<QString>, snapshot);
    QFETCH(QList<QString>, update);
    QFETCH(QList<QString>, collector);
    QFETCH(bool, success);

    CloneBrokerApp *broker = CloneBrokerApp::createBroker();

    broker->bindBroker(snapshot, update, collector);

    bool test_ret = broker->unbindBroker();
    QCOMPARE(test_ret, success);

    deleteObjects(QList<QObject *>() << broker);
}

void CloneTestSuite::testBrokerBindUnbind()
{
    CloneBrokerApp *broker = CloneBrokerApp::createBroker();

    QVERIFY(broker->bindBroker({SOCK_SNAP_ADDR}, {SOCK_UPDT_ADDR}, {SOCK_COLL_ADDR}));
    QVERIFY(broker->unbindBroker());
    QVERIFY(broker->bindBroker({SOCK_SNAP_ADDR}, {SOCK_UPDT_ADDR}, {SOCK_COLL_ADDR}));
    QVERIFY(broker->unbindBroker());

    deleteObjects(QList<QObject *>() << broker);
}

void CloneTestSuite::testSnapshotSyncNode_data()
{
    QTest::addColumn<int>("timeout_ms");
    QTest::addColumn<int>("num_syncs");

    QTest::newRow("No snapshot syncs") << 1000 << 0;
    QTest::newRow("Success snapshot sync") << 1000 << 1;
}

void CloneTestSuite::testSnapshotSyncNode()
{
    QFETCH(int, timeout_ms);
    QFETCH(int, num_syncs);

    CloneBrokerApp *broker = CloneBrokerApp::createBroker();
    CloneNodeApp *node = CloneNodeApp::createNode();

    if (num_syncs)
        QVERIFY(broker->bindBroker({SOCK_SNAP_ADDR}, {SOCK_UPDT_ADDR}, {SOCK_COLL_ADDR}));

    QVERIFY(node->connectNode(SOCK_SNAP_ADDR, SOCK_UPDT_ADDR, SOCK_COLL_ADDR));

    QVERIFY(waitForSignal(node, SIGNAL(snapshotSynced(QUuid)),
        timeout_ms, num_syncs));

    deleteObjects(QList<QObject *>() << broker << node);
}

void CloneTestSuite::testSnapshotSyncWithSubscriptions()
{
    CloneBrokerApp *broker = CloneBrokerApp::createBroker();
    QVERIFY(broker->bindBroker({SOCK_SNAP_ADDR}, {SOCK_UPDT_ADDR}, {SOCK_COLL_ADDR}));

    CloneNodeApp *node1 = CloneNodeApp::createNode();
    QVERIFY(node1->connectNode(SOCK_SNAP_ADDR, SOCK_UPDT_ADDR, SOCK_COLL_ADDR));
    QVERIFY(waitForSignal(node1, SIGNAL(connectionReady()), 2500));
    QVERIFY(node1->postTopic("/state/of/module/1", QByteArray::fromHex("xx")));

    CloneNodeApp *node2 = CloneNodeApp::createNode();
    QVERIFY(node2->subscribeToSpecificTopics({"/state/of/module/2"}));
    QVERIFY(node2->connectNode(SOCK_SNAP_ADDR, SOCK_UPDT_ADDR, SOCK_COLL_ADDR));

    // node2 shall not receive the state of node1 via snaphost sync
    QVERIFY(waitForSignal(node2,
        SIGNAL(topicUpdated(QByteArray, QByteArray, QUuid)), 5000, 0, {{}},
        SIGNAL(snapshotSynced(QUuid))));

    deleteObjects({broker, node1, node2});
}

void CloneTestSuite::testSnapshotSyncBroker_data()
{
    QTest::addColumn<int>("timeout_ms");
    QTest::addColumn<int>("num_syncs");

    QTest::newRow("No snapshot syncs") << 1000 << 0;
    QTest::newRow("Success snapshot sync") << 1000 << 1;
}

void CloneTestSuite::testSnapshotSyncBroker()
{
    QFETCH(int, timeout_ms);
    QFETCH(int, num_syncs);

    CloneBrokerApp *broker = CloneBrokerApp::createBroker();
    CloneNodeApp *node = CloneNodeApp::createNode();

    if (num_syncs)
        QVERIFY(broker->bindBroker({SOCK_SNAP_ADDR}, {SOCK_UPDT_ADDR}, {SOCK_COLL_ADDR}));

    QVERIFY(node->connectNode(SOCK_SNAP_ADDR, SOCK_UPDT_ADDR, SOCK_COLL_ADDR));

    QVERIFY(waitForSignal(broker, SIGNAL(snapshotSynced(QUuid)),
        timeout_ms, num_syncs));

    deleteObjects(QList<QObject *>() << broker << node);
}

void CloneTestSuite::testNodeSubscription_data()
{
    QTest::addColumn<QList<QByteArray>>("topics");
    QTest::addColumn<bool>("everything");
    QTest::addColumn<bool>("succ_topic");
    QTest::addColumn<bool>("succ_connect");

    QTest::newRow("Subscribe any topic")
        << QList<QByteArray>()
        << true << true << true;
    QTest::newRow("Subscribe to emtpy topics #1")
        << QList<QByteArray>()
        << false << false << true;
    QTest::newRow("Subscribe to emtpy topics #2")
        << (QList<QByteArray>() << "")
        << false << false << true;
    QTest::newRow("Subscribe to emtpy topics #3")
        << (QList<QByteArray>() << "/topic1" << "")
        << false << false << true;
    QTest::newRow("Subscribe to one valid topic")
        << (QList<QByteArray>() << "/topic1")
        << false << true << true;
    QTest::newRow("Subscribe to multiple valid topics")
        << (QList<QByteArray>() << "/topic1" << "/topic2" << "/topic3")
        << false << true << true;
    QTest::newRow("Subscribe to multiple valid topics")
        << (QList<QByteArray>() << "/topic1" << "/topic2" << "/topic3")
        << false << true << true;
    QTest::newRow("Subscribe to same valid topics")
        << (QList<QByteArray>() << "/topic1" << "/topic1" << "/topic1")
        << false << true << true;
}

void CloneTestSuite::testNodeSubscription()
{
    QFETCH(QList<QByteArray>, topics);
    QFETCH(bool, everything);
    QFETCH(bool, succ_topic);
    QFETCH(bool, succ_connect);
    bool ret_topic, ret_connect;

    CloneNodeApp *node = CloneNodeApp::createNode();

    if (!everything)
        ret_topic = node->subscribeToSpecificTopics(topics);
    else
        ret_topic = node->subscribeToAllTopics();

    QCOMPARE(ret_topic, succ_topic);

    ret_connect = node->connectNode(SOCK_SNAP_ADDR, SOCK_UPDT_ADDR, SOCK_COLL_ADDR);

    QCOMPARE(ret_connect, succ_connect);

    deleteObjects(QList<QObject *>() << node);
}

void CloneTestSuite::testBenchmarkNodeConnection()
{
    CloneNodeApp *node = CloneNodeApp::createNode();

    QBENCHMARK {
        QVERIFY(node->connectNode(SOCK_SNAP_ADDR, SOCK_UPDT_ADDR, SOCK_COLL_ADDR));
        QVERIFY(node->disconnectNode());
    }

    deleteObjects(QList<QObject *>() << node, 2000);
}

void CloneTestSuite::testBenchmarkBrokerBind()
{
    CloneBrokerApp *broker = CloneBrokerApp::createBroker();

    QBENCHMARK {
        QVERIFY(broker->bindBroker({SOCK_SNAP_ADDR}, {SOCK_UPDT_ADDR}, {SOCK_COLL_ADDR}));
        QVERIFY(broker->unbindBroker());
    }

    deleteObjects(QList<QObject *>() << broker, 2000);
}

void CloneTestSuite::testUuidEncode_data()
{
    QTest::addColumn<QUuid>("uuid");
    QTest::addColumn<QByteArray>("bytes");

    QTest::newRow("Encode valid uuid")
        << QUuid(0x67c8770b, 0x44f1, 0x410a,
            0xab, 0x9a, 0xf9, 0xb5, 0x44, 0x6f, 0x13, 0xee)
        << QByteArray::fromHex("67C8770B44F1410AAB9AF9B5446F13EE");
}

void CloneTestSuite::testUuidEncode()
{
    QFETCH(QUuid, uuid);
    QFETCH(QByteArray, bytes);

    QByteArray encdata = zmq::zmqEncodeMessagePart<QUuid>(uuid);
    QCOMPARE(encdata, bytes);
}

void CloneTestSuite::testUuidDecode_data()
{
    QTest::addColumn<QByteArray>("bytes");
    QTest::addColumn<QUuid>("uuid");

    QTest::newRow("Decode valid uuid")
        << QByteArray::fromHex("67C8770B44F1410AAB9AF9B5446F13EE")
        << QUuid(0x67c8770b, 0x44f1, 0x410a,
            0xab, 0x9a, 0xf9, 0xb5, 0x44, 0x6f, 0x13, 0xee);
}

void CloneTestSuite::testUuidDecode()
{
    QFETCH(QByteArray, bytes);
    QFETCH(QUuid, uuid);

    QUuid decdata = zmq::zmqDecodeMessagePart<QUuid>(bytes);
    QCOMPARE(decdata, uuid);
}

void CloneTestSuite::testTopicPost_data()
{
    QTest::addColumn<QString>("name");
    QTest::addColumn<QByteArray>("value");
    QTest::addColumn<QList<QByteArray>>("subscriptions");
    QTest::addColumn<bool>("connected");
    QTest::addColumn<bool>("success");

    QTest::newRow("Send message without topic")
        << "" << QByteArray::fromHex("AABBCC")
        << QList<QByteArray>()
        << true << false;
    QTest::newRow("Send message without value")
        << "/topic" << QByteArray()
        << QList<QByteArray>()
        << true << true;
    QTest::newRow("Send message without subscription")
        << "/topic" << QByteArray::fromHex("AABBCC")
        << QList<QByteArray>()
        << true << true;
    QTest::newRow("Send message with subscription")
        << "/topic" << QByteArray::fromHex("AABBCC")
        << (QList<QByteArray>() << "/topic")
        << true << true;
    QTest::newRow("Send message with different subscription")
        << "/topic1" << QByteArray::fromHex("AABBCC")
        << (QList<QByteArray>() << "/topic2")
        << true << false;
    QTest::newRow("Send message with more than one subscription")
        << "/topic3" << QByteArray::fromHex("AABBCC")
        << (QList<QByteArray>() << "/topic1" << "/topic2" << "/topic3")
        << true << true;
    QTest::newRow("Send valid subtopic with subscriptions")
        << "/topic2/subtopic1" << QByteArray::fromHex("AABBCC")
        << (QList<QByteArray>() << "/topic1" << "/topic2" << "/topic3")
        << true << true;
    QTest::newRow("Send invalid subtopic with subscriptions #1")
        << "/topic4/subtopic1" << QByteArray::fromHex("AABBCC")
        << (QList<QByteArray>() << "/topic1" << "/topic2" << "/topic3")
        << true << false;
    QTest::newRow("Send invalid subtopic with subscriptions #2")
        << "/topic4/topic1/subtopic1" << QByteArray::fromHex("AABBCC")
        << (QList<QByteArray>() << "/topic1" << "/topic2" << "/topic3")
        << true << false;
    QTest::newRow("Send invalid topic with subscriptions")
        << "/topic" << QByteArray::fromHex("AABBCC")
        << (QList<QByteArray>() << "/topic1" << "/topic2" << "/topic3")
        << true << false;
    QTest::newRow("Send message without connection")
        << "/topic" << QByteArray::fromHex("AABBCC")
        << QList<QByteArray>()
        << false << false;
}

void CloneTestSuite::testTopicPost()
{
    QFETCH(QString, name);
    QFETCH(QByteArray, value);
    QFETCH(QList<QByteArray>, subscriptions);
    QFETCH(bool, connected);
    QFETCH(bool, success);

    CloneBrokerApp *broker = CloneBrokerApp::createBroker();
    CloneNodeApp *node = CloneNodeApp::createNode();

    if (!subscriptions.isEmpty())
        QVERIFY(node->subscribeToSpecificTopics(subscriptions));
    else
        QVERIFY(node->subscribeToAllTopics());

    if (connected) {
        QVERIFY(node->connectNode(SOCK_SNAP_ADDR, SOCK_UPDT_ADDR, SOCK_COLL_ADDR));
        QVERIFY(waitForSignal(node, SIGNAL(nodeConnected()), 500));

        QVERIFY(broker->bindBroker({SOCK_SNAP_ADDR}, {SOCK_UPDT_ADDR}, {SOCK_COLL_ADDR}));
        QVERIFY(waitForSignal(node, SIGNAL(connectionReady()), 2500));
    }

    bool post_ok = node->postTopic(name.toLocal8Bit(), value);
    QCOMPARE(post_ok, success);

    if (post_ok) {
        QVERIFY(waitForSignal(node,
                              SIGNAL(topicUpdated(QByteArray, QByteArray, QUuid)),
                              500,
                              1,
                              {{qVariantFromValue(name.toLocal8Bit()), qVariantFromValue(value), qVariantFromValue(node->uuid())}}
                              )
                );
    }

    if (connected) {
        QVERIFY(node->disconnectNode());
        QVERIFY(waitForSignal(node, SIGNAL(nodeDisconnected()), 500));
    }

    deleteObjects(QList<QObject *>() << broker << node);
}

void CloneTestSuite::testTopicSync_data()
{
    QTest::addColumn<QList<QByteArray>>("initState");
    QTest::addColumn<QList<QByteArray>>("syncState");
    QTest::addColumn<QList<QByteArray>>("postState");
    QTest::addColumn<QList<QByteArray>>("diffState");

    QTest::newRow("Sync no topics")
        << QList<QByteArray>{}
        << QList<QByteArray>{}
        << QList<QByteArray>{}
        << QList<QByteArray>{};
    QTest::newRow("Sync one event")
        << QList<QByteArray>{
            "/path/to/event", QByteArray()}
        << QList<QByteArray>{}
        << QList<QByteArray>{}
        << QList<QByteArray>{};
    QTest::newRow("Sync one event and post another event")
        << QList<QByteArray>{
            "/path/to/event", QByteArray()}
        << QList<QByteArray>{}
        << QList<QByteArray>{
            "/path/to/event", QByteArray()}
        << QList<QByteArray>{};
    QTest::newRow("Sync one topic")
        << QList<QByteArray>{
            "/state/of/app", QByteArray::fromHex("aa")}
        << QList<QByteArray>{
            "/state/of/app", QByteArray::fromHex("aa")}
        << QList<QByteArray>{}
        << QList<QByteArray>{};
    QTest::newRow("Sync and overwrite one topic")
        << QList<QByteArray>{
            "/state/of/app", QByteArray::fromHex("aa"),
            "/state/of/app", QByteArray::fromHex("bb")}
        << QList<QByteArray>{
            "/state/of/app", QByteArray::fromHex("bb")}
        << QList<QByteArray>{}
        << QList<QByteArray>{};
    QTest::newRow("Sync two topics")
        << QList<QByteArray>{
            "/state/of/app/1", QByteArray::fromHex("aa"),
            "/state/of/app/2", QByteArray::fromHex("bb")}
        << QList<QByteArray>{
            "/state/of/app/1", QByteArray::fromHex("aa"),
            "/state/of/app/2", QByteArray::fromHex("bb")}
        << QList<QByteArray>{}
        << QList<QByteArray>{};
    QTest::newRow("Sync four topics")
        << QList<QByteArray>{
            "/state/of/app/1", QByteArray::fromHex("aa"),
            "/state/of/app/2", QByteArray::fromHex("bb"),
            "/state/of/app/3", QByteArray::fromHex("cc"),
            "/state/of/app/4", QByteArray::fromHex("dd")}
        << QList<QByteArray>{
            "/state/of/app/1", QByteArray::fromHex("aa"),
            "/state/of/app/2", QByteArray::fromHex("bb"),
            "/state/of/app/3", QByteArray::fromHex("cc"),
            "/state/of/app/4", QByteArray::fromHex("dd")}
        << QList<QByteArray>{}
        << QList<QByteArray>{};
    QTest::newRow("Sync four topics and overwrite the second")
        << QList<QByteArray>{
            "/state/of/app/1", QByteArray::fromHex("aa"),
            "/state/of/app/2", QByteArray::fromHex("bb"),
            "/state/of/app/3", QByteArray::fromHex("cc"),
            "/state/of/app/4", QByteArray::fromHex("dd"),
            "/state/of/app/2", QByteArray::fromHex("ee")}
        << QList<QByteArray>{
            "/state/of/app/1", QByteArray::fromHex("aa"),
            "/state/of/app/3", QByteArray::fromHex("cc"),
            "/state/of/app/4", QByteArray::fromHex("dd"),
            "/state/of/app/2", QByteArray::fromHex("ee")}
        << QList<QByteArray>{}
        << QList<QByteArray>{};
    QTest::newRow("Sync four topics and overwrite the second and the first")
        << QList<QByteArray>{
            "/state/of/app/1", QByteArray::fromHex("aa"),
            "/state/of/app/2", QByteArray::fromHex("bb"),
            "/state/of/app/3", QByteArray::fromHex("cc"),
            "/state/of/app/4", QByteArray::fromHex("dd"),
            "/state/of/app/2", QByteArray::fromHex("ee"),
            "/state/of/app/1", QByteArray::fromHex("ff")}
        << QList<QByteArray>{
            "/state/of/app/3", QByteArray::fromHex("cc"),
            "/state/of/app/4", QByteArray::fromHex("dd"),
            "/state/of/app/2", QByteArray::fromHex("ee"),
            "/state/of/app/1", QByteArray::fromHex("ff")}
        << QList<QByteArray>{}
        << QList<QByteArray>{};
    QTest::newRow("Sync two topics and one event #1")
        << QList<QByteArray>{
            "/event/of/app/1", QByteArray::fromHex("cc"),
            "/state/of/app/1", QByteArray::fromHex("aa"),
            "/state/of/app/2", QByteArray::fromHex("bb")}
        << QList<QByteArray>{
            "/state/of/app/1", QByteArray::fromHex("aa"),
            "/state/of/app/2", QByteArray::fromHex("bb")}
        << QList<QByteArray>{}
        << QList<QByteArray>{};
    QTest::newRow("Sync two topics and one event #2")
        << QList<QByteArray>{
            "/state/of/app/1", QByteArray::fromHex("aa"),
            "/state/of/app/2", QByteArray::fromHex("bb"),
            "/event/of/app/1", QByteArray::fromHex("cc")}
        << QList<QByteArray>{
            "/state/of/app/1", QByteArray::fromHex("aa"),
            "/state/of/app/2", QByteArray::fromHex("bb")}
        << QList<QByteArray>{}
        << QList<QByteArray>{};
    QTest::newRow("Sync two topics and two events")
        << QList<QByteArray>{
            "/event/of/app/1", QByteArray::fromHex("cc"),
            "/state/of/app/1", QByteArray::fromHex("aa"),
            "/event/of/app/2", QByteArray::fromHex("dd"),
            "/state/of/app/2", QByteArray::fromHex("bb")}
        << QList<QByteArray>{
            "/state/of/app/1", QByteArray::fromHex("aa"),
            "/state/of/app/2", QByteArray::fromHex("bb")}
        << QList<QByteArray>{}
        << QList<QByteArray>{};
    QTest::newRow("Sync one topic and post the same")
        << QList<QByteArray>{
            "/state/of/app/1", QByteArray::fromHex("aa")}
        << QList<QByteArray>{
            "/state/of/app/1", QByteArray::fromHex("aa")}
        << QList<QByteArray>{
            "/state/of/app/1", QByteArray::fromHex("bb")}
        << QList<QByteArray>{
            "/state/of/app/1", QByteArray::fromHex("bb")};
    QTest::newRow("Sync one topic and post another one")
        << QList<QByteArray>{
            "/state/of/app/1", QByteArray::fromHex("aa")}
        << QList<QByteArray>{
            "/state/of/app/1", QByteArray::fromHex("aa")}
        << QList<QByteArray>{
            "/state/of/app/2", QByteArray::fromHex("bb")}
        << QList<QByteArray>{
            "/state/of/app/2", QByteArray::fromHex("bb")};
    QTest::newRow("Sync two topics and post the same")
        << QList<QByteArray>{
            "/state/of/app/1", QByteArray::fromHex("aa"),
            "/state/of/app/2", QByteArray::fromHex("bb")}
        << QList<QByteArray>{
            "/state/of/app/1", QByteArray::fromHex("aa"),
            "/state/of/app/2", QByteArray::fromHex("bb")}
        << QList<QByteArray>{
            "/state/of/app/1", QByteArray::fromHex("cc"),
            "/state/of/app/2", QByteArray::fromHex("dd")}
        << QList<QByteArray>{
            "/state/of/app/1", QByteArray::fromHex("cc"),
            "/state/of/app/2", QByteArray::fromHex("dd")};
    QTest::newRow("Sync two topics and post another twos")
        << QList<QByteArray>{
            "/state/of/app/1", QByteArray::fromHex("aa"),
            "/state/of/app/2", QByteArray::fromHex("bb")}
        << QList<QByteArray>{
            "/state/of/app/1", QByteArray::fromHex("aa"),
            "/state/of/app/2", QByteArray::fromHex("bb")}
        << QList<QByteArray>{
            "/state/of/app/3", QByteArray::fromHex("cc"),
            "/state/of/app/4", QByteArray::fromHex("dd")}
        << QList<QByteArray>{
            "/state/of/app/3", QByteArray::fromHex("cc"),
            "/state/of/app/4", QByteArray::fromHex("dd")};
    QTest::newRow("Sync no topics and post one")
        << QList<QByteArray>{}
        << QList<QByteArray>{}
        << QList<QByteArray>{
            "/state/of/app/1", QByteArray::fromHex("aa")}
        << QList<QByteArray>{
            "/state/of/app/1", QByteArray::fromHex("aa")};
    QTest::newRow("Sync no topics and another twos")
        << QList<QByteArray>{}
        << QList<QByteArray>{}
        << QList<QByteArray>{
            "/state/of/app/1", QByteArray::fromHex("aa"),
            "/state/of/app/2", QByteArray::fromHex("bb")}
        << QList<QByteArray>{
            "/state/of/app/1", QByteArray::fromHex("aa"),
            "/state/of/app/2", QByteArray::fromHex("bb")};
}

void CloneTestSuite::testTopicSync()
{
    QFETCH(QList<QByteArray>, initState);
    QFETCH(QList<QByteArray>, syncState);
    QFETCH(QList<QByteArray>, postState);
    QFETCH(QList<QByteArray>, diffState);

    QVERIFY(initState.size() % 2 == 0);
    QVERIFY(syncState.size() % 2 == 0);
    QVERIFY(postState.size() % 2 == 0);
    QVERIFY(diffState.size() % 2 == 0);

    auto addState = [this] (CloneNodeApp *node, QList<QByteArray> topics) {
        QVERIFY(node->connectNode(SOCK_SNAP_ADDR, SOCK_UPDT_ADDR, SOCK_COLL_ADDR));
        QVERIFY(waitForSignal(node, SIGNAL(connectionReady()), 2500));

        for (int i = 0; i < topics.size() - 1; i += 2) {
            const QByteArray &n = topics.at(i);
            const QByteArray &v = topics.at(i + 1);
            QVERIFY(node->postTopic(n, v));
            QVERIFY(waitForSignal(node,
                       SIGNAL(topicUpdated(QByteArray, QByteArray, QUuid)),
                       500,
                       1,
                       {{qVariantFromValue(n), qVariantFromValue(v), qVariantFromValue(node->uuid())}}
            ));
        }

        node->disconnectNode();
    };

    auto verifyState = [this] (CloneNodeApp *node, QList<QByteArray> topics, QUuid uuid) {
        QVERIFY(node->connectNode(SOCK_SNAP_ADDR, SOCK_UPDT_ADDR, SOCK_COLL_ADDR));

        QList<QList<QVariant>> sigargs;
        for (int i = 0; i < topics.size() - 1; i += 2) {
            const QByteArray &n = topics.at(i);
            const QByteArray &v = topics.at(i + 1);
            sigargs.append({qVariantFromValue(n), qVariantFromValue(v),
                qVariantFromValue(uuid)});
        }

        QVERIFY(waitForSignal(node,
            SIGNAL(topicUpdated(QByteArray, QByteArray, QUuid)), 5000,
            sigargs.size(), sigargs,
            SIGNAL(snapshotSynced(QUuid))));

        QVERIFY(node->disconnectNode());
    };

    CloneBrokerApp *broker = CloneBrokerApp::createBroker();
    QVERIFY(broker->bindBroker({SOCK_SNAP_ADDR}, {SOCK_UPDT_ADDR}, {SOCK_COLL_ADDR}));

    // Setup initial state
    CloneNodeApp *node1 = CloneNodeApp::createNode();
    addState(node1, initState);

    // Sync state
    CloneNodeApp *node2 = CloneNodeApp::createNode();
    verifyState(node2, syncState, node1->uuid());

    // Post additional topics with node3
    CloneNodeApp *node3 = CloneNodeApp::createNode();
    addState(node3, postState);

    // Resync node2
    verifyState(node2, diffState, node3->uuid());

    deleteObjects({broker, node1, node2, node3});
}

void CloneTestSuite::testTopicPostBeforeSync()
{
    // FIXME: test to be reviewed
    QByteArray topic = "/state/of/app";
    QByteArray value = QByteArray::fromHex("aa");

    CloneNodeApp *node = CloneNodeApp::createNode();
    QVERIFY(node->connectNode(SOCK_SNAP_ADDR, SOCK_UPDT_ADDR, SOCK_COLL_ADDR));
    QVERIFY(waitForSignal(node, SIGNAL(nodeConnected()), 500));

    QTest::qSleep(500);
    QVERIFY(node->postTopic(topic, QByteArray::fromHex("aa")));

    CloneBrokerApp *broker = CloneBrokerApp::createBroker();
    QVERIFY(broker->bindBroker({SOCK_SNAP_ADDR}, {SOCK_UPDT_ADDR}, {SOCK_COLL_ADDR}));

    QTest::qSleep(500);
    QVERIFY(node->disconnectNode());
    QVERIFY(node->connectNode(SOCK_SNAP_ADDR, SOCK_UPDT_ADDR, SOCK_COLL_ADDR));

    QVERIFY(waitForSignal(node, SIGNAL(topicUpdated(QByteArray, QByteArray, QUuid)),
                          5000,
                          1,
                          {{qVariantFromValue(topic), qVariantFromValue(value), qVariantFromValue(node->uuid())}}
    ));

    deleteObjects({broker, node});
}

void CloneTestSuite::testBenchmarkTopicRoundTrip()
{
    CloneNodeApp *node = CloneNodeApp::createNode();
    CloneBrokerApp *broker = CloneBrokerApp::createBroker();

    QVERIFY(broker->bindBroker({SOCK_SNAP_ADDR}, {SOCK_UPDT_ADDR}, {SOCK_COLL_ADDR}));
    QVERIFY(node->connectNode(SOCK_SNAP_ADDR, SOCK_UPDT_ADDR, SOCK_COLL_ADDR));
    QVERIFY(waitForSignal(node, SIGNAL(connectionReady()), 2500));

    QByteArray name = "/topic/test";
    QByteArray value = QByteArray::fromHex("AABBCC");

    QList<QList<QVariant>> sigargs;
    sigargs.append(QList<QVariant>()
        << qVariantFromValue(name)
        << qVariantFromValue(value)
        << qVariantFromValue(node->uuid()));

    QBENCHMARK {
        QVERIFY(node->postTopic(name, value));
        QVERIFY(waitForSignal(node, SIGNAL(topicUpdated(QByteArray, QByteArray, QUuid)),
                              1000, 1,
                              sigargs));
    }

    deleteObjects(QList<QObject *>() << node << broker);
}

void CloneTestSuite::testBenchmarkTopicUpdate()
{
    CloneNodeApp *node1 = CloneNodeApp::createNode();
    CloneNodeApp *node2 = CloneNodeApp::createNode();
    CloneBrokerApp *broker = CloneBrokerApp::createBroker();

    QVERIFY(broker->bindBroker({SOCK_SNAP_ADDR}, {SOCK_UPDT_ADDR}, {SOCK_COLL_ADDR}));

    QVERIFY(node1->connectNode(SOCK_SNAP_ADDR, SOCK_UPDT_ADDR, SOCK_COLL_ADDR));
    QVERIFY(waitForSignal(node1, SIGNAL(connectionReady()), 2500));

    QVERIFY(node2->connectNode(SOCK_SNAP_ADDR, SOCK_UPDT_ADDR, SOCK_COLL_ADDR));
    QVERIFY(waitForSignal(node2, SIGNAL(connectionReady()), 2500));

    QByteArray name = "/topic/test";
    QByteArray value = QByteArray::fromHex("AABBCC");

    QList<QList<QVariant>> sigargs;
    sigargs.append(QList<QVariant>()
        << qVariantFromValue(name)
        << qVariantFromValue(value)
        << qVariantFromValue(node1->uuid()));

    QBENCHMARK {
        QVERIFY(node1->postTopic(name, value));
        QVERIFY(waitForSignal(node2, SIGNAL(topicUpdated(QByteArray, QByteArray, QUuid)),
                              1000, 1,
                              sigargs));
    }

    deleteObjects(QList<QObject *>() << node1 << node2 << broker);
}
