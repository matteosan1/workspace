#include "rulesetter.h"

#include <QString>
#include <QVariant>
#include <QDebug>

RuleSetter::RuleSetter(QSqlQuery& query, QDialog* parent) : QDialog(parent)
{
    QString qryStr = "SELECT * from rules;";
    query.exec(qryStr);

    if (query.first())
    {
        m_win             = query.value(0).toInt();
        m_goal            = query.value(1).toInt();
        m_yellow          = query.value(2).toFloat();
        m_red             = query.value(3).toInt();
        m_assist          = query.value(4).toInt();
        m_missedPenalties = query.value(5).toInt();
        m_savedPenalties  = query.value(6).toInt();
        m_ownGoal         = query.value(7).toInt();
        m_captain         = query.value(8).toInt();
        m_outOfRole       = query.value(9).toInt();
        m_autoGoalkeeper  = query.value(10).toInt();
    }
}

int RuleSetter::roleToInt(QString& role)
{
    if (role == "P")
        return Portiere;
    else if (role == "DT")
        return DifensoreTerzino;
    else if (role == "DC")
        return DifensoreCentrale;
    else if (role == "CE")
        return CentrocampistaEsterno;
    else if (role == "CC")
        return CentrocampistaCentrale;
    else if (role == "CT")
        return CentrocampistaTrequartista;
    else if (role == "AC")
        return AttaccanteCentrale;
    else if (role == "AM")
        return AttaccanteMovimento;
    else if (role == "Pan")
        return Panchina;
    else
        qDebug() << "Ruolo non convertibile...";
}
