/****************************************************************************
** HelpBrowser meta object code from reading C++ file 'helpbrowser.h'
**
** Created: Sun Jun 17 16:57:44 2007
**      by: The Qt MOC ($Id: qt/moc_yacc.cpp   3.3.7   edited Oct 19 16:22 $)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#undef QT_NO_COMPAT
#include "helpbrowser.h"
#include <qmetaobject.h>
#include <qapplication.h>

#include <private/qucomextra_p.h>
#if !defined(Q_MOC_OUTPUT_REVISION) || (Q_MOC_OUTPUT_REVISION != 26)
#error "This file was generated using the moc from 3.3.7. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

const char *HelpBrowser::className() const
{
    return "HelpBrowser";
}

QMetaObject *HelpBrowser::metaObj = 0;
static QMetaObjectCleanUp cleanUp_HelpBrowser( "HelpBrowser", &HelpBrowser::staticMetaObject );

#ifndef QT_NO_TRANSLATION
QString HelpBrowser::tr( const char *s, const char *c )
{
    if ( qApp )
	return qApp->translate( "HelpBrowser", s, c, QApplication::DefaultCodec );
    else
	return QString::fromLatin1( s );
}
#ifndef QT_NO_TRANSLATION_UTF8
QString HelpBrowser::trUtf8( const char *s, const char *c )
{
    if ( qApp )
	return qApp->translate( "HelpBrowser", s, c, QApplication::UnicodeUTF8 );
    else
	return QString::fromUtf8( s );
}
#endif // QT_NO_TRANSLATION_UTF8

#endif // QT_NO_TRANSLATION

QMetaObject* HelpBrowser::staticMetaObject()
{
    if ( metaObj )
	return metaObj;
    QMetaObject* parentObject = QWidget::staticMetaObject();
    static const QUMethod slot_0 = {"updateCaption", 0, 0 };
    static const QMetaData slot_tbl[] = {
	{ "updateCaption()", &slot_0, QMetaData::Private }
    };
    metaObj = QMetaObject::new_metaobject(
	"HelpBrowser", parentObject,
	slot_tbl, 1,
	0, 0,
#ifndef QT_NO_PROPERTIES
	0, 0,
	0, 0,
#endif // QT_NO_PROPERTIES
	0, 0 );
    cleanUp_HelpBrowser.setMetaObject( metaObj );
    return metaObj;
}

void* HelpBrowser::qt_cast( const char* clname )
{
    if ( !qstrcmp( clname, "HelpBrowser" ) )
	return this;
    return QWidget::qt_cast( clname );
}

bool HelpBrowser::qt_invoke( int _id, QUObject* _o )
{
    switch ( _id - staticMetaObject()->slotOffset() ) {
    case 0: updateCaption(); break;
    default:
	return QWidget::qt_invoke( _id, _o );
    }
    return TRUE;
}

bool HelpBrowser::qt_emit( int _id, QUObject* _o )
{
    return QWidget::qt_emit(_id,_o);
}
#ifndef QT_NO_PROPERTIES

bool HelpBrowser::qt_property( int id, int f, QVariant* v)
{
    return QWidget::qt_property( id, f, v);
}

bool HelpBrowser::qt_static_property( QObject* , int , int , QVariant* ){ return FALSE; }
#endif // QT_NO_PROPERTIES
