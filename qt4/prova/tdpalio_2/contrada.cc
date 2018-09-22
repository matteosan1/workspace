#include "contrada.h"

Contrada::Contrada() {
    Nome = "";
    for(int i=0; i<4; i++) {
        Status[i] = 0;
        Vittorie[i] = 0;
    }
    Giocatore = -1;
    Fantino = -1;

    for(int i=0; i<17; i++)
        Feeling[i] = 6;
}

Contrada::~Contrada()
{}

void Contrada::setContrada(int j, string a, string d, int* b, int* c) {
  Nome = a;
  nomeCompleto = d;
  Indice = j;
  for(int i=0; i<4; i++)
    Status[i] = b[i];
  
  for(int i=0; i<17; i++)
    Feeling[i] = c[i];
}

ostream& operator<<(ostream& out, Contrada x) {
  string s = x.nomeCompleto;
  for(unsigned int i=0; i<s.length(); i++) {
    if (s.substr(i,1) == " ")
      s.replace(i,1,"_");
  }

  out << x.Nome << "\n";
  out << s << "\n";
  out << x.Indice << "\n";
  for(int i=0; i<4; i++)
    out << x.Status[i] << " ";
  out << "\n";
  for(int i=0; i<4; i++)
    out << x.Vittorie[i] << " ";
  out << "\n";
  out << x.Giocatore << " " << x.Fantino << '\n';
  for(int i=0; i<17; i++)
    out << x.Feeling[i] << " ";
  out << "\n";
  
  return out;
}

istream& operator>>(istream& in, Contrada& x) {
  string s;

  in >> x.Nome;
  in >> s;
  in >> x.Indice;
  for(int i=0; i<4; i++)
    in >> x.Status[i];
  for(int i=0; i<4; i++)
    in >> x.Vittorie[i];
  in >> x.Giocatore >> x.Fantino;
  for(int i=0; i<17; i++)
    in >> x.Feeling[i];
  
  for(unsigned int i=0; i<s.length(); i++) {
    if (s.substr(i,1) == "_")
      s.replace(i,1," ");
  }
  
  x.nomeCompleto = s;

  return in;
}

int Contrada::avversaria() {
    for(int i=0; i<17; i++)
        if (Feeling[i] == 0)
            return i;

    return -1;
}

