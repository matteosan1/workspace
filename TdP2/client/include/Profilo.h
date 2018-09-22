#ifndef PROFILO_H
#define PROFILO_H

#include "ui_profilo.h"

#include <QString>

class Profilo : public QDialog {
  Q_OBJECT

 public:
  Profilo(QWidget* parent = 0);
  ~Profilo() {}

  QString getNome() { return nome; }
  QString getCognome() { return cognome; }
  QString getUser() { return username; }

  public slots:
  void text1(QString);
  void text2(QString);
  void text3(QString);
  void esci();

 private:

    Ui::ProfiloDialog ui;
    QString nome, cognome, username;
};

#endif
