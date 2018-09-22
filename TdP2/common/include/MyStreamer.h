//
// C++ Interface: MyStreamer
//
// Description:
//
//
// Author: Matteo Sani <matteo.sani@cern.ch>, (C) 2008
//
// Copyright: See COPYING file that comes with this distribution
//
//
#ifndef MYSTREAMER_H
#define MYSTREAMER_H

#include "code.h"
#include "cavallo.h"
#include "contrada.h"
#include "giocatore.h"
#include "fantino.h"
#include "partito.h"

#include <QVector>
#include <QStringList>
#include <QDataStream>

#include <iostream>

using namespace std;
//FIXME da ogni classe "base" togliere namespace std;

class MyStreamer
{
 public:
  MyStreamer();
  virtual ~MyStreamer();
  void clear();
  void dump();	
  
  // Streamers
  int socket_number;
  MessageCode code;
  QVector<int> intStream;
  QVector<Cavallo> cavalloStream;
  QVector<Fantino> fantinoStream;
  QVector<Contrada> contradaStream;
  QVector<QStringList> stringListStream;
  QVector<QString> stringStream;
  QVector<Offerta> offertaStream;
  QVector<Partito> partitoStream;
  Giocatore giocatoreStream;
  
  friend QDataStream& operator<<(QDataStream& out, MyStreamer x);
  friend QDataStream& operator>>(QDataStream& in, MyStreamer& x);
};
#endif
