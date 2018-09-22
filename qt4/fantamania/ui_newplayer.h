/********************************************************************************
** Form generated from reading UI file 'newplayer.ui'
**
** Created by: Qt User Interface Compiler version 4.8.7
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_NEWPLAYER_H
#define UI_NEWPLAYER_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QDialogButtonBox>
#include <QtGui/QGroupBox>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QRadioButton>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_NewPlayer
{
public:
    QDialogButtonBox *buttonBox;
    QLabel *label;
    QLabel *label_2;
    QLineEdit *lineEdit;
    QLineEdit *lineEdit_2;
    QGroupBox *groupBox;
    QWidget *layoutWidget;
    QVBoxLayout *vboxLayout;
    QRadioButton *radioButton;
    QRadioButton *radioButton_2;
    QRadioButton *radioButton_3;
    QRadioButton *radioButton_4;
    QLineEdit *lineEdit_3;
    QLabel *label_3;
    QLineEdit *lineEdit_4;
    QLabel *label_4;

    void setupUi(QDialog *NewPlayer)
    {
        if (NewPlayer->objectName().isEmpty())
            NewPlayer->setObjectName(QString::fromUtf8("NewPlayer"));
        NewPlayer->resize(400, 476);
        buttonBox = new QDialogButtonBox(NewPlayer);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        buttonBox->setGeometry(QRect(40, 430, 341, 32));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::NoButton|QDialogButtonBox::Ok);
        label = new QLabel(NewPlayer);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(40, 30, 56, 18));
        label_2 = new QLabel(NewPlayer);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(40, 70, 56, 18));
        lineEdit = new QLineEdit(NewPlayer);
        lineEdit->setObjectName(QString::fromUtf8("lineEdit"));
        lineEdit->setGeometry(QRect(120, 30, 113, 23));
        lineEdit_2 = new QLineEdit(NewPlayer);
        lineEdit_2->setObjectName(QString::fromUtf8("lineEdit_2"));
        lineEdit_2->setGeometry(QRect(120, 70, 113, 23));
        groupBox = new QGroupBox(NewPlayer);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        groupBox->setGeometry(QRect(110, 120, 141, 151));
        layoutWidget = new QWidget(groupBox);
        layoutWidget->setObjectName(QString::fromUtf8("layoutWidget"));
        layoutWidget->setGeometry(QRect(10, 30, 121, 97));
        vboxLayout = new QVBoxLayout(layoutWidget);
        vboxLayout->setObjectName(QString::fromUtf8("vboxLayout"));
        vboxLayout->setContentsMargins(0, 0, 0, 0);
        radioButton = new QRadioButton(layoutWidget);
        radioButton->setObjectName(QString::fromUtf8("radioButton"));

        vboxLayout->addWidget(radioButton);

        radioButton_2 = new QRadioButton(layoutWidget);
        radioButton_2->setObjectName(QString::fromUtf8("radioButton_2"));

        vboxLayout->addWidget(radioButton_2);

        radioButton_3 = new QRadioButton(layoutWidget);
        radioButton_3->setObjectName(QString::fromUtf8("radioButton_3"));

        vboxLayout->addWidget(radioButton_3);

        radioButton_4 = new QRadioButton(layoutWidget);
        radioButton_4->setObjectName(QString::fromUtf8("radioButton_4"));

        vboxLayout->addWidget(radioButton_4);

        lineEdit_3 = new QLineEdit(NewPlayer);
        lineEdit_3->setObjectName(QString::fromUtf8("lineEdit_3"));
        lineEdit_3->setGeometry(QRect(130, 350, 113, 23));
        label_3 = new QLabel(NewPlayer);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(50, 310, 56, 18));
        lineEdit_4 = new QLineEdit(NewPlayer);
        lineEdit_4->setObjectName(QString::fromUtf8("lineEdit_4"));
        lineEdit_4->setGeometry(QRect(130, 310, 113, 23));
        label_4 = new QLabel(NewPlayer);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setGeometry(QRect(50, 350, 56, 18));

        retranslateUi(NewPlayer);
        QObject::connect(buttonBox, SIGNAL(accepted()), NewPlayer, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), NewPlayer, SLOT(reject()));

        QMetaObject::connectSlotsByName(NewPlayer);
    } // setupUi

    void retranslateUi(QDialog *NewPlayer)
    {
        NewPlayer->setWindowTitle(QApplication::translate("NewPlayer", "Nuovo Giocatore", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("NewPlayer", "Cognome", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("NewPlayer", "Nome", 0, QApplication::UnicodeUTF8));
        groupBox->setTitle(QApplication::translate("NewPlayer", "Ruolo", 0, QApplication::UnicodeUTF8));
        radioButton->setText(QApplication::translate("NewPlayer", "Portiere", 0, QApplication::UnicodeUTF8));
        radioButton_2->setText(QApplication::translate("NewPlayer", "Difensore", 0, QApplication::UnicodeUTF8));
        radioButton_3->setText(QApplication::translate("NewPlayer", "Centrocampista", 0, QApplication::UnicodeUTF8));
        radioButton_4->setText(QApplication::translate("NewPlayer", "Attaccante", 0, QApplication::UnicodeUTF8));
        label_3->setText(QApplication::translate("NewPlayer", "Squadra", 0, QApplication::UnicodeUTF8));
        lineEdit_4->setInputMask(QString());
        label_4->setText(QApplication::translate("NewPlayer", "Prezzo", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class NewPlayer: public Ui_NewPlayer {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_NEWPLAYER_H
