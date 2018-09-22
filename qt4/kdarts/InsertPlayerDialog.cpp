#include "InsertPlayerDialog.h"

#include <QHeaderView>

InsertPlayerDialog::InsertPlayerDialog(QWidget* parent)
    : QDialog(parent) {

    ui.setupUi(this);

    model = new InsertPlayerModel();

    ui.tableView->verticalHeader()->hide();
    ui.tableView->setModel(model);
    ui.tableView->show();

}

void InsertPlayerDialog::insertRow() {
    ui.tableView->model()->insertRows(0, 1);
}

void InsertPlayerDialog::removeRow() {

    int row = ui.tableView->currentIndex().row();
    ui.tableView->model()->removeRows(row, 1);
}
