#ifndef PLAYER_H
#define PLAYER_H

#include <QObject>
#include <QString>

class Player : public QObject
{
    Q_OBJECT
public:
    explicit Player(QObject *parent = 0);

signals:

public slots:

public:
    QString name;
    int playedRole;
    int role;
    float vote;
    float finalVote;
    int order;
    int captain;
};

#endif // PLAYER_H
