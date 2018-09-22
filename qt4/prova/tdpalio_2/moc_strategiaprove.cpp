/****************************************************************************
** StrategiaProve meta object code from reading C++ file 'strategiaprove.h'
**
** Created: Mon Jun 18 01:43:51 2007
**      by: The Qt MOC ($Id: qt/moc_yacc.cpp   3.3.7   edited Oct 19 16:22 $)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#undef QT_NO_COMPAT
#include "strategiaprove.h"
#include <qmetaobject.h>
#include <qapplication.h>

#include <private/qucomextra_p.h>
#if !defined(Q_MOC_OUTPUT_REVISION) || (Q_MOC_OUTPUT_REVISION != 26)
#error "This file was generated using the moc from 3.3.7. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

const char *StrategiaProve::className() const
{
    return "StrategiaProve";
}

QMetaObject *StrategiaProve::metaObj = 0;
static QMetaObjectCleanUp cleanUp_StrategiaProve( "StrategiaProve", &StrategiaProve::staticMetaObject );

#ifndef QT_NO_TRANSLATION
QString StrategiaProve::tr( const char *s, const char *c )
{
    if ( qApp )
	return qApp->translate( "StrategiaProve", s, c, QApplication::DefaultCodec );
    else
	return QString::fromLatin1( s );
}
#ifndef QT_NO_TRANSLATION_UTF8
QString StrategiaProve::trUtf8( const char *s, const char *c )
{
    if ( qApp )
	return qApp->translate( "StrategiaProve", s, c, QApplication::UnicodeUTF8 );
    else
	return QString::fromUtf8( s );
}
#endif // QT_NO_TRANSLATION_UTF8

#endif // QT_NO_TRANSLATION

QMetaObject* StrategiaProve::staticMetaObject()
{
    if ( metaObj )
	return metaObj;
    QMetaObject* parentObject = QDialog::staticMetaObject();
    static const QUParameter param_slot_0[] = {
	{ "fantini", &static_QUType_varptr, "\x04", QUParameter::In },
	{ "contrade", &static_QUType_varptr, "\x04", QUParameter::In },
	{ "contrada", &static_QUType_ptr, "Barbero", QUParameter::In },
	{ "status", &static_QUType_varptr, "\x10", QUParameter::In }
    };
    static const QUMethod slot_0 = {"FillCombo", 4, param_slot_0 };
    static const QUParameter param_slot_1[] = {
	{ "state", &static_QUType_int, 0, QUParameter::In }
    };
    static const QUMethod slot_1 = {"enableCombo1", 1, param_slot_1 };
    static const QUParameter param_slot_2[] = {
	{ "state", &static_QUType_int, 0, QUParameter::In }
    };
    static const QUMethod slot_2 = {"enableCombo2", 1, param_slot_2 };
    static const QUParameter param_slot_3[] = {
	{ "state", &static_QUType_int, 0, QUParameter::In }
    };
    static const QUMethod slot_3 = {"enableCombo3", 1, param_slot_3 };
    static const QUMethod slot_4 = {"languageChange", 0, 0 };
    static const QMetaData slot_tbl[] = {
	{ "FillCombo(QStringList,QStringList,Barbero*,int*)", &slot_0, QMetaData::Public },
	{ "enableCombo1(int)", &slot_1, QMetaData::Public },
	{ "enableCombo2(int)", &slot_2, QMetaData::Public },
	{ "enableCombo3(int)", &slot_3, QMetaData::Public },
	{ "languageChange()", &slot_4, QMetaData::Protected }
    };
    metaObj = QMetaObject::new_metaobject(
	"StrategiaProve", parentObject,
	slot_tbl, 5,
	0, 0,
#ifndef QT_NO_PROPERTIES
	0, 0,
	0, 0,
#endif // QT_NO_PROPERTIES
	0, 0 );
    cleanUp_StrategiaProve.setMetaObject( metaObj );
    return metaObj;
}

void* StrategiaProve::qt_cast( const char* clname )
{
    if ( !qstrcmp( clname, "StrategiaProve" ) )
	return this;
    return QDialog::qt_cast( clname );
}

bool StrategiaProve::qt_invoke( int _id, QUObject* _o )
{
    switch ( _id - staticMetaObject()->slotOffset() ) {
    case 0: FillCombo((QStringList)(*((QStringList*)static_QUType_ptr.get(_o+1))),(QStringList)(*((QStringList*)static_QUType_ptr.get(_o+2))),(Barbero*)static_QUType_ptr.get(_o+3),(int*)static_QUType_varptr.get(_o+4)); break;
    case 1: enableCombo1((int)static_QUType_int.get(_o+1)); break;
    case 2: enableCombo2((int)static_QUType_int.get(_o+1)); break;
    case 3: enableCombo3((int)static_QUType_int.get(_o+1)); break;
    case 4: languageChange(); break;
    default:
	return QDialog::qt_invoke( _id, _o );
    }
    return TRUE;
}

bool StrategiaProve::qt_emit( int _id, QUObject* _o )
{
    return QDialog::qt_emit(_id,_o);
}
#ifndef QT_NO_PROPERTIES

bool StrategiaProve::qt_property( int id, int f, QVariant* v)
{
    return QDialog::qt_property( id, f, v);
}

bool StrategiaProve::qt_static_property( QObject* , int , int , QVariant* ){ return FALSE; }
#endif // QT_NO_PROPERTIES
