#ifndef CLONETESTSUITE_H
#define CLONETESTSUITE_H

#include <QList>
#include <QObject>

class CloneNodeApp;

class CloneTestSuite: public QObject
{
    Q_OBJECT

private slots:
    void initTestCase();
    void cleanupTestCase();
    void init();
    void cleanup();

    void testNodeSimpleStart_data();
    void testNodeSimpleStart();

    void testNodeConnectionTimeout();
    void testNodeConnectionHeartbeat();
    void testNodeConnectionHeartbeatWithTopics();

    void testNodeConnectNoMaster_data();
    void testNodeConnectNoMaster();

    void testNodeDisconnect_data();
    void testNodeDisconnect();

    void testNodeConnectDisconnect();

    void testBrokerSimpleStart_data();
    void testBrokerSimpleStart();

    void testBrokerBind_data();
    void testBrokerBind();

    void testBrokerUnbind_data();
    void testBrokerUnbind();

    void testBrokerBindUnbind();

    void testSnapshotSyncNode_data();
    void testSnapshotSyncNode();

    void testSnapshotSyncWithSubscriptions();

    void testSnapshotSyncBroker_data();
    void testSnapshotSyncBroker();

    void testNodeSubscription_data();
    void testNodeSubscription();

    void testBenchmarkNodeConnection();
    void testBenchmarkBrokerBind();

    void testUuidEncode_data();
    void testUuidEncode();

    void testUuidDecode_data();
    void testUuidDecode();

    void testTopicPost_data();
    void testTopicPost();

    void testTopicSync_data();
    void testTopicSync();

    void testTopicPostBeforeSync();

    void testBenchmarkTopicRoundTrip();
    void testBenchmarkTopicUpdate();


private:
    void deleteObjects(QList<QObject *> objects, int timeoutMsec = 5000);
};

#endif // CLONETESTSUITE_H
