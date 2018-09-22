#include "teamModifier.h"
#include "ui_teammodifier.h"

#include <QFileDialog>
#include <QMessageBox>
#include <QSqlQuery>
#include <QSqlError>
#include <QSqlRecord>
#include <QSqlRelationalDelegate>

#include <QDebug>

TeamModifier::TeamModifier(QSqlDatabase& db, QDialog *parent) :
    QDialog(parent),
    m_ui(new Ui::UiTeamModifier),
    m_teamName(""),
     m_db(db)
{
    m_ui->setupUi(this);

    connect(m_ui->buttonBox, SIGNAL(accepted()), this, SLOT(accept()));
    connect(m_ui->buttonBox, SIGNAL(rejected()), this, SLOT(reject()));

    connect(m_ui->pushButtonAddTeam, SIGNAL(clicked(bool)), this, SLOT(insertTeamRow()));
    connect(m_ui->pushButtonRemoveTeam, SIGNAL(clicked(bool)), this, SLOT(removeTeamRow()));

    connect(m_ui->pushButton, SIGNAL(clicked(bool)), this, SLOT(updateTeamImage()));
    connect(m_ui->pushButtonAdd, SIGNAL(clicked(bool)), this, SLOT(insertRow()));
    connect(m_ui->pushButtonRemove, SIGNAL(clicked(bool)), this, SLOT(removeRow()));

    connect(m_ui->tableViewTeam, SIGNAL(clicked(QModelIndex)), this, SLOT(selectTeam(QModelIndex)));

    m_teamModel = new CustomSqlModel(this, m_db);
    m_teamModel->setEditStrategy(QSqlTableModel::OnFieldChange);
    m_teamModel->setTable("teamName");
    m_teamModel->select();
    m_ui->tableViewTeam->setModel(m_teamModel);
    m_teamModel->setHeaderData(1, Qt::Horizontal, tr("SQUADRA"));
    m_teamModel->setHeaderData(3, Qt::Horizontal, tr("TELEFONO"));
    //m_ui->tableViewTeam->setItemDelegate(new MySqlDelegate());
    m_ui->tableViewTeam->setColumnHidden(0, true);
    m_ui->tableViewTeam->setColumnHidden(2, true);

    m_rosterModel = new QSqlRelationalTableModel(this, m_db);
    m_rosterModel->setTable("roster");
    m_rosterModel->setRelation(3, QSqlRelation("roles", "nRole", "shortName"));
    //m_rosterModel->setEditStrategy(QSqlTableModel::OnFieldChange);
    m_rosterModel->select();
    m_ui->tableView->setModel(m_rosterModel);
    m_rosterModel->setHeaderData(1, Qt::Horizontal, tr("NOME"));
    m_rosterModel->setHeaderData(2, Qt::Horizontal, tr("COGNOME"));
    m_rosterModel->setHeaderData(3, Qt::Horizontal, tr("RUOLO"));
    m_rosterModel->setHeaderData(4, Qt::Horizontal, tr("PREZZO"));
    m_rosterModel->setHeaderData(6, Qt::Horizontal, tr("SQUADRA"));
    m_ui->tableView->setColumnHidden(0, true);
    m_ui->tableView->setColumnHidden(5, true);
    m_ui->tableView->setItemDelegate(new QSqlRelationalDelegate());
    m_ui->tableView->setModel(m_rosterModel);

    QModelIndex index = m_teamModel->index(0, 1);
    m_ui->tableViewTeam->setCurrentIndex(index);
    emit m_ui->tableViewTeam->clicked(index);
}

void TeamModifier::updateTeamImage()
{
    QString filename = QFileDialog::getOpenFileName(0, "Team Image", "/home/sani/Projects/fantandroid/app/res", "*.jpg");

    if (filename != "")
    {
        QPixmap pixmap(filename);
        pixmap = pixmap.scaled(100, 100, Qt::KeepAspectRatio, Qt::FastTransformation);
        QIcon buttonIcon(pixmap);
        m_ui->pushButton->setIcon(buttonIcon);
        m_ui->pushButton->setIconSize(pixmap.rect().size());

        QFile file(filename);
        if (!file.open(QIODevice::ReadOnly))
            return;
        QByteArray inByteArray = file.readAll();
        QModelIndex index = m_ui->tableViewTeam->currentIndex();
        int row = index.row();
        m_teamModel->setData(m_teamModel->index(row, 2), inByteArray);
    }
}

void TeamModifier::updateDB()
{
    m_teamModel->submitAll();

    int rowCount = m_rosterModel->rowCount();
    for (int i=0; i<rowCount; ++i)
    {
        m_rosterModel->setData(m_rosterModel->index(i, 5), m_teamName, Qt::EditRole);
        m_rosterModel->setData(m_rosterModel->index(i, 1),
                               m_rosterModel->data(m_rosterModel->index(i, 1), Qt::DisplayRole).toString().toUpper());
        m_rosterModel->setData(m_rosterModel->index(i, 2),
                               m_rosterModel->data(m_rosterModel->index(i, 2), Qt::DisplayRole).toString().toUpper());
        m_rosterModel->setData(m_rosterModel->index(i, 6),
                               m_rosterModel->data(m_rosterModel->index(i, 6), Qt::DisplayRole).toString().toUpper());
    }

    m_rosterModel->submitAll();

    m_teamModel->database().commit();
    m_rosterModel->database().commit();
}

void TeamModifier::discardDB()
{
    m_teamModel->revertAll();
    m_rosterModel->revertAll();
}

void TeamModifier::insertTeamRow()
{
    int rowCount = m_teamModel->rowCount();
    if (!m_teamModel->insertRows(rowCount, 1))
    {
        qDebug() << "insert team rows" << m_teamModel->lastError().text();
        return;
    }
    m_teamModel->submit();
}

void TeamModifier::insertRow()
{
    if (m_teamName == "")
    {
        QMessageBox::critical(this, "ERRORE", "Scegli una squadra", QMessageBox::Cancel);
        return;
    }

//    QSqlRecord record(m_rosterModel->record());
//    m_rosterModel->insertRecord(-1, record);

    int rowCount = m_rosterModel->rowCount();
    qDebug() << rowCount;
    if(!m_rosterModel->insertRows(rowCount, 1)) {
        qDebug() << "insertRows" << m_rosterModel->lastError().text();
        return;
    }

    m_rosterModel->submit();
}

void TeamModifier::removeTeamRow()
{
    QModelIndex index = m_ui->tableViewTeam->currentIndex();
    m_teamModel->removeRow(index.row());
    m_teamModel->submit();
}

void TeamModifier::removeRow()
{
    QModelIndex index = m_ui->tableView->currentIndex();
    m_rosterModel->removeRow(index.row());
    m_rosterModel->submit();
}

void TeamModifier::updateView(QModelIndex& index)//QString teamName)
{
    if (index.isValid())
    {
        int row = index.row();
        m_rosterModel->setFilter("team='"+m_teamName+"'");
        m_rosterModel->setSort(1, Qt::SortOrder::AscendingOrder);
        m_rosterModel->select();

        QByteArray imageData = m_teamModel->data(m_teamModel->index(row, 2), Qt::EditRole).toByteArray();
        QPixmap pixmap;
        if (pixmap.loadFromData(imageData))
        {
            pixmap = pixmap.scaled(100, 100, Qt::KeepAspectRatio, Qt::FastTransformation);
        }

        QIcon buttonIcon(pixmap);
        m_ui->pushButton->setIcon(buttonIcon);
        m_ui->pushButton->setIconSize(pixmap.rect().size());
    }
}

void TeamModifier::selectTeam(QModelIndex index)
{
    int row = index.row();
    m_teamName = m_teamModel->data(m_teamModel->index(row, 1), Qt::DisplayRole).toString();
    updateView(index);
}
