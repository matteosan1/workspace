/****************************************************************************
** Meta object code from reading C++ file 'nuovogiocatore.h'
**
** Created: Mon Oct 22 19:09:16 2007
**      by: The Qt Meta Object Compiler version 59 (Qt 4.3.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "nuovogiocatore.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'nuovogiocatore.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 59
#error "This file was generated using the moc from 4.3.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

static const uint qt_meta_data_NuovoGiocatoreDialog[] = {

 // content:
       1,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   10, // methods
       0,    0, // properties
       0,    0, // enums/sets

 // slots: signature, parameters, type, tag, flags
      28,   22,   21,   21, 0x0a,
      45,   21,   21,   21, 0x0a,
      66,   54,   21,   21, 0x0a,
     108,   21,  104,   21, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_NuovoGiocatoreDialog[] = {
    "NuovoGiocatoreDialog\0\0state\0"
    "enableCombo(int)\0accept()\0lista,index\0"
    "setContrade(QStringList,QVector<int>)\0"
    "int\0assegnaContrada()\0"
};

const QMetaObject NuovoGiocatoreDialog::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_NuovoGiocatoreDialog,
      qt_meta_data_NuovoGiocatoreDialog, 0 }
};

const QMetaObject *NuovoGiocatoreDialog::metaObject() const
{
    return &staticMetaObject;
}

void *NuovoGiocatoreDialog::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_NuovoGiocatoreDialog))
	return static_cast<void*>(const_cast< NuovoGiocatoreDialog*>(this));
    return QDialog::qt_metacast(_clname);
}

int NuovoGiocatoreDialog::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: enableCombo((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 1: accept(); break;
        case 2: setContrade((*reinterpret_cast< QStringList(*)>(_a[1])),(*reinterpret_cast< QVector<int>(*)>(_a[2]))); break;
        case 3: { int _r = assegnaContrada();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = _r; }  break;
        }
        _id -= 4;
    }
    return _id;
}
