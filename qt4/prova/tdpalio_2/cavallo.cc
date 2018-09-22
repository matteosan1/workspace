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

ostream& operator<<(ostream& out, Cavallo x) {
  string s = x.Nome;
  for(unsigned int i=0; i<s.length(); i++) {
    if (s.substr(i,1) == " ")
      s.replace(i,1,"_");
  }

  out << s << "\n";
  out << x.indice << " ";
  out << x.colore << " ";
  for(int i=0; i<3; i++)
    out << x.Capacita[i] << " ";
  for(int i=0; i<4; i++)
    out << x.Score[i] << " ";
  out << "\n";

  return out;
}

istream& operator>>(istream& in, Cavallo& x) {

  string s;
  in >> s;

  for(unsigned int i=0; i<s.length(); i++) {
    if (s.substr(i,1) == "_")
      s.replace(i,1," ");
  }

  in >> x.indice >> x.colore;

  for(int j=0; j<3; j++)
    in >> x.Capacita[j];

  for(int j=0; j<4; j++)
    in >> x.Score[j];

  x.Nome = s;

  return in;
}

