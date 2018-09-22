#include "ListaCuffie.h"

#include <QMessageBox>

ListaCuffie::ListaCuffie(QVector<Contrada>* c, QWidget* parent)
  : QDialog(parent), contrade(c) {
  
  ui.setupUi(this);
  setWindowTitle("Ritardi nelle vittorie");
  
  //connect(ui.cavalliView, SIGNAL(itemSelectionChanged()), this, SLOT(selection()));

  ui.tableView->setRowCount(contrade->size());
  ui.tableView->setColumnCount(3);
  
  ui.tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
  //ui.tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
  //ui.tableView->setSelectionMode(QAbstractItemView::MultiSelection);
  
  QStringList headerLabels;
  headerLabels << "Contrada" << "Cuffia" << "Ultima vittoria";
  ui.tableView->setHorizontalHeaderLabels(headerLabels);
  
  populateTable();
  
  ui.tableView->resizeColumnsToContents();
  //ui.tableView->resize(500, 300);
  ui.tableView->show();
}

void ListaCuffie::populateTable() {

  // Ordina il vettore per cuffia
  for(int i=0; i<contrade->size(); ++i) {
    for(int j=i+1; j<contrade->size()-1; j++) {
      if ((*contrade)[i].cuffia() < (*contrade)[j].cuffia()) {
	Contrada temp = (*contrade)[i];
	(*contrade)[i] = (*contrade)[j];
	(*contrade)[j] = temp;
      }
    }
  }
      
  for(int i=0; i<contrade->size(); ++i) {
    QTableWidgetItem* item0 = new QTableWidgetItem((*contrade)[i].getNome());
    QTableWidgetItem* item1 = new QTableWidgetItem(QString("%1").arg((*contrade)[i].cuffia()));
    // FIXME aggiungere ultima vittoria
    //QTableWidgetItem* item2 = new QTableWidgetItem(QString("%1").arg((*contrade)[i].agosto()));
    // FIXME aggiungere barberino
    /*
    QTableWidgetItem* item0;
    item3 = new QTableWidgetItem(QIcon(":/status/pictures/barbero_nomecon.bmp"), "");
    */
    ui.tableView->setItem(i, 0, item0);
    ui.tableView->setItem(i, 1, item1);
    //ui.tableView->setItem(i, 2, item2);
  }
}

ListaCuffie::~ListaCuffie() {}

