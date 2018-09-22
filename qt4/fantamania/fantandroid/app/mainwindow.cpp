#include "mainwindow.h"

#include <QMessageBox>
#include <QInputDialog>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QDir>
#include <QImage>
#include <QPixmap>

#include <QDebug>

#include "../core/ComboBoxDelegate.h"

#define EMPTY_PLAYER "--------"

//#ifdef Q_OS_ANDROID
#define OUTPUT_DIR "/data/data/com.example.android.tools/databases/"
//#else
//#define OUTPUT_DIR "/Users/sani/"
//#endif

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    QString myDir(OUTPUT_DIR);
    if (!QDir(myDir).exists())
    {
        QDir().mkdir(myDir);
    }

    m_db = new QSqlDatabase(QSqlDatabase::addDatabase( "QSQLITE","MyConnection" ));
    m_db->setDatabaseName(myDir+QString("team.sqlite"));
    if (!m_db->open())
    {
        QMessageBox::warning(this, tr("Connessione fallita!"), tr("Impossibile connettersi al database: ")+m_db->lastError().driverText());
    }
    else
    {
        QString qryStr;
        QSqlQuery query(*m_db);

        if (!m_db->tables().contains("teamName"))
        {
            bool ok;
            m_teamLabel = QInputDialog::getText(0, QString("Nuova Squadra"),
                                                QString("Nome della squadra: "), QLineEdit::Normal,
                                                QString(""), &ok);

            chooseImage();

            if (ok)
            {
                qryStr = QString("CREATE TABLE teamName (name VARCHAR, image VARCHAR);");
                query.exec(qryStr);

                qryStr = QString("INSERT INTO teamName (name) VALUES (\"") + m_teamLabel + QString("\");");
                if (!query.exec(qryStr))
                    QMessageBox::warning(this, tr("Creazione tabella fallita!"), tr("Impossibile creare la tabella teamName"));

                // todo aggiungere squadra e prezzo
                qryStr = QString("CREATE TABLE roster (name VARCHAR, surname VARCHAR, role INTEGER);");
                query.prepare(qryStr);
                if (!query.exec())
                    QMessageBox::warning(this, tr("Creazione tabella fallita!"), tr("Impossibile creare la tabella roster"));
            }
        }
        else
        {
            qryStr = QString("SELECT * from teamName;");
            query.exec(qryStr);
            query.first();
            m_teamLabel = query.value("name").toString();
            m_teamImage = query.value("image").toString();

            qryStr = QString("SELECT * from roster order by role, surname;");
            query.exec(qryStr);

            m_players.clear();
            while(query.next())
            {
                Giocatore* player = new Giocatore();
                player->setCognome(query.value("surname").toString());
                player->setNome(query.value("name").toString());
                player->setRuolo(RuoloEnum(query.value("role").toInt()));

                m_players.append(player);
            }
        }
    }

    m_points = new Punteggi();

    m_ui.setupUi(this);
    m_ui.labelTeamName->setText(m_teamLabel);
    //setTeamLogo(m_teamImage);

    m_ui.pushButtonTeam->setObjectName("Team");
    m_ui.pushButtonLineup->setObjectName("Lineup");
    connect(m_ui.pushButtonLineup, SIGNAL(clicked(bool)), this, SLOT(changeStack()));
    connect(m_ui.pushButtonTeam, SIGNAL(clicked(bool)), this, SLOT(changeStack()));
    connect(this, SIGNAL(stackTo(int)), m_ui.stackedWidget, SLOT(setCurrentIndex(int)));

    m_model = new GiocatoriInsert();
    teamSorter();
    m_model->setPlayers(m_players);

    // todo connect the DB to the model of the tableview
//    QSqlTableModel *model = new QSqlTableModel(parentObject, database);
//    model->setTable("A");
//    model->setEditStrategy(QSqlTableModel::OnManualSubmit);
//    model->select();
//    model->removeColumn(0); // don't show the ID
//    model->setHeaderData(0, Qt::Horizontal, tr("Column 1"));
//    model->setHeaderData(1, Qt::Horizontal, tr("Column 2"));

//    // Attach it to the view
//    ui->view->setModel(model);
    m_ui.tableViewPlayers->verticalHeader()->hide();
    m_ui.tableViewPlayers->setItemDelegateForColumn(2, new ComboBoxDelegate());
    m_ui.tableViewPlayers->setModel(m_model);
    m_ui.tableViewPlayers->show();
    m_scroller = QScroller::scroller(m_ui.tableViewPlayers);
    m_ui.tableViewPlayers->setVerticalScrollMode(QAbstractItemView::ScrollPerPixel);
    m_ui.tableViewPlayers->setHorizontalScrollMode(QAbstractItemView::ScrollPerPixel);

    QScrollerProperties properties = m_scroller->scrollerProperties();
    QVariant overshootPolicy = QVariant::fromValue<QScrollerProperties::OvershootPolicy>(QScrollerProperties::OvershootAlwaysOff);
    properties.setScrollMetric(QScrollerProperties::VerticalOvershootPolicy, overshootPolicy);
    m_scroller->setScrollerProperties(properties);
    properties.setScrollMetric(QScrollerProperties::HorizontalOvershootPolicy, overshootPolicy);
    m_scroller->setScrollerProperties(properties);

    m_scroller->grabGesture(m_ui.tableViewPlayers, QScroller::LeftMouseButtonGesture);
    //m_scroller->grabGesture(m_ui.tableViewPlayers, QScroller::TouchGesture);

    connect(m_ui.pushButtonNew, SIGNAL(pressed()), this, SLOT(insertRow()));
    connect(m_ui.pushButtonDelete, SIGNAL(pressed()), this, SLOT(removeRow()));

    m_ui.pushButtonRosterOK->setObjectName("RosterOK");
    connect(m_ui.pushButtonRosterOK, SIGNAL(pressed()), this, SLOT(changeStack()));

    //m_giornata = -1;

    m_ui.comboBoxModulo->addItem(m_points->m_schemiString[0]);
    for (int i=1; i<NUMERO_SCHEMI; i++)
    {
        //if (m_punteggi->m_schemi[i-1] == 1)
        m_ui.comboBoxModulo->addItem(m_points->m_schemiString[i]);
    }

    connect(m_ui.comboBoxModulo, SIGNAL(currentIndexChanged(int)), this, SLOT(updateModules(int)));
    connect(m_ui.pushButtonAggiungii, SIGNAL(clicked(bool)), this, SLOT(aggiungiPushed()));
    connect(m_ui.listPanchinari, SIGNAL(itemDoubleClicked(QListWidgetItem*)), this, SLOT(removePanchinaro(QListWidgetItem*)));

    m_ui.pushButtonLineupOK->setObjectName("LineupOK");
    connect(m_ui.pushButtonLineupOK, SIGNAL(pressed()), this, SLOT(changeStack()));
    m_ui.pushButtonCancelLineup->setObjectName("LineupCancel");
    connect(m_ui.pushButtonCancelLineup, SIGNAL(pressed()), this, SLOT(changeStack()));

    m_combos.append(m_ui.comboBoxPortiere);
    m_combos.append(m_ui.comboBoxDifensoreDx);
    m_combos.append(m_ui.comboBoxDifensoreSx);
    m_combos.append(m_ui.comboBoxDifensoreCx1);
    m_combos.append(m_ui.comboBoxDifensoreCx2);
    m_combos.append(m_ui.comboBoxDifensoreCx3);
    m_combos.append(m_ui.comboBoxCentrocampistaDx);
    m_combos.append(m_ui.comboBoxCentrocampistaSx);
    m_combos.append(m_ui.comboBoxCentrocampistaCx1);
    m_combos.append(m_ui.comboBoxCentrocampistaCx2);
    m_combos.append(m_ui.comboBoxCentrocampistaCx3);
    m_combos.append(m_ui.comboBoxAttaccanteDx);
    m_combos.append(m_ui.comboBoxAttaccanteSx);
    m_combos.append(m_ui.comboBoxAttaccanteCx);

    int index = 0;
    foreach (QComboBox* combo, m_combos)
    {
        combo->setObjectName(QString::number(index));
        connect(combo, SIGNAL(currentIndexChanged(QString)), this, SLOT(playerSelected(QString)));
        index++;
    }

    disableAllCombo();

#ifdef Q_OS_ANDROID
    //connect(&m_imagePicker, SIGNAL(imageSelected(QString)), this, SLOT(setTeamLogo(QString)));
    connect(&m_imagePicker, SIGNAL(imageSelected(QImage)), this, SLOT(setTeamLogo(QImage)));
#endif
    connect(m_ui.labelPicture, SIGNAL(clicked(bool)), this, SLOT(chooseImage()));

#ifdef Q_OS_ANDROID
    QAndroidJniObject phoneNumber = QAndroidJniObject::callStaticObjectMethod("com.example.android.tools.TelephoneNumber",
                                                                              "phoneNumber",
                                                                              "()Ljava/lang/String;");
#endif
    m_phoneNumber = phoneNumber.toString();
    qDebug() << m_phoneNumber;
}

MainWindow::~MainWindow()
{
    m_db->close();
    delete m_db;
}

void MainWindow::insertRow()
{
    m_ui.tableViewPlayers->model()->insertRows(0, 1);
    QModelIndex index = m_ui.tableViewPlayers->currentIndex();
    int row = index.row();
    int column = 0;
    QModelIndex newIndex = m_ui.tableViewPlayers->model()->index(row,column);
    m_ui.tableViewPlayers->setCurrentIndex(newIndex);
    m_ui.tableViewPlayers->setFocus();
    m_ui.tableViewPlayers->edit(newIndex);
    m_isModified = true;
}

void MainWindow::removeRow()
{
    QModelIndex index = m_ui.tableViewPlayers->currentIndex();
    QString name = index.sibling(index.row(), 1).data().toString();
    QString surname = index.sibling(index.row(), 0).data().toString();
    int role = index.sibling(index.row(), 2).data().toInt();

    QString qryStr = "DELETE FROM roster WHERE name=\"" + name + "\" and surname = \"" + surname + "\" and role = " + QString::number(role) + ";";
    QSqlQuery query(*m_db);


    query.exec(qryStr);

    int row = m_ui.tableViewPlayers->currentIndex().row();
    m_ui.tableViewPlayers->model()->removeRows(row, 1);
    m_isModified = true;
}

void MainWindow::changeStack()
{
    QPushButton* sender = (QPushButton*)QObject::sender();
    if (sender != NULL)
    {
        if (sender->objectName() == "Team")
        {
            //if (m_db->transaction())
                emit stackTo(1);
        }
        else if (sender->objectName() == "Lineup")
        {
            emit stackTo(2);
        }
        else if (sender->objectName() == "LineupOK")
        {
            sendLineup();
            emit stackTo(0);
        }
        else if (sender->objectName() == "LineupCancel")
        {
            QString title = "Formazione";
            QMessageBox::warning(this, title, "Formazione non terminata");
            emit stackTo(0);
        }
        else if (sender->objectName() == "RosterOK")
        {
            updateTeam();
            emit stackTo(0);
        }
    }
}

void MainWindow::updateTeam()
{
    if (m_isModified) {
        m_players = giocatori();

        int ret = QMessageBox::warning(this, "Fantandroid Avvertimento",
                                       tr("Vuoi salvare i cambiamenti ?"),
                                       QMessageBox::Yes | QMessageBox::Default,
                                       QMessageBox::No | QMessageBox::Escape);
        if (ret == QMessageBox::Yes)
        {
            //m_db->commit();
            fileSave();
        }
        //else
            //m_db->rollback();
    }

    for(int i=0; i<m_players.size(); ++i) {
        if (m_players[i]->cognome() == "")
            m_players[i]->setCognome(QString("GIOCATORE %d").arg(i));
        if (m_players[i]->nome() == "")
            m_players[i]->setNome(" ");
        if (m_players[i]->squadra() == "")
            m_players[i]->setSquadra(" ");
    }

    teamSorter();
}

void MainWindow::sendLineup()
{
#ifdef Q_OS_ANDROID
    QString header = QString("Formazione ") + m_teamLabel;
    QAndroidJniObject jsSubject = QAndroidJniObject::fromString(header);
    QAndroidJniObject jsContent = QAndroidJniObject::fromString(finalizeMessage());

    QAndroidJniObject::callStaticMethod<void>("com.example.android.tools.QShareUtil",
                                              "share",
                                              "(Ljava/lang/String;Ljava/lang/String;)V",
                                              jsSubject.object<jstring>(),
                                              jsContent.object<jstring>()
                                              );
#endif
}

void MainWindow::playerSelected(QString player)
{
    if (player == EMPTY_PLAYER)
        return;

    QComboBox* sender = (QComboBox*)QObject::sender();
    if (sender != NULL)
    {
        int senderId = sender->objectName().toInt();

        if (player == EMPTY_PLAYER)
        {
            foreach (Giocatore* p, m_players)
            {
                int index = p->partita(0).Formazione();

                if (index == senderId)
                {
                    p->partita(0).SetFormazione(-1);
                }
            }
        }
        else {
            foreach (Giocatore* p, m_players)
            {
                if (p->nomeCompleto() == player)
                {
                    int index = p->partita(0).Formazione();
                    p->partita(0).SetFormazione(senderId);
                    if (index != -1)
                    {
                        m_combos.at(index)->setCurrentIndex(0);
                        break;
                    }
                }
            }
        }
    }

    int nGiocano = 0;
    foreach (Giocatore* p, m_players)
    {
        int index = p->partita(0).Formazione();
        if (index != -1)
            nGiocano++;
    }

    if (nGiocano == 11)
    {
        // todo check nGiocano, capitano settato e panchina fatta
        m_ui.pushButtonLineupOK->setEnabled(true);
        m_ui.comboBoxCapitano->clear();
        m_ui.comboBoxPanchinari->clear();
        foreach (Giocatore* p, m_players)
        {
            if (p->partita(0).Formazione() != -1)
                m_ui.comboBoxCapitano->addItem(p->nomeCompleto());
            else
                m_ui.comboBoxPanchinari->addItem(p->nomeCompleto());
        }
    }
    else
    {
        m_ui.pushButtonLineupOK->setEnabled(false);
        m_ui.comboBoxCapitano->clear();
        m_ui.comboBoxPanchinari->clear();
    }
}

void MainWindow::updateModules(const int& chosenModule)
{
    int realModule = -1;
    int counter = 0;
    for (int i=1; i<NUMERO_SCHEMI; i++)
    {
        //if (m_punteggi->m_schemi[i-1] != 0)
        counter++;

        if (counter == chosenModule)
            realModule = i-1;
    }

    disableAllCombo();
    enableCombo(m_ui.comboBoxPortiere, Portiere);

    switch(realModule)
    {
    case 0: // 5-4-1
        enableCombo(m_ui.comboBoxDifensoreSx, DifensoreLaterale);
        enableCombo(m_ui.comboBoxDifensoreDx, DifensoreLaterale);
        enableCombo(m_ui.comboBoxDifensoreCx1, DifensoreCentrale);
        enableCombo(m_ui.comboBoxDifensoreCx2, DifensoreCentrale);
        enableCombo(m_ui.comboBoxDifensoreCx3, DifensoreCentrale);
        enableCombo(m_ui.comboBoxCentrocampistaCx1, CentrocampistaCentrale);
        enableCombo(m_ui.comboBoxCentrocampistaCx2, CentrocampistaCentrale);
        enableCombo(m_ui.comboBoxCentrocampistaSx, CentrocampistaEsterno);
        enableCombo(m_ui.comboBoxCentrocampistaDx, CentrocampistaEsterno);
        enableCombo(m_ui.comboBoxAttaccanteCx, AttaccanteCentrale);
        break;
    case 1: // 5-3-1-1
        enableCombo(m_ui.comboBoxDifensoreSx, DifensoreLaterale);
        enableCombo(m_ui.comboBoxDifensoreDx, DifensoreLaterale);
        enableCombo(m_ui.comboBoxDifensoreCx1, DifensoreCentrale);
        enableCombo(m_ui.comboBoxDifensoreCx2, DifensoreCentrale);
        enableCombo(m_ui.comboBoxDifensoreCx3, DifensoreCentrale);
        enableCombo(m_ui.comboBoxCentrocampistaCx1, CentrocampistaCentrale);
        enableCombo(m_ui.comboBoxCentrocampistaCx2, CentrocampistaCentrale);
        enableCombo(m_ui.comboBoxCentrocampistaCx3, CentrocampistaCentrale);
        enableCombo(m_ui.comboBoxAttaccanteCx, CentrocampistaTrequartista);
        enableCombo(m_ui.comboBoxAttaccanteDx, AttaccanteMovimento);
        break;
    case 2: // 5-3-2
        enableCombo(m_ui.comboBoxDifensoreSx, DifensoreLaterale);
        enableCombo(m_ui.comboBoxDifensoreDx, DifensoreLaterale);
        enableCombo(m_ui.comboBoxDifensoreCx1, DifensoreCentrale);
        enableCombo(m_ui.comboBoxDifensoreCx2, DifensoreCentrale);
        enableCombo(m_ui.comboBoxDifensoreCx3, DifensoreCentrale);
        enableCombo(m_ui.comboBoxCentrocampistaCx1, CentrocampistaCentrale);
        enableCombo(m_ui.comboBoxCentrocampistaCx2, CentrocampistaCentrale);
        enableCombo(m_ui.comboBoxCentrocampistaCx3, CentrocampistaCentrale);
        enableCombo(m_ui.comboBoxAttaccanteSx, AttaccanteMovimento, AttaccanteCentrale);
        enableCombo(m_ui.comboBoxAttaccanteDx, AttaccanteMovimento, AttaccanteCentrale);
        break;
    case 3: // 4-5-1
        enableCombo(m_ui.comboBoxDifensoreSx, DifensoreLaterale);
        enableCombo(m_ui.comboBoxDifensoreDx, DifensoreLaterale);
        enableCombo(m_ui.comboBoxDifensoreCx1, DifensoreCentrale);
        enableCombo(m_ui.comboBoxDifensoreCx2, DifensoreCentrale);
        enableCombo(m_ui.comboBoxCentrocampistaCx1, CentrocampistaCentrale);
        enableCombo(m_ui.comboBoxCentrocampistaCx2, CentrocampistaCentrale);
        enableCombo(m_ui.comboBoxCentrocampistaCx3, CentrocampistaCentrale);
        enableCombo(m_ui.comboBoxCentrocampistaSx, CentrocampistaEsterno);
        enableCombo(m_ui.comboBoxCentrocampistaDx, CentrocampistaEsterno);
        enableCombo(m_ui.comboBoxAttaccanteCx, AttaccanteCentrale);
        break;
    case 4: // 4-4-2
        enableCombo(m_ui.comboBoxDifensoreSx, DifensoreLaterale);
        enableCombo(m_ui.comboBoxDifensoreDx, DifensoreLaterale);
        enableCombo(m_ui.comboBoxDifensoreCx1, DifensoreCentrale);
        enableCombo(m_ui.comboBoxDifensoreCx2, DifensoreCentrale);
        enableCombo(m_ui.comboBoxCentrocampistaCx1, CentrocampistaCentrale);
        enableCombo(m_ui.comboBoxCentrocampistaCx2, CentrocampistaCentrale);
        enableCombo(m_ui.comboBoxCentrocampistaSx, CentrocampistaEsterno);
        enableCombo(m_ui.comboBoxCentrocampistaDx, CentrocampistaEsterno);
        enableCombo(m_ui.comboBoxAttaccanteDx, AttaccanteMovimento, AttaccanteCentrale);
        enableCombo(m_ui.comboBoxAttaccanteSx, AttaccanteMovimento, AttaccanteCentrale);
        break;
    case 5: // 4-3-2-1
        enableCombo(m_ui.comboBoxDifensoreSx, DifensoreLaterale);
        enableCombo(m_ui.comboBoxDifensoreDx, DifensoreLaterale);
        enableCombo(m_ui.comboBoxDifensoreCx1, DifensoreCentrale);
        enableCombo(m_ui.comboBoxDifensoreCx2, DifensoreCentrale);
        enableCombo(m_ui.comboBoxCentrocampistaCx1, CentrocampistaCentrale);
        enableCombo(m_ui.comboBoxCentrocampistaCx2, CentrocampistaCentrale);
        enableCombo(m_ui.comboBoxCentrocampistaCx3, CentrocampistaCentrale);
        enableCombo(m_ui.comboBoxAttaccanteDx, CentrocampistaTrequartista);
        enableCombo(m_ui.comboBoxAttaccanteSx, CentrocampistaTrequartista);
        enableCombo(m_ui.comboBoxAttaccanteCx, AttaccanteCentrale);
        break;
    case 6: // 4-3-1-2
        enableCombo(m_ui.comboBoxDifensoreSx, DifensoreLaterale);
        enableCombo(m_ui.comboBoxDifensoreDx, DifensoreLaterale);
        enableCombo(m_ui.comboBoxDifensoreCx1, DifensoreCentrale);
        enableCombo(m_ui.comboBoxDifensoreCx2, DifensoreCentrale);
        enableCombo(m_ui.comboBoxCentrocampistaCx1, CentrocampistaCentrale);
        enableCombo(m_ui.comboBoxCentrocampistaCx2, CentrocampistaCentrale);
        enableCombo(m_ui.comboBoxCentrocampistaCx3, CentrocampistaCentrale);
        enableCombo(m_ui.comboBoxAttaccanteCx, CentrocampistaTrequartista);
        enableCombo(m_ui.comboBoxAttaccanteDx, AttaccanteCentrale);
        enableCombo(m_ui.comboBoxAttaccanteSx, AttaccanteCentrale);
        break;
    case 7: // 4-3-3
        enableCombo(m_ui.comboBoxDifensoreSx, DifensoreLaterale);
        enableCombo(m_ui.comboBoxDifensoreDx, DifensoreLaterale);
        enableCombo(m_ui.comboBoxDifensoreCx1, DifensoreCentrale);
        enableCombo(m_ui.comboBoxDifensoreCx2, DifensoreCentrale);
        enableCombo(m_ui.comboBoxCentrocampistaCx1, CentrocampistaCentrale);
        enableCombo(m_ui.comboBoxCentrocampistaCx2, CentrocampistaCentrale);
        enableCombo(m_ui.comboBoxCentrocampistaCx3, CentrocampistaCentrale);
        enableCombo(m_ui.comboBoxAttaccanteCx, AttaccanteCentrale);
        enableCombo(m_ui.comboBoxAttaccanteDx, AttaccanteMovimento);
        enableCombo(m_ui.comboBoxAttaccanteSx, AttaccanteMovimento);
        break;
    case 8: // 4-2-3-1
        enableCombo(m_ui.comboBoxDifensoreCx1, DifensoreCentrale);
        enableCombo(m_ui.comboBoxDifensoreCx2, DifensoreCentrale);
        enableCombo(m_ui.comboBoxDifensoreDx, DifensoreLaterale);
        enableCombo(m_ui.comboBoxDifensoreSx, DifensoreLaterale);
        enableCombo(m_ui.comboBoxCentrocampistaCx1, CentrocampistaCentrale);
        enableCombo(m_ui.comboBoxCentrocampistaCx2, CentrocampistaCentrale);
        enableCombo(m_ui.comboBoxCentrocampistaCx3, CentrocampistaTrequartista);
        enableCombo(m_ui.comboBoxAttaccanteCx, AttaccanteCentrale);
        enableCombo(m_ui.comboBoxCentrocampistaDx, CentrocampistaEsterno, CentrocampistaTrequartista);
        enableCombo(m_ui.comboBoxCentrocampistaSx, CentrocampistaEsterno, CentrocampistaTrequartista);
        break;
    case 9: // 4-2-1-3
        enableCombo(m_ui.comboBoxDifensoreCx1, DifensoreCentrale);
        enableCombo(m_ui.comboBoxDifensoreCx2, DifensoreCentrale);
        enableCombo(m_ui.comboBoxDifensoreDx, DifensoreLaterale);
        enableCombo(m_ui.comboBoxDifensoreSx, DifensoreLaterale);
        enableCombo(m_ui.comboBoxCentrocampistaCx1, CentrocampistaCentrale);
        enableCombo(m_ui.comboBoxCentrocampistaCx2, CentrocampistaCentrale);
        enableCombo(m_ui.comboBoxCentrocampistaCx3, CentrocampistaTrequartista);
        enableCombo(m_ui.comboBoxAttaccanteCx, AttaccanteCentrale);
        enableCombo(m_ui.comboBoxAttaccanteSx, AttaccanteMovimento);
        enableCombo(m_ui.comboBoxAttaccanteDx, AttaccanteMovimento);
        break;
    case 10: // 4-2-4
        enableCombo(m_ui.comboBoxDifensoreCx1, DifensoreCentrale);
        enableCombo(m_ui.comboBoxDifensoreCx2, DifensoreCentrale);
        enableCombo(m_ui.comboBoxDifensoreDx, DifensoreLaterale);
        enableCombo(m_ui.comboBoxDifensoreSx, DifensoreLaterale);
        enableCombo(m_ui.comboBoxCentrocampistaCx1, CentrocampistaCentrale);
        enableCombo(m_ui.comboBoxCentrocampistaCx2, CentrocampistaCentrale);
        enableCombo(m_ui.comboBoxCentrocampistaCx3, AttaccanteCentrale);
        enableCombo(m_ui.comboBoxAttaccanteCx, AttaccanteCentrale);
        enableCombo(m_ui.comboBoxAttaccanteSx, AttaccanteMovimento, CentrocampistaEsterno);
        enableCombo(m_ui.comboBoxAttaccanteDx, AttaccanteMovimento, CentrocampistaEsterno);
        break;
    case 11: // 3-5-2
        enableCombo(m_ui.comboBoxDifensoreCx1, DifensoreCentrale);
        enableCombo(m_ui.comboBoxDifensoreCx2, DifensoreCentrale);
        enableCombo(m_ui.comboBoxDifensoreCx3, DifensoreCentrale);
        enableCombo(m_ui.comboBoxCentrocampistaCx1, CentrocampistaCentrale);
        enableCombo(m_ui.comboBoxCentrocampistaCx2, CentrocampistaCentrale);
        enableCombo(m_ui.comboBoxCentrocampistaCx3, CentrocampistaCentrale);
        enableCombo(m_ui.comboBoxCentrocampistaSx, CentrocampistaEsterno);
        enableCombo(m_ui.comboBoxCentrocampistaDx, CentrocampistaEsterno);
        enableCombo(m_ui.comboBoxAttaccanteSx, AttaccanteMovimento, AttaccanteCentrale);
        enableCombo(m_ui.comboBoxAttaccanteDx, AttaccanteMovimento, AttaccanteCentrale);
        break;
    case 12: // 3-4-1-2
        enableCombo(m_ui.comboBoxDifensoreCx1, DifensoreCentrale);
        enableCombo(m_ui.comboBoxDifensoreCx2, DifensoreCentrale);
        enableCombo(m_ui.comboBoxDifensoreCx3, DifensoreCentrale);
        enableCombo(m_ui.comboBoxCentrocampistaCx1, CentrocampistaCentrale);
        enableCombo(m_ui.comboBoxCentrocampistaCx2, CentrocampistaCentrale);
        enableCombo(m_ui.comboBoxCentrocampistaSx, CentrocampistaEsterno);
        enableCombo(m_ui.comboBoxCentrocampistaDx, CentrocampistaEsterno);
        enableCombo(m_ui.comboBoxAttaccanteCx, CentrocampistaTrequartista);
        enableCombo(m_ui.comboBoxAttaccanteSx, AttaccanteMovimento, AttaccanteCentrale);
        enableCombo(m_ui.comboBoxAttaccanteDx, AttaccanteMovimento, AttaccanteCentrale);
        break;
    case 13: // 3-4-3
        enableCombo(m_ui.comboBoxDifensoreCx1, DifensoreCentrale);
        enableCombo(m_ui.comboBoxDifensoreCx2, DifensoreCentrale);
        enableCombo(m_ui.comboBoxDifensoreCx3, DifensoreCentrale);
        enableCombo(m_ui.comboBoxCentrocampistaCx1, CentrocampistaCentrale);
        enableCombo(m_ui.comboBoxCentrocampistaCx2, CentrocampistaCentrale);
        enableCombo(m_ui.comboBoxCentrocampistaSx, CentrocampistaEsterno);
        enableCombo(m_ui.comboBoxCentrocampistaDx, CentrocampistaEsterno);
        enableCombo(m_ui.comboBoxAttaccanteCx, AttaccanteCentrale);
        enableCombo(m_ui.comboBoxAttaccanteSx, AttaccanteMovimento);
        enableCombo(m_ui.comboBoxAttaccanteDx, AttaccanteMovimento);
        break;
    }
}

void MainWindow::enableCombo(QComboBox* combo, RuoloEnum ruolo1, RuoloEnum ruolo2)
{
    combo->setEnabled(true);
    combo->setVisible(true);

    combo->clear();
    combo->addItem(EMPTY_PLAYER);

    foreach (Giocatore* p, m_players)
    {
        if (p->ruolo() == ruolo1 or p->ruolo() == ruolo2)
        {
            combo->addItem(p->nomeCompleto());
        }
    }
}

void MainWindow::disableAllCombo()
{
    m_ui.comboBoxPortiere->setEnabled(false);
    m_ui.comboBoxDifensoreSx->setEnabled(false);
    m_ui.comboBoxDifensoreDx->setEnabled(false);
    m_ui.comboBoxDifensoreCx1->setEnabled(false);
    m_ui.comboBoxDifensoreCx2->setEnabled(false);
    m_ui.comboBoxDifensoreCx3->setEnabled(false);
    m_ui.comboBoxCentrocampistaCx1->setEnabled(false);
    m_ui.comboBoxCentrocampistaCx2->setEnabled(false);
    m_ui.comboBoxCentrocampistaCx3->setEnabled(false);
    m_ui.comboBoxCentrocampistaSx->setEnabled(false);
    m_ui.comboBoxCentrocampistaDx->setEnabled(false);
    m_ui.comboBoxAttaccanteCx->setEnabled(false);
    m_ui.comboBoxAttaccanteDx->setEnabled(false);
    m_ui.comboBoxAttaccanteSx->setEnabled(false);

    m_ui.comboBoxPortiere->setVisible(false);
    m_ui.comboBoxDifensoreSx->setVisible(false);
    m_ui.comboBoxDifensoreDx->setVisible(false);
    m_ui.comboBoxDifensoreCx1->setVisible(false);
    m_ui.comboBoxDifensoreCx2->setVisible(false);
    m_ui.comboBoxDifensoreCx3->setVisible(false);
    m_ui.comboBoxCentrocampistaCx1->setVisible(false);
    m_ui.comboBoxCentrocampistaCx2->setVisible(false);
    m_ui.comboBoxCentrocampistaCx3->setVisible(false);
    m_ui.comboBoxCentrocampistaSx->setVisible(false);
    m_ui.comboBoxCentrocampistaDx->setVisible(false);
    m_ui.comboBoxAttaccanteCx->setVisible(false);
    m_ui.comboBoxAttaccanteDx->setVisible(false);
    m_ui.comboBoxAttaccanteSx->setVisible(false);
}

void MainWindow::aggiungiPushed()
{
    QString player = m_ui.comboBoxPanchinari->currentText();

    bool alreadyIn = false;
    for (int i=0; i<m_ui.listPanchinari->count(); ++i)
    {
        if (player == m_ui.listPanchinari->item(i)->text())
        {
            alreadyIn = true;
            break;
        }
    }

    if (!alreadyIn)
    {
        int row = m_ui.listPanchinari->currentRow();
        if (row == -1)
            row = m_ui.listPanchinari->count() + 1;
        m_ui.listPanchinari->insertItem(row+1, player);
    }
}

void MainWindow::removePanchinaro(QListWidgetItem* item)
{
    delete item;
}

QString MainWindow::finalizeMessage()
{
    QString text;
    QString capitano = m_ui.comboBoxCapitano->currentText();

    text = text + "Modulo: " + m_ui.comboBoxModulo->currentText() + "\n";
    foreach(QComboBox* combo, m_combos)
    {
        if (combo->isEnabled())
        {
            QString player = combo->currentText();
            RuoloEnum ruolo;

            foreach (Giocatore* p, m_players)
            {
                if (p->nomeCompleto() == player)
                {
                    ruolo = p->ruolo();
                    break;
                }
            }

            if (player == capitano)
                text = text + player + " [" + Giocatore::ruoloToString(ruolo) + "] (C)\n";
            else
                text = text + player + " [" + Giocatore::ruoloToString(ruolo) + "]\n";
        }
    }

    text = text + "\nPANCHINA\n";
    for (int i=0; i<m_ui.listPanchinari->count(); ++i)
    {
        text = text + m_ui.listPanchinari->item(i)->text() + "\n";
    }

    return text;
}

void MainWindow::fileSave()
{
    QString qryStr;
    QSqlQuery query(*m_db);
    QSqlQuery query2(*m_db);

    for (int i=0; i<m_players.size(); ++i)
    {
        qryStr = "SELECT * FROM roster WHERE name=\""+m_players.at(i)->nome()+"\" and surname=\""+m_players.at(i)->cognome()+"\";";
        if (query.exec(qryStr))
        {
            if (!query.first())
            {
                qryStr = "INSERT INTO roster (name, surname, role) VALUES (\""+m_players.at(i)->nome()+"\",\""
                        + m_players.at(i)->cognome()+"\","+QString::number(int(m_players.at(i)->ruolo()))+");";

                query2.exec(qryStr);
            }
            else
            {
                qryStr = QString("UPDATE roster SET ")
                        + QString("name=\"")+m_players.at(i)->nome()+QString("\",")
                        + QString("surname=\"")+m_players.at(i)->cognome()+QString("\",")
                        + QString("role=")+QString::number(int(m_players.at(i)->ruolo()))
                        + QString("WHERE name=\"")+m_players.at(i)->nome()+QString("\" and surname=\"")+m_players.at(i)->cognome()+QString("\";");

                query2.exec(qryStr);
            }
        }
    }

    m_isModified = false;
}

void MainWindow::teamSorter()
{
    for(int i=0; i<m_players.size()-1; ++i)
    {
        for(int j=i+1; j<m_players.size(); ++j)
        {
            if ((m_players[i]->ruolo() > m_players[j]->ruolo()) ||
                    ((m_players[i]->nomeCompleto() > m_players[j]->nomeCompleto()) &&
                     (m_players[i]->ruolo() == m_players[j]->ruolo()))) {
                Giocatore* temp = m_players[i];
                m_players[i] = m_players[j];
                m_players[j] = temp;
            }
        }
    }
}

void MainWindow::setTeamLogo(QImage teamLogo)
{
    //QMessageBox::warning(this, tr("Connessione fallita!"), tr("FOTO2: ")+teamLogo);

    //m_teamImage = teamLogo;
    //QImage myImage;
    //myImage.load(teamLogo);
    //myImage = myImage.scaled(200, 200);
    m_ui.labelPicture->setIcon(QIcon(QPixmap::fromImage(teamLogo)));
}

void MainWindow::chooseImage()
{

#ifdef Q_OS_ANDROID
    m_imagePicker.show();
#endif

}

