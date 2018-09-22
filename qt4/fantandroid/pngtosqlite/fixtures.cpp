#include "fixtures.h"

#include <QDebug>

#define BYE -1

Fixtures::Fixtures()
{}

void Fixtures::generateRoundRobin(int num_teams)
{
    //if (num_teams % 2 == 0)
    generateRoundRobinEven(num_teams);
    //else
    //    return generateRoundRobinOdd(num_teams);
}


void Fixtures::rotateArray(QList<int>& teams)
{
    int temp = teams.last();
    for (int i=teams.length()-1; i>1; i--)
    {
        teams[i] = teams.at(i-1);
    }
    teams[1] = temp;
}

QPair<int, int> Fixtures::match(int mainRound, int round, int nMatch)
{
    QPair<int, int> temp = m_rounds.at(round).at(nMatch);

    bool swap = false;

    if (round%2 == 0)
        swap = !swap;

    if (mainRound%2 == 0)
        swap = !swap;

    if (!swap)
        return temp;
    else
        return QPair<int, int>(temp.second, temp.first);
}

void Fixtures::generateRoundRobinEven(int num_teams)
{
    QList<QPair<int, int> > round;
    QList<int> teams;
    for (int i=0; i<num_teams; ++i)
        teams.append(i);

    for (int j=0; j<num_teams-1; ++j)
    {
        round.clear();
        for (int i=0; i<num_teams/2; i++)
            round.append(QPair<int, int>(teams.at(i), teams.at(teams.size()-i-1)));

        m_rounds.append(round);
        rotateArray(teams);
    }
}
