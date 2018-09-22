/****************************************************************************
** Meta object code from reading C++ file 'stareditor.h'
**
** Created: Sun Oct 14 13:14:51 2007
**      by: The Qt Meta Object Compiler version 59 (Qt 4.3.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "stareditor.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'stareditor.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 59
#error "This file was generated using the moc from 4.3.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

static const uint qt_meta_data_StarEditor[] = {

 // content:
       1,       // revision
       0,       // classname
       0,    0, // classinfo
       1,   10, // methods
       0,    0, // properties
       0,    0, // enums/sets

 // signals: signature, parameters, type, tag, flags
      12,   11,   11,   11, 0x05,

       0        // eod
};

static const char qt_meta_stringdata_StarEditor[] = {
    "StarEditor\0\0editingFinished()\0"
};

const QMetaObject StarEditor::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_StarEditor,
      qt_meta_data_StarEditor, 0 }
};

const QMetaObject *StarEditor::metaObject() const
{
    return &staticMetaObject;
}

void *StarEditor::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_StarEditor))
	return static_cast<void*>(const_cast< StarEditor*>(this));
    return QWidget::qt_metacast(_clname);
}

int StarEditor::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: editingFinished(); break;
        }
        _id -= 1;
    }
    return _id;
}

// SIGNAL 0
void StarEditor::editingFinished()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}
