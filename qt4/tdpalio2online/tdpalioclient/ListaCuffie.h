#ifndef LISTACUFFIE_H
#define LISTACUFFIE_H

#include "ui_listagenerica.h"

#include "../tdpaliocommon/contrada.h"

#include <QVector>

class ListaCuffie : public QDialog {
    Q_OBJECT

public:
    ListaCuffie(QVector<Contrada>* c = 0, QWidget* parent = 0);
    ~ListaCuffie();

    void populateTable();

public slots:
    

private:
    //int selezione[21];

    Ui::ListaGenerica ui;
    QVector<Contrada>* contrade;
};

#endif
