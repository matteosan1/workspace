#ifndef TEAMMODIFIER_H
#define TEAMMODIFIER_H

#include <QDialog>
#include <QSqlDatabase>
#include <QSqlRelationalTableModel>
#include <QModelIndex>

#include "customsqlmodel.h"

namespace Ui {
    class UiTeamModifier;
}

class TeamModifier : public QDialog
{
    Q_OBJECT

public:
    explicit TeamModifier(QSqlDatabase& db, QDialog *parent = 0);
    ~TeamModifier() {}

    QSqlDatabase dbTeam() { return m_teamModel->database(); }
    QSqlDatabase dbRoster() { return m_rosterModel->database(); }

public slots:
    void discardDB();
    void updateDB();
    void updateTeamImage();
    void insertRow();
    void removeRow();
    void insertTeamRow();
    void removeTeamRow();
    void updateView(QModelIndex& index);
    void selectTeam(QModelIndex index);

private:
    Ui::UiTeamModifier*       m_ui;
    QString                   m_teamName;
    QSqlDatabase              m_db;

    QSqlRelationalTableModel* m_rosterModel;
    CustomSqlModel*           m_teamModel;
};

#endif
