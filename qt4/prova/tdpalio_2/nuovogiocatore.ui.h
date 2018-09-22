/****************************************************************************
** ui.h extension file, included from the uic-generated form implementation.
**
** If you want to add, delete, or rename functions or slots, use
** Qt Designer to update this file, preserving your code.
**
** You should not define a constructor or destructor in this file.
** Instead, write your code in functions called init() and destroy().
** These will automatically be called by the form's constructor and
** destructor.
*****************************************************************************/

#include <iostream>

#include "giocatore.h"
#include "TRandom.h"

using namespace std;

void NuovoGiocatore::enableCombo(int state) {
    if (state != 0) 
	contradaCombo->setEnabled(false);
    else
	contradaCombo->setEnabled(true);
}

Giocatore NuovoGiocatore::getGiocatore() {
    return g;
}

void NuovoGiocatore::accept() {
    g.setNome(nomeEdit->text());
    g.setCognome(cognomeEdit->text());
    
    if (randomCheck->isChecked()) 
	g.setContrada(assegnaContrada());
    else 
	g.setContrada(indice[contradaCombo->currentItem()]);
	
    QDialog::accept();
}

void NuovoGiocatore::setContrade(QStringList lista, vector<int> index) {
    indice = index;
    contradaCombo->insertStringList(lista);
}

int NuovoGiocatore::assegnaContrada() {
    
    // mettere seed casuale
    TRandom r(1000);
    unsigned int limite = contradaCombo->count();
    int scelta = r.Integer(limite);
    return scelta;
}    
