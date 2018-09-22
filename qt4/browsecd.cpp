#include "browsecd.h"
#include "groupboxcontrol.h"

#include <qvariant.h>
#include <qpushbutton.h>
#include <qlabel.h>
#include <qlineedit.h>
#include <qcombobox.h>
#include <qradiobutton.h>
#include <qlayout.h>
#include <qtooltip.h>
#include <qwhatsthis.h>

/*
 *  Constructs a browseCD as a child of 'parent', with the
 *  name 'name' and widget flags set to 'f'.
 *
 *  The dialog will by default be modeless, unless you set 'modal' to
 *  TRUE to construct a modal dialog.
 */
browseCD::browseCD( QWidget* parent, const char* name, bool modal, WFlags fl )
    : QDialog( parent, name, modal, fl )
{
    if ( !name )
	setName( "browseCD" );

    QWidget* privateLayoutWidget = new QWidget( this, "layout16" );
    privateLayoutWidget->setGeometry( QRect( 11, 11, 626, 462 ) );
    layout16 = new QVBoxLayout( privateLayoutWidget, 11, 6, "layout16"); 

    layout35 = new QGridLayout( 0, 1, 1, 0, 6, "layout35"); 

    authorLabel = new QLabel( privateLayoutWidget, "authorLabel" );

    layout35->addWidget( authorLabel, 0, 0 );

    authorEdit = new QLineEdit( privateLayoutWidget, "authorEdit" );

    layout35->addWidget( authorEdit, 0, 1 );

    titleLabel = new QLabel( privateLayoutWidget, "titleLabel" );

    layout35->addWidget( titleLabel, 1, 0 );

    titleEdit = new QLineEdit( privateLayoutWidget, "titleEdit" );

    layout35->addWidget( titleEdit, 1, 1 );
    layout16->addLayout( layout35 );
    spacer32 = new QSpacerItem( 20, 53, QSizePolicy::Minimum, QSizePolicy::Expanding );
    layout16->addItem( spacer32 );

    layout54 = new QHBoxLayout( 0, 0, 6, "layout54"); 

    layout53 = new QHBoxLayout( 0, 0, 6, "layout53"); 

    layout51 = new QVBoxLayout( 0, 0, 6, "layout51"); 

    supplierLabel = new QLabel( privateLayoutWidget, "supplierLabel" );
    layout51->addWidget( supplierLabel );

    companyLabel = new QLabel( privateLayoutWidget, "companyLabel" );
    layout51->addWidget( companyLabel );
    layout53->addLayout( layout51 );

    layout52 = new QVBoxLayout( 0, 0, 6, "layout52"); 

    supplierEdit = new QLineEdit( privateLayoutWidget, "supplierEdit" );
    layout52->addWidget( supplierEdit );

    companyEdit = new QLineEdit( privateLayoutWidget, "companyEdit" );
    layout52->addWidget( companyEdit );
    layout53->addLayout( layout52 );
    layout54->addLayout( layout53 );
    spacer22 = new QSpacerItem( 100, 20, QSizePolicy::Expanding, QSizePolicy::Minimum );
    layout54->addItem( spacer22 );

    layout50 = new QHBoxLayout( 0, 0, 6, "layout50"); 

    layout48 = new QVBoxLayout( 0, 0, 6, "layout48"); 

    formatLabel = new QLabel( privateLayoutWidget, "formatLabel" );
    layout48->addWidget( formatLabel );

    Code = new QLabel( privateLayoutWidget, "Code" );
    layout48->addWidget( Code );
    layout50->addLayout( layout48 );

    layout49 = new QVBoxLayout( 0, 0, 6, "layout49"); 

    formatCombo = new QComboBox( FALSE, privateLayoutWidget, "formatCombo" );
    layout49->addWidget( formatCombo );

    codeEdit = new QLineEdit( privateLayoutWidget, "codeEdit" );
    layout49->addWidget( codeEdit );
    layout50->addLayout( layout49 );
    layout54->addLayout( layout50 );
    spacer26 = new QSpacerItem( 100, 20, QSizePolicy::Expanding, QSizePolicy::Minimum );
    layout54->addItem( spacer26 );
    layout16->addLayout( layout54 );
    spacer33 = new QSpacerItem( 20, 55, QSizePolicy::Minimum, QSizePolicy::Expanding );
    layout16->addItem( spacer33 );

    layout15 = new QHBoxLayout( 0, 0, 6, "layout15"); 

    layout37 = new QGridLayout( 0, 1, 1, 0, 6, "layout37"); 

    retailPriceLabel = new QLabel( privateLayoutWidget, "retailPriceLabel" );

    layout37->addWidget( retailPriceLabel, 0, 0 );

    sellingPriceLabel = new QLabel( privateLayoutWidget, "sellingPriceLabel" );

    layout37->addWidget( sellingPriceLabel, 1, 0 );

    sellingPriceEdit = new QLineEdit( privateLayoutWidget, "sellingPriceEdit" );

    layout37->addWidget( sellingPriceEdit, 1, 1 );

    specialPriceLabel = new QLabel( privateLayoutWidget, "specialPriceLabel" );

    layout37->addWidget( specialPriceLabel, 2, 0 );

    specialPriceEdit = new QLineEdit( privateLayoutWidget, "specialPriceEdit" );

    layout37->addWidget( specialPriceEdit, 2, 1 );

    retailPriceEdit = new QLineEdit( privateLayoutWidget, "retailPriceEdit" );

    layout37->addWidget( retailPriceEdit, 0, 1 );
    layout15->addLayout( layout37 );
    spacer30 = new QSpacerItem( 49, 20, QSizePolicy::Expanding, QSizePolicy::Minimum );
    layout15->addItem( spacer30 );

    statusBox = new groupBoxControl( privateLayoutWidget, "statusBox" );
    statusBox->setChecked( FALSE );
    statusBox->setProperty( "selectedId", -1 );

    QWidget* privateLayoutWidget_2 = new QWidget( statusBox, "layout14" );
    privateLayoutWidget_2->setGeometry( QRect( 11, 21, 73, 100 ) );
    layout14 = new QVBoxLayout( privateLayoutWidget_2, 11, 6, "layout14"); 

    normalCheck = new QRadioButton( privateLayoutWidget_2, "normalCheck" );
    normalCheck->setChecked( TRUE );
    layout14->addWidget( normalCheck );

    newCheck = new QRadioButton( privateLayoutWidget_2, "newCheck" );
    layout14->addWidget( newCheck );

    offertCheck = new QRadioButton( privateLayoutWidget_2, "offertCheck" );
    offertCheck->setEnabled( TRUE );
    layout14->addWidget( offertCheck );

    deletedCheck = new QRadioButton( privateLayoutWidget_2, "deletedCheck" );
    layout14->addWidget( deletedCheck );
    layout15->addWidget( statusBox );
    spacer31 = new QSpacerItem( 49, 20, QSizePolicy::Expanding, QSizePolicy::Minimum );
    layout15->addItem( spacer31 );

    layout44 = new QGridLayout( 0, 1, 1, 0, 6, "layout44"); 

    orderedLabel = new QLabel( privateLayoutWidget, "orderedLabel" );

    layout44->addWidget( orderedLabel, 2, 0 );

    stockLabel = new QLabel( privateLayoutWidget, "stockLabel" );

    layout44->addWidget( stockLabel, 0, 0 );

    stockEdit = new QLineEdit( privateLayoutWidget, "stockEdit" );

    layout44->addWidget( stockEdit, 0, 1 );

    soldEdit = new QLineEdit( privateLayoutWidget, "soldEdit" );

    layout44->addWidget( soldEdit, 1, 1 );

    orderedEdit = new QLineEdit( privateLayoutWidget, "orderedEdit" );

    layout44->addWidget( orderedEdit, 2, 1 );

    soldLabel = new QLabel( privateLayoutWidget, "soldLabel" );

    layout44->addWidget( soldLabel, 1, 0 );
    layout15->addLayout( layout44 );
    layout16->addLayout( layout15 );
    spacer34 = new QSpacerItem( 20, 54, QSizePolicy::Minimum, QSizePolicy::Expanding );
    layout16->addItem( spacer34 );

    layout43 = new QHBoxLayout( 0, 0, 6, "layout43"); 
    spacer27 = new QSpacerItem( 40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum );
    layout43->addItem( spacer27 );

    okButton = new QPushButton( privateLayoutWidget, "okButton" );
    layout43->addWidget( okButton );
    spacer28 = new QSpacerItem( 40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum );
    layout43->addItem( spacer28 );

    cancelButton = new QPushButton( privateLayoutWidget, "cancelButton" );
    layout43->addWidget( cancelButton );
    spacer29 = new QSpacerItem( 40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum );
    layout43->addItem( spacer29 );
    layout16->addLayout( layout43 );
    languageChange();
    resize( QSize(648, 484).expandedTo(minimumSizeHint()) );
    clearWState( WState_Polished );

    // signals and slots connections
    connect( cancelButton, SIGNAL( clicked() ), this, SLOT( reject() ) );
    connect( okButton, SIGNAL( clicked() ), this, SLOT( accept() ) );

    // tab order
    setTabOrder( authorEdit, titleEdit );
    setTabOrder( titleEdit, supplierEdit );
    setTabOrder( supplierEdit, companyEdit );
    setTabOrder( companyEdit, formatCombo );
    setTabOrder( formatCombo, codeEdit );
    setTabOrder( codeEdit, retailPriceEdit );
    setTabOrder( retailPriceEdit, sellingPriceEdit );
    setTabOrder( sellingPriceEdit, specialPriceEdit );
    setTabOrder( specialPriceEdit, normalCheck );
    setTabOrder( normalCheck, newCheck );
    setTabOrder( newCheck, offertCheck );
    setTabOrder( offertCheck, deletedCheck );
    setTabOrder( deletedCheck, stockEdit );
    setTabOrder( stockEdit, soldEdit );
    setTabOrder( soldEdit, orderedEdit );
    setTabOrder( orderedEdit, okButton );
    setTabOrder( okButton, cancelButton );

    // buddies
    authorLabel->setBuddy( authorEdit );
    titleLabel->setBuddy( titleEdit );
    supplierLabel->setBuddy( supplierEdit );
    companyLabel->setBuddy( companyEdit );
    formatLabel->setBuddy( formatCombo );
    Code->setBuddy( codeEdit );
    retailPriceLabel->setBuddy( retailPriceEdit );
    sellingPriceLabel->setBuddy( sellingPriceEdit );
    specialPriceLabel->setBuddy( specialPriceEdit );
    orderedLabel->setBuddy( orderedEdit );
    stockLabel->setBuddy( stockEdit );
    soldLabel->setBuddy( soldEdit );
}

/*
 *  Destroys the object and frees any allocated resources
 */
browseCD::~browseCD()
{
    // no need to delete child widgets, Qt does it all for us
}

/*
 *  Sets the strings of the subwidgets using the current
 *  language.
 */
void browseCD::languageChange()
{
    setCaption( tr( "Insert CD" ) );
    authorLabel->setText( tr( "Author:" ) );
    titleLabel->setText( tr( "Title:" ) );
    supplierLabel->setText( tr( "Supplier:" ) );
    companyLabel->setText( tr( "Company:" ) );
    formatLabel->setText( tr( "Format:" ) );
    Code->setText( tr( "Code:" ) );
    retailPriceLabel->setText( tr( "Retail price:" ) );
    sellingPriceLabel->setText( tr( "Selling price:" ) );
    specialPriceLabel->setText( tr( "Special price:" ) );
    statusBox->setTitle( tr( "Status" ) );
    normalCheck->setText( tr( "Normal" ) );
    newCheck->setText( tr( "New" ) );
    offertCheck->setText( tr( "Offert" ) );
    deletedCheck->setText( tr( "Deleted" ) );
    orderedLabel->setText( tr( "Ordered:" ) );
    stockLabel->setText( tr( "Stock:" ) );
    soldLabel->setText( tr( "Sold:" ) );
    okButton->setText( tr( "OK" ) );
    cancelButton->setText( tr( "Cancel" ) );
}

void browseCD::reject()
{
    qWarning( "browseCD::reject(): Not implemented yet" );
}

void browseCD::accept()
{
    qWarning( "browseCD::accept(): Not implemented yet" );
}

