/****************************************************************************
** Meta object code from reading C++ file 'insgiocatore.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.7)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "insgiocatore.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'insgiocatore.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.7. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_InsGiocatore[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      14,   13,   13,   13, 0x08,
      34,   32,   13,   13, 0x08,
      54,   32,   13,   13, 0x08,
      77,   32,   13,   13, 0x08,
      99,   32,   13,   13, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_InsGiocatore[] = {
    "InsGiocatore\0\0changeRadio(bool)\0s\0"
    "changeNome(QString)\0changeCognome(QString)\0"
    "changePrezzo(QString)\0changeSquadra(QString)\0"
};

void InsGiocatore::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        InsGiocatore *_t = static_cast<InsGiocatore *>(_o);
        switch (_id) {
        case 0: _t->changeRadio((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 1: _t->changeNome((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 2: _t->changeCognome((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 3: _t->changePrezzo((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 4: _t->changeSquadra((*reinterpret_cast< QString(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData InsGiocatore::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject InsGiocatore::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_InsGiocatore,
      qt_meta_data_InsGiocatore, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &InsGiocatore::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *InsGiocatore::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *InsGiocatore::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_InsGiocatore))
        return static_cast<void*>(const_cast< InsGiocatore*>(this));
    return QDialog::qt_metacast(_clname);
}

int InsGiocatore::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 5)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 5;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
