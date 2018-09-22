/****************************************************************************
** Form implementation generated from reading ui file 'main.ui'
**
** Created: Fri May 4 20:39:05 2007
**      by: The User Interface Compiler ($Id: qt/main.cpp   3.3.7   edited Aug 31 2005 $)
**
** WARNING! All changes made in this file will be lost!
****************************************************************************/

#include "main.h"

#include <qvariant.h>
#include <qlayout.h>
#include <qtooltip.h>
#include <qwhatsthis.h>
#include <qaction.h>
#include <qmenubar.h>
#include <qpopupmenu.h>
#include <qtoolbar.h>
#include <qimage.h>
#include <qpixmap.h>

/*
 *  Constructs a Form1 as a child of 'parent', with the
 *  name 'name' and widget flags set to 'f'.
 *
 */
Form1::Form1( QWidget* parent, const char* name, WFlags fl )
    : QMainWindow( parent, name, fl )
{
    (void)statusBar();
    if ( !name )
	setName( "Form1" );

    // actions
    fileNewAction = new QAction( this, "fileNewAction" );
    fileNewAction->setIconSet( QIconSet( QPixmap::fromMimeSource( "filenew" ) ) );
    fileOpenAction = new QAction( this, "fileOpenAction" );
    fileOpenAction->setIconSet( QIconSet( QPixmap::fromMimeSource( "fileopen" ) ) );
    fileSaveAction = new QAction( this, "fileSaveAction" );
    fileSaveAction->setIconSet( QIconSet( QPixmap::fromMimeSource( "filesave" ) ) );
    fileSaveAsAction = new QAction( this, "fileSaveAsAction" );
    filePrintAction = new QAction( this, "filePrintAction" );
    filePrintAction->setIconSet( QIconSet( QPixmap::fromMimeSource( "print" ) ) );
    fileExitAction = new QAction( this, "fileExitAction" );
    editUndoAction = new QAction( this, "editUndoAction" );
    editUndoAction->setIconSet( QIconSet( QPixmap::fromMimeSource( "undo" ) ) );
    editRedoAction = new QAction( this, "editRedoAction" );
    editRedoAction->setIconSet( QIconSet( QPixmap::fromMimeSource( "redo" ) ) );
    editCutAction = new QAction( this, "editCutAction" );
    editCutAction->setIconSet( QIconSet( QPixmap::fromMimeSource( "editcut" ) ) );
    editCopyAction = new QAction( this, "editCopyAction" );
    editCopyAction->setIconSet( QIconSet( QPixmap::fromMimeSource( "editcopy" ) ) );
    editPasteAction = new QAction( this, "editPasteAction" );
    editPasteAction->setIconSet( QIconSet( QPixmap::fromMimeSource( "editpaste" ) ) );
    editFindAction = new QAction( this, "editFindAction" );
    editFindAction->setIconSet( QIconSet( QPixmap::fromMimeSource( "searchfind" ) ) );
    helpContentsAction = new QAction( this, "helpContentsAction" );
    helpIndexAction = new QAction( this, "helpIndexAction" );
    helpAboutAction = new QAction( this, "helpAboutAction" );


    // toolbars
    toolBar = new QToolBar( QString(""), this, DockTop ); 

    fileNewAction->addTo( toolBar );
    fileOpenAction->addTo( toolBar );
    fileSaveAction->addTo( toolBar );
    fileSaveAsAction->addTo( toolBar );
    filePrintAction->addTo( toolBar );
    fileExitAction->addTo( toolBar );
    editUndoAction->addTo( toolBar );


    // menubar
    MenuBar = new QMenuBar( this, "MenuBar" );


    fileMenu = new QPopupMenu( this );
    fileNewAction->addTo( fileMenu );
    fileOpenAction->addTo( fileMenu );
    fileSaveAction->addTo( fileMenu );
    fileSaveAsAction->addTo( fileMenu );
    fileMenu->insertSeparator();
    filePrintAction->addTo( fileMenu );
    fileMenu->insertSeparator();
    fileExitAction->addTo( fileMenu );
    MenuBar->insertItem( QString(""), fileMenu, 1 );

    editMenu = new QPopupMenu( this );
    editUndoAction->addTo( editMenu );
    editRedoAction->addTo( editMenu );
    editMenu->insertSeparator();
    editCutAction->addTo( editMenu );
    editCopyAction->addTo( editMenu );
    editPasteAction->addTo( editMenu );
    editMenu->insertSeparator();
    editFindAction->addTo( editMenu );
    MenuBar->insertItem( QString(""), editMenu, 2 );

    helpMenu = new QPopupMenu( this );
    helpContentsAction->addTo( helpMenu );
    helpIndexAction->addTo( helpMenu );
    helpMenu->insertSeparator();
    helpAboutAction->addTo( helpMenu );
    MenuBar->insertItem( QString(""), helpMenu, 3 );

    languageChange();
    resize( QSize(600, 480).expandedTo(minimumSizeHint()) );
    clearWState( WState_Polished );

    // signals and slots connections
    connect( fileNewAction, SIGNAL( activated() ), this, SLOT( fileNew() ) );
    connect( fileOpenAction, SIGNAL( activated() ), this, SLOT( fileOpen() ) );
    connect( fileSaveAction, SIGNAL( activated() ), this, SLOT( fileSave() ) );
    connect( fileSaveAsAction, SIGNAL( activated() ), this, SLOT( fileSaveAs() ) );
    connect( filePrintAction, SIGNAL( activated() ), this, SLOT( filePrint() ) );
    connect( fileExitAction, SIGNAL( activated() ), this, SLOT( fileExit() ) );
    connect( editUndoAction, SIGNAL( activated() ), this, SLOT( editUndo() ) );
    connect( editRedoAction, SIGNAL( activated() ), this, SLOT( editRedo() ) );
    connect( editCutAction, SIGNAL( activated() ), this, SLOT( editCut() ) );
    connect( editCopyAction, SIGNAL( activated() ), this, SLOT( editCopy() ) );
    connect( editPasteAction, SIGNAL( activated() ), this, SLOT( editPaste() ) );
    connect( editFindAction, SIGNAL( activated() ), this, SLOT( editFind() ) );
    connect( helpIndexAction, SIGNAL( activated() ), this, SLOT( helpIndex() ) );
    connect( helpContentsAction, SIGNAL( activated() ), this, SLOT( helpContents() ) );
    connect( helpAboutAction, SIGNAL( activated() ), this, SLOT( helpAbout() ) );
}

/*
 *  Destroys the object and frees any allocated resources
 */
Form1::~Form1()
{
    // no need to delete child widgets, Qt does it all for us
}

/*
 *  Sets the strings of the subwidgets using the current
 *  language.
 */
void Form1::languageChange()
{
    setCaption( tr( "Form1" ) );
    fileNewAction->setText( tr( "New" ) );
    fileNewAction->setMenuText( tr( "&New" ) );
    fileNewAction->setAccel( tr( "Ctrl+N" ) );
    fileOpenAction->setText( tr( "Open" ) );
    fileOpenAction->setMenuText( tr( "&Open..." ) );
    fileOpenAction->setAccel( tr( "Ctrl+O" ) );
    fileSaveAction->setText( tr( "Save" ) );
    fileSaveAction->setMenuText( tr( "&Save" ) );
    fileSaveAction->setAccel( tr( "Ctrl+S" ) );
    fileSaveAsAction->setText( tr( "Save As" ) );
    fileSaveAsAction->setMenuText( tr( "Save &As..." ) );
    fileSaveAsAction->setAccel( QString::null );
    filePrintAction->setText( tr( "Print" ) );
    filePrintAction->setMenuText( tr( "&Print..." ) );
    filePrintAction->setAccel( tr( "Ctrl+P" ) );
    fileExitAction->setText( tr( "Exit" ) );
    fileExitAction->setMenuText( tr( "E&xit" ) );
    fileExitAction->setAccel( QString::null );
    editUndoAction->setText( tr( "Undo" ) );
    editUndoAction->setMenuText( tr( "&Undo" ) );
    editUndoAction->setAccel( tr( "Ctrl+Z" ) );
    editRedoAction->setText( tr( "Redo" ) );
    editRedoAction->setMenuText( tr( "&Redo" ) );
    editRedoAction->setAccel( tr( "Ctrl+Y" ) );
    editCutAction->setText( tr( "Cut" ) );
    editCutAction->setMenuText( tr( "Cu&t" ) );
    editCutAction->setAccel( tr( "Ctrl+X" ) );
    editCopyAction->setText( tr( "Copy" ) );
    editCopyAction->setMenuText( tr( "&Copy" ) );
    editCopyAction->setAccel( tr( "Ctrl+C" ) );
    editPasteAction->setText( tr( "Paste" ) );
    editPasteAction->setMenuText( tr( "&Paste" ) );
    editPasteAction->setAccel( tr( "Ctrl+V" ) );
    editFindAction->setText( tr( "Find" ) );
    editFindAction->setMenuText( tr( "&Find..." ) );
    editFindAction->setAccel( tr( "Ctrl+F" ) );
    helpContentsAction->setText( tr( "Contents" ) );
    helpContentsAction->setMenuText( tr( "&Contents..." ) );
    helpContentsAction->setAccel( QString::null );
    helpIndexAction->setText( tr( "Index" ) );
    helpIndexAction->setMenuText( tr( "&Index..." ) );
    helpIndexAction->setAccel( QString::null );
    helpAboutAction->setText( tr( "About" ) );
    helpAboutAction->setMenuText( tr( "&About" ) );
    helpAboutAction->setAccel( QString::null );
    toolBar->setLabel( tr( "Tools" ) );
    if (MenuBar->findItem(1))
        MenuBar->findItem(1)->setText( tr( "&File" ) );
    if (MenuBar->findItem(2))
        MenuBar->findItem(2)->setText( tr( "&Edit" ) );
    if (MenuBar->findItem(3))
        MenuBar->findItem(3)->setText( tr( "&Help" ) );
}

void Form1::fileNew()
{
    qWarning( "Form1::fileNew(): Not implemented yet" );
}

void Form1::fileOpen()
{
    qWarning( "Form1::fileOpen(): Not implemented yet" );
}

void Form1::fileSave()
{
    qWarning( "Form1::fileSave(): Not implemented yet" );
}

void Form1::fileSaveAs()
{
    qWarning( "Form1::fileSaveAs(): Not implemented yet" );
}

void Form1::filePrint()
{
    qWarning( "Form1::filePrint(): Not implemented yet" );
}

void Form1::fileExit()
{
    qWarning( "Form1::fileExit(): Not implemented yet" );
}

void Form1::editUndo()
{
    qWarning( "Form1::editUndo(): Not implemented yet" );
}

void Form1::editRedo()
{
    qWarning( "Form1::editRedo(): Not implemented yet" );
}

void Form1::editCut()
{
    qWarning( "Form1::editCut(): Not implemented yet" );
}

void Form1::editCopy()
{
    qWarning( "Form1::editCopy(): Not implemented yet" );
}

void Form1::editPaste()
{
    qWarning( "Form1::editPaste(): Not implemented yet" );
}

void Form1::editFind()
{
    qWarning( "Form1::editFind(): Not implemented yet" );
}

void Form1::helpIndex()
{
    qWarning( "Form1::helpIndex(): Not implemented yet" );
}

void Form1::helpContents()
{
    qWarning( "Form1::helpContents(): Not implemented yet" );
}

void Form1::helpAbout()
{
    qWarning( "Form1::helpAbout(): Not implemented yet" );
}

