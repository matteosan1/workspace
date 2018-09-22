/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.7.0
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
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindowTemp
{
public:
    QWidget *centralwidget;
    QPushButton *pushButtonTeam;
    QPushButton *pushButtonLineup;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindowTemp)
    {
        if (MainWindowTemp->objectName().isEmpty())
            MainWindowTemp->setObjectName(QStringLiteral("MainWindowTemp"));
        MainWindowTemp->resize(480, 640);
        centralwidget = new QWidget(MainWindowTemp);
        centralwidget->setObjectName(QStringLiteral("centralwidget"));
        pushButtonTeam = new QPushButton(centralwidget);
        pushButtonTeam->setObjectName(QStringLiteral("pushButtonTeam"));
        pushButtonTeam->setGeometry(QRect(60, 60, 341, 131));
        QFont font;
        font.setPointSize(30);
        pushButtonTeam->setFont(font);
        pushButtonLineup = new QPushButton(centralwidget);
        pushButtonLineup->setObjectName(QStringLiteral("pushButtonLineup"));
        pushButtonLineup->setGeometry(QRect(60, 280, 341, 131));
        pushButtonLineup->setFont(font);
        MainWindowTemp->setCentralWidget(centralwidget);
        statusbar = new QStatusBar(MainWindowTemp);
        statusbar->setObjectName(QStringLiteral("statusbar"));
        MainWindowTemp->setStatusBar(statusbar);

        retranslateUi(MainWindowTemp);

        QMetaObject::connectSlotsByName(MainWindowTemp);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindowTemp)
    {
        MainWindowTemp->setWindowTitle(QApplication::translate("MainWindowTemp", "MainWindow", 0));
        pushButtonTeam->setText(QApplication::translate("MainWindowTemp", "Modifica Rosa", 0));
        pushButtonLineup->setText(QApplication::translate("MainWindowTemp", "Consegna Formazione", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWindowTemp: public Ui_MainWindowTemp {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
