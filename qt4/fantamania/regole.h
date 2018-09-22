#ifndef REGOLE_H
#define REGOLE_H

#include "ui_regolamentoDialog.h"
#include "punteggi.h"
#include "GiocatoriInsert.h"

#include <QDialog>
#include <QModelIndex>

class Regole: public QDialog {
    Q_OBJECT

public:
    Regole(QWidget *parent = 0, Punteggi* p=0);
    QList<Giocatore*> GetGiocatori() {
        GiocatoriInsert* temp = dynamic_cast<GiocatoriInsert*>(model);
        return temp->GetGiocatori();
    }

private slots:
    void changeCheck(int);
    void changeSpin(int);
    void insertRow();
    void removeRow();

private:
    Ui::RegolamentoDialog ui;
    Punteggi* punt;
    QAbstractItemModel* model;
};

#endif
