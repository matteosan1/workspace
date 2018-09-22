#ifndef LISTAFANTINI_H
#define LISTAFANTINI_H

#include "ui_listagenerica.h"

#include "../tdpaliocommon/fantino.h"

#include <QVector>

class ListaFantini : public QDialog {
    Q_OBJECT

public:
    ListaFantini(QVector<Fantino>* c = 0, QWidget* parent = 0);
    ~ListaFantini();

    void populateTable();

public slots:

private:
    //int selezione[21];

    Ui::ListaGenerica ui;
    QVector<Fantino>* fantini;
};

#endif 
