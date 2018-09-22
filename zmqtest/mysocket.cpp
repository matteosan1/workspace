#include "mysocket.h"

#include <QDebug>

MySocket::MySocket(QObject *parent) : QObject(parent)
{
    /***** ZMQ *****/
    context = (context_t*)zmq_ctx_new ();
    subscriber = (socket_t*)zmq_socket (context, ZMQ_SUB);
    int rc = zmq_connect (subscriber, "tcp://localhost:5561");

    char *filter = (char*)"";
    rc = zmq_setsockopt (subscriber, ZMQ_SUBSCRIBE,filter, strlen (filter));
    unsigned int fd=0;
    size_t fd_size = sizeof(fd);
    rc = zmq_getsockopt(subscriber,ZMQ_FD,&fd,&fd_size);

    qsn = new QSocketNotifier(fd, QSocketNotifier::Read, this);
    connect(qsn, SIGNAL(activated(int)), this, SLOT(readZMQData()), Qt::DirectConnection);
}

MySocket::~MySocket()
{
    zmq_close (subscriber);
    zmq_ctx_destroy (context);
    //delete ui;
}

void MySocket::readZMQData()
{
    qsn->setEnabled(false);
    qDebug() << "Got data!";

    int events = 0;
    std::size_t eventsSize = sizeof(events);
    zmq_getsockopt(subscriber,ZMQ_EVENTS, &events, &eventsSize);
    if(events & ZMQ_POLLIN){
        qDebug() << " ======  Data to read ======";

        QString string = QString::fromUtf8(s_recv(*subscriber).c_str());
        qDebug() << "DATA: " << string;
        //free(string);
    }

    qsn->setEnabled(true);
}
