#ifndef TRATTADIALOG_H
#define TRATTADIALOG_H

#include "ui_tratta.h"

#include "../tdpaliocommon/cavallo.h"

#include <QVector>

class TrattaDialog : public QDialog {
    Q_OBJECT

public:
    TrattaDialog(int q, QVector<Cavallo>* c = 0, QWidget* parent = 0);
    ~TrattaDialog();

    QVector<int> getSelection();
    void populateTable();

public slots:
    void cambiaCaption(QString s);
    void selection();

private:
    Ui::Tratta ui;
    QVector<Cavallo>* cavalli;
    int limite;
};

#endif // TRATTADIALOG_H
