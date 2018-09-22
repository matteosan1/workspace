#ifndef LISTAVITTORIE_H
#define LISTAVITTORIE_H

#include "ui_listagenerica.h"

#include "../tdpaliocommon/contrada.h"

#include <QVector>

class ListaVittorie : public QDialog {
    Q_OBJECT

public:
    ListaVittorie(QVector<Contrada>* c = 0, QWidget* parent = 0);
    ~ListaVittorie();

    void populateTable();

public slots:
    

private:
    //int selezione[21];

    Ui::ListaGenerica ui;
    QVector<Contrada>* contrade;
};

#endif
