#include "corsa.h"

Corsa::Corsa(QVector<Berbero>* b) : barberi(p) {
  
  piazza.clear();
  ifstream f("piazza.dat");
  while (!f.eof()) {
    Colonnini c;
    f >> c.larghezza;
    f >> c.best;
    piazza.push_back(c);
  }
  
  for(int i=0; i<10; i++) {
    // FIXME fissare le posizioni secondo l'ordine alla mossa
    Posizione p(i);
    posBarberi.push_back(p);
  }
}

void Corsa::loopCorsa() {
  mossa();

  // FIXME al primo che arriva alla fonte assegnare un vantaggio totale per il palio
  bool arrivo = false;
  while (!arrivo) {
    for(int i=0; i<10; i++) {
      calcoloVelocita(canape[i]);
      calcolaTraiettoria(canape[i]);

      if (posBarberi[i].giro == 4) {
	arrivo = true;
	break;
      }
      aggiornaParametri(i);
    }
  }

  // produci il report di arrivo
}

bool Corsa::controllaContatti(int contrada) {
  
  if (barberi[contrada].getPartiti().size() == 0)
    return;

  Posizione posTemp(posBarberi[contrada]);

  for(int i=0; i<10; i++) {
    if (i == contrada) 
      continue;
    
    // FIXME per il momento considera vicino solo contrade allo stesso colonnino
    if (posTemp.colonnino == posBarberi[i].colonnino) {
      int diff = abs(posTemp.traiettoria - posBarberi[i].traiettoria); 
      if (diff == 1) {
	QVector<Partito> partiti = barberi[contrada].getPartiti();
	for(int j=0; j<partiti.size(); j++) {
	  if (partiti[j].getTipo == 1) {
	    if (partiti[j].getFermata() == i) {
	      posBarbero[i].velocita /= .3;
	      barberi[contrada].setPartitoFatto(j);
	    }
	  }
	  if (partiti[j].getTipo == 2) {
	    if (partiti[j].getContrada() == i) {
	      barberi[contrada].setPartitoFatto(j);	      
	      return true;
	    }
	  }
	}
      }
    }
  }
    
  return false;
}

void Corsa::controllaCadute(int contrada) {

  int colonnino = posBarbero[contrada].colonnino;
  if (piazza[colonnino].zona == "S. Martino" || 
      piazza[colonnino].zona == "Casato") {
   
    // FIXME controlla se e` in curva e calcola probabilita di caduta in base al cavallo e al fantino
    // FIXME oltre che alla velocita e alla direzione

  } 
}

void Corsa::mossa() {
  
  // FIXME aggiungere partito per ostacolare contrade al canape
  int prende_la_mossa = -1;
  QVector<Partito> partiti = barberi[canape[10]].getPartiti();
  for(int i=0; i<partiti.size(); i++)
    if (partito[i].getTipo() == 2) 
      prende_la_mossa = partito[i].getContrada();

  for(int i=0; i<10; i++) {    
    if (canape[i] == prende_la_mossa) 
      posBarberi[canape[i]].colonnino += 10;  // FIXME calibrare il vantaggio

    float prontezza = 4*(random->Uniform(barberi[canape[i]].getFantino()->prontezza())/10);
    posBarberi[canape[i]].colonnino += (int)prontezza;  // FIXME calibrare il vantaggio

    posBarberi[canape[i]].traiettoria = (int)canape[i]/10*(int)piazza[posBarberi[canape[i]].colonnino].larghezza;
    posBarberi[canape[i]].velocita += barberi[canape[i]].getCavallo()->scatto();
    
    for(int j=0; j<10; j++) {
      if (j == canape[i])
	continue;
      if (posBarberi[canape[i]] == posBarberi[j]) {
	j = -1;
	if (posBarberi[canape[i]].traiettoria == piazza[posBarberi[canape[i]].colonnino].larghezza)
	  posBarberi[canape[i]].colonnino--;
	else 
	  posBarberi[canape[i]].larghezza++;
      } 
    }
  }
}

void Corsa::calcoloTraiettoria(int contrada) {

  float dir[3];

  int velocita = posBarbero[contrada].velocita();

  for(int i=0; i<velocita; i++) {

    int dist = posBarbero[contrada].traiettoria - piazza[posBarbero[contrada].colonnino+1].best;

    Posizione posTemp(posBarbero[contrada]);
    posTemp.colonnino++;   
    // dritto
    dir[0] = 1;
    for(int j=0; j<10; j++) {
      if (canape[j] == contrada)
	continue;
      if (posTemp == posBarbero[canape[j]])
	dir[0] = 100;
    }
    // sinistra
    int dist1 = dist + 1;
    if (abs(dist) > abs(dist1))
      dir[1] = 1.5;
    else
      dir[1] = 0.5;
    if (direzione < 0)
      dir[1] -= 2;
    if (posBarbero[contrada].traiettoria == piazza[posBarbero[contrada].colonnino].larghezza)
      dir[1] = 100;
    posTemp.traiettoria++;
    for(int j=0; j<10; j++) {
      if (canape[j] == contrada)
	continue;
      if (posTemp == posBarbero[canape[j]])
	dir[0] = 100;
    }
    // destra
    dist1 = dist - 1;
    if (abs(dist) > abs(dist1))
      dir[2] = 1.5;
    else
      dir[2] = 0.5;
    if (direzione > 0)
      dir[2] -= 2;
    if (posBarbero[contrada].traiettoria == 0)
      dir[2] = 100;
    posTemp.traiettoria -= 2;
    for(int j=0; j<10; j++) {
      if (canape[j] == contrada)
	continue;
      if (posTemp == posBarberi[canape[j]])
	dir[0] = 100;
    }

    if ((dir[0] == 100) && (dir[1] == 100) &&(dir[2] == 100)) {
      // FIXME fermati e rallenta a quello davanti
      break;
    }

    int direzione = -1;
    float min = -1;
    for(int j=0; j<3; j++) {
      if (dir[j] < min || min == -1) {
	direzione = j;
	min = dir[j];
      }
    }
    
    float step = (posBarbero[contrada].traiettoria - piazza[posBarbero[contrada].colonnino].best)*0.09;
    posBarberi[contrada].colonnino += step;
    if (direzione == 0) {
      if (posBarberi[contrada].direzione > 0)
	posBarberi[contrada].direzione -= 0.2;
      if (posBarberi[contrada].direzione < 0)
	posBarberi[contrada].direzione += 0.2;
    }
    if (direzione == 1) {
      posBarberi[contrada].larghezza++;
      posBarberi[contrada].direzione = 1;
    }
    
    if (direzione == 2) {
      posBarberi[contrada].larghezza--;
      posBarberi[contrada].direzione = -1;
    }

    if (controllaContatti()) {
      // FIXME deve forse rallentare
      break;
    }

    controllaCaduta();
    if (posBarberi[contrada].colonnino > 100) {
      posBarberi[contrada].giro++;
      posBarberi[contrada].colonnino = (posBarberi[contrada].colonnino % 100);
    }
  }
}

void Corsa::calcoloVelocita() {
  // calcola velocita in base allo scatto
  // alla velocita massima
  // alla resistenza
}

