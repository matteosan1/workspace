#ifndef CORSA_H
#define CORSA_H

#include "../tdpaliocommon/barbero.h"

#include <QVector>

struct Posizione {
  Posizione(int i) {
    colonnino = 0;
    traiettoria = i;
    velocita = 0;
    direzione = 0;
    giro = 0;
  };

  Posizione(Posizione p) {
    colonnino = p.colonnino;
    traiettoria = p.traiettoria;
    velocita = p.velocita;
    direzione = p.direzione;
    giro = p.giro;
  };

  bool operator==(Posizione p1) {
    if ((p1.colonnino == colonnino) && 
	(p1.traiettoria == traiettoria))
      return true;
    
    return false;
  };

  int colonnino;
  int velocita;
  int traiettoria;
  float direzione;
  int giro;
};

struct Colonnini {
  int larghezza;
  int best;
};

class Corsa {
  
 public:
  Corsa() {};
  Corsa(QVector<Barbero>*);

  ~Corsa() { //FIXME distruggi i vari puntatori 
  };
  
  void mossa();
  void loopCorsa();
  void calcolaTraiettoria();
  void calcoloVelocita();

 private:
  QVector<Barbero>* barberi;
  QVector<Posizione> posBarberi;
  QVector<Colonnini> piazza;
  int canape[10];
};

#endif
