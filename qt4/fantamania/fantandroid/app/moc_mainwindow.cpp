/****************************************************************************
** Meta object code from reading C++ file 'mainwindow.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.7.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../../../../Volumes/Untitled 1/Ginevra/app/mainwindow.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mainwindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.7.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_MainWindow_t {
    QByteArrayData data[26];
    char stringdata0[312];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_MainWindow_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_MainWindow_t qt_meta_stringdata_MainWindow = {
    {
QT_MOC_LITERAL(0, 0, 10), // "MainWindow"
QT_MOC_LITERAL(1, 11, 7), // "stackTo"
QT_MOC_LITERAL(2, 19, 0), // ""
QT_MOC_LITERAL(3, 20, 10), // "pageNumber"
QT_MOC_LITERAL(4, 31, 10), // "sendLineup"
QT_MOC_LITERAL(5, 42, 11), // "changeStack"
QT_MOC_LITERAL(6, 54, 13), // "updateModules"
QT_MOC_LITERAL(7, 68, 12), // "chosenModule"
QT_MOC_LITERAL(8, 81, 14), // "playerSelected"
QT_MOC_LITERAL(9, 96, 6), // "player"
QT_MOC_LITERAL(10, 103, 14), // "aggiungiPushed"
QT_MOC_LITERAL(11, 118, 16), // "removePanchinaro"
QT_MOC_LITERAL(12, 135, 16), // "QListWidgetItem*"
QT_MOC_LITERAL(13, 152, 10), // "selectTeam"
QT_MOC_LITERAL(14, 163, 12), // "selectRoster"
QT_MOC_LITERAL(15, 176, 8), // "teamName"
QT_MOC_LITERAL(16, 185, 16), // "singlePlayerStat"
QT_MOC_LITERAL(17, 202, 5), // "index"
QT_MOC_LITERAL(18, 208, 14), // "configDownload"
QT_MOC_LITERAL(19, 223, 8), // "exitCode"
QT_MOC_LITERAL(20, 232, 16), // "updateTeamChoice"
QT_MOC_LITERAL(21, 249, 13), // "changeRoundUp"
QT_MOC_LITERAL(22, 263, 15), // "changeRoundDown"
QT_MOC_LITERAL(23, 279, 15), // "keyReleaseEvent"
QT_MOC_LITERAL(24, 295, 10), // "QKeyEvent*"
QT_MOC_LITERAL(25, 306, 5) // "event"

    },
    "MainWindow\0stackTo\0\0pageNumber\0"
    "sendLineup\0changeStack\0updateModules\0"
    "chosenModule\0playerSelected\0player\0"
    "aggiungiPushed\0removePanchinaro\0"
    "QListWidgetItem*\0selectTeam\0selectRoster\0"
    "teamName\0singlePlayerStat\0index\0"
    "configDownload\0exitCode\0updateTeamChoice\0"
    "changeRoundUp\0changeRoundDown\0"
    "keyReleaseEvent\0QKeyEvent*\0event"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_MainWindow[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      15,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   89,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       4,    0,   92,    2, 0x0a /* Public */,
       5,    0,   93,    2, 0x0a /* Public */,
       6,    1,   94,    2, 0x0a /* Public */,
       8,    1,   97,    2, 0x0a /* Public */,
      10,    0,  100,    2, 0x0a /* Public */,
      11,    1,  101,    2, 0x0a /* Public */,
      13,    0,  104,    2, 0x0a /* Public */,
      14,    1,  105,    2, 0x0a /* Public */,
      16,    1,  108,    2, 0x0a /* Public */,
      18,    1,  111,    2, 0x0a /* Public */,
      20,    0,  114,    2, 0x0a /* Public */,
      21,    0,  115,    2, 0x0a /* Public */,
      22,    0,  116,    2, 0x0a /* Public */,
      23,    1,  117,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::Int,    3,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    7,
    QMetaType::Void, QMetaType::QString,    9,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 12,    2,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,   15,
    QMetaType::Void, QMetaType::QModelIndex,   17,
    QMetaType::Void, QMetaType::Bool,   19,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 24,   25,

       0        // eod
};

void MainWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        MainWindow *_t = static_cast<MainWindow *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->stackTo((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 1: _t->sendLineup(); break;
        case 2: _t->changeStack(); break;
        case 3: _t->updateModules((*reinterpret_cast< const int(*)>(_a[1]))); break;
        case 4: _t->playerSelected((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 5: _t->aggiungiPushed(); break;
        case 6: _t->removePanchinaro((*reinterpret_cast< QListWidgetItem*(*)>(_a[1]))); break;
        case 7: _t->selectTeam(); break;
        case 8: _t->selectRoster((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 9: _t->singlePlayerStat((*reinterpret_cast< QModelIndex(*)>(_a[1]))); break;
        case 10: _t->configDownload((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 11: _t->updateTeamChoice(); break;
        case 12: _t->changeRoundUp(); break;
        case 13: _t->changeRoundDown(); break;
        case 14: _t->keyReleaseEvent((*reinterpret_cast< QKeyEvent*(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (MainWindow::*_t)(int );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&MainWindow::stackTo)) {
                *result = 0;
                return;
            }
        }
    }
}

const QMetaObject MainWindow::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_MainWindow.data,
      qt_meta_data_MainWindow,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *MainWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MainWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_MainWindow.stringdata0))
        return static_cast<void*>(const_cast< MainWindow*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int MainWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 15)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 15;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 15)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 15;
    }
    return _id;
}

// SIGNAL 0
void MainWindow::stackTo(int _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_END_MOC_NAMESPACE
