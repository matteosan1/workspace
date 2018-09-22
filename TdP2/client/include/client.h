#ifndef TDPALIOCLIENT_H
#define TDPALIOCLIENT_H

#include "ui_tdpalio.h"

#include "../tdpaliocommon/giocatore.h"
#include "../tdpaliocommon/cavallo.h"
#include "../tdpaliocommon/code.h"
#include "../tdpaliocommon/MyStreamer.h"

#include <QTcpSocket>
#include <QVector>
#include <QTextEdit>
#include <QShortcut>

//class TRandom;

class TDPalioClient : public QMainWindow {
    Q_OBJECT

public:
    TDPalioClient(QWidget* parent = 0);

    void sendMessage(MessageCode);
    void processMessage(QDataStream&);
    void closeEvent(QCloseEvent* event);
    void assegnazione();
    void sceltaCavalli(int, QVector<Cavallo>);
    void sceltaFantino(int, QVector<Fantino>);

    void aggiornaContradaPanel(Contrada);
    void aggiornaCavalloPanel(Cavallo);
    void aggiornaContradeTabel(int, QStringList);

    void visualizzaTabellaVittorie(QVector<Contrada>*, int);
    void visualizzaTabellaFantini();
    void visualizzaTabellaCavalli();
    void visualizzaTabellaCuffie();
    void visualizzaStatusContrada();

    void visualizzaAssegnazione(QVector<int>, QVector<QString>, QVector<Cavallo>);
    void visualizzaEstrazione(QStringList);

    void leggiChat(QVector<QString>);
            //salvaCorrente();
    //int Avversaria( int io );
    //int ordine_prove[10][6];

public slots:
    void scriviChat();	
    void apriChat();
    void chiudiChat();
    void startGame();
    void becomeSpectator();
    void chooseContrada();
    void incomingMessage();
    void displayError(QAbstractSocket::SocketError);
    void openConnection();
    /*
    void controller();
    QString getData();
    void fileNew();
    void caricaFile( const QString & fileName );
    void fileOpen();
    void salvaFile( const QString & fileName );
    bool fileSave();
    bool fileSaveAs();
    void filePrint();
    */
    void nuovoGioco(QStringList, QStringList);
    void nuovoGiocatore(QStringList, QVector<int>);
    void aiutoInformazioni();
    void ready();
    void battesimo();
    void abilitaSuono(bool a);
    /*
    void estrazione( int n );

    void formaCavalli();
    void visualizzaEstrazione();
    void SceltaStrategia();
    void SceltaCavalli();
    void Assegnazione( int * cav );

    void Segnatura();
    void RisposteFantini();
    void InserisciPartito();
    void RispostePartiti();
    void Prove();
    */

 private:
    bool soundWanted;
    //QVector<Cavallo> cavalli;
    //QVector<Fantino> fantini;
    //QVector<Giocatore> giocatori;
    //QVector<Contrada> contrade;

    bool modificato;
    //int anno;
    //int nProva;

    Ui::MainWindow ui;

    QTcpSocket *tcpSocket;
    int isPlaying;

    Giocatore giocatore;
    QTextEdit* textStatus;
    QVector<int> selection;

    int number_int;
    QString text_string;
    int socket_number;

    MyStreamer* myStreamer;

    QShortcut* ctrlM, *esc;
    QStringList listaChat;
    QString chatPeer;	
};

#endif
