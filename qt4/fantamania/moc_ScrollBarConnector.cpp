/****************************************************************************
** Meta object code from reading C++ file 'ScrollBarConnector.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.7)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "ScrollBarConnector.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'ScrollBarConnector.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.7. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_ScrollBarConnector[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      26,   20,   19,   19, 0x09,
      44,   20,   19,   19, 0x09,

       0        // eod
};

static const char qt_meta_stringdata_ScrollBarConnector[] = {
    "ScrollBarConnector\0\0value\0bar1_changed(int)\0"
    "bar2_changed(int)\0"
};

void ScrollBarConnector::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        ScrollBarConnector *_t = static_cast<ScrollBarConnector *>(_o);
        switch (_id) {
        case 0: _t->bar1_changed((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 1: _t->bar2_changed((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData ScrollBarConnector::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject ScrollBarConnector::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_ScrollBarConnector,
      qt_meta_data_ScrollBarConnector, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &ScrollBarConnector::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *ScrollBarConnector::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *ScrollBarConnector::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_ScrollBarConnector))
        return static_cast<void*>(const_cast< ScrollBarConnector*>(this));
    return QObject::qt_metacast(_clname);
}

int ScrollBarConnector::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 2)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 2;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
