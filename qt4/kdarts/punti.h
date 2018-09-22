#ifndef PUNTI_H
#define PUNTI_H

#include "ui_tabellone.h"

#include <QDialog>
#include <QString>

using namespace std;

class TabelloneDialog : public QDialog {
    Q_OBJECT

    public:
        TabelloneDialog(QWidget *parent = 0, int p=501, QString n="Alkemyst");

        QString getNome();
        int getPunti();
        void setPunti(int a);

    private:
        Ui::Dialog ui;
        QString nome;
        int punti;
};
#endif
