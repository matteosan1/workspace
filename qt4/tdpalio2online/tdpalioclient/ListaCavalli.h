#ifndef LISTACAVALLI_H
#define LISTACAVALLI_H

#include "ui_listatratta.h"

#include <QVector>
#include <QString>

class ListaCavalli : public QDialog {
    Q_OBJECT

public:
    ListaCavalli(QVector<QString>* c = 0, QWidget* parent = 0);
    ~ListaCavalli();

    void writeEdit();

public slots:

private:
    //int selezione[21];

    Ui::ListaTratta ui;
    QVector<QString>* cavalli;
};

#endif 
