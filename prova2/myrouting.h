#ifndef MYROUTING_H
#define MYROUTING_H

#include <QObject>

class MyRouting : public QObject
{
    Q_OBJECT
public:
    explicit MyRouting(QObject *parent = nullptr);

signals:

public slots:
};

#endif // MYROUTING_H
