#ifndef CAVALLO_H
#define CAVALLO_H

#include <QString>
#include <QTextStream>
#include <QDataStream>
#include <QVector>

using namespace std;

class Cavallo {
 public:
  Cavallo();
  virtual ~Cavallo();
  
  int indice() { return index; };
  int eta() { return Score[0]; };
  int tratte() { return Score[1]; };
  int paliCorsi() { return Score[2]; };
  int paliVinti() { return Score[3]; };
  
  int scatto() { return Capacita[0]; };
  int velocita() { return Capacita[1]; };
  int precisione() { return Capacita[2]; };
  
  float media();
  QVector<int> caratteristiche();
    
  QString getNome() { return Nome; };
  int getColore() { return colore; };

  int coscia() { return coscia_; };
  void setCoscia(int a) { coscia_ = a; };

  int selezione() { return selezione_; };
  void setSelezione() { selezione_ ++; };
  void noSelezione() { selezione_ = 0; };	  	

  int forma() { return forma_; };
  void setForma(int a) { forma_ = a; }; 
  
  void setInfortunio(int i) { infortunio_ = i; };	

  friend QDataStream& operator<<(QDataStream& out, Cavallo x);
  friend QTextStream& operator<<(QTextStream& out, Cavallo x);
  friend QTextStream& operator>>(QTextStream& in, Cavallo& x);
  friend QDataStream& operator>>(QDataStream& in, Cavallo& x);
  
 private:
  int index;
  QString Nome;
  int colore;
  int Capacita[3];      // scatto(ripresa), velocita(v max), precisione(capacita` di infilarsi nei pertugi)
  int Score[4];         // anni, tratte, palii corsi, palii vinti
  int selezione_;
  int coscia_;
  int forma_;
  int infortunio_;
};

#endif
