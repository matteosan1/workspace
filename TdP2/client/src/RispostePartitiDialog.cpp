#include "RispostePartitiDialog.h"

#include <QMessageBox>

RispostePartitiDialog::RispostePartitiDialog(QVector<Partito>* c, QWidget* parent) : QDialog(parent), partiti(c) {
  
  ui.setupUi(this);
  //setWindowTitle("Lista Fantini Disponibili");
  
  //connect(ui.tableView, SIGNAL(itemSelectionChanged()), this, SLOT(selection()));
  
  ui.tableView->setRowCount(partiti->size());
  ui.tableView->setColumnCount(4);

  //ui.tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
  //ui.tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
  //ui.tableView->setSelectionMode(QAbstractItemView::MultiSelection);
  
  QStringList headerLabels;
  headerLabels << "Contrada" << "Tipo di Partito" << "Contro" << "Compenso";
  ui.tableView->setHorizontalHeaderLabels(headerLabels);
  
  populateTable();
  
  ui.tableView->resizeColumnsToContents();
  //ui.tableView->resize(500, 300);
  ui.tableView->show();
}

void RispostePartitiDialog::populateTable() {
  
  for(int i=0; i<partiti->size(); ++i) {
    QTableWidgetItem* item0 = new QTableWidgetItem((*barberi)[(*partiti)[i].chi()].getContrada()->getNome());
    if ((*partiti)[i].tipo == 1) 
      QTableWidgetItem* item1 = new QTableWidgetItem(QString("Fermare"));
    else 
      QTableWidgetItem* item1 = new QTableWidgetItem(QString("Andare piano"));
    
    QTableWidgetItem* item2 = new QTableWidgetItem((*barberi)[(*partiti)[i].controchi()].getContrada()->getNome());    
    QTableWidgetItem* item3 = new QTableWidgetItem(QString("%1").arg((*partiti)[i].getPremio()));

    ui.tableView->setItem(i, 0, item0);
    ui.tableView->setItem(i, 1, item1);
    ui.tableView->setItem(i, 2, item2);
    ui.tableView->setItem(i, 3, item3);
  }
}

RispostePartitiDialog::~RispostePartitiDialog()
{}

