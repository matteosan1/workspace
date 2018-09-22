/****************************************************************************
** Tratta meta object code from reading C++ file 'tratta.h'
**
** Created: Sun Jun 17 16:57:48 2007
**      by: The Qt MOC ($Id: qt/moc_yacc.cpp   3.3.7   edited Oct 19 16:22 $)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#undef QT_NO_COMPAT
#include "tratta.h"
#include <qmetaobject.h>
#include <qapplication.h>

#include <private/qucomextra_p.h>
#if !defined(Q_MOC_OUTPUT_REVISION) || (Q_MOC_OUTPUT_REVISION != 26)
#error "This file was generated using the moc from 3.3.7. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

const char *Tratta::className() const
{
    return "Tratta";
}

QMetaObject *Tratta::metaObj = 0;
static QMetaObjectCleanUp cleanUp_Tratta( "Tratta", &Tratta::staticMetaObject );

#ifndef QT_NO_TRANSLATION
QString Tratta::tr( const char *s, const char *c )
{
    if ( qApp )
	return qApp->translate( "Tratta", s, c, QApplication::DefaultCodec );
    else
	return QString::fromLatin1( s );
}
#ifndef QT_NO_TRANSLATION_UTF8
QString Tratta::trUtf8( const char *s, const char *c )
{
    if ( qApp )
	return qApp->translate( "Tratta", s, c, QApplication::UnicodeUTF8 );
    else
	return QString::fromUtf8( s );
}
#endif // QT_NO_TRANSLATION_UTF8

#endif // QT_NO_TRANSLATION

QMetaObject* Tratta::staticMetaObject()
{
    if ( metaObj )
	return metaObj;
    QMetaObject* parentObject = QDialog::staticMetaObject();
    static const QUParameter param_slot_0[] = {
	{ "nomi", &static_QUType_varptr, "\x04", QUParameter::In },
	{ "corsi", &static_QUType_varptr, "\x04", QUParameter::In },
	{ "vinti", &static_QUType_varptr, "\x04", QUParameter::In },
	{ "l", &static_QUType_int, 0, QUParameter::In }
    };
    static const QUMethod slot_0 = {"riempiLista", 4, param_slot_0 };
    static const QUMethod slot_1 = {"accept", 0, 0 };
    static const QUParameter param_slot_2[] = {
	{ "s", &static_QUType_QString, 0, QUParameter::In }
    };
    static const QUMethod slot_2 = {"cambiaCaption", 1, param_slot_2 };
    static const QUMethod slot_3 = {"languageChange", 0, 0 };
    static const QMetaData slot_tbl[] = {
	{ "riempiLista(QStringList,QStringList,QStringList,int)", &slot_0, QMetaData::Public },
	{ "accept()", &slot_1, QMetaData::Public },
	{ "cambiaCaption(QString)", &slot_2, QMetaData::Public },
	{ "languageChange()", &slot_3, QMetaData::Protected }
    };
    metaObj = QMetaObject::new_metaobject(
	"Tratta", parentObject,
	slot_tbl, 4,
	0, 0,
#ifndef QT_NO_PROPERTIES
	0, 0,
	0, 0,
#endif // QT_NO_PROPERTIES
	0, 0 );
    cleanUp_Tratta.setMetaObject( metaObj );
    return metaObj;
}

void* Tratta::qt_cast( const char* clname )
{
    if ( !qstrcmp( clname, "Tratta" ) )
	return this;
    return QDialog::qt_cast( clname );
}

bool Tratta::qt_invoke( int _id, QUObject* _o )
{
    switch ( _id - staticMetaObject()->slotOffset() ) {
    case 0: riempiLista((QStringList)(*((QStringList*)static_QUType_ptr.get(_o+1))),(QStringList)(*((QStringList*)static_QUType_ptr.get(_o+2))),(QStringList)(*((QStringList*)static_QUType_ptr.get(_o+3))),(int)static_QUType_int.get(_o+4)); break;
    case 1: accept(); break;
    case 2: cambiaCaption((QString)static_QUType_QString.get(_o+1)); break;
    case 3: languageChange(); break;
    default:
	return QDialog::qt_invoke( _id, _o );
    }
    return TRUE;
}

bool Tratta::qt_emit( int _id, QUObject* _o )
{
    return QDialog::qt_emit(_id,_o);
}
#ifndef QT_NO_PROPERTIES

bool Tratta::qt_property( int id, int f, QVariant* v)
{
    return QDialog::qt_property( id, f, v);
}

bool Tratta::qt_static_property( QObject* , int , int , QVariant* ){ return FALSE; }
#endif // QT_NO_PROPERTIES
