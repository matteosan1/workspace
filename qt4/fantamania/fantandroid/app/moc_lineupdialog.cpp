/****************************************************************************
** Meta object code from reading C++ file 'lineupdialog.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.7.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "lineupdialog.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'lineupdialog.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.7.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_LineupDialog_t {
    QByteArrayData data[9];
    char stringdata0[112];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_LineupDialog_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_LineupDialog_t qt_meta_stringdata_LineupDialog = {
    {
QT_MOC_LITERAL(0, 0, 12), // "LineupDialog"
QT_MOC_LITERAL(1, 13, 13), // "updateModules"
QT_MOC_LITERAL(2, 27, 0), // ""
QT_MOC_LITERAL(3, 28, 12), // "chosenModule"
QT_MOC_LITERAL(4, 41, 14), // "playerSelected"
QT_MOC_LITERAL(5, 56, 6), // "player"
QT_MOC_LITERAL(6, 63, 14), // "aggiungiPushed"
QT_MOC_LITERAL(7, 78, 16), // "removePanchinaro"
QT_MOC_LITERAL(8, 95, 16) // "QListWidgetItem*"

    },
    "LineupDialog\0updateModules\0\0chosenModule\0"
    "playerSelected\0player\0aggiungiPushed\0"
    "removePanchinaro\0QListWidgetItem*"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_LineupDialog[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    1,   34,    2, 0x08 /* Private */,
       4,    1,   37,    2, 0x08 /* Private */,
       6,    0,   40,    2, 0x08 /* Private */,
       7,    1,   41,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void, QMetaType::QString,    5,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 8,    2,

       0        // eod
};

void LineupDialog::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        LineupDialog *_t = static_cast<LineupDialog *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->updateModules((*reinterpret_cast< const int(*)>(_a[1]))); break;
        case 1: _t->playerSelected((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 2: _t->aggiungiPushed(); break;
        case 3: _t->removePanchinaro((*reinterpret_cast< QListWidgetItem*(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObject LineupDialog::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_LineupDialog.data,
      qt_meta_data_LineupDialog,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *LineupDialog::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *LineupDialog::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_LineupDialog.stringdata0))
        return static_cast<void*>(const_cast< LineupDialog*>(this));
    return QDialog::qt_metacast(_clname);
}

int LineupDialog::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 4)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 4;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 4)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 4;
    }
    return _id;
}
QT_END_MOC_NAMESPACE