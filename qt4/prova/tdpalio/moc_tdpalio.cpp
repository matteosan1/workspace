/****************************************************************************
** Meta object code from reading C++ file 'tdpalio.h'
**
** Created: Mon Oct 22 19:24:39 2007
**      by: The Qt Meta Object Compiler version 59 (Qt 4.3.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "tdpalio.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'tdpalio.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 59
#error "This file was generated using the moc from 4.3.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

static const uint qt_meta_data_TDPalio[] = {

 // content:
       1,       // revision
       0,       // classname
       0,    0, // classinfo
      26,   10, // methods
       0,    0, // properties
       0,    0, // enums/sets

 // slots: signature, parameters, type, tag, flags
       9,    8,    8,    8, 0x0a,
      30,    8,   22,    8, 0x0a,
      40,    8,    8,    8, 0x0a,
      59,   50,    8,    8, 0x0a,
      79,    8,    8,    8, 0x0a,
      90,   50,    8,    8, 0x0a,
     114,    8,  109,    8, 0x0a,
     125,    8,  109,    8, 0x0a,
     138,    8,    8,    8, 0x0a,
     150,    8,    8,    8, 0x0a,
     158,    8,    8,    8, 0x0a,
     175,    8,    8,    8, 0x0a,
     197,  195,    8,    8, 0x0a,
     215,  213,    8,    8, 0x0a,
     234,    8,    8,    8, 0x0a,
     246,    8,    8,    8, 0x0a,
     261,    8,    8,    8, 0x0a,
     284,    8,    8,    8, 0x0a,
     302,    8,    8,    8, 0x0a,
     322,  318,    8,    8, 0x0a,
     341,    8,    8,    8, 0x0a,
     357,    8,    8,    8, 0x0a,
     369,    8,    8,    8, 0x0a,
     387,    8,    8,    8, 0x0a,
     406,    8,    8,    8, 0x0a,
     424,    8,    8,    8, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_TDPalio[] = {
    "TDPalio\0\0controller()\0QString\0getData()\0"
    "fileNew()\0fileName\0caricaFile(QString)\0"
    "fileOpen()\0salvaFile(QString)\0bool\0"
    "fileSave()\0fileSaveAs()\0filePrint()\0"
    "close()\0nuovoGiocatore()\0aiutoInformazioni()\0"
    "n\0estrazione(int)\0a\0abilitaSuono(bool)\0"
    "nuovaFase()\0formaCavalli()\0"
    "visualizzaEstrazione()\0SceltaStrategia()\0"
    "SceltaCavalli()\0cav\0Assegnazione(int*)\0"
    "SceltaFantino()\0Segnatura()\0"
    "RisposteFantini()\0InserisciPartito()\0"
    "RispostePartiti()\0Prove()\0"
};

const QMetaObject TDPalio::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_TDPalio,
      qt_meta_data_TDPalio, 0 }
};

const QMetaObject *TDPalio::metaObject() const
{
    return &staticMetaObject;
}

void *TDPalio::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_TDPalio))
	return static_cast<void*>(const_cast< TDPalio*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int TDPalio::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: controller(); break;
        case 1: { QString _r = getData();
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = _r; }  break;
        case 2: fileNew(); break;
        case 3: caricaFile((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 4: fileOpen(); break;
        case 5: salvaFile((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 6: { bool _r = fileSave();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        case 7: { bool _r = fileSaveAs();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        case 8: filePrint(); break;
        case 9: close(); break;
        case 10: nuovoGiocatore(); break;
        case 11: aiutoInformazioni(); break;
        case 12: estrazione((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 13: abilitaSuono((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 14: nuovaFase(); break;
        case 15: formaCavalli(); break;
        case 16: visualizzaEstrazione(); break;
        case 17: SceltaStrategia(); break;
        case 18: SceltaCavalli(); break;
        case 19: Assegnazione((*reinterpret_cast< int*(*)>(_a[1]))); break;
        case 20: SceltaFantino(); break;
        case 21: Segnatura(); break;
        case 22: RisposteFantini(); break;
        case 23: InserisciPartito(); break;
        case 24: RispostePartiti(); break;
        case 25: Prove(); break;
        }
        _id -= 26;
    }
    return _id;
}
