/****************************************************************************
** Meta object code from reading C++ file 'tdpalioaiclient.h'
**
** Created: Thu Jun 25 15:59:43 2009
**      by: The Qt Meta Object Compiler version 61 (Qt 4.5.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "tdpalioaiclient.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'tdpalioaiclient.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 61
#error "This file was generated using the moc from 4.5.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_TDPalioAiClient[] = {

 // content:
       2,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   12, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors

 // slots: signature, parameters, type, tag, flags
      17,   16,   16,   16, 0x0a,
      35,   16,   16,   16, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_TDPalioAiClient[] = {
    "TDPalioAiClient\0\0incomingMessage()\0"
    "displayError(QAbstractSocket::SocketError)\0"
};

const QMetaObject TDPalioAiClient::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_TDPalioAiClient,
      qt_meta_data_TDPalioAiClient, 0 }
};

const QMetaObject *TDPalioAiClient::metaObject() const
{
    return &staticMetaObject;
}

void *TDPalioAiClient::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_TDPalioAiClient))
        return static_cast<void*>(const_cast< TDPalioAiClient*>(this));
    return QObject::qt_metacast(_clname);
}

int TDPalioAiClient::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: incomingMessage(); break;
        case 1: displayError((*reinterpret_cast< QAbstractSocket::SocketError(*)>(_a[1]))); break;
        default: ;
        }
        _id -= 2;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
