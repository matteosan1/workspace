/*
#include "sceltapartito.h"

#include <qvariant.h>
#include <qpushbutton.h>
#include <qlabel.h>
#include <qcombobox.h>
#include <qspinbox.h>
#include <q3buttongroup.h>
#include <qradiobutton.h>
#include <qlayout.h>
#include <qtooltip.h>
#include <q3whatsthis.h>
//Added by qt3to4:
#include <Q3HBoxLayout>
#include <Q3VBoxLayout>
#include "sceltapartto.ui.h"

SceltaPartito::SceltaPartito( QWidget* parent, const char* name, bool modal, Qt::WFlags fl )
    : QDialog( parent, name, modal, fl )
{

    // signals and slots connections
    connect( cancelButton, SIGNAL( clicked() ), this, SLOT( reject() ) );
    connect( tipo3, SIGNAL( toggled(bool) ), this, SLOT( enableCombo(bool) ) );
    init();
}

SceltaPartito::~SceltaPartito()
{}
*/
