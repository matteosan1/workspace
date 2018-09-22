#include "cavallo.h"

Cavallo::Cavallo() {
  Nome = "";
  for(int i=0; i<4; i++) {
    Capacita[i] = 0;
    Score[i] = 0;
  }
}

Cavallo::~Cavallo()
{}

float Cavallo::media() {
  float m = (float)(precisione()+velocita()+scatto())/3.;
  return m;
}

QTextStream& operator<<(QTextStream& out, Cavallo x) {
  x.Nome.replace(" ", "_");

  out << x.Nome << "\n";
  out << x.index << " ";
  out << x.colore << " ";
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

  in >> x.index >> x.colore;

  for(int j=0; j<3; j++)
    in >> x.Capacita[j];

  for(int j=0; j<4; j++)
    in >> x.Score[j];

  //x.Nome = s;

  return in;
}

