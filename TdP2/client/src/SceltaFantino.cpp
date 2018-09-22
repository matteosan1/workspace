#include "SceltaFantino.h"

#include <QMessageBox>
#include <iostream>

SceltaFantino::SceltaFantino(int q, QVector<Fantino>* c, QWidget* parent)
  : QDialog(parent), fantini(c) {
  
  ui.setupUi(this);
  connect(ui.cavalliView, SIGNAL(itemSelectionChanged()), this, SLOT(selection()));

  ui.okButton->setEnabled(false);
  ui.cavalliView->setRowCount(fantini->size());
  ui.cavalliView->setColumnCount(5);

  ui.cavalliView->setEditTriggers(QAbstractItemView::NoEditTriggers);
  ui.cavalliView->setSelectionBehavior(QAbstractItemView::SelectRows);
  ui.cavalliView->setSelectionMode(QAbstractItemView::MultiSelection);

  QStringList headerLabels;
  headerLabels << "Fantino" << "Eta`" << "Corsi" << "Vinti" 
	       << "Stato" << "Prezzo";
  ui.cavalliView->setHorizontalHeaderLabels(headerLabels);
  populateTable();

  ui.cavalliView->resizeColumnsToContents();
  //ui.cavalliView->resize(500, 300);
  ui.cavalliView->show();  

  setWindowTitle("Fantini disponibili...");
  selezione = -1;
}

void SceltaFantino::populateTable() {

  for(int i=0; i<fantini->size(); ++i) {
    QTableWidgetItem* item0 = new QTableWidgetItem((*fantini)[i].getNome());
    QTableWidgetItem* item1 = new QTableWidgetItem(QString("%1").arg((*fantini)[i].eta()));
    QTableWidgetItem* item2 = new QTableWidgetItem(QString("%1").arg((*fantini)[i].paliCorsi()));
    QTableWidgetItem* item3 = new QTableWidgetItem(QString("%1").arg((*fantini)[i].paliVinti()));

    QTableWidgetItem* item4;
    if ((*fantini)[i].killer() > 0) {
      item4 = new QTableWidgetItem(QIcon(":/status/pictures/killer.png"), "");
    } else {
      if ((*fantini)[i].media() > 6.0)
	item4 = new QTableWidgetItem(QIcon(":/status/pictures/buono.bmp"), "");
      else if ((*fantini)[i].media() < 4.0)
	item4 = new QTableWidgetItem(QIcon(":/status/pictures/scarso.bmp"), "");
      else
	item4 = new QTableWidgetItem(QIcon(":/status/pictures/suff.bmp"), "");
    }

    QTableWidgetItem* item5 = new QTableWidgetItem(QString("%1").arg((*fantini)[i].prezzo()));

    ui.cavalliView->setItem(i, 0, item0);
    ui.cavalliView->setItem(i, 1, item1);
    ui.cavalliView->setItem(i, 2, item2);
    ui.cavalliView->setItem(i, 3, item3);
    ui.cavalliView->setItem(i, 4, item4);
    ui.cavalliView->setItem(i, 5, item5);
  }
}

SceltaFantino::~SceltaFantino() {}

void SceltaFantino::selection() {
  selezione = ui.cavalliView->selectedItems().at(0)->row();

  if (selezione)
    ui.okButton->setEnabled(true);
  else
    ui.okButton->setEnabled(false);
}



