#ifndef INSVOTI_H
#define INSVOTI_H

#include <QDialog>
#include <QStringList>

#include "lib/giocatore.h"
#include "punteggi.h"

#include <vector>

using namespace std;

class InsVoti {
  
 public:
  InsVoti(QStringList&, vector<Giocatore>*, Punteggi*, int, int, QString&, QString&);
  bool SetVoti();
  bool Parser(QStringList, bool);
  QString modulo, giocavano, totale;
  int giornata;
  QString username, password;
  int Error();
  bool Connection();
  
 private:
  QStringList list;
  vector<Giocatore>* giocatori;
  Punteggi* punteggi;
  int num_partite;
};

#endif
