/********************************************************************************
** Form generated from reading UI file 'teamModifierOld.ui'
**
** Created by: Qt User Interface Compiler version 5.6.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TEAMMODIFIEROLD_H
#define UI_TEAMMODIFIEROLD_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTableView>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow2
{
public:
    QWidget *centralwidget;
    QGridLayout *gridLayout;
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *horizontalLayout;
    QVBoxLayout *verticalLayout;
    QPushButton *pushButtonAddTeam;
    QPushButton *pushButtonRemoveTeam;
    QTableView *tableViewTeam;
    QSpacerItem *horizontalSpacer_2;
    QPushButton *pushButton;
    QTableView *tableView;
    QHBoxLayout *horizontalLayout_2;
    QPushButton *pushButtonAdd;
    QPushButton *pushButtonRemove;
    QSpacerItem *horizontalSpacer;
    QDialogButtonBox *buttonBox;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow2)
    {
        if (MainWindow2->objectName().isEmpty())
            MainWindow2->setObjectName(QStringLiteral("MainWindow2"));
        MainWindow2->resize(800, 600);
        centralwidget = new QWidget(MainWindow2);
        centralwidget->setObjectName(QStringLiteral("centralwidget"));
        gridLayout = new QGridLayout(centralwidget);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        pushButtonAddTeam = new QPushButton(centralwidget);
        pushButtonAddTeam->setObjectName(QStringLiteral("pushButtonAddTeam"));

        verticalLayout->addWidget(pushButtonAddTeam);

        pushButtonRemoveTeam = new QPushButton(centralwidget);
        pushButtonRemoveTeam->setObjectName(QStringLiteral("pushButtonRemoveTeam"));

        verticalLayout->addWidget(pushButtonRemoveTeam);


        horizontalLayout->addLayout(verticalLayout);

        tableViewTeam = new QTableView(centralwidget);
        tableViewTeam->setObjectName(QStringLiteral("tableViewTeam"));
        tableViewTeam->setSelectionMode(QAbstractItemView::SingleSelection);
        tableViewTeam->setSelectionBehavior(QAbstractItemView::SelectItems);

        horizontalLayout->addWidget(tableViewTeam);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_2);

        pushButton = new QPushButton(centralwidget);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(pushButton->sizePolicy().hasHeightForWidth());
        pushButton->setSizePolicy(sizePolicy);
        pushButton->setMinimumSize(QSize(100, 100));

        horizontalLayout->addWidget(pushButton);


        verticalLayout_2->addLayout(horizontalLayout);

        tableView = new QTableView(centralwidget);
        tableView->setObjectName(QStringLiteral("tableView"));
        tableView->setEditTriggers(QAbstractItemView::AnyKeyPressed|QAbstractItemView::EditKeyPressed|QAbstractItemView::SelectedClicked);
        tableView->setSelectionMode(QAbstractItemView::SingleSelection);

        verticalLayout_2->addWidget(tableView);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        pushButtonAdd = new QPushButton(centralwidget);
        pushButtonAdd->setObjectName(QStringLiteral("pushButtonAdd"));

        horizontalLayout_2->addWidget(pushButtonAdd);

        pushButtonRemove = new QPushButton(centralwidget);
        pushButtonRemove->setObjectName(QStringLiteral("pushButtonRemove"));

        horizontalLayout_2->addWidget(pushButtonRemove);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer);

        buttonBox = new QDialogButtonBox(centralwidget);
        buttonBox->setObjectName(QStringLiteral("buttonBox"));
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        horizontalLayout_2->addWidget(buttonBox);


        verticalLayout_2->addLayout(horizontalLayout_2);


        gridLayout->addLayout(verticalLayout_2, 0, 0, 1, 1);

        MainWindow2->setCentralWidget(centralwidget);
        statusbar = new QStatusBar(MainWindow2);
        statusbar->setObjectName(QStringLiteral("statusbar"));
        MainWindow2->setStatusBar(statusbar);

        retranslateUi(MainWindow2);

        QMetaObject::connectSlotsByName(MainWindow2);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow2)
    {
        MainWindow2->setWindowTitle(QApplication::translate("MainWindow2", "MainWindow", 0));
        pushButtonAddTeam->setText(QApplication::translate("MainWindow2", "Add Team", 0));
        pushButtonRemoveTeam->setText(QApplication::translate("MainWindow2", "Remove Team", 0));
        pushButton->setText(QString());
        pushButtonAdd->setText(QApplication::translate("MainWindow2", "Add", 0));
        pushButtonRemove->setText(QApplication::translate("MainWindow2", "Remove", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWindow2: public Ui_MainWindow2 {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TEAMMODIFIEROLD_H
