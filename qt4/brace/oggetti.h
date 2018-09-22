#ifndef _OGGETTI_
#define _OGGETTI_

#include<qstring.h>
#include<qdatetime.h>

#include<fstream>
#include<vector>

using namespace std;

class Prenotazione {

 public:
  Prenotazione();
  Prenotazione(int i): id(i) {}
  ~Prenotazione();

  void SetNome(string i) { nome = i; };
  void SetTavolo(int i) { tavolo = i; };
  void SetGente(int i) { gente = i; };
  void SetId(int i) { id = i; };
  void SetDate(QDate q) { data = q; };
  
  string GetNome() { return nome; };
  int GetTavolo() { return tavolo; };
  int GetGente() { return gente; };
  int GetId() { return id; };
  QDate GetData() { return data; };
  
  friend ostream& operator<<(ostream& out, Prenotazione x);
  friend istream& operator>>(istream& in, Prenotazione& x);
  
 private:
  int id;
  QString nome;
  QDate data;
  int tavolo;
  int gente;
};

class Tavolo {
  
 public:
  Tavolo();
  ~Tavolo();

  void SetNumero(int n) { numero = n; };
  void SetPosti(int n);
  void SetPosizione(string s) { posizione = s; };
  
  void AddPreno(Prenotazione p);

  int GetNumero() { return numero; };
  int GetRimasti() { return rimasti; };
  int GetPosti() { return posti; };
  string GetPosizione() { return posizione; };
  vector<int> GetPreno() { return preno; };

  friend ostream& operator<<(ostream& out, Tavolo x);
  friend istream& operator>>(istream& in, Tavolo& x);

 private:
  vector<int> preno;
  int numero;
  int posti;
  int rimasti;
  QString posizione;
};


typedef std::vector<Tavolo> Cena;

class Braciere {
 public:
  Braciere  ();
  virtual ~Braciere();
    
  friend ostream& operator<<(ostream& out, Braciere x);
  friend istream& operator>>(istream& in, Braciere& x);
  
  std::vector<Prenotazione> lePreno;
  QDate fine;
  QDate inizio;
  QString nome;
  std::vector<Tavolo> iTavoli;
  std::vector<Cena> leCene;
};

#endif
