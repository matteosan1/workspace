/****************************************************************************
** Meta object code from reading C++ file 'tratta.h'
**
** Created: Mon Oct 22 19:09:23 2007
**      by: The Qt Meta Object Compiler version 59 (Qt 4.3.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "tratta.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'tratta.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 59
#error "This file was generated using the moc from 4.3.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

static const uint qt_meta_data_TrattaDialog[] = {

 // content:
       1,       // revision
       0,       // classname
       0,    0, // classinfo
       1,   10, // methods
       0,    0, // properties
       0,    0, // enums/sets

 // slots: signature, parameters, type, tag, flags
      16,   14,   13,   13, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_TrattaDialog[] = {
    "TrattaDialog\0\0s\0cambiaCaption(QString)\0"
};

const QMetaObject TrattaDialog::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_TrattaDialog,
      qt_meta_data_TrattaDialog, 0 }
};

const QMetaObject *TrattaDialog::metaObject() const
{
    return &staticMetaObject;
}

void *TrattaDialog::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_TrattaDialog))
	return static_cast<void*>(const_cast< TrattaDialog*>(this));
    return QDialog::qt_metacast(_clname);
}

int TrattaDialog::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: cambiaCaption((*reinterpret_cast< QString(*)>(_a[1]))); break;
        }
        _id -= 1;
    }
    return _id;
}
