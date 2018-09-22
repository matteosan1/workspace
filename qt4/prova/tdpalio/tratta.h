#ifndef TRATTA_H
#define TRATTA_H

#include "ui_tratta.h"

//#include "TrattaList.h"
#include "cavallo.h"

#include <QVector>

class TrattaDialog : public QDialog {
    Q_OBJECT

public:
    TrattaDialog(QVector<Cavallo>* c = 0, QWidget* parent = 0);
    ~TrattaDialog();

    QVector<int> getSelection();
    void populateTable();

public slots:
    void cambiaCaption(QString s);

private:
    int selezione[21];
    int limite;

    Ui::Tratta ui;
    QVector<Cavallo>* cavalli;
};

#endif // TRATTA_H
