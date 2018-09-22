#ifndef FORMTIPO_H
#define FORMTIPO_H

#include "ui_formazionetipoDialog.h"
#include "lib/giocatore.h"
#include "punteggi.h"

#include <QDialog>
#include <QStringList>
#include <QGraphicsScene>
#include <QList>

class FormTipo: public QDialog {
    Q_OBJECT

    public:
        FormTipo(QList<Giocatore*> g, QWidget *parent = 0, Punteggi* p = 0);
        void fillCombo();
        void setScene();
        void setCampo();
        void ordina();

    private slots:
        void changeFormazione(int);

    private:
        Ui::Dialog ui;
        QList<Giocatore*> giocatori;
        Punteggi* punt;
        QStringList list, nomi;
        QGraphicsScene* scene;
        QList<QPair<QString, float> > pairs[3];
        int n[3];
};

#endif
