#ifndef MYSOCKET_H
#define MYSOCKET_H

#include <QTcpSocket>
#include "code.h"

enum Type {Human, AI};
enum Status {Disconnected = -4, Connected, Spectator, Waiting};

class MySocket {
  
 public:
  MySocket(Type t) { 
    username = "";
    socket = 0;
    state = Disconnected;
    type = t;
    answered = false;
    lastMessage = Dummy;	
  }

  ~MySocket() {
    delete socket;
  }
  
  QTcpSocket* socket;
  QString username;
  int state;
  int type;
  bool answered;
  MessageCode lastMessage;
};

#endif
