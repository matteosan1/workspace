/****************************************************************************
** Form implementation generated from reading ui file 'messaggio.ui'
**
** Created: Sun Jun 17 16:56:01 2007
**      by: The User Interface Compiler ($Id: qt/main.cpp   3.3.7   edited Aug 31 2005 $)
**
** WARNING! All changes made in this file will be lost!
****************************************************************************/

#include "messaggio.h"

#include <qvariant.h>
#include <qpushbutton.h>
#include <qlabel.h>
#include <qheader.h>
#include <qlistview.h>
#include <qlayout.h>
#include <qtooltip.h>
#include <qwhatsthis.h>
#include <qimage.h>
#include <qpixmap.h>

#include "messaggio.ui.h"

/*
 *  Constructs a Messaggio as a child of 'parent', with the
 *  name 'name' and widget flags set to 'f'.
 *
 *  The dialog will by default be modeless, unless you set 'modal' to
 *  TRUE to construct a modal dialog.
 */
Messaggio::Messaggio( QWidget* parent, const char* name, bool modal, WFlags fl )
    : QDialog( parent, name, modal, fl )
{
    if ( !name )
	setName( "Messaggio" );
    setSizePolicy( QSizePolicy( (QSizePolicy::SizeType)5, (QSizePolicy::SizeType)5, 0, 0, sizePolicy().hasHeightForWidth() ) );
    setBaseSize( QSize( 500, 0 ) );
    MessaggioLayout = new QVBoxLayout( this, 11, 6, "MessaggioLayout"); 
    MessaggioLayout->setResizeMode( QLayout::Fixed );

    layout86 = new QVBoxLayout( 0, 0, 6, "layout86"); 

    layout84 = new QVBoxLayout( 0, 0, 6, "layout84"); 

    layout83 = new QHBoxLayout( 0, 0, 6, "layout83"); 
    spacer22 = new QSpacerItem( 130, 20, QSizePolicy::Expanding, QSizePolicy::Minimum );
    layout83->addItem( spacer22 );

    layout81 = new QVBoxLayout( 0, 0, 6, "layout81"); 

    contradaLabel = new QLabel( this, "contradaLabel" );
    contradaLabel->setSizePolicy( QSizePolicy( (QSizePolicy::SizeType)3, (QSizePolicy::SizeType)5, 0, 0, contradaLabel->sizePolicy().hasHeightForWidth() ) );
    QFont contradaLabel_font(  contradaLabel->font() );
    contradaLabel_font.setPointSize( 18 );
    contradaLabel->setFont( contradaLabel_font ); 
    contradaLabel->setAlignment( int( QLabel::AlignCenter ) );
    layout81->addWidget( contradaLabel );

    capitanoLabel = new QLabel( this, "capitanoLabel" );
    QFont capitanoLabel_font(  capitanoLabel->font() );
    capitanoLabel_font.setPointSize( 12 );
    capitanoLabel->setFont( capitanoLabel_font ); 
    capitanoLabel->setAlignment( int( QLabel::AlignCenter ) );
    layout81->addWidget( capitanoLabel );

    leggiButton = new QPushButton( this, "leggiButton" );
    leggiButton->setToggleButton( TRUE );
    layout81->addWidget( leggiButton );
    layout83->addLayout( layout81 );
    spacer22_2 = new QSpacerItem( 110, 20, QSizePolicy::Expanding, QSizePolicy::Minimum );
    layout83->addItem( spacer22_2 );
    layout84->addLayout( layout83 );

    messaggiList = new QListView( this, "messaggiList" );
    messaggiList->addColumn( tr( "Column 1" ) );
    layout84->addWidget( messaggiList );
    layout86->addLayout( layout84 );

    layout85 = new QHBoxLayout( 0, 0, 6, "layout85"); 
    spacer24 = new QSpacerItem( 40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum );
    layout85->addItem( spacer24 );

    okButton = new QPushButton( this, "okButton" );
    layout85->addWidget( okButton );
    spacer25 = new QSpacerItem( 40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum );
    layout85->addItem( spacer25 );
    layout86->addLayout( layout85 );
    MessaggioLayout->addLayout( layout86 );
    languageChange();
    resize( QSize(600, 475).expandedTo(minimumSizeHint()) );
    clearWState( WState_Polished );

    // signals and slots connections
    connect( okButton, SIGNAL( clicked() ), this, SLOT( accept() ) );
    connect( leggiButton, SIGNAL( toggled(bool) ), messaggiList, SLOT( setShown(bool) ) );
    connect( leggiButton, SIGNAL( toggled(bool) ), okButton, SLOT( setShown(bool) ) );
    init();
}

/*
 *  Destroys the object and frees any allocated resources
 */
Messaggio::~Messaggio()
{
    // no need to delete child widgets, Qt does it all for us
}

/*
 *  Sets the strings of the subwidgets using the current
 *  language.
 */
void Messaggio::languageChange()
{
    setCaption( tr( "Messaggio" ) );
    contradaLabel->setText( tr( "Contrada Sovrana dell'Istrice" ) );
    capitanoLabel->setText( tr( "textLabel5" ) );
    leggiButton->setText( tr( "Leggi messaggio" ) );
    messaggiList->header()->setLabel( 0, tr( "Column 1" ) );
    messaggiList->clear();
    QListViewItem * item = new QListViewItem( messaggiList, 0 );
    item->setText( 0, tr( "New Item" ) );

    okButton->setText( tr( "OK" ) );
}

