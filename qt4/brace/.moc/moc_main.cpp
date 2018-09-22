/****************************************************************************
** Form1 meta object code from reading C++ file 'main.h'
**
** Created: Fri May 4 20:39:13 2007
**      by: The Qt MOC ($Id: qt/moc_yacc.cpp   3.3.7   edited Oct 19 16:22 $)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#undef QT_NO_COMPAT
#include "../.ui/main.h"
#include <qmetaobject.h>
#include <qapplication.h>

#include <private/qucomextra_p.h>
#if !defined(Q_MOC_OUTPUT_REVISION) || (Q_MOC_OUTPUT_REVISION != 26)
#error "This file was generated using the moc from 3.3.7. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

const char *Form1::className() const
{
    return "Form1";
}

QMetaObject *Form1::metaObj = 0;
static QMetaObjectCleanUp cleanUp_Form1( "Form1", &Form1::staticMetaObject );

#ifndef QT_NO_TRANSLATION
QString Form1::tr( const char *s, const char *c )
{
    if ( qApp )
	return qApp->translate( "Form1", s, c, QApplication::DefaultCodec );
    else
	return QString::fromLatin1( s );
}
#ifndef QT_NO_TRANSLATION_UTF8
QString Form1::trUtf8( const char *s, const char *c )
{
    if ( qApp )
	return qApp->translate( "Form1", s, c, QApplication::UnicodeUTF8 );
    else
	return QString::fromUtf8( s );
}
#endif // QT_NO_TRANSLATION_UTF8

#endif // QT_NO_TRANSLATION

QMetaObject* Form1::staticMetaObject()
{
    if ( metaObj )
	return metaObj;
    QMetaObject* parentObject = QMainWindow::staticMetaObject();
    static const QUMethod slot_0 = {"fileNew", 0, 0 };
    static const QUMethod slot_1 = {"fileOpen", 0, 0 };
    static const QUMethod slot_2 = {"fileSave", 0, 0 };
    static const QUMethod slot_3 = {"fileSaveAs", 0, 0 };
    static const QUMethod slot_4 = {"filePrint", 0, 0 };
    static const QUMethod slot_5 = {"fileExit", 0, 0 };
    static const QUMethod slot_6 = {"editUndo", 0, 0 };
    static const QUMethod slot_7 = {"editRedo", 0, 0 };
    static const QUMethod slot_8 = {"editCut", 0, 0 };
    static const QUMethod slot_9 = {"editCopy", 0, 0 };
    static const QUMethod slot_10 = {"editPaste", 0, 0 };
    static const QUMethod slot_11 = {"editFind", 0, 0 };
    static const QUMethod slot_12 = {"helpIndex", 0, 0 };
    static const QUMethod slot_13 = {"helpContents", 0, 0 };
    static const QUMethod slot_14 = {"helpAbout", 0, 0 };
    static const QUMethod slot_15 = {"languageChange", 0, 0 };
    static const QMetaData slot_tbl[] = {
	{ "fileNew()", &slot_0, QMetaData::Public },
	{ "fileOpen()", &slot_1, QMetaData::Public },
	{ "fileSave()", &slot_2, QMetaData::Public },
	{ "fileSaveAs()", &slot_3, QMetaData::Public },
	{ "filePrint()", &slot_4, QMetaData::Public },
	{ "fileExit()", &slot_5, QMetaData::Public },
	{ "editUndo()", &slot_6, QMetaData::Public },
	{ "editRedo()", &slot_7, QMetaData::Public },
	{ "editCut()", &slot_8, QMetaData::Public },
	{ "editCopy()", &slot_9, QMetaData::Public },
	{ "editPaste()", &slot_10, QMetaData::Public },
	{ "editFind()", &slot_11, QMetaData::Public },
	{ "helpIndex()", &slot_12, QMetaData::Public },
	{ "helpContents()", &slot_13, QMetaData::Public },
	{ "helpAbout()", &slot_14, QMetaData::Public },
	{ "languageChange()", &slot_15, QMetaData::Protected }
    };
    metaObj = QMetaObject::new_metaobject(
	"Form1", parentObject,
	slot_tbl, 16,
	0, 0,
#ifndef QT_NO_PROPERTIES
	0, 0,
	0, 0,
#endif // QT_NO_PROPERTIES
	0, 0 );
    cleanUp_Form1.setMetaObject( metaObj );
    return metaObj;
}

void* Form1::qt_cast( const char* clname )
{
    if ( !qstrcmp( clname, "Form1" ) )
	return this;
    return QMainWindow::qt_cast( clname );
}

bool Form1::qt_invoke( int _id, QUObject* _o )
{
    switch ( _id - staticMetaObject()->slotOffset() ) {
    case 0: fileNew(); break;
    case 1: fileOpen(); break;
    case 2: fileSave(); break;
    case 3: fileSaveAs(); break;
    case 4: filePrint(); break;
    case 5: fileExit(); break;
    case 6: editUndo(); break;
    case 7: editRedo(); break;
    case 8: editCut(); break;
    case 9: editCopy(); break;
    case 10: editPaste(); break;
    case 11: editFind(); break;
    case 12: helpIndex(); break;
    case 13: helpContents(); break;
    case 14: helpAbout(); break;
    case 15: languageChange(); break;
    default:
	return QMainWindow::qt_invoke( _id, _o );
    }
    return TRUE;
}

bool Form1::qt_emit( int _id, QUObject* _o )
{
    return QMainWindow::qt_emit(_id,_o);
}
#ifndef QT_NO_PROPERTIES

bool Form1::qt_property( int id, int f, QVariant* v)
{
    return QMainWindow::qt_property( id, f, v);
}

bool Form1::qt_static_property( QObject* , int , int , QVariant* ){ return FALSE; }
#endif // QT_NO_PROPERTIES
