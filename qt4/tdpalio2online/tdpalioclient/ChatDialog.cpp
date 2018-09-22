#include "ChatDialog.h"

#include <QMessageBox>

ChatDialog::ChatDialog(TDPalioClient* tdp, QWidget* parent)
    : QDialog(parent), tdaplio(tdp) {

    ui.setupUi(this);
    // FIXME setta il titolo con il nome della contrada
    setWindowTitle("Lista Fantini Disponibili");

}

