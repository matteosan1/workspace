#ifndef MYREPLY_H
#define MYREPLY_H

#include <QObject>

class MyReply : public QObject
{
    Q_OBJECT
public:
    explicit MyReply(QObject *parent = nullptr);

signals:

public slots:
};

#endif // MYREPLY_H
