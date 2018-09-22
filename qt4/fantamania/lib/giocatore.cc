#include "giocatore.h"

#include <iostream>

Giocatore::Giocatore() {
  cognome = "";
  prezzo = 0;
  ruolo = 0;
  for(int i=0; i<50; ++i)
    prestazioni[i].SetNull();
}

float Giocatore::GetMedia(Punteggi* p) {
  
  int giocate = GetGiocate();
  float somma = 0.;
  
  for(int i=0; i<50; ++i)
    somma += GetVoto(i, p);
  
  if (giocate != 0)
    return somma/(float)giocate;
  else
    return 0;
}

int Giocatore::GetAmmonizioni() {
  int result = 0;
  
  for(int i=0; i<50; ++i)
    if (prestazioni[i].Sanzioni() == 1)
      result++;
  
  return result;
}

int Giocatore::GetEspulsioni() {
  int result = 0;
  
  for(int i=0; i<50; ++i)
    if (prestazioni[i].Sanzioni() == 2)
      result++;
  
  return result;
}

QString Giocatore::GetPresenze() {
  
  int result = 0, result1 = 0;
  
  for(int i=0; i<50; ++i) {
    if (prestazioni[i].Formazione() == 1)
      result++;
    
    if (prestazioni[i].Formazione() == 2)
      result1++;
  }
  
  QString s = QString("%1 (%2)").arg(result).arg(result1);
  
  return s;
}

int Giocatore::GetGiocate() {
  int giocate=0;
  
  for(int i=0; i<50; ++i)
    if (prestazioni[i].GetVoto() != 0)
      giocate++;
  
  return giocate;
}

int Giocatore::GetRigori() {
  
  int giocate=0;
  
  for(int i=0; i<50; ++i) {
    if (GetRuolo() == 0)
      giocate += prestazioni[i].GoalRigore();
    else
      giocate += prestazioni[i].RigoriParati();
  }
  
  return giocate;
}

int Giocatore::GetAutogoal() {
  int giocate=0;
  
  for(int i=0; i<50; ++i)
    giocate += prestazioni[i].Autogoal();
  
  return giocate;
}

int Giocatore::GetGoal() {
  
  int giocate=0;
  
  for(int i=0; i<50; ++i) {
    if (GetRuolo() == 0)
      giocate += prestazioni[i].GoalSubiti();
    else
      giocate += prestazioni[i].Goal();
  }
  
  return giocate;
}


void Giocatore::SetGiocatore(QString a, QString b, int c, QString e, int f) {
  
  nome = a;
  cognome = b;
  ruolo  = c;
  squadra = e;
  prezzo = f;
}

Giocatore::~Giocatore() {}

void Giocatore::SetPartita(int giornata, int b, int *c, float v) {
  prestazioni[giornata].SetPartita(b, c, v);
  //prestazioni[giornata].SetHagiocato();
};

float Giocatore::GetVoto(int i, Punteggi* p) {
  
  float v = 0.0;
  v += prestazioni[i].GetVoto();                                    // voto
  v += (float)prestazioni[i].Autogoal() * (float)p->au;             // autogoal
  v += (float)prestazioni[i].Sanzioni() * (float)p->am * 0.5;       // ammonizioni etc.
  if ((ruolo == 0) || (ruolo == 5)) {
    v += (float)prestazioni[i].RigoriParati() * (float)p->rp;     // rigori parati
    v += (float)prestazioni[i].GoalSubiti() * (float)p->gsu;      // goal subiti
    //v -= (float)(prestazioni[i].RigoriGetData(5) -
    //	   prestazioni[i].GetData(4));                          // rigori non parati
  }
  else {
    v += (float)prestazioni[i].GoalRigore() * (float)p->rse;      // rigori segnati
    v += (float)prestazioni[i].Goal() * (float)p->gse;            // goal
    // Nuova regola del +4 per i goal dei difensori
    if (ruolo < 2)
      v += (float)prestazioni[i].Goal();

    v += (float)prestazioni[i].RigoriSbagliati() * (float)p->rsb; // rigori sbagliati
  }
  
  return v;
}

QTextStream& operator>>(QTextStream& in, Giocatore& x) {

  in >> x.nome >> x.cognome >> x.ruolo;
  in >> x.squadra >> x.prezzo;
  
  x.nome = x.nome.replace("_", " ");
  x.cognome = x.cognome.replace("_", " ");
  x.squadra = x.squadra.replace("_", " ");
  
  for(int i=0; i<50; i++)
    in >> x.prestazioni[i];
  
  return in;
}

QTextStream& operator<<(QTextStream& out, Giocatore x) {
  
  x.nome = x.nome.replace(" ", "_");
  x.cognome = x.cognome.replace(" ", "_");
  x.squadra = x.squadra.replace(" ", "_");
  
  out << x.nome << " " << x.cognome << " " << x.ruolo << '\n';
  out << x.squadra << " " << x.prezzo << '\n';
  for(int i=0; i<50; i++)
    out << x.prestazioni[i];
  
  return out;
}

Prestazione& Giocatore::GetPartita(int giornata) {
  return prestazioni[giornata];
}
