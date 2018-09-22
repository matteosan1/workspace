#ifndef TDPALIOAICLIENT_H
#define TDPALIOAICLIENT_H

#include "../tdpaliocommon/code.h"
#include "../tdpaliocommon/giocatore.h"
#include "../tdpaliocommon/cavallo.h"
#include "../tdpaliocommon/fantino.h"
#include "../tdpaliocommon/barbero.h"
#include "../tdpaliocommon/code.h"

#include "../tdpaliocommon/MyStreamer.h"

#include <QTcpSocket>
#include <QVector>

class TRandom;

class TDPalioAiClient : public QObject {
    Q_OBJECT

public:
  TDPalioAiClient(int, TRandom*);

    //enum Fase {eInizio, eEstrazione, eTratta, eProve, eSegnatura, ePalio, eFinePalio};
    //enum Mese {Luglio, Agosto, Straordinario};

    void sendMessage(MessageCode);
    void openConnection(int a);
    void processMessage(QDataStream&);
    void sceltaCavalli(int, QVector<Cavallo>);
    void sceltaFantino(int, QVector<Fantino>);
    void inserisciPartito(QVector<Barbero>);
    void rispostePartiti(QVector<Barbero>);

    //bool salvaCorrente();
    //int Avversaria( int io );
    //int ordine_prove[10][6];

public slots:
    void incomingMessage();
    void displayError(QAbstractSocket::SocketError);
    /*
    void controller();
    QString getData();
    void close();
    void estrazione( int n );
    void nuovaFase();
    void formaCavalli();
    void visualizzaEstrazione();
    void SceltaCavalli();
    void Assegnazione( int * cav );
    void SceltaFantino();
    void Segnatura();
    void Prove();
    */
private:
    //Fase fase;
    //QString curFile;
    //QVector<Barbero> barberi;
    TRandom *random;
    //int luglio[17], agosto[17], settembre[17];
    //QVector<Cavallo> cavalli;
    //QVector<Fantino> fantini;
    //QVector<Contrada> contrade;
    //int corrono[17];
    bool modificato;
    //int anno;
    //Mese mese;
    //int nProva;

    QTcpSocket *tcpSocket;
    int socket_number;
    int isChoosing;    // probabilmente inutile
    Barbero* barbero;
    QVector<Fantino> fantini;
    int round;

    MyStreamer* myStreamer;
};

#endif
