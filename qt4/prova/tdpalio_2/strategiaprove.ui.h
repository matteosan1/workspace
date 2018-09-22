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
using namespace std;

void StrategiaProve::FillCombo(QStringList fantini, QStringList contrade, Barbero* contrada, int* status) {
    cout << status[0] << endl;
    contrada1Combo->insertStringList(contrade);
    contrada2Combo->insertStringList(contrade);
    contrada3Combo->insertStringList(contrade);
    cout << "2" << endl;
    
    for(unsigned int i=0; i<fantini.size(); ++i) {
        if (status[i] == 1) {
            scelta1Combo->insertItem(QPixmap("./pictures/adept_purge.png"), fantini[i]);
            scelta2Combo->insertItem(QPixmap("./pictures/adept_purge.png"), fantini[i]);
            scelta3Combo->insertItem(QPixmap("./pictures/adept_purge.png"), fantini[i]);
        } else {
            scelta1Combo->insertItem(fantini[i]);
            scelta2Combo->insertItem(fantini[i]);
            scelta3Combo->insertItem(fantini[i]);
        }
    }
    cout << "3" << endl;

    contradaLabel->setText(contrada->getContrada()->getNomeCompleto());
    QString monta;
    if (contrada->getFantino() != 0)
            monta = contrada->getFantino()->getNome();
    else
        monta = "nessun fantino scelto.";
    
    montaLabel->setText("Monta attuale: "+monta);
    cavalloLabel->setText(contrada->getCavallo()->getNome());
    formaBar->setCenterIndicator(true);
    formaBar->setProgress(contrada->forma());
    QStringList strategia;
    strategia.append("Mossa");
    strategia.append("Spunto");
    strategia.append("Curve");
    cout << "4" << endl;

    //for(unsigned int i=0; i<contrade.size(); i++)
	//strategia.append("Ostacola " + contrade[i]);
    primaCombo->insertStringList(strategia);
 cout << "5" << endl;

    secondaCombo->insertStringList(strategia);
    terzaCombo->insertStringList(strategia);
    quartaCombo->insertStringList(strategia);
    generaleCombo->insertStringList(strategia);
    acciaCombo->insertStringList(strategia);
}

void StrategiaProve::enableCombo1( int state ) {
    contrada1Combo->setEnabled(state);
}

void StrategiaProve::enableCombo2( int state ) {
    contrada2Combo->setEnabled(state);
}

void StrategiaProve::enableCombo3( int state ) {
    contrada3Combo->setEnabled(state);
}
