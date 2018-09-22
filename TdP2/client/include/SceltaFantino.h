#ifndef SCELTAFANTINO_H
#define SCELTAFANTINO_H

#include "ui_tratta.h"

#include "../tdpaliocommon/fantino.h"

#include <QVector>

class SceltaFantino : public QDialog {
  Q_OBJECT
    
public:
  SceltaFantino(int, QVector<Fantino>* c = 0, QWidget* parent = 0);
  ~SceltaFantino();
  
  void populateTable();
  int getSelection() { return selezione; };

public slots:
  void selection();

private:
    //int selezione[21];
  int selezione;
  Ui::Tratta ui;
  QVector<Fantino>* fantini;
};

#endif
