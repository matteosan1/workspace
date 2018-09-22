#ifndef PARTITO_H
#define PARTITO_H

#include <QTextStream>
#include <QDataStream>

using namespace std;

class Partito {
 public:
  Partito();
  virtual ~Partito();
  
  int getContrada() { return contrada; };
  int getFermata() { return contrada2; };
  int getTipo() { return tipo; };
  int getPremio() { return soldi; };

  bool fatto() { return eseguito==2; };
  bool accettato() { return eseguito==1; };

  void setAccettato() { eseguito = 1; };
  void setFatto() { eseguito = 2; };
  void setPartito(int a, int b, int c);
  void setPartito(int a, int b, int c, int d);
 
  friend QTextStream& operator<<(QTextStream& out, Partito x);
  friend QDataStream& operator<<(QDataStream& out, Partito x);
  friend QDataStream& operator>>(QDataStream& in, Partito& x);
  friend QTextStream& operator>>(QTextStream& in, Partito& x);
  
 private:
  int contrada;
  int contrada2;
  int tipo;
  int soldi;
  bool eseguito;
};

#endif
