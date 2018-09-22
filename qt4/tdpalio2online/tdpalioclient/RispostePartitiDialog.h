#ifndef RISPOSTEPARTITI_H
#define RISPOSTEPARTITI_H

#include "ui_rispostepartiti.h"

#include <QVector>

class RispostePartitiDialog : public QDialog {
    Q_OBJECT

public:
    RispostePartitiDialog(QVector<Partito>* c = 0, QWidget* parent = 0);
    ~RispostePartitiDialog();

    void populateTable();

public slots:

private:
    //int selezione[21];

    Ui::ListaGenerica ui;
    QVector<Partito>* partiti;
};

#endif 
