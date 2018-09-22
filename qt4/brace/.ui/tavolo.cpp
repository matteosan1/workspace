/****************************************************************************
** Form implementation generated from reading ui file 'tavolo.ui'
**
** Created: Fri May 4 20:39:08 2007
**      by: The User Interface Compiler ($Id: qt/main.cpp   3.3.7   edited Aug 31 2005 $)
**
** WARNING! All changes made in this file will be lost!
****************************************************************************/

#include "tavolo.h"

#include <qvariant.h>
#include <qpushbutton.h>
#include <qlabel.h>
#include <qlineedit.h>
#include <qspinbox.h>
#include <qcombobox.h>
#include <qlayout.h>
#include <qtooltip.h>
#include <qwhatsthis.h>
#include <qimage.h>
#include <qpixmap.h>

/*
 *  Constructs a Tavolo as a child of 'parent', with the
 *  name 'name' and widget flags set to 'f'.
 *
 *  The dialog will by default be modeless, unless you set 'modal' to
 *  TRUE to construct a modal dialog.
 */
Tavolo::Tavolo( QWidget* parent, const char* name, bool modal, WFlags fl )
    : QDialog( parent, name, modal, fl )
{
    if ( !name )
	setName( "Tavolo" );
    TavoloLayout = new QHBoxLayout( this, 11, 6, "TavoloLayout"); 

    layout7 = new QVBoxLayout( 0, 0, 6, "layout7"); 

    layout6 = new QHBoxLayout( 0, 0, 6, "layout6"); 

    layout5 = new QVBoxLayout( 0, 0, 6, "layout5"); 

    labelNumero = new QLabel( this, "labelNumero" );
    layout5->addWidget( labelNumero );

    labelPosti = new QLabel( this, "labelPosti" );
    layout5->addWidget( labelPosti );

    labelPosizione = new QLabel( this, "labelPosizione" );
    layout5->addWidget( labelPosizione );
    layout6->addLayout( layout5 );
    spacer5 = new QSpacerItem( 40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum );
    layout6->addItem( spacer5 );

    layout4 = new QVBoxLayout( 0, 0, 6, "layout4"); 

    editNumero = new QLineEdit( this, "editNumero" );
    layout4->addWidget( editNumero );

    layout1 = new QHBoxLayout( 0, 0, 6, "layout1"); 
    spacer1 = new QSpacerItem( 40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum );
    layout1->addItem( spacer1 );

    spinPosti = new QSpinBox( this, "spinPosti" );
    spinPosti->setValue( 20 );
    layout1->addWidget( spinPosti );
    layout4->addLayout( layout1 );

    comboPosizione = new QComboBox( FALSE, this, "comboPosizione" );
    layout4->addWidget( comboPosizione );
    layout6->addLayout( layout4 );
    layout7->addLayout( layout6 );
    spacer6 = new QSpacerItem( 20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding );
    layout7->addItem( spacer6 );

    layout3 = new QHBoxLayout( 0, 0, 6, "layout3"); 
    spacer3 = new QSpacerItem( 40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum );
    layout3->addItem( spacer3 );

    buttonOK = new QPushButton( this, "buttonOK" );
    layout3->addWidget( buttonOK );
    spacer2 = new QSpacerItem( 40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum );
    layout3->addItem( spacer2 );

    buttonCancel = new QPushButton( this, "buttonCancel" );
    layout3->addWidget( buttonCancel );
    spacer4 = new QSpacerItem( 40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum );
    layout3->addItem( spacer4 );
    layout7->addLayout( layout3 );
    TavoloLayout->addLayout( layout7 );
    languageChange();
    resize( QSize(259, 185).expandedTo(minimumSizeHint()) );
    clearWState( WState_Polished );
}

/*
 *  Destroys the object and frees any allocated resources
 */
Tavolo::~Tavolo()
{
    // no need to delete child widgets, Qt does it all for us
}

/*
 *  Sets the strings of the subwidgets using the current
 *  language.
 */
void Tavolo::languageChange()
{
    setCaption( tr( "Tavolo" ) );
    labelNumero->setText( tr( "Numero Tavolo" ) );
    labelPosti->setText( tr( "Posti " ) );
    labelPosizione->setText( tr( "Posizione" ) );
    buttonOK->setText( tr( "OK" ) );
    buttonCancel->setText( tr( "Cancel" ) );
}

