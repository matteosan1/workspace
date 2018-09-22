#ifndef CLONECLIENT_H
#define CLONECLIENT_H

#include <QObject>
#include <zmq.hpp>
#include "zhelpers.hpp"

using namespace zmq;

class CloneClient : public QObject
{
    Q_OBJECT
public:
    explicit CloneClient(QObject *parent = 0);

    void startPoller();

signals:

public slots:

private:
    context_t* m_context;
    socket_t* m_subscriber;

    socket_t* m_sync;
};

#endif // CLONECLIENT_H



//  s_recv(syncclient);
//  std::cout << "Connected to subscriber" << std::endl;

//  int update_nbr = 0;
//  while(1) {
//    if (s_recv(subscriber).compare("END") == 0) {
//      std::cout << "FINE" << std::endl;
//      break;
//    }

//    update_nbr++;
//  }

//  std::cout << "Received " << update_nbr << "updates" << std::endl;
