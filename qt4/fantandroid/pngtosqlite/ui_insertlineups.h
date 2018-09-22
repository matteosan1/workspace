/********************************************************************************
** Form generated from reading UI file 'insertlineups.ui'
**
** Created by: Qt User Interface Compiler version 5.6.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_INSERTLINEUPS_H
#define UI_INSERTLINEUPS_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_UiInsertLineup
{
public:
    QGridLayout *gridLayout;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout_2;
    QHBoxLayout *horizontalLayout;
    QLabel *labelRound;
    QSpinBox *spinBoxRound;
    QSpacerItem *horizontalSpacer;
    QTextEdit *textEdit;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *UiInsertLineup)
    {
        if (UiInsertLineup->objectName().isEmpty())
            UiInsertLineup->setObjectName(QStringLiteral("UiInsertLineup"));
        UiInsertLineup->resize(519, 428);
        gridLayout = new QGridLayout(UiInsertLineup);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        labelRound = new QLabel(UiInsertLineup);
        labelRound->setObjectName(QStringLiteral("labelRound"));

        horizontalLayout->addWidget(labelRound);

        spinBoxRound = new QSpinBox(UiInsertLineup);
        spinBoxRound->setObjectName(QStringLiteral("spinBoxRound"));
        spinBoxRound->setMinimum(1);

        horizontalLayout->addWidget(spinBoxRound);


        horizontalLayout_2->addLayout(horizontalLayout);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer);


        verticalLayout->addLayout(horizontalLayout_2);

        textEdit = new QTextEdit(UiInsertLineup);
        textEdit->setObjectName(QStringLiteral("textEdit"));

        verticalLayout->addWidget(textEdit);

        buttonBox = new QDialogButtonBox(UiInsertLineup);
        buttonBox->setObjectName(QStringLiteral("buttonBox"));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        verticalLayout->addWidget(buttonBox);


        gridLayout->addLayout(verticalLayout, 0, 0, 1, 1);


        retranslateUi(UiInsertLineup);
        QObject::connect(buttonBox, SIGNAL(accepted()), UiInsertLineup, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), UiInsertLineup, SLOT(reject()));

        QMetaObject::connectSlotsByName(UiInsertLineup);
    } // setupUi

    void retranslateUi(QDialog *UiInsertLineup)
    {
        UiInsertLineup->setWindowTitle(QApplication::translate("UiInsertLineup", "Dialog", 0));
        labelRound->setText(QApplication::translate("UiInsertLineup", "Giornata", 0));
    } // retranslateUi

};

namespace Ui {
    class UiInsertLineup: public Ui_UiInsertLineup {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_INSERTLINEUPS_H
