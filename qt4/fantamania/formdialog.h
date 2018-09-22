#ifndef FORMAZIONE_H
#define FORMAZIONE_H

#include "ui_formazione.h"
#include "lib/giocatore.h"
#include "punteggi.h"

#include <QDialog>
#include <QStringList>
#include <QString>
#include <QList>

class QComboBox;

class FormDialog: public QDialog {
    Q_OBJECT

public:
    FormDialog(QList<Giocatore*> g, Punteggi* punteggi = 0,  int p2 = -1, QWidget *parent = 0);
    QString readLines();
    int getGiornata() const { return m_giornata; }

private slots:
    void setGiornata(int);
    void checkModulo();
    void updatePlayers(const int& chosenModule);

private:
    void enableCombo(QComboBox* combo, int ruolo);
    void disableAllCombo();

    QStringList m_modules;

    int m_giornata;
    Ui::Formazione m_ui;
    int m_partite;
    QList<Giocatore*> m_giocatori;
    Punteggi* m_punteggi;
};

#endif
