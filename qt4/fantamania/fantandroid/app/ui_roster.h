/********************************************************************************
** Form generated from reading UI file 'roster.ui'
**
** Created by: Qt User Interface Compiler version 5.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ROSTER_H
#define UI_ROSTER_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTableView>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_roster
{
public:
    QVBoxLayout *verticalLayout;
    QTableView *tableViewPlayers;
    QPushButton *pushButtonNew;
    QPushButton *pushButtonDelete;
    QDialogButtonBox *buttonBox;

    void setupUi(QWidget *roster)
    {
        if (roster->objectName().isEmpty())
            roster->setObjectName(QStringLiteral("roster"));
        roster->resize(480, 640);
        QSizePolicy sizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(roster->sizePolicy().hasHeightForWidth());
        roster->setSizePolicy(sizePolicy);
        verticalLayout = new QVBoxLayout(roster);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        tableViewPlayers = new QTableView(roster);
        tableViewPlayers->setObjectName(QStringLiteral("tableViewPlayers"));
        sizePolicy.setHeightForWidth(tableViewPlayers->sizePolicy().hasHeightForWidth());
        tableViewPlayers->setSizePolicy(sizePolicy);
        tableViewPlayers->setEditTriggers(QAbstractItemView::AnyKeyPressed);
        tableViewPlayers->setCornerButtonEnabled(false);

        verticalLayout->addWidget(tableViewPlayers);

        pushButtonNew = new QPushButton(roster);
        pushButtonNew->setObjectName(QStringLiteral("pushButtonNew"));

        verticalLayout->addWidget(pushButtonNew);

        pushButtonDelete = new QPushButton(roster);
        pushButtonDelete->setObjectName(QStringLiteral("pushButtonDelete"));

        verticalLayout->addWidget(pushButtonDelete);

        buttonBox = new QDialogButtonBox(roster);
        buttonBox->setObjectName(QStringLiteral("buttonBox"));
        QSizePolicy sizePolicy1(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(buttonBox->sizePolicy().hasHeightForWidth());
        buttonBox->setSizePolicy(sizePolicy1);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        verticalLayout->addWidget(buttonBox);


        retranslateUi(roster);

        QMetaObject::connectSlotsByName(roster);
    } // setupUi

    void retranslateUi(QWidget *roster)
    {
        roster->setWindowTitle(QApplication::translate("roster", "Form", 0));
        pushButtonNew->setText(QApplication::translate("roster", "Nuovo", 0));
        pushButtonDelete->setText(QApplication::translate("roster", "Rimuovi", 0));
    } // retranslateUi

};

namespace Ui {
    class roster: public Ui_roster {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ROSTER_H
