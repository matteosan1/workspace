/********************************************************************************
** Form generated from reading UI file 'teammodifier.ui'
**
** Created by: Qt User Interface Compiler version 5.6.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TEAMMODIFIER_H
#define UI_TEAMMODIFIER_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTableView>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_UiTeamModifier
{
public:
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

    void setupUi(QDialog *UiTeamModifier)
    {
        if (UiTeamModifier->objectName().isEmpty())
            UiTeamModifier->setObjectName(QStringLiteral("UiTeamModifier"));
        UiTeamModifier->resize(778, 550);
        gridLayout = new QGridLayout(UiTeamModifier);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        pushButtonAddTeam = new QPushButton(UiTeamModifier);
        pushButtonAddTeam->setObjectName(QStringLiteral("pushButtonAddTeam"));

        verticalLayout->addWidget(pushButtonAddTeam);

        pushButtonRemoveTeam = new QPushButton(UiTeamModifier);
        pushButtonRemoveTeam->setObjectName(QStringLiteral("pushButtonRemoveTeam"));

        verticalLayout->addWidget(pushButtonRemoveTeam);


        horizontalLayout->addLayout(verticalLayout);

        tableViewTeam = new QTableView(UiTeamModifier);
        tableViewTeam->setObjectName(QStringLiteral("tableViewTeam"));
        tableViewTeam->setSelectionMode(QAbstractItemView::SingleSelection);
        tableViewTeam->setSelectionBehavior(QAbstractItemView::SelectItems);

        horizontalLayout->addWidget(tableViewTeam);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_2);

        pushButton = new QPushButton(UiTeamModifier);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(pushButton->sizePolicy().hasHeightForWidth());
        pushButton->setSizePolicy(sizePolicy);
        pushButton->setMinimumSize(QSize(100, 100));

        horizontalLayout->addWidget(pushButton);


        verticalLayout_2->addLayout(horizontalLayout);

        tableView = new QTableView(UiTeamModifier);
        tableView->setObjectName(QStringLiteral("tableView"));
        tableView->setEditTriggers(QAbstractItemView::AnyKeyPressed|QAbstractItemView::EditKeyPressed|QAbstractItemView::SelectedClicked);
        tableView->setSelectionMode(QAbstractItemView::SingleSelection);

        verticalLayout_2->addWidget(tableView);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        pushButtonAdd = new QPushButton(UiTeamModifier);
        pushButtonAdd->setObjectName(QStringLiteral("pushButtonAdd"));

        horizontalLayout_2->addWidget(pushButtonAdd);

        pushButtonRemove = new QPushButton(UiTeamModifier);
        pushButtonRemove->setObjectName(QStringLiteral("pushButtonRemove"));

        horizontalLayout_2->addWidget(pushButtonRemove);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer);

        buttonBox = new QDialogButtonBox(UiTeamModifier);
        buttonBox->setObjectName(QStringLiteral("buttonBox"));
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        horizontalLayout_2->addWidget(buttonBox);


        verticalLayout_2->addLayout(horizontalLayout_2);


        gridLayout->addLayout(verticalLayout_2, 0, 0, 1, 1);


        retranslateUi(UiTeamModifier);

        QMetaObject::connectSlotsByName(UiTeamModifier);
    } // setupUi

    void retranslateUi(QDialog *UiTeamModifier)
    {
        UiTeamModifier->setWindowTitle(QApplication::translate("UiTeamModifier", "Dialog", 0));
        pushButtonAddTeam->setText(QApplication::translate("UiTeamModifier", "Add Team", 0));
        pushButtonRemoveTeam->setText(QApplication::translate("UiTeamModifier", "Remove Team", 0));
        pushButton->setText(QString());
        pushButtonAdd->setText(QApplication::translate("UiTeamModifier", "Add", 0));
        pushButtonRemove->setText(QApplication::translate("UiTeamModifier", "Remove", 0));
    } // retranslateUi

};

namespace Ui {
    class UiTeamModifier: public Ui_UiTeamModifier {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TEAMMODIFIER_H
