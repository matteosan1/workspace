#ifndef MYSOCKET_H
#define MYSOCKET_H

#include "zmq.hpp"
#include "zhelpers.hpp"

#include <QSocketNotifier>
#include <QObject>

using namespace zmq;

class MySocket : public QObject
{
    Q_OBJECT
public:
    explicit MySocket(QObject *parent = 0);
    ~MySocket();

private slots:
    //void on_pushButton_clicked();
    void readZMQData();

private:
    QSocketNotifier *qsn;
    context_t *context;
    socket_t *subscriber;
};

#endif // MYSOCKET_H
