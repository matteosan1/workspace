#include "punti.h"

TabelloneDialog::TabelloneDialog(QWidget *parent, int p, QString n)
    : QDialog(parent) {

  ui.setupUi(this);

  nome = n;
  punti = p;

  ui.lcdNumber->display(punti);
  ui.label->setText(nome);
}

void TabelloneDialog::setPunti(int a) {
  punti = a;
  ui.lcdNumber->display(punti);
}

int TabelloneDialog::getPunti() {
  return punti;
}

QString TabelloneDialog::getNome() {
  return nome;
}

