/****************************************************************************
** Messaggio meta object code from reading C++ file 'messaggio.h'
**
** Created: Sun Jun 17 16:57:44 2007
**      by: The Qt MOC ($Id: qt/moc_yacc.cpp   3.3.7   edited Oct 19 16:22 $)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#undef QT_NO_COMPAT
#include "messaggio.h"
#include <qmetaobject.h>
#include <qapplication.h>

#include <private/qucomextra_p.h>
#if !defined(Q_MOC_OUTPUT_REVISION) || (Q_MOC_OUTPUT_REVISION != 26)
#error "This file was generated using the moc from 3.3.7. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

const char *Messaggio::className() const
{
    return "Messaggio";
}

QMetaObject *Messaggio::metaObj = 0;
static QMetaObjectCleanUp cleanUp_Messaggio( "Messaggio", &Messaggio::staticMetaObject );

#ifndef QT_NO_TRANSLATION
QString Messaggio::tr( const char *s, const char *c )
{
    if ( qApp )
	return qApp->translate( "Messaggio", s, c, QApplication::DefaultCodec );
    else
	return QString::fromLatin1( s );
}
#ifndef QT_NO_TRANSLATION_UTF8
QString Messaggio::trUtf8( const char *s, const char *c )
{
    if ( qApp )
	return qApp->translate( "Messaggio", s, c, QApplication::UnicodeUTF8 );
    else
	return QString::fromUtf8( s );
}
#endif // QT_NO_TRANSLATION_UTF8

#endif // QT_NO_TRANSLATION

QMetaObject* Messaggio::staticMetaObject()
{
    if ( metaObj )
	return metaObj;
    QMetaObject* parentObject = QDialog::staticMetaObject();
    static const QUParameter param_slot_0[] = {
	{ "mex", &static_QUType_QString, 0, QUParameter::In },
	{ "check", &static_QUType_bool, 0, QUParameter::In }
    };
    static const QUMethod slot_0 = {"InserisciMessaggio", 2, param_slot_0 };
    static const QUMethod slot_1 = {"languageChange", 0, 0 };
    static const QMetaData slot_tbl[] = {
	{ "InserisciMessaggio(QString,bool)", &slot_0, QMetaData::Public },
	{ "languageChange()", &slot_1, QMetaData::Protected }
    };
    metaObj = QMetaObject::new_metaobject(
	"Messaggio", parentObject,
	slot_tbl, 2,
	0, 0,
#ifndef QT_NO_PROPERTIES
	0, 0,
	0, 0,
#endif // QT_NO_PROPERTIES
	0, 0 );
    cleanUp_Messaggio.setMetaObject( metaObj );
    return metaObj;
}

void* Messaggio::qt_cast( const char* clname )
{
    if ( !qstrcmp( clname, "Messaggio" ) )
	return this;
    return QDialog::qt_cast( clname );
}

bool Messaggio::qt_invoke( int _id, QUObject* _o )
{
    switch ( _id - staticMetaObject()->slotOffset() ) {
    case 0: InserisciMessaggio((QString)static_QUType_QString.get(_o+1),(bool)static_QUType_bool.get(_o+2)); break;
    case 1: languageChange(); break;
    default:
	return QDialog::qt_invoke( _id, _o );
    }
    return TRUE;
}

bool Messaggio::qt_emit( int _id, QUObject* _o )
{
    return QDialog::qt_emit(_id,_o);
}
#ifndef QT_NO_PROPERTIES

bool Messaggio::qt_property( int id, int f, QVariant* v)
{
    return QDialog::qt_property( id, f, v);
}

bool Messaggio::qt_static_property( QObject* , int , int , QVariant* ){ return FALSE; }
#endif // QT_NO_PROPERTIES
