/********************************************************************************
** Form generated from reading ui file 'nuovogiocatore.ui'
**
** Created: Mon Oct 22 19:03:28 2007
**      by: Qt User Interface Compiler version 4.3.2
**
** WARNING! All changes made in this file will be lost when recompiling ui file!
********************************************************************************/

#ifndef UI_NUOVOGIOCATORE_H
#define UI_NUOVOGIOCATORE_H

#include <Qt3Support/Q3MimeSourceFactory>
#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QCheckBox>
#include <QtGui/QComboBox>
#include <QtGui/QDialog>
#include <QtGui/QGridLayout>
#include <QtGui/QHBoxLayout>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QPushButton>
#include <QtGui/QSpacerItem>
#include <QtGui/QVBoxLayout>
#include <vector>
#include "giocatore.h"

class Ui_NuovoGiocatore
{
public:
    QVBoxLayout *vboxLayout;
    QVBoxLayout *vboxLayout1;
    QHBoxLayout *hboxLayout;
    QGridLayout *gridLayout;
    QLabel *cognomeLabel;
    QLabel *nomeLabel;
    QLineEdit *nomeEdit;
    QLineEdit *cognomeEdit;
    QSpacerItem *spacerItem;
    QVBoxLayout *vboxLayout2;
    QCheckBox *randomCheck;
    QComboBox *contradaCombo;
    QSpacerItem *spacerItem1;
    QHBoxLayout *hboxLayout1;
    QSpacerItem *spacerItem2;
    QPushButton *okButton;
    QSpacerItem *spacerItem3;
    QPushButton *cancellaButton;
    QSpacerItem *spacerItem4;

    void setupUi(QDialog *NuovoGiocatore)
    {
    if (NuovoGiocatore->objectName().isEmpty())
        NuovoGiocatore->setObjectName(QString::fromUtf8("NuovoGiocatore"));
    NuovoGiocatore->resize(432, 183);
    vboxLayout = new QVBoxLayout(NuovoGiocatore);
    vboxLayout->setSpacing(6);
    vboxLayout->setMargin(11);
    vboxLayout->setObjectName(QString::fromUtf8("vboxLayout"));
    vboxLayout1 = new QVBoxLayout();
    vboxLayout1->setSpacing(6);
    vboxLayout1->setObjectName(QString::fromUtf8("vboxLayout1"));
    hboxLayout = new QHBoxLayout();
    hboxLayout->setSpacing(6);
    hboxLayout->setObjectName(QString::fromUtf8("hboxLayout"));
    gridLayout = new QGridLayout();
    gridLayout->setSpacing(6);
    gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
    cognomeLabel = new QLabel(NuovoGiocatore);
    cognomeLabel->setObjectName(QString::fromUtf8("cognomeLabel"));
    cognomeLabel->setWordWrap(false);

    gridLayout->addWidget(cognomeLabel, 1, 0, 1, 1);

    nomeLabel = new QLabel(NuovoGiocatore);
    nomeLabel->setObjectName(QString::fromUtf8("nomeLabel"));
    nomeLabel->setWordWrap(false);

    gridLayout->addWidget(nomeLabel, 0, 0, 1, 1);

    nomeEdit = new QLineEdit(NuovoGiocatore);
    nomeEdit->setObjectName(QString::fromUtf8("nomeEdit"));

    gridLayout->addWidget(nomeEdit, 0, 1, 1, 1);

    cognomeEdit = new QLineEdit(NuovoGiocatore);
    cognomeEdit->setObjectName(QString::fromUtf8("cognomeEdit"));

    gridLayout->addWidget(cognomeEdit, 1, 1, 1, 1);


    hboxLayout->addLayout(gridLayout);

    spacerItem = new QSpacerItem(40, 20, QSizePolicy::Minimum, QSizePolicy::Expanding);

    hboxLayout->addItem(spacerItem);

    vboxLayout2 = new QVBoxLayout();
    vboxLayout2->setSpacing(6);
    vboxLayout2->setObjectName(QString::fromUtf8("vboxLayout2"));
    randomCheck = new QCheckBox(NuovoGiocatore);
    randomCheck->setObjectName(QString::fromUtf8("randomCheck"));

    vboxLayout2->addWidget(randomCheck);

    contradaCombo = new QComboBox(NuovoGiocatore);
    contradaCombo->setObjectName(QString::fromUtf8("contradaCombo"));

    vboxLayout2->addWidget(contradaCombo);


    hboxLayout->addLayout(vboxLayout2);


    vboxLayout1->addLayout(hboxLayout);

    spacerItem1 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

    vboxLayout1->addItem(spacerItem1);

    hboxLayout1 = new QHBoxLayout();
    hboxLayout1->setSpacing(6);
    hboxLayout1->setObjectName(QString::fromUtf8("hboxLayout1"));
    spacerItem2 = new QSpacerItem(40, 20, QSizePolicy::Minimum, QSizePolicy::Expanding);

    hboxLayout1->addItem(spacerItem2);

    okButton = new QPushButton(NuovoGiocatore);
    okButton->setObjectName(QString::fromUtf8("okButton"));

    hboxLayout1->addWidget(okButton);

    spacerItem3 = new QSpacerItem(40, 20, QSizePolicy::Minimum, QSizePolicy::Expanding);

    hboxLayout1->addItem(spacerItem3);

    cancellaButton = new QPushButton(NuovoGiocatore);
    cancellaButton->setObjectName(QString::fromUtf8("cancellaButton"));

    hboxLayout1->addWidget(cancellaButton);

    spacerItem4 = new QSpacerItem(40, 20, QSizePolicy::Minimum, QSizePolicy::Expanding);

    hboxLayout1->addItem(spacerItem4);


    vboxLayout1->addLayout(hboxLayout1);


    vboxLayout->addLayout(vboxLayout1);


    retranslateUi(NuovoGiocatore);
    QObject::connect(cancellaButton, SIGNAL(clicked()), NuovoGiocatore, SLOT(reject()));
    QObject::connect(randomCheck, SIGNAL(stateChanged(int)), NuovoGiocatore, SLOT(enableCombo(int)));
    QObject::connect(okButton, SIGNAL(clicked()), NuovoGiocatore, SLOT(accept()));

    QMetaObject::connectSlotsByName(NuovoGiocatore);
    } // setupUi

    void retranslateUi(QDialog *NuovoGiocatore)
    {
    NuovoGiocatore->setWindowTitle(QApplication::translate("NuovoGiocatore", "Nuovo Giocatore", 0, QApplication::UnicodeUTF8));
    cognomeLabel->setText(QApplication::translate("NuovoGiocatore", "Cognome:", 0, QApplication::UnicodeUTF8));
    nomeLabel->setText(QApplication::translate("NuovoGiocatore", "Nome:", 0, QApplication::UnicodeUTF8));
    randomCheck->setText(QApplication::translate("NuovoGiocatore", "Assegna", 0, QApplication::UnicodeUTF8));
    okButton->setText(QApplication::translate("NuovoGiocatore", "OK", 0, QApplication::UnicodeUTF8));
    cancellaButton->setText(QApplication::translate("NuovoGiocatore", "Cancella", 0, QApplication::UnicodeUTF8));
    Q_UNUSED(NuovoGiocatore);
    } // retranslateUi

};

namespace Ui {
    class NuovoGiocatore: public Ui_NuovoGiocatore {};
} // namespace Ui

#endif // UI_NUOVOGIOCATORE_H
