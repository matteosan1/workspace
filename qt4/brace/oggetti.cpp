#include "oggetti.h"

Prenotazione::Prenotazione() {

  nome = "";
  gente = 0;
  tavolo = 0;
  
}

Prenotazione::~Prenotazione()
{}

Tavolo::Tavolo() {
  numero = 0;
  posti = 0;
  rimasti = 0;
  posizione = "";
}

Tavolo::~Tavolo()
{}

void Tavolo::SetPosti(int n) {
 
  posti = n;
  rimasti = n;
}

void Tavolo::AddPreno(Prenotazione p) {

  preno.push_back(p.GetId());
  rimasti -= p.GetGente();
} 

ostream& operator<<(ostream& out, Prenotazione x) {

  out << x.id << " ";
  out << x.nome << " ";
  out << x.data.toString() << " ";
  out << x.tavolo << " ";
  out << x.gente << "\n";
  
  return out;
  
}

istream& operator>>(istream& in, Prenotazione& x) {

  string s;
  in >> x.id >> s >> s >> x.tavolo >> x.gente;
  
  x.nome = s;
  // sistemare la data da stringa...
  //x.data(s);

  return in;
}
  
ostream& operator<<(ostream& out, Tavolo x) {

  out << x.numero << " " << x.posti << " " << x.rimasti << "\n";
  out << x.posizione << "\n";
  out << x.preno.size() << "\n";
  for(unsigned int i=0; i<x.preno.size(); i++)
    out << x.preno[i] << "\n";

  return out;
}

istream& operator>>(istream& in, Tavolo& x) {
  
  string s;
  unsigned int size;
  in >> x.numero >> x.posti >> x.rimasti;
  in >> s;
  x.posizione = s;
  in >> size;
  x.preno.resize(size);
  for(unsigned int i=0; i<size; i++)
    in >> x.preno[i];

  return in;
}

Braciere::Braciere() {
  nome = "";
}

Braciere::~Braciere()
{}

ostream& operator<<(ostream& out, Braciere x) {
  string s;
  //  string s = x.Nome;
  //for(unsigned int i=0; i<s.length(); i++) {
  //  if (s.substr(i,1) == " ")
  //    s.replace(i,1,"_");
  //}
  

  // FIXME problema stringa to data
  out << x.nome << "\n";
  out << s << "\n";
  out << s << "\n";
  
  out << x.iTavoli.size() << "\n";
  for(unsigned int i=0; i<x.iTavoli.size(); i++)
    out << x.iTavoli[i] << "\n";

  out << x.lePreno.size() << "\n";
  for(unsigned int j=0; j<x.lePreno.size(); j++)
    out << x.lePreno[j] << "\n";

  out << x.leCene.size() << "\n";
  for(unsigned int j=0; j<x.leCene.size(); j++) {
    for(unsigned int i=0; i<x.iTavoli.size(); i++) {
      out << x.leCene[j][i] << "\n";
    }
  }
  
  return out;
}

istream& operator>>(istream& in, Braciere& x) {

  unsigned int size, size_tav;
  string s;
  //string s;
  //in >> s;
  
  //for(unsigned int i=0; i<s.length(); i++) {
  //  if (s.substr(i,1) == "_")
  //    s.replace(i,1," ");
  //}
  in >> s;
  x.nome = s;
  // FIXME problema data
  in >> s;
  in >> s;  
  
  in >> size_tav;
  x.iTavoli.resize(size_tav);
  for(unsigned int i=0; i<x.iTavoli.size(); i++)
    in >> x.iTavoli[i];

  in >> size;
  x.lePreno.resize(size);
  for(unsigned int j=0; j<x.lePreno.size(); j++)
    in >> x.lePreno[j];

  in >> size;
  x.leCene.resize(size);
  for(unsigned int j=0; j<x.leCene.size(); j++) {
    for(unsigned int i=0; i<x.iTavoli.size(); i++) {
      in >> x.leCene[j][i];
    }
  }
  
  return in;
}

