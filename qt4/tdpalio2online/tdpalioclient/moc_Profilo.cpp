/****************************************************************************
** Meta object code from reading C++ file 'Profilo.h'
**
** Created: Thu Jun 25 15:59:25 2009
**      by: The Qt Meta Object Compiler version 61 (Qt 4.5.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "Profilo.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'Profilo.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 61
#error "This file was generated using the moc from 4.5.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_Profilo[] = {

 // content:
       2,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   12, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors

 // slots: signature, parameters, type, tag, flags
       9,    8,    8,    8, 0x0a,
      24,    8,    8,    8, 0x0a,
      39,    8,    8,    8, 0x0a,
      54,    8,    8,    8, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_Profilo[] = {
    "Profilo\0\0text1(QString)\0text2(QString)\0"
    "text3(QString)\0esci()\0"
};

const QMetaObject Profilo::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_Profilo,
      qt_meta_data_Profilo, 0 }
};

const QMetaObject *Profilo::metaObject() const
{
    return &staticMetaObject;
}

void *Profilo::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_Profilo))
        return static_cast<void*>(const_cast< Profilo*>(this));
    return QDialog::qt_metacast(_clname);
}

int Profilo::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: text1((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 1: text2((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 2: text3((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 3: esci(); break;
        default: ;
        }
        _id -= 4;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
