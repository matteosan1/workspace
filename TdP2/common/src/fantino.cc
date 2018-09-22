#include "fantino.h"

namespace common {

Fantino::Fantino() :
    m_nome(""),
    m_contrada(-1)
{
    for(int i=0; i<4; i++)
        m_capacita[i] = 0;

    for(int i=0; i<3; i++)
        m_score[i] = 0;

    for(int i=0; i<17; i++)
        m_feelingContrade[i] = 6;
}

Fantino::~Fantino()
{}

Offerta::~Offerta()
{}

Offerta::Offerta()
{}

void Offerta::setOfferta(const int& chiOffre, const int& controChi, const int& aVincere, const int& aPerdere)
{
    m_chi = chiOffre;
    m_controchi = controChi;
    m_avincere_ = aVincere;
    m_aperdere_ = aPerdere;
}

void Fantino::clearOfferte(const int& da , const int& a)
{

    for (int i=da; i<a; ++i)
    {
        m_offerte.removeAt(i);
    }
}

void Fantino::setOfferta(const int& chiOffre, const int& controChi, const int& aVincere, const int& aPerdere) {

    Offerta o;
    o.setOfferta(chiOffre, controChi, aVincere, aPerdere);
    m_offerte.append(o);
}

//void Fantino::creaFantino(int a0, QString a, int b, int c, int d, int e, int f, Offerta* g) {

//    index = a0;
//    Nome = a;
//    Capacita[0] = b;
//    Capacita[1] = c;
//    Capacita[2] = d;
//    for(int i=0; i<4; i++)
//        Score[i] = 0;

//    for(int i=0; i<17; i++)
//        Feeling[i] = 0;

//    contrada = e;
//    nOff = f;
//    for(int i=0; i<18; i++)
//        offerte[i] = *(g+i);
}

void Fantino::creaFantino(const int& indice,
                          const QString& nome,
                          const int& prontezza,
                          const int& determinazione,
                          const int& bravura,
                          const int& contrada) {

    m_indice = indice;
    m_nome = nome;
    m_capacita[0] = prontezza;
    m_capacita[1] = determinazione;
    m_capacita[2] = bravura;
    for(int i=0; i<3; i++)
        m_score[i] = 0;

    for(int i=0; i<17; i++)
        m_feelingContrade[i] = 0;

    contrada = e;
}

//void Fantino::setPiazza(int i) {

//    if ((i<5) && (i>1))
//        Score[3] += 100;
//    if (i>4)
//        Score[3] += 1;
//}

int Fantino::prezzo()
{
    int prezzo = 20;
    if ((paliCorsi() != 0) && (paliCorsi() < 5))
        prezzo += 10 * paliCorsi();

    int secondi = (int)(piazzamenti()/100);
    int ultimi = piazzamenti()-secondi*100;

    if (eta() < 11) {
        prezzo += 20 * secondi;
        prezzo -= 10 * ultimi;
    } else {
        prezzo -= 10 * secondi;
        prezzo -= 20 * ultimi;
    }
    prezzo += paliVinti() * 50;

    if ((paliCorsi() > 4) && (prezzo < 60))
        prezzo = 50;

    return prezzo;
}

/*
QTextStream& operator<<(QTextStream& out, Offerta x) {  

  out << x.chi_ << " ";
  out << x.controchi_ << " ";
  out << x.avincere_ << " ";
  out << x.aperdere_ << " ";
  out << x.coefficiente_ << "\n";

  return out;
}

QDataStream& operator<<(QDataStream& out, Offerta x) {  

  out << x.chi_ << " ";
  out << x.controchi_ << " ";
  out << x.avincere_ << " ";
  out << x.aperdere_ << " ";
  out << x.coefficiente_ << "\n";

  return out;
}

QDataStream& operator>>(QDataStream& in, Offerta& x) {  

  in >> x.chi_ >>  x.controchi_ >> x.avincere_ >> x.aperdere_  >> x.coefficiente_;

  return in;
}

QTextStream& operator<<(QTextStream& out, Fantino x) {
    //QString s = x.Nome;
    x.Nome.replace(" ", "_");

    out << x.Nome << " ";
    out << x.index << "\n";
    for(int i=0; i<3; i++)
      out << x.Capacita[i] << " ";
    for(int i=0; i<4; i++)
      out << x.Score[i] << "\n";
    for(int i=0; i<17; i++)
      out << x.Feeling[i] << " ";
    out << "\n";
    out << x.contrada << "\n";

    return out;
}

QDataStream& operator<<(QDataStream& out, Fantino x) {
    //QString s = x.Nome;
    x.Nome.replace(" ", "_");

    out << x.Nome;
    out << x.index;
    for(int i=0; i<3; i++)
        out << x.Capacita[i];
    for(int i=0; i<4; i++)
        out << x.Score[i];
    for(int i=0; i<17; i++)
        out << x.Feeling[i];
    out << x.contrada;

    return out;
}

QTextStream& operator>>(QTextStream& in, Fantino& x) {
    //string s;
    in >> x.Nome;
    x.Nome.replace("_", " ");

    in >> x.index;
    for(int i=0; i<3; i++)
        in >> x.Capacita[i];
    for(int i=0; i<4; i++)
        in >> x.Score[i];
    for(int i=0; i<17; i++)
        in >> x.Feeling[i];
    in >> x.contrada;

    //x.Nome = s;
    return in;
}

QDataStream& operator>>(QDataStream& in, Fantino& x) {
    //string s;
    in >> x.Nome;
    x.Nome.replace("_", " ");

    in >> x.index;
    for(int i=0; i<3; i++)
        in >> x.Capacita[i];
    for(int i=0; i<4; i++)
        in >> x.Score[i];
    for(int i=0; i<17; i++)
        in >> x.Feeling[i];
    in >> x.contrada;

    //x.Nome = s;
    return in;
}
*/
QList<int> Fantino::caratteristiche()
{
    QList<int> a;
    for(int i=0; i<3; i++)
        a.append(m_capacita[i]);

    return a;
}
} // common
