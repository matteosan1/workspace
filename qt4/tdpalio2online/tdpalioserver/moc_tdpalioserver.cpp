/****************************************************************************
** Meta object code from reading C++ file 'tdpalioserver.h'
**
** Created: Thu Jun 25 15:59:43 2009
**      by: The Qt Meta Object Compiler version 61 (Qt 4.5.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "tdpalioserver.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'tdpalioserver.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 61
#error "This file was generated using the moc from 4.5.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_TDPalioServer[] = {

 // content:
       2,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   12, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors

 // slots: signature, parameters, type, tag, flags
      15,   14,   14,   14, 0x08,
      34,   14,   14,   14, 0x08,
      54,   52,   14,   14, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_TDPalioServer[] = {
    "TDPalioServer\0\0acceptConnection()\0"
    "incomingMessage()\0e\0"
    "error(QAbstractSocket::SocketError)\0"
};

const QMetaObject TDPalioServer::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_TDPalioServer,
      qt_meta_data_TDPalioServer, 0 }
};

const QMetaObject *TDPalioServer::metaObject() const
{
    return &staticMetaObject;
}

void *TDPalioServer::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_TDPalioServer))
        return static_cast<void*>(const_cast< TDPalioServer*>(this));
    return QObject::qt_metacast(_clname);
}

int TDPalioServer::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: acceptConnection(); break;
        case 1: incomingMessage(); break;
        case 2: error((*reinterpret_cast< QAbstractSocket::SocketError(*)>(_a[1]))); break;
        default: ;
        }
        _id -= 3;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
