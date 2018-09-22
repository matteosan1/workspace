#include "Profilo.h"

#include <QMessageBox>

Profilo::Profilo(QWidget* parent) : QDialog(parent) {

    ui.setupUi(this);

    connect(ui.lineNome, SIGNAL(textChanged(QString)), this, SLOT(text1(QString)));
    connect(ui.lineCognome, SIGNAL(textChanged(QString)), this, SLOT(text2(QString)));
    connect(ui.lineUsername, SIGNAL(textChanged(QString)), this, SLOT(text3(QString)));
    connect(ui.pushButton, SIGNAL(clicked()), this, SLOT(esci()));
}

void Profilo::text1(QString t) {
  nome = t;
}

void Profilo::text2(QString t) {
  cognome = t;
}

void Profilo::text3(QString t) {
  // FIXME controllare che non abbia caratteri strani
  username = t;
}

void Profilo::esci() {
  if (nome == "") {
    QMessageBox::warning(this,"Errore nel Profilo.", "Devi specificare un nome.");
    return;
  }
  
  if (cognome == "") {
    QMessageBox::warning(this,"Errore nel Profilo.", "Devi specificare un cognome.");
    return;
  }

  if (username == "") {
    QMessageBox::warning(this,"Errore nel Profilo.", "Devi specificare uno username.");
    return;
  }
  
  QDialog::accept();
}
