/****************************************************************************
** Form implementation generated from reading ui file 'braciere.ui'
**
** Created: Fri May 4 20:39:11 2007
**      by: The User Interface Compiler ($Id: qt/main.cpp   3.3.7   edited Aug 31 2005 $)
**
** WARNING! All changes made in this file will be lost!
****************************************************************************/

#include "braciere.h"

#include <qvariant.h>
#include <qpushbutton.h>
#include <qlabel.h>
#include <qlineedit.h>
#include <qdatetimeedit.h>
#include <qlayout.h>
#include <qtooltip.h>
#include <qwhatsthis.h>
#include <qimage.h>
#include <qpixmap.h>

/*
 *  Constructs a braciere as a child of 'parent', with the
 *  name 'name' and widget flags set to 'f'.
 *
 *  The dialog will by default be modeless, unless you set 'modal' to
 *  TRUE to construct a modal dialog.
 */
braciere::braciere( QWidget* parent, const char* name, bool modal, WFlags fl )
    : QDialog( parent, name, modal, fl )
{
    if ( !name )
	setName( "braciere" );
    braciereLayout = new QHBoxLayout( this, 11, 6, "braciereLayout"); 

    layout14 = new QVBoxLayout( 0, 0, 6, "layout14"); 

    layout13 = new QHBoxLayout( 0, 0, 6, "layout13"); 

    labelNome = new QLabel( this, "labelNome" );
    layout13->addWidget( labelNome );
    spacer18 = new QSpacerItem( 40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum );
    layout13->addItem( spacer18 );

    editNome = new QLineEdit( this, "editNome" );
    layout13->addWidget( editNome );
    layout14->addLayout( layout13 );
    spacer17 = new QSpacerItem( 20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding );
    layout14->addItem( spacer17 );

    layout12 = new QHBoxLayout( 0, 0, 6, "layout12"); 

    labelInizio = new QLabel( this, "labelInizio" );
    layout12->addWidget( labelInizio );

    dateInizio = new QDateEdit( this, "dateInizio" );
    dateInizio->setDate( QDate( 2000, 1, 1 ) );
    dateInizio->setAutoAdvance( FALSE );
    layout12->addWidget( dateInizio );
    spacer16 = new QSpacerItem( 40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum );
    layout12->addItem( spacer16 );

    labelFine = new QLabel( this, "labelFine" );
    layout12->addWidget( labelFine );

    dateFine = new QDateEdit( this, "dateFine" );
    layout12->addWidget( dateFine );
    layout14->addLayout( layout12 );
    spacer19 = new QSpacerItem( 20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding );
    layout14->addItem( spacer19 );

    layout11 = new QHBoxLayout( 0, 0, 6, "layout11"); 
    spacer14 = new QSpacerItem( 40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum );
    layout11->addItem( spacer14 );

    buttonOK = new QPushButton( this, "buttonOK" );
    layout11->addWidget( buttonOK );
    spacer13 = new QSpacerItem( 40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum );
    layout11->addItem( spacer13 );

    buttonCancel = new QPushButton( this, "buttonCancel" );
    layout11->addWidget( buttonCancel );
    spacer15 = new QSpacerItem( 40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum );
    layout11->addItem( spacer15 );
    layout14->addLayout( layout11 );
    braciereLayout->addLayout( layout14 );
    languageChange();
    resize( QSize(351, 195).expandedTo(minimumSizeHint()) );
    clearWState( WState_Polished );
}

/*
 *  Destroys the object and frees any allocated resources
 */
braciere::~braciere()
{
    // no need to delete child widgets, Qt does it all for us
}

/*
 *  Sets the strings of the subwidgets using the current
 *  language.
 */
void braciere::languageChange()
{
    setCaption( tr( "Braciere" ) );
    labelNome->setText( tr( "Nome Bracierer" ) );
    labelInizio->setText( tr( "Data Inizio" ) );
    labelFine->setText( tr( "Data Fine" ) );
    buttonOK->setText( tr( "OK" ) );
    buttonCancel->setText( tr( "Cancel" ) );
}

