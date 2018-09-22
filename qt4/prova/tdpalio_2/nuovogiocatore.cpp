/****************************************************************************
** Form implementation generated from reading ui file 'nuovogiocatore.ui'
**
** Created: Sun Jun 17 16:56:02 2007
**      by: The User Interface Compiler ($Id: qt/main.cpp   3.3.7   edited Aug 31 2005 $)
**
** WARNING! All changes made in this file will be lost!
****************************************************************************/

#include "nuovogiocatore.h"

#include <qvariant.h>
#include <qpushbutton.h>
#include <qlabel.h>
#include <qlineedit.h>
#include <qcheckbox.h>
#include <qcombobox.h>
#include <qlayout.h>
#include <qtooltip.h>
#include <qwhatsthis.h>
#include "nuovogiocatore.ui.h"

/*
 *  Constructs a NuovoGiocatore as a child of 'parent', with the
 *  name 'name' and widget flags set to 'f'.
 *
 *  The dialog will by default be modeless, unless you set 'modal' to
 *  TRUE to construct a modal dialog.
 */
NuovoGiocatore::NuovoGiocatore( QWidget* parent, const char* name, bool modal, WFlags fl )
    : QDialog( parent, name, modal, fl )
{
    if ( !name )
	setName( "NuovoGiocatore" );
    NuovoGiocatoreLayout = new QVBoxLayout( this, 11, 6, "NuovoGiocatoreLayout"); 

    layout6 = new QVBoxLayout( 0, 0, 6, "layout6"); 

    layout3 = new QHBoxLayout( 0, 0, 6, "layout3"); 

    layout1 = new QGridLayout( 0, 1, 1, 0, 6, "layout1"); 

    cognomeLabel = new QLabel( this, "cognomeLabel" );

    layout1->addWidget( cognomeLabel, 1, 0 );

    nomeLabel = new QLabel( this, "nomeLabel" );

    layout1->addWidget( nomeLabel, 0, 0 );

    nomeEdit = new QLineEdit( this, "nomeEdit" );

    layout1->addWidget( nomeEdit, 0, 1 );

    cognomeEdit = new QLineEdit( this, "cognomeEdit" );

    layout1->addWidget( cognomeEdit, 1, 1 );
    layout3->addLayout( layout1 );
    spacer6 = new QSpacerItem( 40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum );
    layout3->addItem( spacer6 );

    layout2 = new QVBoxLayout( 0, 0, 6, "layout2"); 

    randomCheck = new QCheckBox( this, "randomCheck" );
    layout2->addWidget( randomCheck );

    contradaCombo = new QComboBox( FALSE, this, "contradaCombo" );
    layout2->addWidget( contradaCombo );
    layout3->addLayout( layout2 );
    layout6->addLayout( layout3 );
    spacer5 = new QSpacerItem( 20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding );
    layout6->addItem( spacer5 );

    layout4 = new QHBoxLayout( 0, 0, 6, "layout4"); 
    spacer1 = new QSpacerItem( 40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum );
    layout4->addItem( spacer1 );

    okButton = new QPushButton( this, "okButton" );
    layout4->addWidget( okButton );
    spacer3 = new QSpacerItem( 40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum );
    layout4->addItem( spacer3 );

    cancellaButton = new QPushButton( this, "cancellaButton" );
    layout4->addWidget( cancellaButton );
    spacer4 = new QSpacerItem( 40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum );
    layout4->addItem( spacer4 );
    layout6->addLayout( layout4 );
    NuovoGiocatoreLayout->addLayout( layout6 );
    languageChange();
    resize( QSize(432, 183).expandedTo(minimumSizeHint()) );
    clearWState( WState_Polished );

    // signals and slots connections
    connect( cancellaButton, SIGNAL( clicked() ), this, SLOT( reject() ) );
    connect( randomCheck, SIGNAL( stateChanged(int) ), this, SLOT( enableCombo(int) ) );
    connect( okButton, SIGNAL( clicked() ), this, SLOT( accept() ) );
}

/*
 *  Destroys the object and frees any allocated resources
 */
NuovoGiocatore::~NuovoGiocatore()
{
    // no need to delete child widgets, Qt does it all for us
}

/*
 *  Sets the strings of the subwidgets using the current
 *  language.
 */
void NuovoGiocatore::languageChange()
{
    setCaption( tr( "Nuovo Giocatore" ) );
    cognomeLabel->setText( tr( "Cognome:" ) );
    nomeLabel->setText( tr( "Nome:" ) );
    randomCheck->setText( tr( "Assegna" ) );
    okButton->setText( tr( "OK" ) );
    cancellaButton->setText( tr( "Cancella" ) );
}

