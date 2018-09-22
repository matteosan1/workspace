#include "insertlineup.h"
#include <QDebug>

InsertLineup::InsertLineup(QDialog *parent) :
    QDialog(parent)
{
    m_ui.setupUi(this);
    connect(m_ui.textEdit, SIGNAL(textChanged()), this, SLOT(lineupChanged()));
}

void InsertLineup::lineupChanged()
{
    m_lineup = m_ui.textEdit->toPlainText();
}

QString InsertLineup::lineup()
{
    return m_lineup;
}

void InsertLineup::setWindowTitle(QString &title)
{
    // todo add window title
}

int InsertLineup::round()
{
    m_ui.spinBoxRound->value();
}

void InsertLineup::parseLineup(QString& team, QString& tactic, QStringList& players, QStringList& role, QList<int>& captain, QList<int>& order)
{
    //QString temp = m_ui.textEdit->toPlainText().trimmed();
    //qDebug() << QString("A%1A").arg(temp);
    QStringList lineupStringList = m_ui.textEdit->toPlainText().trimmed().split("\n");
    team   = lineupStringList.at(0);
    tactic = lineupStringList.at(1);
    tactic = tactic.mid(8);

    for (int i=0; i<11; i++)
    {
        QString lineupTemp = lineupStringList[i+3].replace("*", "");
        QStringList playerSplitted = lineupTemp.split(" ");
        if (playerSplitted.last() == "(C)")
        {
            captain.append(1);
            int len = playerSplitted.length();
            role << playerSplitted[len-2].split("[")[1].split("]")[0];//playerSplitted[len-2].mid(1, 2);
            qDebug() << role;
            QString temp = "";
            for (int i=0; i<len-3; i++)
                temp += playerSplitted.at(i) + " ";

            players << temp.trimmed();
        }
        else
        {
            captain.append(0);
            role << playerSplitted.last().split("[")[1].split("]")[0];//mid(1, 2);
            int len = playerSplitted.length();
            QString temp = "";
            for (int i=0; i<len-1; i++)
                temp += playerSplitted.at(i) + " ";
            players << temp.trimmed();
        }
        order.append(i);
    }

    for (int i=15; i<lineupStringList.length(); i++)
    {
        QStringList playerSplitted = lineupStringList.at(i).split(" ");
        QString temp = playerSplitted.at(0);
        players << temp.toUpper();
        role << "Pan";
        captain.append(0);
        order.append(i);
    }
}

void InsertLineup::parseVotes(QList<Vote>& votes)
{
    QStringList voteStringList = m_ui.textEdit->toPlainText().split("\n");
    foreach (QString line, voteStringList)
    {
        Vote v;
        QStringList splittedLine = line.split(",");
        v.name          = splittedLine.at(0);
        v.round         = splittedLine.at(1).toInt();
        v.scored        = splittedLine.at(2).toInt();
        v.conceded      = splittedLine.at(3).toInt();
        v.assist        = splittedLine.at(4).toInt();
        v.yellowCards   = splittedLine.at(5).toInt();
        v.redCards      = splittedLine.at(6).toInt();
        v.savedPenalty  = splittedLine.at(7).toInt();
        v.failedPenalty = splittedLine.at(8).toInt();
        v.ownGoal       = splittedLine.at(9).toInt();
        v.vote          = splittedLine.at(10).toFloat();

        votes.append(v);
    }
}
