#ifndef BARBERI_H
#define BARBERI_H

#include "contrada.h"
#include "fantino.h"
#include "cavallo.h"
#include "partito.h"

#include <QDataStream>
#include <QTextStream>
#include <QPair>

using namespace std;

typedef QVector<QPair<int, int> > ProveStrategie;

class Barbero {
 public:
  Barbero();
  virtual ~Barbero();
  
  void setNumero(int i) { numero_ = i; };
  int getNumero() { return numero_; };	 	

  void setContrada(Contrada* c) { contrada = c; };
  void setFantino(Fantino* c) { fantino = c; };
  void setCavallo(Cavallo* c) { cavallo = c; };
  
  void setEstrazione(int i) { estrazione_ = i; };	
  int estrazione() { return estrazione_; };

  void setProve(ProveStrategie p);
  ProveStrategie getProve() { return prove; };
  
  void setStrategia(int a) { theStrategia = a; };
  int strategia() { return theStrategia; };
  
  void setAvversaria(int a) { theAvversaria = a; };
  int avversaria() { return theAvversaria; };
  
  void setForma(int j, int f) { theForma[j] = f; };
  int forma(int i) { return theForma[i]; };
  int getIndice(int i) { return indice[i]; };
  
  Contrada* getContrada() { return contrada; };
  Fantino* getFantino() { return fantino; };
  Cavallo* getCavallo() { return cavallo; };

  Partito partito(int i) { return partiti_[i]; };
  QVector<Partito> getPartiti() { return partiti_; };
  void clearPartiti() { partiti_.clear(); };	
  void clearPartito(int i) { partiti_.remove(i); };	
  bool partitiAccettati();
  bool setPartito(Partito p);
  bool setPartito(int a, int b, int c);
  void setPartitoFatto(int i);    
  
  friend QTextStream& operator<<(QTextStream& out, Barbero& x);
  friend QDataStream& operator<<(QDataStream& out, Barbero& x);
  friend QDataStream& operator>>(QDataStream& in, Barbero& x);
  friend QTextStream& operator>>(QTextStream& in, Barbero& x);
  
 private:
  int numero_;	
  Contrada* contrada;
  Fantino* fantino;
  Cavallo* cavallo;
  QVector<Partito> partiti_;
  int theStrategia;
  int theAvversaria;
  int theForma[3];
  ProveStrategie prove;
  int indice[3];
  int estrazione_;	
};

#endif
