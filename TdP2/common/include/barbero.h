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
  
  void setNumero(int i) { m_numero = i; }
  int numero() const { return m_numero; }

  void setContrada(Contrada* c) { m_contrada = c; }
  void setFantino(Fantino* c) { m_fantino = c; }
  void setCavallo(Cavallo* c) { m_cavallo = c; }
  
  void setEstrazione(int i) { m_estrazione_ = i; }
  int estrazione() const { return m_estrazione; }

  void setProve(ProveStrategie p);
  ProveStrategie prove() { return m_prove; }
  
  void setStrategia(int a) { m_strategia = a; }
  int strategia() const { return m_strategia; }
  
  void setAvversaria(int a) { m_avversaria = a; }
  int avversaria() const { return m_avversaria; }
  
  void setForma(int j, int f) { m_forma[j] = f; }
  int forma(int i) { return m_forma[i]; }
  int indice(int i) const { return m_indice[i]; }
  
  Contrada* contrada() { return m_contrada; }
  Fantino* fantino() { return m_fantino; }
  Cavallo* cavallo() { return m_cavallo; }

  Partito partito(int i) { return m_partiti[i]; }
  QVector<Partito> getPartiti() { return partiti_; };
  void clearPartiti() { partiti_.clear(); };	
  void clearPartito(int i) { partiti_.remove(i); };	
  bool partitiAccettati();
  bool setPartito(Partito p);
  bool setPartito(int a, int b, int c);
  void setPartitoFatto(int i);    
  
//  friend QTextStream& operator<<(QTextStream& out, Barbero& x);
//  friend QDataStream& operator<<(QDataStream& out, Barbero& x);
//  friend QDataStream& operator>>(QDataStream& in, Barbero& x);
//  friend QTextStream& operator>>(QTextStream& in, Barbero& x);
  
 private:
  int            m_numero;
  Contrada*      m_contrada;
  Fantino*       m_fantino;
  Cavallo*       m_cavallo;
  QList<Partito> m_partiti;
  int            m_strategia;
  int            m_avversaria;
  int            m_forma[3];
  ProveStrategie m_prove;
  int            m_indice[3];
  int            m_estrazione;
};

#endif
