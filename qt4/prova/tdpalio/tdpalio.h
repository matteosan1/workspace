#ifndef TDPALIO_H
#define TDPALIO_H

#include "ui_tdpalio.h"

#include "giocatore.h"
#include "contrada.h"
#include "fantino.h"
#include "cavallo.h"
#include "barbero.h"

#include <QVector>

class TRandom;

class TDPalio : public QMainWindow {
    Q_OBJECT

public:
    TDPalio(QWidget* parent = 0);

    enum Fase {eInizio, eEstrazione, eTratta, eProve, eSegnatura, ePalio, eFinePalio};
    enum Mese {Luglio, Agosto, Straordinario};

    bool salvaCorrente();
    int Avversaria( int io );
    int ordine_prove[10][6];

public slots:
    void controller();
    QString getData();
    void fileNew();
    void caricaFile( const QString & fileName );
    void fileOpen();
    void salvaFile( const QString & fileName );
    bool fileSave();
    bool fileSaveAs();
    void filePrint();
    void close();
    void nuovoGiocatore();
    void aiutoInformazioni();
    void estrazione( int n );
    void abilitaSuono( bool a );
    void nuovaFase();
    void formaCavalli();
    void visualizzaEstrazione();
    void SceltaStrategia();
    void SceltaCavalli();
    void Assegnazione( int * cav );
    void SceltaFantino();
    void Segnatura();
    void RisposteFantini();
    void InserisciPartito();
    void RispostePartiti();
    void Prove();


private:
    Fase fase;
    bool soundWanted;
    QString curFile;
    QVector<Barbero> barberi;
    TRandom *random;
    int luglio[17], agosto[17], settembre[17];
    QVector<Cavallo> cavalli;
    QVector<Fantino> fantini;
    QVector<Giocatore> giocatori;
    QVector<Contrada> contrade;
    int corrono[17];
    bool modificato;
    int anno;
    Mese mese;
    int nProva;

    //QPixmap image0;
    //QPixmap image1;
    //QPixmap image2;
    //QPixmap image3;
    //QPixmap image4;
    //QPixmap image5;

    Ui::MainWindow ui;
};

#endif // TDPALIO_H
