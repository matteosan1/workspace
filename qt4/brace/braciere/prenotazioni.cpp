#include "prenotazioni.h"

Prenotazione::Prenotazione() {

  nome = "";
  gente = 0;
  tavolo = -1;
  zona = Nulla;
  capotavola = false;
}

Prenotazione::~Prenotazione()
{}

Tavolo::Tavolo() {
  numero = 0;
  posti = 0;
  rimasti = 0;
  zona = Nulla;
}

Tavolo::~Tavolo()
{}

void Tavolo::SetPosti(int n) {
 
  posti = n;
  rimasti = n;
}

void Tavolo::AddPreno(Prenotazione p) {

  preno.push_back(p);
  rimasti -= p.GetGente();
}

int Tavolo::GetCapotavola() {
  
  int result = 0;
  for(unsigned int i=0; i<preno.size(); ++i)
    if (preno[i].GetCapotavola())
      result++;
  
  return result;
}
