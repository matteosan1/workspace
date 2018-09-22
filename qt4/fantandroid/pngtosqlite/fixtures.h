#ifndef FIXTURES_H
#define FIXTURES_H

#include <QList>
#include <QPair>

class Fixtures
{
public:
    Fixtures();

    void generateRoundRobin(int num_teams);

    void rotateArray(QList<int>& teams);

    QPair<int, int> match(int mainRound, int round, int nMatch);

    //QList<QList<int>> generateRoundRobinOdd(int num_teams);

    void generateRoundRobinEven(int num_teams);

private:
    QList<QList<QPair<int, int> > > m_rounds;
};

#endif
