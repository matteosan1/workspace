/****************************************************************************
** Form implementation generated from reading ui file 'tratta.ui'
**
** Created: Sun Jun 17 16:57:43 2007
**      by: The User Interface Compiler ($Id: qt/main.cpp   3.3.7   edited Aug 31 2005 $)
**
** WARNING! All changes made in this file will be lost!
****************************************************************************/

#include "tratta.h"

#include <qvariant.h>
#include <qtable.h>
#include <qpushbutton.h>
#include <qlayout.h>
#include <qtooltip.h>
#include <qwhatsthis.h>
#include <qimage.h>
#include <qpixmap.h>

#include "tratta.ui.h"

/*
 *  Constructs a Tratta as a child of 'parent', with the
 *  name 'name' and widget flags set to 'f'.
 *
 *  The dialog will by default be modeless, unless you set 'modal' to
 *  TRUE to construct a modal dialog.
 */
Tratta::Tratta( QWidget* parent, const char* name, bool modal, WFlags fl )
    : QDialog( parent, name, modal, fl )
{
    if ( !name )
	setName( "Tratta" );
    TrattaLayout = new QVBoxLayout( this, 11, 6, "TrattaLayout"); 

    cavalliList = new QTable( this, "cavalliList" );
    cavalliList->setNumCols( cavalliList->numCols() + 1 );
    cavalliList->horizontalHeader()->setLabel( cavalliList->numCols() - 1, tr( "Cavallo" ) );
    cavalliList->setNumCols( cavalliList->numCols() + 1 );
    cavalliList->horizontalHeader()->setLabel( cavalliList->numCols() - 1, tr( "Corsi" ) );
    cavalliList->setNumCols( cavalliList->numCols() + 1 );
    cavalliList->horizontalHeader()->setLabel( cavalliList->numCols() - 1, tr( "Vinti" ) );
    cavalliList->setNumCols( cavalliList->numCols() + 1 );
    cavalliList->horizontalHeader()->setLabel( cavalliList->numCols() - 1, tr( "X" ) );
    cavalliList->setNumRows( cavalliList->numRows() + 1 );
    cavalliList->verticalHeader()->setLabel( cavalliList->numRows() - 1, tr( "0" ) );
    cavalliList->setNumRows( 1 );
    cavalliList->setNumCols( 4 );
    TrattaLayout->addWidget( cavalliList );

    layout7 = new QHBoxLayout( 0, 0, 6, "layout7"); 
    spacer7 = new QSpacerItem( 40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum );
    layout7->addItem( spacer7 );

    okButton = new QPushButton( this, "okButton" );
    okButton->setEnabled( TRUE );
    layout7->addWidget( okButton );
    spacer9 = new QSpacerItem( 40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum );
    layout7->addItem( spacer9 );
    TrattaLayout->addLayout( layout7 );
    languageChange();
    resize( QSize(259, 504).expandedTo(minimumSizeHint()) );
    clearWState( WState_Polished );

    // signals and slots connections
    connect( okButton, SIGNAL( clicked() ), this, SLOT( accept() ) );
    init();
}

/*
 *  Destroys the object and frees any allocated resources
 */
Tratta::~Tratta()
{
    // no need to delete child widgets, Qt does it all for us
}

/*
 *  Sets the strings of the subwidgets using the current
 *  language.
 */
void Tratta::languageChange()
{
    setCaption( tr( "Scelta Cavalli" ) );
    cavalliList->horizontalHeader()->setLabel( 0, tr( "Cavallo" ) );
    cavalliList->horizontalHeader()->setLabel( 1, tr( "Corsi" ) );
    cavalliList->horizontalHeader()->setLabel( 2, tr( "Vinti" ) );
    cavalliList->horizontalHeader()->setLabel( 3, tr( "X" ) );
    cavalliList->verticalHeader()->setLabel( 0, tr( "0" ) );
    okButton->setText( tr( "OK" ) );
}

