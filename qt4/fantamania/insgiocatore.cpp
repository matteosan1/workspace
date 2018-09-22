#include "insgiocatore.h"

InsGiocatore::InsGiocatore(Giocatore* g, QWidget *parent)
    : QDialog(parent),  giocatore(g) {

    ui.setupUi(this);
    ui.radioButton->setChecked(true);

    // TODO bloccare le lettere nel campo prezzo
    // TODO bloccare ok se il cognome e` vuoto
    connect(ui.lineEdit, SIGNAL(textChanged(const QString&)), this, SLOT(changeCognome(QString)));
    connect(ui.lineEdit_2, SIGNAL(textChanged(const QString&)), this, SLOT(changeNome(QString)));
    connect(ui.lineEdit_3, SIGNAL(textChanged(const QString&)), this, SLOT(changePrezzo(QString)));
    connect(ui.lineEdit_4, SIGNAL(textChanged(const QString&)), this, SLOT(changeSquadra(QString)));
    connect(ui.radioButton, SIGNAL(toggled(bool)), this, SLOT(changeRadio(bool)));
    connect(ui.radioButton_2, SIGNAL(toggled(bool)), this, SLOT(changeRadio(bool)));
    connect(ui.radioButton_3, SIGNAL(toggled(bool)), this, SLOT(changeRadio(bool)));
    connect(ui.radioButton_4, SIGNAL(toggled(bool)), this, SLOT(changeRadio(bool)));

    if (giocatore != 0)
        fillField();
    else
        giocatore = new Giocatore();
}

void InsGiocatore::fillField() {
    if (giocatore->GetRuolo() == 0)
        ui.radioButton->setChecked(true);
    if (giocatore->GetRuolo() == 1)
        ui.radioButton_2->setChecked(true);
    if (giocatore->GetRuolo() == 2)
        ui.radioButton_3->setChecked(true);
    if (giocatore->GetRuolo() == 3)
        ui.radioButton_4->setChecked(true);

    ui.lineEdit->setText(giocatore->GetCognome());
    ui.lineEdit_2->setText(giocatore->GetNome());
    ui.lineEdit_3->setText(QString("%1").arg(giocatore->GetPrezzo()));
    ui.lineEdit_4->setText(giocatore->GetSquadra());
}

void InsGiocatore::changeRadio(bool a) {
    int ruolo;
    if (ui.radioButton->isChecked())
        ruolo = 0;
    if (ui.radioButton_2->isChecked())
        ruolo = 1;
    if (ui.radioButton_3->isChecked())
        ruolo = 2;
    if (ui.radioButton_4->isChecked())
        ruolo = 3;

    giocatore->SetRuolo(ruolo);
}

void InsGiocatore::changeNome(QString s) {
    s.replace(" ", "_");
    giocatore->SetNome(s.toUpper());
}

void InsGiocatore::changeCognome(QString s) {
    s.replace(" ", "_");
    giocatore->SetCognome(s.toUpper());
}

void InsGiocatore::changePrezzo(QString s) {
    giocatore->SetPrezzo(s.toInt());
}

void InsGiocatore::changeSquadra(QString s) {
    s.replace(" ", "_");
    giocatore->SetSquadra(s.toUpper());
}
