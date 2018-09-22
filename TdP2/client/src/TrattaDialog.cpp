#include "TrattaDialog.h"

#include <QMessageBox>
#include <iostream>
TrattaDialog::TrattaDialog(int q, QVector<Cavallo>* c, QWidget* parent)
    : QDialog(parent), cavalli(c) {

    ui.setupUi(this);

    connect(ui.cavalliView, SIGNAL(itemSelectionChanged()), this, SLOT(selection()));

    ui.cavalliView->setRowCount(cavalli->size());
    ui.cavalliView->setColumnCount(4);

    ui.cavalliView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui.cavalliView->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui.cavalliView->setSelectionMode(QAbstractItemView::MultiSelection);

    QStringList headerLabels;
    headerLabels << "Cavallo" << "Corsi" << "Vinti" << "Stato";
    ui.cavalliView->setHorizontalHeaderLabels(headerLabels);

    // FIXME problema con il contatore quando limite < 0 (credo)
    if (q < 0)
      limite = 10;
    else
      limite = q;
    
    cambiaCaption(QString("%1").arg(limite));
    populateTable();

    ui.cavalliView->resizeColumnsToContents();
    //ui.cavalliView->resize(500, 300);
    ui.cavalliView->show();
}

void TrattaDialog::selection() {

  int selections = (ui.cavalliView->selectedItems().size()/4);
  cambiaCaption(QString("%1").arg(limite-selections));

  if (limite == selections)
    ui.okButton->setEnabled(true);
  else
    ui.okButton->setEnabled(false);
}

void TrattaDialog::populateTable() {
  
  for(int i=0; i<cavalli->size(); ++i) {
    for(int j=0; j<cavalli->size(); j++) {
      if ((*cavalli)[j].coscia() != i)
	continue;
      
      QTableWidgetItem* item0 = new QTableWidgetItem((*cavalli)[j].getNome());
      QTableWidgetItem* item1 = new QTableWidgetItem(QString("%1").arg((*cavalli)[j].paliCorsi()));
      QTableWidgetItem* item2 = new QTableWidgetItem(QString("%1").arg((*cavalli)[j].paliVinti()));
      QTableWidgetItem* item3;
      if ((*cavalli)[j].media() > 6.0)
	item3 = new QTableWidgetItem(QIcon(":/status/pictures/buono.bmp"), "");
      else if ((*cavalli)[j].media() < 4.0)
	item3 = new QTableWidgetItem(QIcon(":/status/pictures/scarso.bmp"), "");
      else
	item3 = new QTableWidgetItem(QIcon(":/status/pictures/suff.bmp"), "");
      
      ui.cavalliView->setItem(i, 0, item0);
      ui.cavalliView->setItem(i, 1, item1);
      ui.cavalliView->setItem(i, 2, item2);
      ui.cavalliView->setItem(i, 3, item3);
      if ((*cavalli)[j].selezione() != 0) {
	ui.cavalliView->item(i,0)->setFlags(!Qt::ItemIsEnabled);
	ui.cavalliView->item(i,1)->setFlags(!Qt::ItemIsEnabled);
	ui.cavalliView->item(i,2)->setFlags(!Qt::ItemIsEnabled);
	ui.cavalliView->item(i,3)->setFlags(!Qt::ItemIsEnabled);
	if ((*cavalli)[j].selezione() > 5) {
	  ui.cavalliView->item(i,0)->setSelected(1);
	  ui.cavalliView->item(i,1)->setSelected(1);
	  ui.cavalliView->item(i,2)->setSelected(1);
	  ui.cavalliView->item(i,3)->setSelected(1);
	}
      }      
    }  
  }
}

TrattaDialog::~TrattaDialog() {}

void TrattaDialog::cambiaCaption(QString s) {
    QString cap = "Scelta Cavalli (" + s +")";
    setWindowTitle(cap);
}

QVector<int> TrattaDialog::getSelection() {

  QVector<int> result;
  result.resize(cavalli->size());

  for(int i=0; i<ui.cavalliView->selectedItems().size(); i+=4) {
    for(int j=0; j<cavalli->size(); j++) {
      if ((*cavalli)[j].coscia() == ui.cavalliView->selectedItems().at(i)->row())
	// I cavalli scelti sono ordinati per numero assoluto
	// non per numero di coscia
	result[j] = 1;
    }
  }
  
  return result;
}
