#ifndef CONTRADA_H
#define CONTRADA_H

#include <QString>
#include <QTextStream>
#include <QDataStream>

namespace common {

class Contrada {

public:
    Contrada();
    ~Contrada();

    QString nome() const { return m_nome; }
    QString nomeCompleto() const { return m_nomeCompleto; }

    quint8 indice() const { return m_indice; }

    int popolo() const { return m_status[0]; }
    int denaro() const { return m_status[1]; }
    int umore() const { return m_status[2]; }

    int luglio() const { return m_vittorie[0]; }
    int agosto() const { return m_vittorie[1]; }
    int straordinario() const { return m_vittorie[2]; }
    int cuffia() const { return m_vittorie[3]; }

    int giocatore() const { return m_giocatore; }
    int fantino() const { return m_fantino; }
    int barbero() const { return m_barbero; } // ????????
    int monta() const { return m_monta; } // ???????

    int avversaria();

    int feelingContrade(int i) const { return m_feelingContrade[i]; }

    //friend QDataStream& operator<<(QDataStream& out, Contrada x);
    //friend QTextStream& operator<<(QTextStream& out, Contrada x);
    //friend QTextStream& operator>>(QTextStream& in, Contrada& x);
    //friend QDataStream& operator>>(QDataStream& in, Contrada& x);
    void setContrada(int j, QString a, QString d, int* b, int* c);
    void setGiocatore(const int& i) { m_giocatore = i; }
    void setBarbero(const int& b) { m_barbero = b; }
    void setMonta(const int& m) { m_monta = m; }

private:
    QString m_nome;
    QString m_nomeCompleto;
    quint8  m_indice;              // 1 Aquila, 2 Bruco, 3 Chiocciola...
    int     m_status[3];           // popolo, denaro, umore
    int     m_vittorie[4];         // luglio, agosto, settembre, cuffia
    int     m_giocatore;           // -1 niente altrimenti indice del vettore di giocatori
    int     m_fantino;             // eventuale indice del fantino di contrada
    int     m_feelingContrade[17]; // rapporto con le altre contrade
    int     m_barbero;
    int     m_monta;
};

} // common

#endif
