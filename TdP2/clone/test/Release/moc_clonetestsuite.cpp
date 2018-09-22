/****************************************************************************
** Meta object code from reading C++ file 'clonetestsuite.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.5)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../clonetestsuite.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'clonetestsuite.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.5. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_CloneTestSuite[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
      41,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      16,   15,   15,   15, 0x08,
      31,   15,   15,   15, 0x08,
      49,   15,   15,   15, 0x08,
      56,   15,   15,   15, 0x08,
      66,   15,   15,   15, 0x08,
      93,   15,   15,   15, 0x08,
     115,   15,   15,   15, 0x08,
     143,   15,   15,   15, 0x08,
     173,   15,   15,   15, 0x08,
     213,   15,   15,   15, 0x08,
     244,   15,   15,   15, 0x08,
     270,   15,   15,   15, 0x08,
     296,   15,   15,   15, 0x08,
     317,   15,   15,   15, 0x08,
     345,   15,   15,   15, 0x08,
     374,   15,   15,   15, 0x08,
     398,   15,   15,   15, 0x08,
     420,   15,   15,   15, 0x08,
     437,   15,   15,   15, 0x08,
     461,   15,   15,   15, 0x08,
     480,   15,   15,   15, 0x08,
     503,   15,   15,   15, 0x08,
     531,   15,   15,   15, 0x08,
     554,   15,   15,   15, 0x08,
     590,   15,   15,   15, 0x08,
     620,   15,   15,   15, 0x08,
     645,   15,   15,   15, 0x08,
     673,   15,   15,   15, 0x08,
     696,   15,   15,   15, 0x08,
     726,   15,   15,   15, 0x08,
     752,   15,   15,   15, 0x08,
     774,   15,   15,   15, 0x08,
     791,   15,   15,   15, 0x08,
     813,   15,   15,   15, 0x08,
     830,   15,   15,   15, 0x08,
     851,   15,   15,   15, 0x08,
     867,   15,   15,   15, 0x08,
     888,   15,   15,   15, 0x08,
     904,   15,   15,   15, 0x08,
     930,   15,   15,   15, 0x08,
     960,   15,   15,   15, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_CloneTestSuite[] = {
    "CloneTestSuite\0\0initTestCase()\0"
    "cleanupTestCase()\0init()\0cleanup()\0"
    "testNodeSimpleStart_data()\0"
    "testNodeSimpleStart()\0testNodeConnectionTimeout()\0"
    "testNodeConnectionHeartbeat()\0"
    "testNodeConnectionHeartbeatWithTopics()\0"
    "testNodeConnectNoMaster_data()\0"
    "testNodeConnectNoMaster()\0"
    "testNodeDisconnect_data()\0"
    "testNodeDisconnect()\0testNodeConnectDisconnect()\0"
    "testBrokerSimpleStart_data()\0"
    "testBrokerSimpleStart()\0testBrokerBind_data()\0"
    "testBrokerBind()\0testBrokerUnbind_data()\0"
    "testBrokerUnbind()\0testBrokerBindUnbind()\0"
    "testSnapshotSyncNode_data()\0"
    "testSnapshotSyncNode()\0"
    "testSnapshotSyncWithSubscriptions()\0"
    "testSnapshotSyncBroker_data()\0"
    "testSnapshotSyncBroker()\0"
    "testNodeSubscription_data()\0"
    "testNodeSubscription()\0"
    "testBenchmarkNodeConnection()\0"
    "testBenchmarkBrokerBind()\0"
    "testUuidEncode_data()\0testUuidEncode()\0"
    "testUuidDecode_data()\0testUuidDecode()\0"
    "testTopicPost_data()\0testTopicPost()\0"
    "testTopicSync_data()\0testTopicSync()\0"
    "testTopicPostBeforeSync()\0"
    "testBenchmarkTopicRoundTrip()\0"
    "testBenchmarkTopicUpdate()\0"
};

void CloneTestSuite::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        CloneTestSuite *_t = static_cast<CloneTestSuite *>(_o);
        switch (_id) {
        case 0: _t->initTestCase(); break;
        case 1: _t->cleanupTestCase(); break;
        case 2: _t->init(); break;
        case 3: _t->cleanup(); break;
        case 4: _t->testNodeSimpleStart_data(); break;
        case 5: _t->testNodeSimpleStart(); break;
        case 6: _t->testNodeConnectionTimeout(); break;
        case 7: _t->testNodeConnectionHeartbeat(); break;
        case 8: _t->testNodeConnectionHeartbeatWithTopics(); break;
        case 9: _t->testNodeConnectNoMaster_data(); break;
        case 10: _t->testNodeConnectNoMaster(); break;
        case 11: _t->testNodeDisconnect_data(); break;
        case 12: _t->testNodeDisconnect(); break;
        case 13: _t->testNodeConnectDisconnect(); break;
        case 14: _t->testBrokerSimpleStart_data(); break;
        case 15: _t->testBrokerSimpleStart(); break;
        case 16: _t->testBrokerBind_data(); break;
        case 17: _t->testBrokerBind(); break;
        case 18: _t->testBrokerUnbind_data(); break;
        case 19: _t->testBrokerUnbind(); break;
        case 20: _t->testBrokerBindUnbind(); break;
        case 21: _t->testSnapshotSyncNode_data(); break;
        case 22: _t->testSnapshotSyncNode(); break;
        case 23: _t->testSnapshotSyncWithSubscriptions(); break;
        case 24: _t->testSnapshotSyncBroker_data(); break;
        case 25: _t->testSnapshotSyncBroker(); break;
        case 26: _t->testNodeSubscription_data(); break;
        case 27: _t->testNodeSubscription(); break;
        case 28: _t->testBenchmarkNodeConnection(); break;
        case 29: _t->testBenchmarkBrokerBind(); break;
        case 30: _t->testUuidEncode_data(); break;
        case 31: _t->testUuidEncode(); break;
        case 32: _t->testUuidDecode_data(); break;
        case 33: _t->testUuidDecode(); break;
        case 34: _t->testTopicPost_data(); break;
        case 35: _t->testTopicPost(); break;
        case 36: _t->testTopicSync_data(); break;
        case 37: _t->testTopicSync(); break;
        case 38: _t->testTopicPostBeforeSync(); break;
        case 39: _t->testBenchmarkTopicRoundTrip(); break;
        case 40: _t->testBenchmarkTopicUpdate(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObjectExtraData CloneTestSuite::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject CloneTestSuite::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_CloneTestSuite,
      qt_meta_data_CloneTestSuite, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &CloneTestSuite::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *CloneTestSuite::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *CloneTestSuite::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_CloneTestSuite))
        return static_cast<void*>(const_cast< CloneTestSuite*>(this));
    return QObject::qt_metacast(_clname);
}

int CloneTestSuite::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 41)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 41;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
