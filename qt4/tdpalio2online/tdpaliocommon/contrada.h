#ifndef CONTRADA_H
#define CONTRADA_H

#include <QString>
#include <QTextStream>
#include <QDataStream>

using namespace std;

class Contrada {

    public:
        Contrada();
        virtual ~Contrada();

        QString getNome() { return Nome; };
	    QString getNomeCompleto() { return nomeCompleto; };

        unsigned int indice() { return Indice; };

        int popolo() { return Status[0]; };
        int denaro() { return Status[1]; };
        int umore() { return Status[2]; };

        int luglio() { return Vittorie[0]; };
        int agosto() { return Vittorie[1]; };
        int straordinario() { return Vittorie[2]; };
        int cuffia() { return Vittorie[3]; };

        int giocatore() { return Giocatore; };
        int fantino() { return Fantino; };
        int barbero() { return bar; };
        int monta() { return mon; };

        int avversaria();

        int feeling(int i) { return Feeling[i]; };

        friend QDataStream& operator<<(QDataStream& out, Contrada x);
        friend QTextStream& operator<<(QTextStream& out, Contrada x);
        friend QTextStream& operator>>(QTextStream& in, Contrada& x);
	friend QDataStream& operator>>(QDataStream& in, Contrada& x);
        void setContrada(int j, QString a, QString d, int* b, int* c);
        void setGiocatore(int i) { Giocatore = i; };
        void setBarbero(int b) { bar = b; };
        void setMonta(int m) { mon = m; };

    private:
        QString Nome;
	    QString nomeCompleto;
        unsigned int Indice;         // 1 Aquila, 2 Bruco, 3 Chiocciola...
        int Status[3];      // popolo, denaro, umore
        int Vittorie[4];    // luglio, agosto, settembre, cuffia
        int Giocatore;      // -1 niente altrimenti indice del vettore di giocatori
        int Fantino;        // eventuale indice del fantino di contrada
        int Feeling[17];    // rapporto con le altre contrade
        int bar, mon;
 };

#endif
