#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "teamModifier.h"
#include "fixtures.h"
#include "insertlineup.h"
#include "rulesetter.h"
#include "player.h"

#include <QFileDialog>
#include <QMessageBox>
#include <QInputDialog>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>
#include <QProcess>

MainWindow::MainWindow(QWidget *parent) :
  QMainWindow(parent),
  m_ui(new Ui::MainWindow)
{
    m_ui->setupUi(this);

    QObject::connect(m_ui->pushButtonOpen, SIGNAL(clicked(bool)), this, SLOT(loadDB()));
    QObject::connect(m_ui->pushButtonNew, SIGNAL(clicked(bool)), this, SLOT(newLeague()));
    QObject::connect(m_ui->pushButtonUpdate, SIGNAL(clicked(bool)), this, SLOT(updateLeague()));
    QObject::connect(m_ui->pushButtonFixtures, SIGNAL(clicked(bool)), this, SLOT(generateFixture()));
    QObject::connect(m_ui->pushButtonCup, SIGNAL(clicked(bool)), this, SLOT(makeCup()));
    QObject::connect(m_ui->pushButtonInsertLineup, SIGNAL(clicked(bool)), this, SLOT(insertLineup()));
    QObject::connect(m_ui->pushButtonInsertVotes, SIGNAL(clicked(bool)), this, SLOT(insertVotes()));
}

void MainWindow::loadDB()
{
    QString dbname = QFileDialog::getOpenFileName(0, "Choose Leauge", "", "*.sqlite");
    if (dbname == "")
        dbname = "team.sqlite";

    if(QSqlDatabase::contains("PIPPO"))
    {
        m_db = QSqlDatabase::database("PIPPO");
    }
    else
    {
        m_db = QSqlDatabase::addDatabase("QSQLITE", "PIPPO");
        m_db.setDatabaseName(dbname);
    }

    m_db.open();
}

void MainWindow::newLeague()
{
    loadDB();

    QSqlQuery query = QSqlQuery(m_db);
    query.exec("CREATE TABLE IF NOT EXISTS teamName (id INTEGER PRIMARY KEY, name TEXT, image BLOB, phone TEXT);" );
    query.exec("CREATE TABLE IF NOT EXISTS roster (id INTEGER PRIMARY KEY, name TEXT, surname TEXT, role INTEGER, price INTEGER, team TEXT, realTeam TEXT);");
    query.exec("CREATE TABLE IF NOT EXISTS yourTeam (name TEXT)");
    query.exec("CREATE TABLE IF NOT EXISTS leagueOwner (name TEXT)");
    if (!m_db.contains("roles"))
    {
        query.exec("CREATE TABLE IF NOT EXISTS roles (id INTEGER PRIMARY KEY, nRole INTEGER, name TEXT, shortName TEXT)");
        query.exec("INSERT INTO roles (id, nRole, name, shortName) VALUES (1, 0,  'Nullo',                      'N');");
        query.exec("INSERT INTO roles (id, nRole, name, shortName) VALUES (2, 10, 'Portiere',                   'P');");
        query.exec("INSERT INTO roles (id, nRole, name, shortName) VALUES (3, 21, 'DifensoreTerzino',           'DT');");
        query.exec("INSERT INTO roles (id, nRole, name, shortName) VALUES (4, 22, 'DifensoreCentrale',          'DC');");
        query.exec("INSERT INTO roles (id, nRole, name, shortName) VALUES (5, 31, 'CentrocampistaCentrale',     'CC');");
        query.exec("INSERT INTO roles (id, nRole, name, shortName) VALUES (6, 32, 'CentrocampistaEsterno',      'CE');");
        query.exec("INSERT INTO roles (id, nRole, name, shortName) VALUES (7, 33, 'CentrocampistaTrequartista', 'CT');");
        query.exec("INSERT INTO roles (id, nRole, name, shortName) VALUES (8, 41, 'AttaccanteCentrale',         'AC');");
        query.exec("INSERT INTO roles (id, nRole, name, shortName) VALUES (9, 42, 'AttaccanteMovimento',        'AM');");
    }

    query.exec("CREATE TABLE IF NOT EXISTS playerLineups (team TEXT, round INTEGER, name TEXT, ordering INTEGER, captain INTEGER);");
    query.exec("CREATE TABLE IF NOT EXISTS teamLineups (team TEXT, round INTEGER, name TEXT, tactic TEXT);");

    query.exec("CREATE TABLE IF NOT EXISTS playerStats (id INTEGER, \
               playedRole INTEGER,    \
               round INTEGER,         \
               scored INTEGER,        \
               conceded INTEGER,      \
               assist INTEGER,        \
               yellowCard INTEGER,    \
               redCard INTEGER,       \
               savedPenalty INTEGER,  \
               failedPenalty INTEGER, \
               ownGoal INTEGER,       \
               vote REAL);");

    // TODO CONTROLLARE tabelle mancanti
}

void MainWindow::updateLeague()
{
    if (!m_db.isOpen())
    {
        QMessageBox::warning(this, "AVVISO", "Non hai aperto nessun DB.", QMessageBox::Ok);
        return;
    }

    TeamModifier* teams = new TeamModifier(m_db);
    teams->dbTeam().transaction();
    teams->dbRoster().transaction();
    int ret = teams->exec();

    if (ret == QDialog::Accepted)
    {
        teams->dbTeam().commit();
        teams->dbRoster().commit();
    }
    else if (ret == QDialog::Rejected)
    {
        teams->dbTeam().rollback();
        teams->dbRoster().rollback();
    }

    delete teams;
}

void MainWindow::generateFixture()
{
    if (!m_db.isOpen())
    {
        QMessageBox::warning(this, "AVVISO", "Non hai aperto nessun DB.", QMessageBox::Ok);
        return;
    }

    Fixtures fixture;
    QSqlQuery query(m_db);

    int ret = QMessageBox::warning(this, "ATTENZIONE", "Stai per cancellare il vecchio calendario, sicuro ?", QMessageBox::Ok | QMessageBox::Abort);
    if (ret == QMessageBox::Ok)
    {
        query.exec("DELETE FROM fixture;");
        query.exec();
    }
    else
        return;

    QStringList teams;
    if (query.exec("SELECT name FROM teamName ORDER BY name;"))
    {
        while(query.next())
            teams << query.value("name").toString();
    }

    if (teams.size() < 2)
    {
        QMessageBox::critical(this, "ERRORE", "Non puoi creare un calendario con meno di 2 squadre.", QMessageBox::Abort);
        return;
    }

    int nRounds = QInputDialog::getInt(this, "CALENDARIO", "Numero di gironi:", 1, 1, 10);

    fixture.generateRoundRobin(teams.size());

    for (int round=0; round<nRounds; ++round)
    {
        for (int i1=0; i1<teams.size() - 1; ++i1)
        {
            //qDebug() << "GIORNATA: " << i1 + round*(teams.size()-1);
            for (int i=0; i<teams.size()/2; ++i)
            {
                //qDebug() << fixture.match(round, i1, i).first << "-" << fixture.match(round, i1, i).second;
                QString qryStr = "";
                qryStr = "INSERT INTO fixture (date, played,round,team1,team2,goal1,goal2,points1,points2) VALUES (";
                qryStr += QString("'',");
                qryStr += QString("0,");
                qryStr += QString::number(i1 + round*(teams.size()-1)) + QString(",");
                qryStr += QString("'") + teams.at(fixture.match(round, i1, i).first) + QString("',");
                qryStr += QString("'") + teams.at(fixture.match(round, i1, i).second) + QString("',");
                qryStr += QString("0,0,0,0);");

                //qDebug() << qryStr;
                if (!query.exec(qryStr))
                    qDebug() << query.lastError().text();
            }
        }
    }

}

void MainWindow::makeCup()
{

}

void MainWindow::insertLineup()
{
    if (!m_db.isOpen())
    {
        QMessageBox::warning(this, "AVVISO", "Non hai aperto nessun DB.", QMessageBox::Ok);
        return;
    }

    QSqlQuery query(m_db);
    QString qryStr;

    InsertLineup lineup;
    //lineup.setWindowTitle(QString(""));

    int ret = lineup.exec();

    if (ret == QDialog::Accepted)
    {
        QString team, tactic;
        QStringList players, role;
        QList<int> captain, order;
        lineup.parseLineup(team, tactic, players, role, captain, order);

        qryStr = "INSERT INTO teamLineups (team, round, tactic) VALUES (";
        qryStr += "'" + team + "',";
        qryStr += QString::number(lineup.round()) + ",";
        qryStr += "'" + tactic + "');";
        if (!query.exec(qryStr))
            qDebug() << query.lastError().text();
        qDebug() << qryStr;

        qDebug() << players.length() << role.length() <<captain.length() << order.length();
        for (int i=0; i<players.length(); ++i)
        {
            qryStr = "INSERT INTO playerLineups (team, round, name, role, ordering, captain) VALUES (";
            qryStr += "'" + team + "',";
            qryStr += QString::number(lineup.round()) + ",";
            qryStr += "'" + players.at(i) + "',";
            qryStr += QString::number((int)RuleSetter::roleToInt(role[i])) + ",";
            qryStr += QString::number(order.at(i)) + ",";
            qryStr += QString::number(captain.at(i)) + ");";

            qDebug() << qryStr;

            if (!query.exec(qryStr))
                qDebug() << query.lastError().text();
        }
    }
}

void MainWindow::insertVotes()
{
    if (!m_db.isOpen())
    {
        QMessageBox::warning(this, "AVVISO", "Non hai aperto nessun DB.", QMessageBox::Ok);
        return;
    }

    // todo check max giornata by the way I should have giornata already to modify votes

    QSqlQuery query(m_db);
    RuleSetter ruleSetter(query);
    m_db.transaction();

    QString inputFileName = QInputDialog::getText(this, "Inserimento Voti", "Nome del file con i voti:");
    int giornata = QInputDialog::getInt(this, "Inserimento Voti", "Giornata:", 1, 0, 36);
    QProcess p;
    p.start("python analizza_voti.py " + inputFileName + " " + QString::number(giornata));//, QStringList() << inputFileName << QString::number(giornata));
    p.waitForFinished();
    p.start("./dbUpdater.sh");
    p.waitForFinished();

    // Update 0s with 6 when necessary
    QString qryStr = "UPDATE playerStats SET vote = 6 where ";
    qryStr += "vote=0 and (scored <> 0 or conceded <> 0 or yellowCard <> 0 or redCard <> 0 or ownGoal <> 0 ";
    qryStr += "or savedPenalty <> 0 or failedPenalty <> 0 and round=" + QString::number(giornata) + ");";
    if (!query.exec(qryStr))
        qDebug() << query.lastError().text();

    m_db.transaction();
    // Compute finalVote for each player
    qryStr = "UPDATE playerStats SET finalVote = vote";
    qryStr += "+scored*" + QString::number(ruleSetter.m_goal) + "-conceded+yellowCard*" + QString::number(ruleSetter.m_yellow);
    qryStr += "+redCard*" + QString::number(ruleSetter.m_red) + "+ownGoal*" + QString::number(ruleSetter.m_ownGoal);
    qryStr += "+savedPenalty*" + QString::number(ruleSetter.m_savedPenalties) + "+failedPenalty*" + QString::number(ruleSetter.m_missedPenalties);
    qryStr += " where round = " + QString::number(giornata) + ";";
    if (!query.exec(qryStr))
        qDebug() << query.lastError().text();

    int ret = QMessageBox::question(this, "Finalizza Giornata", "Vuoi concludere la giornata ?", QMessageBox::Ok|QMessageBox::Cancel);
    if (ret = QMessageBox::Ok)
    {
        m_db.commit();
        finalizeRound();
    }
    else
        m_db.rollback();
}

void MainWindow::finalizeRound(int& round)
{
    QSqlQuery query(*m_db);
    QSqlQuery subQuery(*m_db);
    QSqlQuery subSubQuery(*m_db);
    QString qryStr;

    // trova tutte le squadre
    QStringList teams;
    teams << "A.C. UGA";
    // controlla se tutte le formazioni sono state inserite
    QString name;
    int playedRole;
    int role;
    float vote;
    float finalVote;
    int order;
    int captain;

    foreach (QString team, teams)
    {

        teamPoint = 0;
        qryStr = "SELECT playerLineup.name, playerLineup.role, roster.role, playerlineup.order, playerLineup.captain, playerStats.vote, playerStats.finalVote";
        qryStr += " FROM playerLineups, playerStats, roster WHERE playerStats.round=" + QString::number(round) + " AND playerStats.team='" + team + "' ";
        qryStr += "AND playerLineups.name=roster.surname||' '||substr(roster.name,1,1)||'.' ORDER BY order ASC;";

        if (!query.exec(qryStr))
            qDebug() << query.lastError().text();

        float points[4]  = {0, 0, 0, 0};
        int   players[4] = {0, 0, 0, 0};
        int substitutions = 0;
        int nplayers = 0;
        while (query.next())
        {
//            // TODO AGGIUNGERE RUOLO VERO PER CALCOLO
//            qryStr = "SELECT name, role, vote, finalVote WHERE round=" + QString::number(round) + " AND name='" + query.value(2).toString() + "';";
//        if (!subQuery(qryStr))
//            qDebug() << subQuery.lastError().text();

            int index = (query.value(1).toInt()/10) - 1;

            if (query.value(5).toFloat() == 0)
            {
                int ret = QMessageBox::question(this, "Voto Zero", query.value(0).toString()+" ha avuto 0. Vuoi dare un 6 politico ?", QMessageBox::Yes|QMessageBox::No);
                if (ret == QMessageBox::Yes)
                {
                    points[index] += 6;
                    players[index] += 1;
                    continue;
                }
             }

             points[index] += query.value(6).toFloat();
             players[index] += 1;
             nplayers++;
             if (nplayers == 11)
                 break;
        }


    }

    // controllo nomi giocatori
    // calcola punteggi per squadra
    // aggiungi modificatori per modulo
    // finalizza i risultati
    // aggiorna i db

}
