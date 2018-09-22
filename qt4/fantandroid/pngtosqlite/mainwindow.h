#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSqlDatabase>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow() {}

    void finalizeRound();

protected slots:
    void loadDB();
    void newLeague();
    void updateLeague();
    void generateFixture();
    void makeCup();
    void insertVotes();
    void insertLineup();

private:
    Ui::MainWindow* m_ui;
    QSqlDatabase m_db;

};
#endif // MAINWINDOW_H
