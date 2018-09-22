#ifndef RULESETTER_H
#define RULESETTER_H

#include <QDialog>
#include <QSqlQuery>

enum RuoloEnum
{
    Nullo = -1,
    Portiere = 10,
    DifensoreTerzino = 21,
    DifensoreCentrale = 22,
    CentrocampistaCentrale = 31,
    CentrocampistaEsterno = 32,
    CentrocampistaTrequartista = 33,
    AttaccanteCentrale = 41,
    AttaccanteMovimento = 42,
    PortiereFuoriRosa = 110,
    DifensoreTerzinoFuoriRosa = 121,
    DifensoreCentraleFuoriRosa = 122,
    CentrocampistaCentraleFuoriRosa = 131,
    CentrocampistaEsternoFuoriRosa = 132,
    CentrocampistaTrequartistaFuoriRosa = 133,
    AttaccanteCentraleFuoriRosa = 141,
    AttaccanteMovimentoFuoriRosa = 142,
    Panchina = 999
};

class RuleSetter : public QDialog
{
public:
    explicit RuleSetter(QSqlQuery& query, QDialog* parent = 0);
    ~RuleSetter() {}

public:
    int m_win;
    int m_goal;
    float m_yellow;
    int m_red;
    int m_assist;
    int m_missedPenalties;
    int m_savedPenalties;
    int m_ownGoal;
    int m_captain;
    int m_outOfRole;
    bool m_autoGoalkeeper;

    // goal thresholds

    static int roleToInt(QString& role);
};

#endif // RULESETTER_H
