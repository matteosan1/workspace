/****************************************************************************
** Meta object code from reading C++ file 'InsertPlayerDialog.h'
**
** Created: Sat Jan 19 02:47:08 2008
**      by: The Qt Meta Object Compiler version 59 (Qt 4.3.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "InsertPlayerDialog.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'InsertPlayerDialog.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 59
#error "This file was generated using the moc from 4.3.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

static const uint qt_meta_data_InsertPlayerDialog[] = {

 // content:
       1,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   10, // methods
       0,    0, // properties
       0,    0, // enums/sets

 // slots: signature, parameters, type, tag, flags
      20,   19,   19,   19, 0x08,
      32,   19,   19,   19, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_InsertPlayerDialog[] = {
    "InsertPlayerDialog\0\0insertRow()\0"
    "removeRow()\0"
};

const QMetaObject InsertPlayerDialog::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_InsertPlayerDialog,
      qt_meta_data_InsertPlayerDialog, 0 }
};

const QMetaObject *InsertPlayerDialog::metaObject() const
{
    return &staticMetaObject;
}

void *InsertPlayerDialog::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_InsertPlayerDialog))
	return static_cast<void*>(const_cast< InsertPlayerDialog*>(this));
    return QDialog::qt_metacast(_clname);
}

int InsertPlayerDialog::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: insertRow(); break;
        case 1: removeRow(); break;
        }
        _id -= 2;
    }
    return _id;
}
