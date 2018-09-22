#include "contrada.h"

#include<iostream>
using namespace std;

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

void Contrada::setContrada(int j, QString a, QString d, int* b, int* c) {
  Nome = a;
  nomeCompleto = d;
  Indice = j;
  for(int i=0; i<4; i++)
    Status[i] = b[i];

  for(int i=0; i<17; i++)
    Feeling[i] = c[i];
}

QTextStream& operator<<(QTextStream& out, Contrada x) {

  x.nomeCompleto.replace(" ", "_");
  out << x.Nome << "\n";
  out << x.nomeCompleto << "\n";
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

QTextStream& operator>>(QTextStream& in, Contrada& x) {

  in >> x.Nome;
  in >> x.nomeCompleto;
  x.nomeCompleto.replace("_", " ");
  in >> x.Indice;
  for(int i=0; i<4; i++)
    in >> x.Status[i];
  for(int i=0; i<4; i++)
    in >> x.Vittorie[i];
  in >> x.Giocatore >> x.Fantino;
  for(int i=0; i<17; i++)
    in >> x.Feeling[i];

  return in;
}

int Contrada::avversaria() {
    for(int i=0; i<17; i++)
        if (Feeling[i] == 0)
            return i;

    return -1;
}
