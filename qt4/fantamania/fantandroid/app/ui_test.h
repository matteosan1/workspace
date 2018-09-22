/********************************************************************************
** Form generated from reading UI file 'test.ui'
**
** Created by: Qt User Interface Compiler version 5.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TEST_H
#define UI_TEST_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTableView>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Test
{
public:
    QVBoxLayout *verticalLayout;
    QTableView *tableRoster;
    QHBoxLayout *horizontalLayout;
    QPushButton *pushButtonOK;
    QPushButton *pushButtonCancel;

    void setupUi(QWidget *Test)
    {
        if (Test->objectName().isEmpty())
            Test->setObjectName(QStringLiteral("Test"));
        Test->resize(480, 640);
        verticalLayout = new QVBoxLayout(Test);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        tableRoster = new QTableView(Test);
        tableRoster->setObjectName(QStringLiteral("tableRoster"));
        QSizePolicy sizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(tableRoster->sizePolicy().hasHeightForWidth());
        tableRoster->setSizePolicy(sizePolicy);
        tableRoster->setMinimumSize(QSize(0, 500));

        verticalLayout->addWidget(tableRoster);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setSizeConstraint(QLayout::SetDefaultConstraint);
        pushButtonOK = new QPushButton(Test);
        pushButtonOK->setObjectName(QStringLiteral("pushButtonOK"));
        sizePolicy.setHeightForWidth(pushButtonOK->sizePolicy().hasHeightForWidth());
        pushButtonOK->setSizePolicy(sizePolicy);
        pushButtonOK->setMaximumSize(QSize(16777215, 150));

        horizontalLayout->addWidget(pushButtonOK);

        pushButtonCancel = new QPushButton(Test);
        pushButtonCancel->setObjectName(QStringLiteral("pushButtonCancel"));
        sizePolicy.setHeightForWidth(pushButtonCancel->sizePolicy().hasHeightForWidth());
        pushButtonCancel->setSizePolicy(sizePolicy);
        pushButtonCancel->setMaximumSize(QSize(16777215, 150));

        horizontalLayout->addWidget(pushButtonCancel);


        verticalLayout->addLayout(horizontalLayout);


        retranslateUi(Test);

        QMetaObject::connectSlotsByName(Test);
    } // setupUi

    void retranslateUi(QWidget *Test)
    {
        Test->setWindowTitle(QApplication::translate("Test", "Form", 0));
        pushButtonOK->setText(QApplication::translate("Test", "OK", 0));
        pushButtonCancel->setText(QApplication::translate("Test", "Cancella", 0));
    } // retranslateUi

};

namespace Ui {
    class Test: public Ui_Test {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TEST_H
