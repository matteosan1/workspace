#include "tratta.h"

//#include "CheckDelegate.h"

#include <QMessageBox>
//#include <QIcon>

TrattaDialog::TrattaDialog(QVector<Cavallo>* c, QWidget* parent)
    : QDialog(parent), cavalli(c) {

    ui.setupUi(this);

    ui.cavalliView->setRowCount(21);
    ui.cavalliView->setColumnCount(4);

    ui.cavalliView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui.cavalliView->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui.cavalliView->setSelectionMode(QAbstractItemView::MultiSelection);

    QStringList headerLabels;
    headerLabels << "Cavallo" << "Corsi" << "Vinti" << "Stato";
    ui.cavalliView->setHorizontalHeaderLabels(headerLabels);

    populateTable();

    ui.cavalliView->resizeColumnsToContents();
    //ui.cavalliView->resize(500, 300);
    ui.cavalliView->show();

    //FIXME checka il numero di cavalli selezionati prima di uscire

}

void TrattaDialog::populateTable() {

    for(int i=0; i<cavalli->size(); ++i) {
        QTableWidgetItem* item0 = new QTableWidgetItem((*cavalli)[i].getNome());
        QTableWidgetItem* item1 = new QTableWidgetItem(QString("%1").arg((*cavalli)[i].paliCorsi()));
        QTableWidgetItem* item2 = new QTableWidgetItem(QString("%1").arg((*cavalli)[i].paliVinti()));
        QTableWidgetItem* item3;
        if ((*cavalli)[i].media() > 6.0)
            item3 = new QTableWidgetItem(QIcon(":/status/pictures/buono.bmp"), "");
        else if ((*cavalli)[i].media() < 4.0)
            item3 = new QTableWidgetItem(QIcon(":/status/pictures/scarso.bmp"), "");
        else
            item3 = new QTableWidgetItem(QIcon(":/status/pictures/suff.bmp"), "");

        ui.cavalliView->setItem(i, 0, item0);
        ui.cavalliView->setItem(i, 1, item1);
        ui.cavalliView->setItem(i, 2, item2);
        ui.cavalliView->setItem(i, 3, item3);
    }
}

TrattaDialog::~TrattaDialog()
{}

void TrattaDialog::cambiaCaption(QString s) {
    QString cap = "Scelta Cavalli - " + s;
    setWindowTitle(cap);
}

QVector<int> TrattaDialog::getSelection() {
    QVector<int> result;

    for(int i=0; i<ui.cavalliView->selectedItems().size(); ++i)
        result.push_back(ui.cavalliView->selectedItems().at(i)->row());

    return result;
}
