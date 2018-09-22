/****************************************************************************
** Form implementation generated from reading ui file 'strategiaprove.ui'
**
** Created: Mon Jun 18 01:56:07 2007
**      by: The User Interface Compiler ($Id: qt/main.cpp   3.3.7   edited Aug 31 2005 $)
**
** WARNING! All changes made in this file will be lost!
****************************************************************************/

#include "strategiaprove.h"

#include <qvariant.h>
#include <qpushbutton.h>
#include <qlabel.h>
#include <qgroupbox.h>
#include <qcombobox.h>
#include <qcheckbox.h>
#include <qspinbox.h>
#include <qprogressbar.h>
#include <qlayout.h>
#include <qtooltip.h>
#include <qwhatsthis.h>
#include "strategiaprove.ui.h"

/*
 *  Constructs a StrategiaProve as a child of 'parent', with the
 *  name 'name' and widget flags set to 'f'.
 *
 *  The dialog will by default be modeless, unless you set 'modal' to
 *  TRUE to construct a modal dialog.
 */
StrategiaProve::StrategiaProve( QWidget* parent, const char* name, bool modal, WFlags fl )
    : QDialog( parent, name, modal, fl )
{
    if ( !name )
	setName( "StrategiaProve" );
    StrategiaProveLayout = new QVBoxLayout( this, 11, 6, "StrategiaProveLayout"); 

    layout23 = new QVBoxLayout( 0, 0, 6, "layout23"); 

    contradaLabel = new QLabel( this, "contradaLabel" );
    contradaLabel->setAlignment( int( QLabel::AlignCenter ) );
    layout23->addWidget( contradaLabel );

    montaLabel = new QLabel( this, "montaLabel" );
    montaLabel->setAlignment( int( QLabel::AlignCenter ) );
    layout23->addWidget( montaLabel );

    layout22 = new QHBoxLayout( 0, 0, 6, "layout22"); 

    layout70 = new QVBoxLayout( 0, 0, 6, "layout70"); 

    scelta1Box = new QGroupBox( this, "scelta1Box" );
    scelta1Box->setColumnLayout(0, Qt::Vertical );
    scelta1Box->layout()->setSpacing( 6 );
    scelta1Box->layout()->setMargin( 11 );
    scelta1BoxLayout = new QHBoxLayout( scelta1Box->layout() );
    scelta1BoxLayout->setAlignment( Qt::AlignTop );

    layout65 = new QHBoxLayout( 0, 0, 6, "layout65"); 

    layout63 = new QVBoxLayout( 0, 0, 6, "layout63"); 

    scelta1Combo = new QComboBox( FALSE, scelta1Box, "scelta1Combo" );
    scelta1Combo->setAutoMask( TRUE );
    scelta1Combo->setDuplicatesEnabled( FALSE );
    layout63->addWidget( scelta1Combo );

    scelta1Check = new QCheckBox( scelta1Box, "scelta1Check" );
    layout63->addWidget( scelta1Check );
    layout65->addLayout( layout63 );

    layout62 = new QGridLayout( 0, 1, 1, 0, 6, "layout62"); 

    contrada1Combo = new QComboBox( FALSE, scelta1Box, "contrada1Combo" );
    contrada1Combo->setEnabled( FALSE );

    layout62->addMultiCellWidget( contrada1Combo, 1, 1, 0, 1 );

    scelta1Spin = new QSpinBox( scelta1Box, "scelta1Spin" );

    layout62->addWidget( scelta1Spin, 0, 1 );
    spacer18 = new QSpacerItem( 40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum );
    layout62->addItem( spacer18, 0, 0 );
    layout65->addLayout( layout62 );
    scelta1BoxLayout->addLayout( layout65 );
    layout70->addWidget( scelta1Box );

    scelta2Group = new QGroupBox( this, "scelta2Group" );
    scelta2Group->setColumnLayout(0, Qt::Vertical );
    scelta2Group->layout()->setSpacing( 6 );
    scelta2Group->layout()->setMargin( 11 );
    scelta2GroupLayout = new QHBoxLayout( scelta2Group->layout() );
    scelta2GroupLayout->setAlignment( Qt::AlignTop );

    layout67 = new QHBoxLayout( 0, 0, 6, "layout67"); 

    layout40 = new QVBoxLayout( 0, 0, 6, "layout40"); 

    scelta2Combo = new QComboBox( FALSE, scelta2Group, "scelta2Combo" );
    scelta2Combo->setAutoMask( TRUE );
    scelta2Combo->setDuplicatesEnabled( FALSE );
    layout40->addWidget( scelta2Combo );

    scelta2Check = new QCheckBox( scelta2Group, "scelta2Check" );
    layout40->addWidget( scelta2Check );
    layout67->addLayout( layout40 );

    layout42 = new QVBoxLayout( 0, 0, 6, "layout42"); 

    layout37 = new QHBoxLayout( 0, 0, 6, "layout37"); 
    spacer12_4 = new QSpacerItem( 40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum );
    layout37->addItem( spacer12_4 );

    scelta2Spin = new QSpinBox( scelta2Group, "scelta2Spin" );
    layout37->addWidget( scelta2Spin );
    layout42->addLayout( layout37 );

    contrada2Combo = new QComboBox( FALSE, scelta2Group, "contrada2Combo" );
    contrada2Combo->setEnabled( FALSE );
    layout42->addWidget( contrada2Combo );
    layout67->addLayout( layout42 );
    scelta2GroupLayout->addLayout( layout67 );
    layout70->addWidget( scelta2Group );

    scelta3Group = new QGroupBox( this, "scelta3Group" );
    scelta3Group->setColumnLayout(0, Qt::Vertical );
    scelta3Group->layout()->setSpacing( 6 );
    scelta3Group->layout()->setMargin( 11 );
    scelta3GroupLayout = new QHBoxLayout( scelta3Group->layout() );
    scelta3GroupLayout->setAlignment( Qt::AlignTop );

    layout69 = new QHBoxLayout( 0, 0, 6, "layout69"); 

    layout41 = new QVBoxLayout( 0, 0, 6, "layout41"); 

    scelta3Combo = new QComboBox( FALSE, scelta3Group, "scelta3Combo" );
    scelta3Combo->setAutoMask( TRUE );
    scelta3Combo->setDuplicatesEnabled( FALSE );
    layout41->addWidget( scelta3Combo );

    scelta3Check = new QCheckBox( scelta3Group, "scelta3Check" );
    layout41->addWidget( scelta3Check );
    layout69->addLayout( layout41 );

    layout43 = new QVBoxLayout( 0, 0, 6, "layout43"); 

    layout39 = new QHBoxLayout( 0, 0, 6, "layout39"); 
    spacer12_3 = new QSpacerItem( 40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum );
    layout39->addItem( spacer12_3 );

    scelta3Spin = new QSpinBox( scelta3Group, "scelta3Spin" );
    layout39->addWidget( scelta3Spin );
    layout43->addLayout( layout39 );

    contrada3Combo = new QComboBox( FALSE, scelta3Group, "contrada3Combo" );
    contrada3Combo->setEnabled( FALSE );
    layout43->addWidget( contrada3Combo );
    layout69->addLayout( layout43 );
    scelta3GroupLayout->addLayout( layout69 );
    layout70->addWidget( scelta3Group );
    layout22->addLayout( layout70 );
    spacer20 = new QSpacerItem( 174, 20, QSizePolicy::Expanding, QSizePolicy::Minimum );
    layout22->addItem( spacer20 );

    layout20 = new QVBoxLayout( 0, 0, 6, "layout20"); 

    provaBox = new QGroupBox( this, "provaBox" );
    provaBox->setColumnLayout(0, Qt::Vertical );
    provaBox->layout()->setSpacing( 6 );
    provaBox->layout()->setMargin( 11 );
    provaBoxLayout = new QHBoxLayout( provaBox->layout() );
    provaBoxLayout->setAlignment( Qt::AlignTop );

    layout5 = new QHBoxLayout( 0, 0, 6, "layout5"); 

    layout3 = new QVBoxLayout( 0, 0, 6, "layout3"); 

    primaLabel = new QLabel( provaBox, "primaLabel" );
    layout3->addWidget( primaLabel );

    secondaLabel = new QLabel( provaBox, "secondaLabel" );
    layout3->addWidget( secondaLabel );

    terzaLabel = new QLabel( provaBox, "terzaLabel" );
    layout3->addWidget( terzaLabel );

    quartaLabel = new QLabel( provaBox, "quartaLabel" );
    layout3->addWidget( quartaLabel );

    generaleLabel = new QLabel( provaBox, "generaleLabel" );
    layout3->addWidget( generaleLabel );

    acciaLabel = new QLabel( provaBox, "acciaLabel" );
    layout3->addWidget( acciaLabel );
    layout5->addLayout( layout3 );

    layout4 = new QVBoxLayout( 0, 0, 6, "layout4"); 

    primaCombo = new QComboBox( FALSE, provaBox, "primaCombo" );
    layout4->addWidget( primaCombo );

    secondaCombo = new QComboBox( FALSE, provaBox, "secondaCombo" );
    layout4->addWidget( secondaCombo );

    terzaCombo = new QComboBox( FALSE, provaBox, "terzaCombo" );
    layout4->addWidget( terzaCombo );

    quartaCombo = new QComboBox( FALSE, provaBox, "quartaCombo" );
    layout4->addWidget( quartaCombo );

    generaleCombo = new QComboBox( FALSE, provaBox, "generaleCombo" );
    layout4->addWidget( generaleCombo );

    acciaCombo = new QComboBox( FALSE, provaBox, "acciaCombo" );
    layout4->addWidget( acciaCombo );
    layout5->addLayout( layout4 );
    provaBoxLayout->addLayout( layout5 );
    layout20->addWidget( provaBox );
    spacer19 = new QSpacerItem( 20, 20, QSizePolicy::Minimum, QSizePolicy::Expanding );
    layout20->addItem( spacer19 );

    cavalloLabel = new QLabel( this, "cavalloLabel" );
    layout20->addWidget( cavalloLabel );

    formaBar = new QProgressBar( this, "formaBar" );
    layout20->addWidget( formaBar );
    spacer19_2 = new QSpacerItem( 20, 20, QSizePolicy::Minimum, QSizePolicy::Expanding );
    layout20->addItem( spacer19_2 );
    layout22->addLayout( layout20 );
    layout23->addLayout( layout22 );

    layout1_2 = new QHBoxLayout( 0, 0, 6, "layout1_2"); 
    spacer1_4 = new QSpacerItem( 40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum );
    layout1_2->addItem( spacer1_4 );

    okButton = new QPushButton( this, "okButton" );
    layout1_2->addWidget( okButton );
    spacer1_2_2 = new QSpacerItem( 40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum );
    layout1_2->addItem( spacer1_2_2 );

    cancelButton = new QPushButton( this, "cancelButton" );
    layout1_2->addWidget( cancelButton );
    spacer1_3_2 = new QSpacerItem( 40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum );
    layout1_2->addItem( spacer1_3_2 );
    layout23->addLayout( layout1_2 );
    StrategiaProveLayout->addLayout( layout23 );
    languageChange();
    resize( QSize(671, 441).expandedTo(minimumSizeHint()) );
    clearWState( WState_Polished );

    // signals and slots connections
    connect( okButton, SIGNAL( clicked() ), this, SLOT( accept() ) );
    connect( cancelButton, SIGNAL( clicked() ), this, SLOT( reject() ) );
    connect( scelta1Check, SIGNAL( stateChanged(int) ), this, SLOT( enableCombo1(int) ) );
    connect( scelta2Check, SIGNAL( stateChanged(int) ), this, SLOT( enableCombo2(int) ) );
    connect( scelta3Check, SIGNAL( stateChanged(int) ), this, SLOT( enableCombo3(int) ) );
}

/*
 *  Destroys the object and frees any allocated resources
 */
StrategiaProve::~StrategiaProve()
{
    // no need to delete child widgets, Qt does it all for us
}

/*
 *  Sets the strings of the subwidgets using the current
 *  language.
 */
void StrategiaProve::languageChange()
{
    setCaption( tr( "Strategia Prove" ) );
    contradaLabel->setText( tr( "textLabel2" ) );
    montaLabel->setText( tr( "textLabel2" ) );
    scelta1Box->setTitle( tr( "Fantino: prima scelta" ) );
    scelta1Check->setText( tr( "Non montare:" ) );
    scelta2Group->setTitle( tr( "Fantino:seconda scelta" ) );
    scelta2Check->setText( tr( "Non montare:" ) );
    scelta3Group->setTitle( tr( "Fantino: terza scelta" ) );
    scelta3Check->setText( tr( "Non montare:" ) );
    provaBox->setTitle( tr( "Strategia Prove" ) );
    primaLabel->setText( tr( "Prima Prova:" ) );
    secondaLabel->setText( tr( "Seconda Prova:" ) );
    terzaLabel->setText( tr( "Terza Prova:" ) );
    quartaLabel->setText( tr( "Quarta Prova:" ) );
    generaleLabel->setText( tr( "Prova Generale:" ) );
    acciaLabel->setText( tr( "Provaccia:" ) );
    cavalloLabel->setText( tr( "textLabel1" ) );
    okButton->setText( tr( "OK" ) );
    cancelButton->setText( tr( "Cancella" ) );
}

