#ifndef INSERTLINEUP_H
#define INSERTLINEUP_H

#include <QDialog>
#include <QStringList>

#include "ui_insertlineups.h"

struct Vote
{
    int id;
    QString name;
    int playedRole;
    int round;
    int scored;
    int conceded;
    int assist;
    int yellowCards;
    int redCards;
    int savedPenalty;
    int failedPenalty;
    int ownGoal;
    float vote;
};

namespace Ui {
    class UiInsertLineup;
}

class InsertLineup : public QDialog
{
    Q_OBJECT
public:
    explicit InsertLineup(QDialog *parent = 0);

    QString lineup();
    int     round();
    void setWindowTitle(QString& title);
    void parseLineup(QString& team, QString& tactic, QStringList& players, QStringList& role, QList<int>& captain, QList<int>& order);
    void parseVotes(QList<Vote>& votes);

signals:

protected slots:
    void lineupChanged();

private:
    Ui::UiInsertLineup m_ui;
    QString m_lineup;
};

#endif // INSERTLINEUP_H
