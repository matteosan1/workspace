#ifndef FANTA_H
#define FANTA_H

#include "ui_fanta.h"

#include <QMainWindow>
#include <QString>
#include <QItemSelection>
#include <QLabel>
#include <QList>

#include "lib/giocatore.h"
#include "punteggi.h"


class FantaDialog : public QMainWindow {
  Q_OBJECT

public:
    FantaDialog(QWidget *parent = 0);
    bool caricaFile(QString fileName);
    void fillList(bool);
    void ordina();
    void fileSaveAs();
    void salvaFile();
    float mediaTotale();

    //float votoPerGiornata(int);
    //QString schemaPerGiornata(int);

    QString username, password;
    void closeEvent(QCloseEvent *event);

private slots:
    void fileOpen();
    void insFormazione();
    void fileSave();
    void changeView(bool);
    void addPlayer();
    void modifyPlayer();
    void killPlayer();
    //void close();
    void nuovaSquadra();
    void tipo();
    void riassunto(const QModelIndex&);

private:
    Ui::fanta ui;
    QString curFile;
    QAbstractItemModel* model;
    bool isModified;
    QLabel* labelSq;

    // da mettere in una classe separata
    Punteggi* m_punteggi;
    QString nome, anno;
    int num_giocatori, schema, num_partite;
    int form[16];
    int sch[50], punteggio[50];
    QList<Giocatore*> m_giocatori;
};

#endif
