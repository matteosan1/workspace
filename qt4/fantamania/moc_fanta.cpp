/****************************************************************************
** Meta object code from reading C++ file 'fanta.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.7)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "fanta.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'fanta.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.7. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_FantaDialog[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
      10,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      13,   12,   12,   12, 0x08,
      24,   12,   12,   12, 0x08,
      40,   12,   12,   12, 0x08,
      51,   12,   12,   12, 0x08,
      68,   12,   12,   12, 0x08,
      80,   12,   12,   12, 0x08,
      95,   12,   12,   12, 0x08,
     108,   12,   12,   12, 0x08,
     123,   12,   12,   12, 0x08,
     130,   12,   12,   12, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_FantaDialog[] = {
    "FantaDialog\0\0fileOpen()\0insFormazione()\0"
    "fileSave()\0changeView(bool)\0addPlayer()\0"
    "modifyPlayer()\0killPlayer()\0nuovaSquadra()\0"
    "tipo()\0riassunto(QModelIndex)\0"
};

void FantaDialog::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        FantaDialog *_t = static_cast<FantaDialog *>(_o);
        switch (_id) {
        case 0: _t->fileOpen(); break;
        case 1: _t->insFormazione(); break;
        case 2: _t->fileSave(); break;
        case 3: _t->changeView((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 4: _t->addPlayer(); break;
        case 5: _t->modifyPlayer(); break;
        case 6: _t->killPlayer(); break;
        case 7: _t->nuovaSquadra(); break;
        case 8: _t->tipo(); break;
        case 9: _t->riassunto((*reinterpret_cast< const QModelIndex(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData FantaDialog::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject FantaDialog::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_FantaDialog,
      qt_meta_data_FantaDialog, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &FantaDialog::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *FantaDialog::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *FantaDialog::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_FantaDialog))
        return static_cast<void*>(const_cast< FantaDialog*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int FantaDialog::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 10)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 10;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
