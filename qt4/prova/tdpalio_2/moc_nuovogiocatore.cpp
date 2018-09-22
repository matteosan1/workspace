/****************************************************************************
** NuovoGiocatore meta object code from reading C++ file 'nuovogiocatore.h'
**
** Created: Sun Jun 17 16:57:45 2007
**      by: The Qt MOC ($Id: qt/moc_yacc.cpp   3.3.7   edited Oct 19 16:22 $)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#undef QT_NO_COMPAT
#include "nuovogiocatore.h"
#include <qmetaobject.h>
#include <qapplication.h>

#include <private/qucomextra_p.h>
#if !defined(Q_MOC_OUTPUT_REVISION) || (Q_MOC_OUTPUT_REVISION != 26)
#error "This file was generated using the moc from 3.3.7. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

const char *NuovoGiocatore::className() const
{
    return "NuovoGiocatore";
}

QMetaObject *NuovoGiocatore::metaObj = 0;
static QMetaObjectCleanUp cleanUp_NuovoGiocatore( "NuovoGiocatore", &NuovoGiocatore::staticMetaObject );

#ifndef QT_NO_TRANSLATION
QString NuovoGiocatore::tr( const char *s, const char *c )
{
    if ( qApp )
	return qApp->translate( "NuovoGiocatore", s, c, QApplication::DefaultCodec );
    else
	return QString::fromLatin1( s );
}
#ifndef QT_NO_TRANSLATION_UTF8
QString NuovoGiocatore::trUtf8( const char *s, const char *c )
{
    if ( qApp )
	return qApp->translate( "NuovoGiocatore", s, c, QApplication::UnicodeUTF8 );
    else
	return QString::fromUtf8( s );
}
#endif // QT_NO_TRANSLATION_UTF8

#endif // QT_NO_TRANSLATION

QMetaObject* NuovoGiocatore::staticMetaObject()
{
    if ( metaObj )
	return metaObj;
    QMetaObject* parentObject = QDialog::staticMetaObject();
    static const QUParameter param_slot_0[] = {
	{ "state", &static_QUType_int, 0, QUParameter::In }
    };
    static const QUMethod slot_0 = {"enableCombo", 1, param_slot_0 };
    static const QUMethod slot_1 = {"accept", 0, 0 };
    static const QUParameter param_slot_2[] = {
	{ "lista", &static_QUType_varptr, "\x04", QUParameter::In },
	{ "index", &static_QUType_ptr, "vector<int>", QUParameter::In }
    };
    static const QUMethod slot_2 = {"setContrade", 2, param_slot_2 };
    static const QUParameter param_slot_3[] = {
	{ 0, &static_QUType_int, 0, QUParameter::Out }
    };
    static const QUMethod slot_3 = {"assegnaContrada", 1, param_slot_3 };
    static const QUMethod slot_4 = {"languageChange", 0, 0 };
    static const QMetaData slot_tbl[] = {
	{ "enableCombo(int)", &slot_0, QMetaData::Public },
	{ "accept()", &slot_1, QMetaData::Public },
	{ "setContrade(QStringList,vector<int>)", &slot_2, QMetaData::Public },
	{ "assegnaContrada()", &slot_3, QMetaData::Public },
	{ "languageChange()", &slot_4, QMetaData::Protected }
    };
    metaObj = QMetaObject::new_metaobject(
	"NuovoGiocatore", parentObject,
	slot_tbl, 5,
	0, 0,
#ifndef QT_NO_PROPERTIES
	0, 0,
	0, 0,
#endif // QT_NO_PROPERTIES
	0, 0 );
    cleanUp_NuovoGiocatore.setMetaObject( metaObj );
    return metaObj;
}

void* NuovoGiocatore::qt_cast( const char* clname )
{
    if ( !qstrcmp( clname, "NuovoGiocatore" ) )
	return this;
    return QDialog::qt_cast( clname );
}

bool NuovoGiocatore::qt_invoke( int _id, QUObject* _o )
{
    switch ( _id - staticMetaObject()->slotOffset() ) {
    case 0: enableCombo((int)static_QUType_int.get(_o+1)); break;
    case 1: accept(); break;
    case 2: setContrade((QStringList)(*((QStringList*)static_QUType_ptr.get(_o+1))),(vector<int>)(*((vector<int>*)static_QUType_ptr.get(_o+2)))); break;
    case 3: static_QUType_int.set(_o,assegnaContrada()); break;
    case 4: languageChange(); break;
    default:
	return QDialog::qt_invoke( _id, _o );
    }
    return TRUE;
}

bool NuovoGiocatore::qt_emit( int _id, QUObject* _o )
{
    return QDialog::qt_emit(_id,_o);
}
#ifndef QT_NO_PROPERTIES

bool NuovoGiocatore::qt_property( int id, int f, QVariant* v)
{
    return QDialog::qt_property( id, f, v);
}

bool NuovoGiocatore::qt_static_property( QObject* , int , int , QVariant* ){ return FALSE; }
#endif // QT_NO_PROPERTIES
