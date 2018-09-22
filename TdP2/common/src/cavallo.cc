#include "cavallo.h"

namespace common {

Cavallo::Cavallo() :
    m_indice(0),
    m_nome(""),
    m_eta(0)
{
    for(int i=0; i<4; i++)
        m_capacita[i] = 0;

    for (int i=0; i<3; ++i)
        m_score[i] = 0;
}

Cavallo::~Cavallo()
{}

float Cavallo::media()
{
    float m = (float)(precisione()+velocita()+scatto())/3.;
    return m;
}

QList<int> Cavallo::caratteristiche()
{
    QList<int> a;
    for(int i=0; i<4; i++)
        a.append(m_capacita[i]);

    return a;
}

/*
QDataStream& operator<<(QDataStream& out, Cavallo x) {

  x.Nome.replace(" ", "_");
  out << x.Nome;
  out << x.index;
  out << x.colore;
  for(int i=0; i<3; i++)
    out << x.Capacita[i];
  for(int i=0; i<4; i++)
    out << x.Score[i];
  
  out << x.coscia_;
  out << x.selezione_;
  out << x.forma_;

  return out;
}

QTextStream& operator<<(QTextStream& out, Cavallo x) {

  x.Nome.replace(" ", "_");

  out << x.Nome << " ";
  out << x.index << " ";
  out << x.colore << "\n";
  for(int i=0; i<3; i++)
    out << x.Capacita[i] << " ";
  for(int i=0; i<4; i++)
    out << x.Score[i] << " ";

  out << "\n";
  
  return out;
}

QTextStream& operator>>(QTextStream& in, Cavallo& x) {
  string s;
  in >> x.Nome;
  x.Nome.replace("_", " ");

  in >> x.index;
  in >> x.colore;

  for(int j=0; j<3; j++)
    in >> x.Capacita[j];

  for(int j=0; j<4; j++)
    in >> x.Score[j];

  return in;
}

QDataStream& operator>>(QDataStream& in, Cavallo& x) {

  in >> x.Nome;
  x.Nome.replace("_", " ");
  
  in >> x.index;
  in >> x.colore;
    
  for(int j=0; j<3; j++)
    in >> x.Capacita[j];
    
  for(int j=0; j<4; j++)
    in >> x.Score[j];
  
  in >> x.coscia_;
  in >> x.selezione_;
  in >> x.forma_;

  return in;
}
*/
}
