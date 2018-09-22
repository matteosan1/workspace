/****************************************************************************
** TDPalio meta object code from reading C++ file 'tdpalio.h'
**
** Created: Thu Jun 21 22:03:28 2007
**      by: The Qt MOC ($Id: qt/moc_yacc.cpp   3.3.7   edited Oct 19 16:22 $)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#undef QT_NO_COMPAT
#include "tdpalio.h"
#include <qmetaobject.h>
#include <qapplication.h>

#include <private/qucomextra_p.h>
#if !defined(Q_MOC_OUTPUT_REVISION) || (Q_MOC_OUTPUT_REVISION != 26)
#error "This file was generated using the moc from 3.3.7. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

const char *TDPalio::className() const
{
    return "TDPalio";
}

QMetaObject *TDPalio::metaObj = 0;
static QMetaObjectCleanUp cleanUp_TDPalio( "TDPalio", &TDPalio::staticMetaObject );

#ifndef QT_NO_TRANSLATION
QString TDPalio::tr( const char *s, const char *c )
{
    if ( qApp )
	return qApp->translate( "TDPalio", s, c, QApplication::DefaultCodec );
    else
	return QString::fromLatin1( s );
}
#ifndef QT_NO_TRANSLATION_UTF8
QString TDPalio::trUtf8( const char *s, const char *c )
{
    if ( qApp )
	return qApp->translate( "TDPalio", s, c, QApplication::UnicodeUTF8 );
    else
	return QString::fromUtf8( s );
}
#endif // QT_NO_TRANSLATION_UTF8

#endif // QT_NO_TRANSLATION

QMetaObject* TDPalio::staticMetaObject()
{
    if ( metaObj )
	return metaObj;
    QMetaObject* parentObject = QMainWindow::staticMetaObject();
    static const QUMethod slot_0 = {"controller", 0, 0 };
    static const QUMethod slot_1 = {"formaCavalli", 0, 0 };
    static const QUParameter param_slot_2[] = {
	{ 0, &static_QUType_QString, 0, QUParameter::Out }
    };
    static const QUMethod slot_2 = {"getData", 1, param_slot_2 };
    static const QUMethod slot_3 = {"visualizzaEstrazione", 0, 0 };
    static const QUMethod slot_4 = {"SceltaStrategia", 0, 0 };
    static const QUMethod slot_5 = {"SceltaCavalli", 0, 0 };
    static const QUParameter param_slot_6[] = {
	{ "cav", &static_QUType_varptr, "\x10", QUParameter::In }
    };
    static const QUMethod slot_6 = {"Assegnazione", 1, param_slot_6 };
    static const QUMethod slot_7 = {"SceltaFantino", 0, 0 };
    static const QUMethod slot_8 = {"Segnatura", 0, 0 };
    static const QUMethod slot_9 = {"RisposteFantini", 0, 0 };
    static const QUMethod slot_10 = {"InserisciPartito", 0, 0 };
    static const QUMethod slot_11 = {"RispostePartiti", 0, 0 };
    static const QUMethod slot_12 = {"Prove", 0, 0 };
    static const QUMethod slot_13 = {"fileNew", 0, 0 };
    static const QUParameter param_slot_14[] = {
	{ "fileName", &static_QUType_QString, 0, QUParameter::In }
    };
    static const QUMethod slot_14 = {"caricaFile", 1, param_slot_14 };
    static const QUMethod slot_15 = {"fileOpen", 0, 0 };
    static const QUParameter param_slot_16[] = {
	{ "fileName", &static_QUType_QString, 0, QUParameter::In }
    };
    static const QUMethod slot_16 = {"salvaFile", 1, param_slot_16 };
    static const QUParameter param_slot_17[] = {
	{ 0, &static_QUType_bool, 0, QUParameter::Out }
    };
    static const QUMethod slot_17 = {"fileSave", 1, param_slot_17 };
    static const QUParameter param_slot_18[] = {
	{ 0, &static_QUType_bool, 0, QUParameter::Out }
    };
    static const QUMethod slot_18 = {"fileSaveAs", 1, param_slot_18 };
    static const QUMethod slot_19 = {"filePrint", 0, 0 };
    static const QUParameter param_slot_20[] = {
	{ "event", &static_QUType_ptr, "QCloseEvent", QUParameter::In }
    };
    static const QUMethod slot_20 = {"closeEvent", 1, param_slot_20 };
    static const QUMethod slot_21 = {"nuovoGiocatore", 0, 0 };
    static const QUMethod slot_22 = {"aiutoInformazioni", 0, 0 };
    static const QUParameter param_slot_23[] = {
	{ "n", &static_QUType_int, 0, QUParameter::In }
    };
    static const QUMethod slot_23 = {"estrazione", 1, param_slot_23 };
    static const QUMethod slot_24 = {"help", 0, 0 };
    static const QUParameter param_slot_25[] = {
	{ "a", &static_QUType_bool, 0, QUParameter::In }
    };
    static const QUMethod slot_25 = {"abilitaSuono", 1, param_slot_25 };
    static const QUMethod slot_26 = {"nuovaFase", 0, 0 };
    static const QUMethod slot_27 = {"languageChange", 0, 0 };
    static const QMetaData slot_tbl[] = {
	{ "controller()", &slot_0, QMetaData::Public },
	{ "formaCavalli()", &slot_1, QMetaData::Public },
	{ "getData()", &slot_2, QMetaData::Public },
	{ "visualizzaEstrazione()", &slot_3, QMetaData::Public },
	{ "SceltaStrategia()", &slot_4, QMetaData::Public },
	{ "SceltaCavalli()", &slot_5, QMetaData::Public },
	{ "Assegnazione(int*)", &slot_6, QMetaData::Public },
	{ "SceltaFantino()", &slot_7, QMetaData::Public },
	{ "Segnatura()", &slot_8, QMetaData::Public },
	{ "RisposteFantini()", &slot_9, QMetaData::Public },
	{ "InserisciPartito()", &slot_10, QMetaData::Public },
	{ "RispostePartiti()", &slot_11, QMetaData::Public },
	{ "Prove()", &slot_12, QMetaData::Public },
	{ "fileNew()", &slot_13, QMetaData::Public },
	{ "caricaFile(const QString&)", &slot_14, QMetaData::Public },
	{ "fileOpen()", &slot_15, QMetaData::Public },
	{ "salvaFile(const QString&)", &slot_16, QMetaData::Public },
	{ "fileSave()", &slot_17, QMetaData::Public },
	{ "fileSaveAs()", &slot_18, QMetaData::Public },
	{ "filePrint()", &slot_19, QMetaData::Public },
	{ "closeEvent(QCloseEvent*)", &slot_20, QMetaData::Public },
	{ "nuovoGiocatore()", &slot_21, QMetaData::Public },
	{ "aiutoInformazioni()", &slot_22, QMetaData::Public },
	{ "estrazione(int)", &slot_23, QMetaData::Public },
	{ "help()", &slot_24, QMetaData::Public },
	{ "abilitaSuono(bool)", &slot_25, QMetaData::Public },
	{ "nuovaFase()", &slot_26, QMetaData::Public },
	{ "languageChange()", &slot_27, QMetaData::Protected }
    };
    metaObj = QMetaObject::new_metaobject(
	"TDPalio", parentObject,
	slot_tbl, 28,
	0, 0,
#ifndef QT_NO_PROPERTIES
	0, 0,
	0, 0,
#endif // QT_NO_PROPERTIES
	0, 0 );
    cleanUp_TDPalio.setMetaObject( metaObj );
    return metaObj;
}

void* TDPalio::qt_cast( const char* clname )
{
    if ( !qstrcmp( clname, "TDPalio" ) )
	return this;
    return QMainWindow::qt_cast( clname );
}

bool TDPalio::qt_invoke( int _id, QUObject* _o )
{
    switch ( _id - staticMetaObject()->slotOffset() ) {
    case 0: controller(); break;
    case 1: formaCavalli(); break;
    case 2: static_QUType_QString.set(_o,getData()); break;
    case 3: visualizzaEstrazione(); break;
    case 4: SceltaStrategia(); break;
    case 5: SceltaCavalli(); break;
    case 6: Assegnazione((int*)static_QUType_varptr.get(_o+1)); break;
    case 7: SceltaFantino(); break;
    case 8: Segnatura(); break;
    case 9: RisposteFantini(); break;
    case 10: InserisciPartito(); break;
    case 11: RispostePartiti(); break;
    case 12: Prove(); break;
    case 13: fileNew(); break;
    case 14: caricaFile((const QString&)static_QUType_QString.get(_o+1)); break;
    case 15: fileOpen(); break;
    case 16: salvaFile((const QString&)static_QUType_QString.get(_o+1)); break;
    case 17: static_QUType_bool.set(_o,fileSave()); break;
    case 18: static_QUType_bool.set(_o,fileSaveAs()); break;
    case 19: filePrint(); break;
    case 20: closeEvent((QCloseEvent*)static_QUType_ptr.get(_o+1)); break;
    case 21: nuovoGiocatore(); break;
    case 22: aiutoInformazioni(); break;
    case 23: estrazione((int)static_QUType_int.get(_o+1)); break;
    case 24: help(); break;
    case 25: abilitaSuono((bool)static_QUType_bool.get(_o+1)); break;
    case 26: nuovaFase(); break;
    case 27: languageChange(); break;
    default:
	return QMainWindow::qt_invoke( _id, _o );
    }
    return TRUE;
}

bool TDPalio::qt_emit( int _id, QUObject* _o )
{
    return QMainWindow::qt_emit(_id,_o);
}
#ifndef QT_NO_PROPERTIES

bool TDPalio::qt_property( int id, int f, QVariant* v)
{
    return QMainWindow::qt_property( id, f, v);
}

bool TDPalio::qt_static_property( QObject* , int , int , QVariant* ){ return FALSE; }
#endif // QT_NO_PROPERTIES
