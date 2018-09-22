/********************************************************************************
** Form generated from reading UI file 'serverconnection.ui'
**
** Created by: Qt User Interface Compiler version 4.8.7
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SERVERCONNECTION_H
#define UI_SERVERCONNECTION_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QCheckBox>
#include <QtGui/QDialog>
#include <QtGui/QDialogButtonBox>
#include <QtGui/QGridLayout>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_serverConnection
{
public:
    QHBoxLayout *hboxLayout;
    QVBoxLayout *vboxLayout;
    QGridLayout *gridLayout;
    QLabel *label;
    QLineEdit *lineEdit;
    QLabel *label_2;
    QLineEdit *lineEdit_2;
    QCheckBox *checkBox;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *serverConnection)
    {
        if (serverConnection->objectName().isEmpty())
            serverConnection->setObjectName(QString::fromUtf8("serverConnection"));
        serverConnection->resize(302, 236);
        hboxLayout = new QHBoxLayout(serverConnection);
        hboxLayout->setObjectName(QString::fromUtf8("hboxLayout"));
        vboxLayout = new QVBoxLayout();
        vboxLayout->setObjectName(QString::fromUtf8("vboxLayout"));
        gridLayout = new QGridLayout();
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        label = new QLabel(serverConnection);
        label->setObjectName(QString::fromUtf8("label"));

        gridLayout->addWidget(label, 0, 0, 1, 1);

        lineEdit = new QLineEdit(serverConnection);
        lineEdit->setObjectName(QString::fromUtf8("lineEdit"));

        gridLayout->addWidget(lineEdit, 0, 1, 1, 1);

        label_2 = new QLabel(serverConnection);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        gridLayout->addWidget(label_2, 1, 0, 1, 1);

        lineEdit_2 = new QLineEdit(serverConnection);
        lineEdit_2->setObjectName(QString::fromUtf8("lineEdit_2"));

        gridLayout->addWidget(lineEdit_2, 1, 1, 1, 1);

        checkBox = new QCheckBox(serverConnection);
        checkBox->setObjectName(QString::fromUtf8("checkBox"));

        gridLayout->addWidget(checkBox, 2, 0, 1, 1);


        vboxLayout->addLayout(gridLayout);

        buttonBox = new QDialogButtonBox(serverConnection);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        vboxLayout->addWidget(buttonBox);


        hboxLayout->addLayout(vboxLayout);


        retranslateUi(serverConnection);
        QObject::connect(buttonBox, SIGNAL(accepted()), serverConnection, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), serverConnection, SLOT(reject()));

        QMetaObject::connectSlotsByName(serverConnection);
    } // setupUi

    void retranslateUi(QDialog *serverConnection)
    {
        serverConnection->setWindowTitle(QApplication::translate("serverConnection", "Connessione", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("serverConnection", "Host:", 0, QApplication::UnicodeUTF8));
        lineEdit->setText(QApplication::translate("serverConnection", "localhost", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("serverConnection", "Porta:", 0, QApplication::UnicodeUTF8));
        lineEdit_2->setInputMask(QApplication::translate("serverConnection", "ddddd; ", 0, QApplication::UnicodeUTF8));
        lineEdit_2->setText(QApplication::translate("serverConnection", "1974", 0, QApplication::UnicodeUTF8));
        checkBox->setText(QApplication::translate("serverConnection", "Server locale", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class serverConnection: public Ui_serverConnection {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SERVERCONNECTION_H
