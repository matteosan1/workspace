/****************************************************************************
** Meta object code from reading C++ file 'modgiocatore.h'
**
** Created: Tue Sep 25 01:46:18 2007
**      by: The Qt Meta Object Compiler version 59 (Qt 4.3.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "modgiocatore.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'modgiocatore.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 59
#error "This file was generated using the moc from 4.3.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

static const uint qt_meta_data_ModGiocatore[] = {

 // content:
       1,       // revision
       0,       // classname
       0,    0, // classinfo
       1,   10, // methods
       0,    0, // properties
       0,    0, // enums/sets

 // slots: signature, parameters, type, tag, flags
      14,   13,   13,   13, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_ModGiocatore[] = {
    "ModGiocatore\0\0changeSelection(int)\0"
};

const QMetaObject ModGiocatore::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_ModGiocatore,
      qt_meta_data_ModGiocatore, 0 }
};

const QMetaObject *ModGiocatore::metaObject() const
{
    return &staticMetaObject;
}

void *ModGiocatore::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_ModGiocatore))
	return static_cast<void*>(const_cast< ModGiocatore*>(this));
    return QDialog::qt_metacast(_clname);
}

int ModGiocatore::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: changeSelection((*reinterpret_cast< int(*)>(_a[1]))); break;
        }
        _id -= 1;
    }
    return _id;
}