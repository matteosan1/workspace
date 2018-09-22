/********************************************************************************
** Form generated from reading UI file 'cup.ui'
**
** Created by: Qt User Interface Compiler version 5.6.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CUP_H
#define UI_CUP_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QListWidget>

QT_BEGIN_NAMESPACE

class Ui_Dialog
{
public:
    QDialogButtonBox *buttonBox;
    QListWidget *listWidgetGirone1;
    QListWidget *listWidgetGirone2;
    QComboBox *comboBoxGirone1;
    QComboBox *comboBoxGirone2;

    void setupUi(QDialog *Dialog)
    {
        if (Dialog->objectName().isEmpty())
            Dialog->setObjectName(QStringLiteral("Dialog"));
        Dialog->resize(537, 367);
        buttonBox = new QDialogButtonBox(Dialog);
        buttonBox->setObjectName(QStringLiteral("buttonBox"));
        buttonBox->setGeometry(QRect(170, 320, 341, 32));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);
        listWidgetGirone1 = new QListWidget(Dialog);
        listWidgetGirone1->setObjectName(QStringLiteral("listWidgetGirone1"));
        listWidgetGirone1->setGeometry(QRect(20, 60, 211, 191));
        listWidgetGirone2 = new QListWidget(Dialog);
        listWidgetGirone2->setObjectName(QStringLiteral("listWidgetGirone2"));
        listWidgetGirone2->setGeometry(QRect(280, 60, 211, 191));
        comboBoxGirone1 = new QComboBox(Dialog);
        comboBoxGirone1->setObjectName(QStringLiteral("comboBoxGirone1"));
        comboBoxGirone1->setGeometry(QRect(20, 30, 211, 26));
        comboBoxGirone2 = new QComboBox(Dialog);
        comboBoxGirone2->setObjectName(QStringLiteral("comboBoxGirone2"));
        comboBoxGirone2->setGeometry(QRect(280, 30, 211, 26));

        retranslateUi(Dialog);
        QObject::connect(buttonBox, SIGNAL(accepted()), Dialog, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), Dialog, SLOT(reject()));

        QMetaObject::connectSlotsByName(Dialog);
    } // setupUi

    void retranslateUi(QDialog *Dialog)
    {
        Dialog->setWindowTitle(QApplication::translate("Dialog", "Dialog", 0));
    } // retranslateUi

};

namespace Ui {
    class Dialog: public Ui_Dialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CUP_H
