/****************************************************************************
** Form implementation generated from reading ui file 'prenotazioni.ui'
**
** Created: Fri May 4 20:39:10 2007
**      by: The User Interface Compiler ($Id: qt/main.cpp   3.3.7   edited Aug 31 2005 $)
**
** WARNING! All changes made in this file will be lost!
****************************************************************************/

#include "prenotazioni.h"

#include <qvariant.h>
#include <qpushbutton.h>
#include <qcombobox.h>
#include <qheader.h>
#include <qlistview.h>
#include <qlayout.h>
#include <qtooltip.h>
#include <qwhatsthis.h>
#include <qimage.h>
#include <qpixmap.h>

/*
 *  Constructs a prenotazioni as a child of 'parent', with the
 *  name 'name' and widget flags set to 'f'.
 *
 *  The dialog will by default be modeless, unless you set 'modal' to
 *  TRUE to construct a modal dialog.
 */
prenotazioni::prenotazioni( QWidget* parent, const char* name, bool modal, WFlags fl )
    : QDialog( parent, name, modal, fl )
{
    if ( !name )
	setName( "prenotazioni" );
    prenotazioniLayout = new QVBoxLayout( this, 11, 6, "prenotazioniLayout"); 

    layout10 = new QVBoxLayout( 0, 0, 6, "layout10"); 

    layout8 = new QHBoxLayout( 0, 0, 6, "layout8"); 
    spacer7 = new QSpacerItem( 40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum );
    layout8->addItem( spacer7 );

    comboData = new QComboBox( FALSE, this, "comboData" );
    layout8->addWidget( comboData );
    layout10->addLayout( layout8 );

    listPrenotazioni = new QListView( this, "listPrenotazioni" );
    listPrenotazioni->addColumn( tr( "Column 1" ) );
    listPrenotazioni->addColumn( tr( "New Column" ) );
    listPrenotazioni->header()->setResizeEnabled( FALSE, listPrenotazioni->header()->count() - 1 );
    listPrenotazioni->addColumn( tr( "New Column" ) );
    listPrenotazioni->header()->setResizeEnabled( FALSE, listPrenotazioni->header()->count() - 1 );
    layout10->addWidget( listPrenotazioni );

    layout9 = new QHBoxLayout( 0, 0, 6, "layout9"); 
    spacer9 = new QSpacerItem( 40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum );
    layout9->addItem( spacer9 );

    buttonO = new QPushButton( this, "buttonO" );
    layout9->addWidget( buttonO );
    spacer10 = new QSpacerItem( 40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum );
    layout9->addItem( spacer10 );

    buttonCancel = new QPushButton( this, "buttonCancel" );
    layout9->addWidget( buttonCancel );
    spacer11 = new QSpacerItem( 40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum );
    layout9->addItem( spacer11 );
    layout10->addLayout( layout9 );
    prenotazioniLayout->addLayout( layout10 );
    languageChange();
    resize( QSize(591, 480).expandedTo(minimumSizeHint()) );
    clearWState( WState_Polished );
}

/*
 *  Destroys the object and frees any allocated resources
 */
prenotazioni::~prenotazioni()
{
    // no need to delete child widgets, Qt does it all for us
}

/*
 *  Sets the strings of the subwidgets using the current
 *  language.
 */
void prenotazioni::languageChange()
{
    setCaption( tr( "Prenotazioni" ) );
    listPrenotazioni->header()->setLabel( 0, tr( "Column 1" ) );
    listPrenotazioni->header()->setLabel( 1, tr( "New Column" ) );
    listPrenotazioni->header()->setLabel( 2, tr( "New Column" ) );
    listPrenotazioni->clear();
    QListViewItem * item = new QListViewItem( listPrenotazioni, 0 );
    item->setText( 0, tr( "Item" ) );

    item = new QListViewItem( listPrenotazioni, item );
    item->setText( 0, tr( "New Item" ) );

    buttonO->setText( tr( "OK" ) );
    buttonCancel->setText( tr( "Cancel" ) );
}

