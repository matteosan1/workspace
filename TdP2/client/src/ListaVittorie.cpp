#include "ListaVittorie.h"

#include <QMessageBox>

ListaVittorie::ListaVittorie(QVector<Contrada>* c, QWidget* parent)
  : QDialog(parent), contrade(c) {
  
  ui.setupUi(this);
  setWindowTitle("Vittorie Riportate nel Campo");
  
  //connect(ui.cavalliView, SIGNAL(itemSelectionChanged()), this, SLOT(selection()));

  ui.tableView->setRowCount(contrade->size());
  ui.tableView->setColumnCount(5);
  
  ui.tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
  //ui.tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
  //ui.tableView->setSelectionMode(QAbstractItemView::MultiSelection);
  
  QStringList headerLabels;
  headerLabels << "Contrada" << "Luglio" << "Agosto" << "Straordinari" << "Totale";
  ui.tableView->setHorizontalHeaderLabels(headerLabels);
  
  populateTable();
  
  ui.tableView->resizeColumnsToContents();
  //ui.tableView->resize(500, 300);
  ui.tableView->show();
}

void ListaVittorie::populateTable() {

  for(int i=0; i<contrade->size(); ++i) {
    QTableWidgetItem* item0 = new QTableWidgetItem((*contrade)[i].getNome());
    QTableWidgetItem* item1 = new QTableWidgetItem(QString("%1").arg((*contrade)[i].luglio()));
    QTableWidgetItem* item2 = new QTableWidgetItem(QString("%1").arg((*contrade)[i].agosto()));
    QTableWidgetItem* item3 = new QTableWidgetItem(QString("%1").arg((*contrade)[i].straordinario()));
    int tot = (*contrade)[i].straordinario() + (*contrade)[i].agosto() + (*contrade)[i].luglio();
    QTableWidgetItem* item4 = new QTableWidgetItem(QString("%1").arg(tot));
    // FIXME aggiungere barberino
    /*
    QTableWidgetItem* item0;
    item3 = new QTableWidgetItem(QIcon(":/status/pictures/barbero_nomecon.bmp"), "");
    */

    ui.tableView->setItem(i, 0, item0);
    ui.tableView->setItem(i, 1, item1);
    ui.tableView->setItem(i, 2, item2);
    ui.tableView->setItem(i, 3, item3);
    ui.tableView->setItem(i, 4, item4);
    //ui.tableView->setItem(i, 0, item0);
  }
}

ListaVittorie::~ListaVittorie() {}

