#ifndef CAVALLO_H
#define CAVALLO_H

#include <QString>
//#include <QTextStream>
//#include <QDataStream>
#include <QList>

namespace common {

class Cavallo {
public:
    Cavallo();
    ~Cavallo();

    int indice() const { return m_indice; }
    int eta() const { return m_eta; }
    int tratte() const { return m_score[0]; }
    int paliCorsi() const { return m_score[1]; }
    int paliVinti() const { return m_score[2]; }

    int scatto() const { return m_capacita[0]; }
    int velocita() const { return m_capacita[1]; }
    int precisione() const { return m_capacita[2]; }

    int forma() const { return m_capacita[3]; }
    void setForma(const int& f) { m_capacita[3] = f; }

    float media();
    QList<int> caratteristiche();
    
    QString nome() { return m_nome; }
    int colore() { return m_colore; }

    int coscia() { return m_coscia; }
    void setCoscia(const int& c) { m_coscia = c; }

    int selezione() const { return m_selezione; }
    void piuSelezione() { m_selezione++; }
    void noSelezione() { m_selezione = 0; }

    void setInfortunio(const int& i) { m_infortunio = i; }

//    friend QDataStream& operator<<(QDataStream& out, Cavallo x);
//    friend QTextStream& operator<<(QTextStream& out, Cavallo x);
//    friend QTextStream& operator>>(QTextStream& in, Cavallo& x);
//    friend QDataStream& operator>>(QDataStream& in, Cavallo& x);

private:
    quint8  m_indice;
    QString m_nome;
    quint8  m_colore;
    quint8  m_eta;
    quint8  m_capacita[3]; // scatto(ripresa), velocita(v max), precisione(capacita` di infilarsi nei pertugi), forma
    quint8  m_score[3];    // tratte, palii corsi, palii vinti
    quint8  m_selezione;
    quint8  m_coscia;
    quint8  m_infortunio;
};
} // common
#endif
