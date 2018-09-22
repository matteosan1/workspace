/****************************************************************************
** Meta object code from reading C++ file 'strategiaprove.h'
**
** Created: Mon Oct 22 19:13:59 2007
**      by: The Qt Meta Object Compiler version 59 (Qt 4.3.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "strategiaprove.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'strategiaprove.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 59
#error "This file was generated using the moc from 4.3.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

static const uint qt_meta_data_StrategiaProveDialog[] = {

 // content:
       1,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   10, // methods
       0,    0, // properties
       0,    0, // enums/sets

 // slots: signature, parameters, type, tag, flags
      55,   22,   21,   21, 0x0a,
     110,  104,   21,   21, 0x0a,
     128,  104,   21,   21, 0x0a,
     146,  104,   21,   21, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_StrategiaProveDialog[] = {
    "StrategiaProveDialog\0\0"
    "fantini,contrade,contrada,status\0"
    "FillCombo(QStringList,QStringList,Barbero*,int*)\0"
    "state\0enableCombo1(int)\0enableCombo2(int)\0"
    "enableCombo3(int)\0"
};

const QMetaObject StrategiaProveDialog::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_StrategiaProveDialog,
      qt_meta_data_StrategiaProveDialog, 0 }
};

const QMetaObject *StrategiaProveDialog::metaObject() const
{
    return &staticMetaObject;
}

void *StrategiaProveDialog::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_StrategiaProveDialog))
	return static_cast<void*>(const_cast< StrategiaProveDialog*>(this));
    return QDialog::qt_metacast(_clname);
}

int StrategiaProveDialog::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: FillCombo((*reinterpret_cast< QStringList(*)>(_a[1])),(*reinterpret_cast< QStringList(*)>(_a[2])),(*reinterpret_cast< Barbero*(*)>(_a[3])),(*reinterpret_cast< int*(*)>(_a[4]))); break;
        case 1: enableCombo1((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 2: enableCombo2((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 3: enableCombo3((*reinterpret_cast< int(*)>(_a[1]))); break;
        }
        _id -= 4;
    }
    return _id;
}
