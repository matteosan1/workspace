#include "VoceSindaco.h"

#include <QSound>

VoceSindaco::VoceSindaco() {

  numeri.resize(10);
  nomi.resize(10);
  counter = 0;
}

void VoceSindaco::caricaSuoni(QString a, QString b) {

  numeri.push_back(a);
  nomi.push_back(b);
}

void VoceSindaco::playSound() {
  
  QSound::play(numeri[counter]);
  
  counter++;
}
