#ifndef TDPALIOSERVER_H
#define TDPALIOSERVER_H

#include "../tdpaliocommon/giocatore.h"
#include "../tdpaliocommon/contrada.h"
#include "../tdpaliocommon/cavallo.h"
#include "../tdpaliocommon/fantino.h"
#include "../tdpaliocommon/barbero.h"
#include "../tdpaliocommon/code.h"
#include "../tdpaliocommon/MySocket.h"
#include "../tdpaliocommon/TRandom.h"
#include "../tdpaliocommon/MyStreamer.h"

#include "tdpalioaiclient.h"
#include "fase.h"

#include <QObject>
#include <QTcpServer>
#include <QTcpSocket>
#include <QVector>

class TDPalioServer : QObject {

Q_OBJECT

  //enum Fase {eInizio, eEstrazione, eTratta, eSceltaFantino, eProve, eSegnatura, ePalio, eFinePalio};
 enum Mese {Luglio, Agosto, Straordinario};

public:
    TDPalioServer(int a);
    void sendMessage(MessageCode, MySocket*);
    void sendMessage(MessageCode, int);
    void processMessage(QDataStream& in);
    void disconnection(int);
    bool caricaFile();
    void salvaFile();
    void controller();
    //void controller(Fase);
    void estrazione(int);
    void sceltaStrategia();
    void sceltaCavalli();
    void preTratta();
    void azzeraSockets();
    void assegnazione();
    void rispostaFantino();
    void formaCavalli();
    void sceltaFantino();
    void preSceltaFantino();
    QVector<Fantino> filtroFantini(Barbero);
    void prove();
    void inserisciPartito();
    void rispostaPartito();
    void segnatura();
    void palio();
    void finePalio();
    void miglioramentoProve(QString&);
    void mossa(); 
    void scegliContrada(int);

private slots:
    void acceptConnection();
    void incomingMessage();
    void error(QAbstractSocket::SocketError e);

private:

    TRandom* random;
    int luglio[17], agosto[17], settembre[17];
    int ordine_prove[10][6];
    QVector<Contrada> contrade;
    QVector<Fantino> fantini;
    QVector<Cavallo> cavalli;
    QVector<Giocatore> giocatori;
    QVector<Barbero> barberi;

    QTcpServer *tcpServer;

    QVector<TDPalioAiClient*> aiclients;
    QVector<MySocket*> sockets;

    int isChoosing;
    QString fileName;

    FaseGioco *fase;
    Mese mese;
    int anno;
    int nProva;
    int corrono[17];\

    MyStreamer *myStreamerIn, *myStreamerOut;
};

#endif
