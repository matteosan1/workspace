#include "ListaFantini.h"

#include <QMessageBox>

ListaFantini::ListaFantini(QVector<Fantino>* c, QWidget* parent)
    : QDialog(parent), fantini(c) {

    ui.setupUi(this);
    setWindowTitle("Lista Fantini Disponibili");

    //connect(ui.tableView, SIGNAL(itemSelectionChanged()), this, SLOT(selection()));

    ui.tableView->setRowCount(fantini->size());
    ui.tableView->setColumnCount(5);

    //ui.tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    //ui.tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    //ui.tableView->setSelectionMode(QAbstractItemView::MultiSelection);

    QStringList headerLabels;
    headerLabels << "Nome" << "Corsi" << "Vinti" << "Forma" << "Prezzo";
    ui.tableView->setHorizontalHeaderLabels(headerLabels);

    populateTable();

    ui.tableView->resizeColumnsToContents();
    //ui.tableView->resize(500, 300);
    ui.tableView->show();
}

void ListaFantini::populateTable() {
  
  // Ordina il vettore per cuffia
  for(int i=0; i<fantini->size(); ++i) {
    for(int j=i+1; j<fantini->size()-1; j++) {
      if ((*fantini)[i].prezzo() < (*fantini)[j].prezzo()) {
	Fantino temp = (*fantini)[i];
	(*fantini)[i] = (*fantini)[j];
	(*fantini)[j] = temp;
      }
    }
  }
      
  for(int i=0; i<fantini->size(); ++i) {
    QTableWidgetItem* item0 = new QTableWidgetItem((*fantini)[i].getNome());
    QTableWidgetItem* item1 = new QTableWidgetItem(QString("%1").arg((*fantini)[i].paliCorsi()));
    QTableWidgetItem* item2 = new QTableWidgetItem(QString("%1").arg((*fantini)[i].paliVinti()));
    QTableWidgetItem* item3;
    if ((*fantini)[i].media() > 6.0)
      item3 = new QTableWidgetItem(QIcon(":/status/pictures/buono.bmp"), "");
    else if ((*fantini)[i].media() < 4.0)
      item3 = new QTableWidgetItem(QIcon(":/status/pictures/scarso.bmp"), "");
    else
      item3 = new QTableWidgetItem(QIcon(":/status/pictures/suff.bmp"), "");
   
    QTableWidgetItem* item4 = new QTableWidgetItem(QString("%1").arg((*fantini)[i].prezzo()));

    ui.tableView->setItem(i, 0, item0);
    ui.tableView->setItem(i, 1, item1);
    ui.tableView->setItem(i, 2, item2);
    ui.tableView->setItem(i, 3, item3);
    ui.tableView->setItem(i, 4, item4);
  }
}

ListaFantini::~ListaFantini()
{}

