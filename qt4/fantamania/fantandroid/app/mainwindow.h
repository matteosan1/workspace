#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QString>
#include <QList>
#include <QStringList>
#include <QScroller>

#include "ui_mainwindow.h"
#include "mainwindow.h"

#include "../core/insertgiocatori.h"
#include "../core/giocatore.h"
#include "../core/punteggi.h"
#include "androidimagepicker.h"

class Punteggi;

class GiocatoriInsert;
class QSqlDatabase;
class QComboBox;
class QListWidgetItem;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

    QList<Giocatore*> giocatori() {
        GiocatoriInsert* temp = dynamic_cast<GiocatoriInsert*>(m_model);
        return temp->GetGiocatori();
    }

    QString finalizeMessage();

public slots:
    void updateTeam();
    void sendLineup();
    void changeStack();
    void insertRow();
    void removeRow();
    void updateModules(const int& chosenModule);
    void playerSelected(QString player);
    void aggiungiPushed();
    void removePanchinaro(QListWidgetItem*);
    //void setTeamLogo(QString teamLogo);
    void setTeamLogo(QImage image);
    void chooseImage();

signals:
    void stackTo(int pageNumber);

private:
    void enableCombo(QComboBox* combo, RuoloEnum ruolo1, RuoloEnum ruolo2 = Nullo);
    void disableAllCombo();

    //int               m_giornata;

private:
    void teamSorter();
    void fileSave();

    Ui::MainWindowTemp m_ui;

    QString             m_teamLabel;
    QString             m_teamImage;
    bool                m_isModified;
    QList<Giocatore*>   m_players;
    QString             m_currentFile;
    QString             m_phoneNumber;
    Punteggi*           m_points;

    GiocatoriInsert*    m_model;
    QSqlDatabase*       m_db;

    QList<QComboBox*>   m_combos;

#ifdef Q_OS_ANDROID
    AndroidImagePicker  m_imagePicker;
#endif
    QScroller*          m_scroller;
};

#endif // MAINWINDOW_H

//#ifndef LINEUP_H
//#define LINEUP_H

//#include "ui_lineup.h"
//#include "../core/giocatore.h"
//#include "../core/punteggi.h"

//#include <QDialog>
//#include <QStringList>
//#include <QString>
//#include <QList>

//class QComboBox;
//class QListWidgetItem;

//class LineupDialog: public QDialog {
//    Q_OBJECT

//public:
//    LineupDialog(QList<Giocatore*> g, Punteggi* punteggi = 0, QWidget *parent = 0);
//    int getGiornata() const { return m_giornata; }
//    QString finalizeMessage();

//private slots:
//    void updateModules(const int& chosenModule);
//    void playerSelected(QString player);
//    void aggiungiPushed();
//    void removePanchinaro(QListWidgetItem*);

//private:
//    void enableCombo(QComboBox* combo, RuoloEnum ruolo1, RuoloEnum ruolo2 = Nullo);
//    void disableAllCombo();

//    int               m_giornata;
//    Ui::lineup        m_ui;
//    QList<Giocatore*> m_giocatori;
//    Punteggi*         m_punteggi;
//    //int m_partite;

//    QList<QComboBox*> m_combos;
//};

//#endif

