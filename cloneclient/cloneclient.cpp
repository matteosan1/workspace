#include "cloneclient.h"

#include <QDebug>

CloneClient::CloneClient(QObject *parent) : QObject(parent)
{
    m_context = new context_t(1);

    m_subscriber = new socket_t(*m_context, ZMQ_SUB);
    m_subscriber->connect("tcp://localhost:5561");
    m_subscriber->setsockopt(ZMQ_SUBSCRIBE, "", 0);


    m_sync = new socket_t(*m_context, ZMQ_REQ);
    m_sync->connect("tcp://localhost:5562");

    s_send(*m_sync, "");
    s_recv(*m_sync);
    qDebug() << "Connected to subscriber";

    startPoller();
}

void CloneClient::startPoller()
{
    //  Initialize poll set
    pollitem_t items [] = {
        //{ receiver, 0, ZMQ_POLLIN, 0 },
        { m_subscriber, 0, ZMQ_POLLIN, 0 }
    };

    //  Process messages from both sockets
    while (1) {
        //message_t message;
        poll (&items [0], 2, -1);

//        if (items [0].revents & ZMQ_POLLIN) {
//            receiver.recv(&message);
//            //  Process task
//        }
        if (items [0].revents & ZMQ_POLLIN) {
            QString message = QString::fromUtf8(s_recv(*m_subscriber).c_str());
            //  Process weather update
            qDebug() << message;
        }
    }

}
