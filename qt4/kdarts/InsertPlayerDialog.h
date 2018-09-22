#ifndef INSERTPLAYERDIALOG_H
#define INSERTPLAYERDIALOG_H

#include "ui_insertplayer.h"
#include "InsertPlayerModel.h"

#include <QDialog>
#include <QStringList>
#include <QVector>

class InsertPlayerDialog : public QDialog {

    Q_OBJECT
    public:
        InsertPlayerDialog(QWidget *parent = 0);
        QVector<QString> GetPlayers() {
            InsertPlayerModel* temp = dynamic_cast<InsertPlayerModel*>(model);
            return temp->GetPlayers();
        }

    private slots:
        void insertRow();
        void removeRow();

    private:
        Ui::InsertPlayer ui;
        QAbstractItemModel* model;
};

#endif
