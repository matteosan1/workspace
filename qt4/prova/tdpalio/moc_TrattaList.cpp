/****************************************************************************
** Meta object code from reading C++ file 'TrattaList.h'
**
** Created: Mon Oct 22 19:09:30 2007
**      by: The Qt Meta Object Compiler version 59 (Qt 4.3.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "TrattaList.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'TrattaList.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 59
#error "This file was generated using the moc from 4.3.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

static const uint qt_meta_data_TrattaList[] = {

 // content:
       1,       // revision
       0,       // classname
       0,    0, // classinfo
       0,    0, // methods
       0,    0, // properties
       0,    0, // enums/sets

       0        // eod
};

static const char qt_meta_stringdata_TrattaList[] = {
    "TrattaList\0"
};

const QMetaObject TrattaList::staticMetaObject = {
    { &QAbstractTableModel::staticMetaObject, qt_meta_stringdata_TrattaList,
      qt_meta_data_TrattaList, 0 }
};

const QMetaObject *TrattaList::metaObject() const
{
    return &staticMetaObject;
}

void *TrattaList::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_TrattaList))
	return static_cast<void*>(const_cast< TrattaList*>(this));
    return QAbstractTableModel::qt_metacast(_clname);
}

int TrattaList::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QAbstractTableModel::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    return _id;
}
