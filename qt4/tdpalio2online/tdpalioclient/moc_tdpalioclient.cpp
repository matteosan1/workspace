/****************************************************************************
** Meta object code from reading C++ file 'tdpalioclient.h'
**
** Created: Thu Jun 25 15:59:23 2009
**      by: The Qt Meta Object Compiler version 61 (Qt 4.5.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "tdpalioclient.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'tdpalioclient.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 61
#error "This file was generated using the moc from 4.5.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_TDPalioClient[] = {

 // content:
       2,       // revision
       0,       // classname
       0,    0, // classinfo
      15,   12, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors

 // slots: signature, parameters, type, tag, flags
      15,   14,   14,   14, 0x0a,
      28,   14,   14,   14, 0x0a,
      39,   14,   14,   14, 0x0a,
      52,   14,   14,   14, 0x0a,
      64,   14,   14,   14, 0x0a,
      82,   14,   14,   14, 0x0a,
      99,   14,   14,   14, 0x0a,
     117,   14,   14,   14, 0x0a,
     160,   14,   14,   14, 0x0a,
     179,  177,   14,   14, 0x0a,
     215,  177,   14,   14, 0x0a,
     256,   14,   14,   14, 0x0a,
     276,   14,   14,   14, 0x0a,
     284,   14,   14,   14, 0x0a,
     298,  296,   14,   14, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_TDPalioClient[] = {
    "TDPalioClient\0\0scriviChat()\0apriChat()\0"
    "chiudiChat()\0startGame()\0becomeSpectator()\0"
    "chooseContrada()\0incomingMessage()\0"
    "displayError(QAbstractSocket::SocketError)\0"
    "openConnection()\0,\0"
    "nuovoGioco(QStringList,QStringList)\0"
    "nuovoGiocatore(QStringList,QVector<int>)\0"
    "aiutoInformazioni()\0ready()\0battesimo()\0"
    "a\0abilitaSuono(bool)\0"
};

const QMetaObject TDPalioClient::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_TDPalioClient,
      qt_meta_data_TDPalioClient, 0 }
};

const QMetaObject *TDPalioClient::metaObject() const
{
    return &staticMetaObject;
}

void *TDPalioClient::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_TDPalioClient))
        return static_cast<void*>(const_cast< TDPalioClient*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int TDPalioClient::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: scriviChat(); break;
        case 1: apriChat(); break;
        case 2: chiudiChat(); break;
        case 3: startGame(); break;
        case 4: becomeSpectator(); break;
        case 5: chooseContrada(); break;
        case 6: incomingMessage(); break;
        case 7: displayError((*reinterpret_cast< QAbstractSocket::SocketError(*)>(_a[1]))); break;
        case 8: openConnection(); break;
        case 9: nuovoGioco((*reinterpret_cast< QStringList(*)>(_a[1])),(*reinterpret_cast< QStringList(*)>(_a[2]))); break;
        case 10: nuovoGiocatore((*reinterpret_cast< QStringList(*)>(_a[1])),(*reinterpret_cast< QVector<int>(*)>(_a[2]))); break;
        case 11: aiutoInformazioni(); break;
        case 12: ready(); break;
        case 13: battesimo(); break;
        case 14: abilitaSuono((*reinterpret_cast< bool(*)>(_a[1]))); break;
        default: ;
        }
        _id -= 15;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
