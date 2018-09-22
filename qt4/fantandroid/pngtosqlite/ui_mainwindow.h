/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.6.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QPushButton *pushButtonNew;
    QPushButton *pushButtonUpdate;
    QPushButton *pushButtonFixtures;
    QPushButton *pushButtonCup;
    QPushButton *pushButtonOpen;
    QPushButton *pushButtonInsertLineup;
    QPushButton *pushButtonInsertVotes;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(800, 600);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QStringLiteral("centralwidget"));
        pushButtonNew = new QPushButton(centralwidget);
        pushButtonNew->setObjectName(QStringLiteral("pushButtonNew"));
        pushButtonNew->setGeometry(QRect(50, 90, 251, 81));
        pushButtonUpdate = new QPushButton(centralwidget);
        pushButtonUpdate->setObjectName(QStringLiteral("pushButtonUpdate"));
        pushButtonUpdate->setGeometry(QRect(50, 200, 251, 81));
        pushButtonFixtures = new QPushButton(centralwidget);
        pushButtonFixtures->setObjectName(QStringLiteral("pushButtonFixtures"));
        pushButtonFixtures->setGeometry(QRect(50, 310, 251, 81));
        pushButtonCup = new QPushButton(centralwidget);
        pushButtonCup->setObjectName(QStringLiteral("pushButtonCup"));
        pushButtonCup->setGeometry(QRect(50, 410, 251, 81));
        pushButtonOpen = new QPushButton(centralwidget);
        pushButtonOpen->setObjectName(QStringLiteral("pushButtonOpen"));
        pushButtonOpen->setGeometry(QRect(360, 90, 251, 81));
        pushButtonInsertLineup = new QPushButton(centralwidget);
        pushButtonInsertLineup->setObjectName(QStringLiteral("pushButtonInsertLineup"));
        pushButtonInsertLineup->setGeometry(QRect(320, 310, 251, 41));
        pushButtonInsertVotes = new QPushButton(centralwidget);
        pushButtonInsertVotes->setObjectName(QStringLiteral("pushButtonInsertVotes"));
        pushButtonInsertVotes->setGeometry(QRect(320, 360, 251, 41));
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QStringLiteral("menubar"));
        menubar->setGeometry(QRect(0, 0, 800, 23));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QStringLiteral("statusbar"));
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", 0));
        pushButtonNew->setText(QApplication::translate("MainWindow", "Crea Nuova Lega", 0));
        pushButtonUpdate->setText(QApplication::translate("MainWindow", "Modifica Lega Esistente", 0));
        pushButtonFixtures->setText(QApplication::translate("MainWindow", "Genera Calendario", 0));
        pushButtonCup->setText(QApplication::translate("MainWindow", "Genera Coppa di Lega", 0));
        pushButtonOpen->setText(QApplication::translate("MainWindow", "Apri Lega Esistente", 0));
        pushButtonInsertLineup->setText(QApplication::translate("MainWindow", "Inserisci Formazione", 0));
        pushButtonInsertVotes->setText(QApplication::translate("MainWindow", "Inserisci Voti", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
