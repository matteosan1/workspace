/****************************************************************************
** Meta object code from reading C++ file 'CaricaGiocoDialog.h'
**
** Created: Thu Jun 25 15:59:17 2009
**      by: The Qt Meta Object Compiler version 61 (Qt 4.5.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "CaricaGiocoDialog.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'CaricaGiocoDialog.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 61
#error "This file was generated using the moc from 4.5.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_CaricaGiocoDialog[] = {

 // content:
       2,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   12, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors

 // slots: signature, parameters, type, tag, flags
      19,   18,   18,   18, 0x0a,
      34,   18,   18,   18, 0x0a,
      41,   18,   18,   18, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_CaricaGiocoDialog[] = {
    "CaricaGiocoDialog\0\0enableButton()\0"
    "load()\0esci()\0"
};

const QMetaObject CaricaGiocoDialog::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_CaricaGiocoDialog,
      qt_meta_data_CaricaGiocoDialog, 0 }
};

const QMetaObject *CaricaGiocoDialog::metaObject() const
{
    return &staticMetaObject;
}

void *CaricaGiocoDialog::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_CaricaGiocoDialog))
        return static_cast<void*>(const_cast< CaricaGiocoDialog*>(this));
    return QDialog::qt_metacast(_clname);
}

int CaricaGiocoDialog::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: enableButton(); break;
        case 1: load(); break;
        case 2: esci(); break;
        default: ;
        }
        _id -= 3;
    }
    return _id;
}
QT_END_MOC_NAMESPACE