#ifndef INSGIOCATORE_H
#define INSGIOCATORE_H

#include <QDialog>
#include <ui_newplayer.h>

#include "lib/giocatore.h"

using namespace std;

class InsGiocatore : public QDialog {
    Q_OBJECT

    public:
        InsGiocatore(Giocatore* g = 0, QWidget *parent = 0);
        void fillField();
        Giocatore* GetGiocatore() { return giocatore; };

    private slots:
        void changeRadio(bool);
        void changeNome(QString s);
        void changeCognome(QString s);
        void changePrezzo(QString s);
        void changeSquadra(QString s);

    private:
        Ui::NewPlayer ui;
        Giocatore* giocatore;
};

#endif
