#ifndef GIOCATORILIST_H
#define GIOCATORILIST_H

#include "lib/giocatore.h"
#include "punteggi.h"

#include <QAbstractTableModel>
#include <QStringList>

#include <vector>

using namespace std;

class GiocatoriList : public QAbstractTableModel {

 Q_OBJECT

 public:
  GiocatoriList(int a, vector<Giocatore> g, bool t, Punteggi* p1, QObject *parent = 0)
    : QAbstractTableModel(parent), giornate(a), giocatori(g), toggle(t), p(p1) {}

  int columnCount(const QModelIndex &parent = QModelIndex()) const;
  int rowCount(const QModelIndex &parent = QModelIndex()) const;
  QVariant data(const QModelIndex &index, int role) const;
  QVariant headerData(int section, Qt::Orientation orientation,
		      int role = Qt::DisplayRole) const;
  float votoPerGiornata(int g) const;
  QString schemaPerGiornata(int g) const;
  bool isToggled() { return toggle; };

 private:
  QStringList stringList;
  int giornate;
  vector<Giocatore> giocatori;
  bool toggle;
  Punteggi* p;
};
#endif
