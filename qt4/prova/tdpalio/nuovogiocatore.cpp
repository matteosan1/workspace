#include "nuovogiocatore.h"

#include "TRandom.h"

#include <iostream>
using namespace std;

NuovoGiocatoreDialog::NuovoGiocatoreDialog(QWidget* parent)
    : QDialog(parent) {

    ui.setupUi(this);
    //if (!name)
	//   setName( "NuovoGiocatore" );

    // signals and slots connections
    //connect(cancellaButton, SIGNAL( clicked() ), this, SLOT( reject() ) );
    connect(ui.randomCheck, SIGNAL(stateChanged(int)), this, SLOT(enableCombo(int)));
    connect(ui.okButton, SIGNAL(clicked()), this, SLOT(accept()));
}

NuovoGiocatoreDialog::~NuovoGiocatoreDialog()
{}

void NuovoGiocatoreDialog::enableCombo(int state) {
    if (state != 0)
        ui.contradaCombo->setEnabled(false);
    else
        ui.contradaCombo->setEnabled(true);
}

Giocatore NuovoGiocatoreDialog::getGiocatore() {
    return g;
}

void NuovoGiocatoreDialog::accept() {
    g.setNome(ui.nomeEdit->text());
    g.setCognome(ui.cognomeEdit->text());

    if (ui.randomCheck->isChecked())
        g.setContrada(assegnaContrada());
    else
        g.setContrada(indice[ui.contradaCombo->currentIndex()]);

    QDialog::accept();
}

void NuovoGiocatoreDialog::setContrade(QStringList lista, QVector<int> index) {
    indice = index;
    ui.contradaCombo->addItems(lista);
}

int NuovoGiocatoreDialog::assegnaContrada() {

    // mettere seed casuale
    TRandom r(1000);
    unsigned int limite = ui.contradaCombo->count();
    int scelta = r.Integer(limite);
    return scelta;
}
