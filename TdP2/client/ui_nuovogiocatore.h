/********************************************************************************
** Form generated from reading UI file 'nuovogiocatore.ui'
**
** Created by: Qt User Interface Compiler version 4.8.7
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
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
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QPushButton>
#include <QtGui/QSpacerItem>
#include <QtGui/QVBoxLayout>
#include <vector>
#include "../tdpaliocommon/giocatore.h"

QT_BEGIN_NAMESPACE

class Ui_NuovoGiocatore
{
public:
    QVBoxLayout *vboxLayout;
    QVBoxLayout *vboxLayout1;
    QHBoxLayout *hboxLayout;
    QVBoxLayout *vboxLayout2;
    QCheckBox *randomCheck;
    QComboBox *contradaCombo;
    QSpacerItem *spacerItem;
    QHBoxLayout *hboxLayout1;
    QSpacerItem *spacerItem1;
    QPushButton *okButton;
    QSpacerItem *spacerItem2;
    QPushButton *cancellaButton;
    QSpacerItem *spacerItem3;

    void setupUi(QDialog *NuovoGiocatore)
    {
        if (NuovoGiocatore->objectName().isEmpty())
            NuovoGiocatore->setObjectName(QString::fromUtf8("NuovoGiocatore"));
        NuovoGiocatore->resize(432, 183);
        vboxLayout = new QVBoxLayout(NuovoGiocatore);
        vboxLayout->setSpacing(6);
        vboxLayout->setContentsMargins(11, 11, 11, 11);
        vboxLayout->setObjectName(QString::fromUtf8("vboxLayout"));
        vboxLayout1 = new QVBoxLayout();
        vboxLayout1->setSpacing(6);
        vboxLayout1->setObjectName(QString::fromUtf8("vboxLayout1"));
        hboxLayout = new QHBoxLayout();
        hboxLayout->setSpacing(6);
        hboxLayout->setObjectName(QString::fromUtf8("hboxLayout"));
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

        spacerItem = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        vboxLayout1->addItem(spacerItem);

        hboxLayout1 = new QHBoxLayout();
        hboxLayout1->setSpacing(6);
        hboxLayout1->setObjectName(QString::fromUtf8("hboxLayout1"));
        spacerItem1 = new QSpacerItem(40, 20, QSizePolicy::Minimum, QSizePolicy::Expanding);

        hboxLayout1->addItem(spacerItem1);

        okButton = new QPushButton(NuovoGiocatore);
        okButton->setObjectName(QString::fromUtf8("okButton"));

        hboxLayout1->addWidget(okButton);

        spacerItem2 = new QSpacerItem(40, 20, QSizePolicy::Minimum, QSizePolicy::Expanding);

        hboxLayout1->addItem(spacerItem2);

        cancellaButton = new QPushButton(NuovoGiocatore);
        cancellaButton->setObjectName(QString::fromUtf8("cancellaButton"));

        hboxLayout1->addWidget(cancellaButton);

        spacerItem3 = new QSpacerItem(40, 20, QSizePolicy::Minimum, QSizePolicy::Expanding);

        hboxLayout1->addItem(spacerItem3);


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
        randomCheck->setText(QApplication::translate("NuovoGiocatore", "Assegna", 0, QApplication::UnicodeUTF8));
        okButton->setText(QApplication::translate("NuovoGiocatore", "OK", 0, QApplication::UnicodeUTF8));
        cancellaButton->setText(QApplication::translate("NuovoGiocatore", "Cancella", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class NuovoGiocatore: public Ui_NuovoGiocatore {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_NUOVOGIOCATORE_H
