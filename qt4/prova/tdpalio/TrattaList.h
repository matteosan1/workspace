#ifndef TRATTALIST_H
#define TRATTALIST_H

#include "cavallo.h"

#include <QAbstractTableModel>
#include <QVector>

using namespace std;

class TrattaList : public QAbstractTableModel {

 Q_OBJECT

 public:
  TrattaList(QVector<Cavallo>* c, QObject *parent = 0)
    : QAbstractTableModel(parent), cavalli(c) {
        for(int i=0; i<21; ++i)
            selezione.insert(i, 0);
    }

  int columnCount(const QModelIndex &parent = QModelIndex()) const;
  int rowCount(const QModelIndex &parent = QModelIndex()) const;
  QVariant data(const QModelIndex &index, int role) const;
  QVariant headerData(int section, Qt::Orientation orientation,
		      int role = Qt::DisplayRole) const;
  Qt::ItemFlags flags(const QModelIndex &index) const;

 private:
  QVector<Cavallo>* cavalli;
  QVector<int> selezione;

};
#endif
