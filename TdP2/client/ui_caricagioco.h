/********************************************************************************
** Form generated from reading UI file 'caricagioco.ui'
**
** Created by: Qt User Interface Compiler version 4.8.7
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CARICAGIOCO_H
#define UI_CARICAGIOCO_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QPushButton>
#include <QtGui/QSpacerItem>
#include <QtGui/QTableWidget>
#include <QtGui/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_CaricaGioco
{
public:
    QHBoxLayout *hboxLayout;
    QVBoxLayout *vboxLayout;
    QTableWidget *tableFile;
    QSpacerItem *spacerItem;
    QHBoxLayout *hboxLayout1;
    QPushButton *newButton;
    QPushButton *caricaButton;
    QPushButton *cancellaButton;

    void setupUi(QDialog *CaricaGioco)
    {
        if (CaricaGioco->objectName().isEmpty())
            CaricaGioco->setObjectName(QString::fromUtf8("CaricaGioco"));
        CaricaGioco->resize(400, 300);
        hboxLayout = new QHBoxLayout(CaricaGioco);
        hboxLayout->setObjectName(QString::fromUtf8("hboxLayout"));
        vboxLayout = new QVBoxLayout();
        vboxLayout->setObjectName(QString::fromUtf8("vboxLayout"));
        tableFile = new QTableWidget(CaricaGioco);
        tableFile->setObjectName(QString::fromUtf8("tableFile"));

        vboxLayout->addWidget(tableFile);

        spacerItem = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        vboxLayout->addItem(spacerItem);

        hboxLayout1 = new QHBoxLayout();
        hboxLayout1->setObjectName(QString::fromUtf8("hboxLayout1"));
        newButton = new QPushButton(CaricaGioco);
        newButton->setObjectName(QString::fromUtf8("newButton"));

        hboxLayout1->addWidget(newButton);

        caricaButton = new QPushButton(CaricaGioco);
        caricaButton->setObjectName(QString::fromUtf8("caricaButton"));
        caricaButton->setEnabled(false);

        hboxLayout1->addWidget(caricaButton);

        cancellaButton = new QPushButton(CaricaGioco);
        cancellaButton->setObjectName(QString::fromUtf8("cancellaButton"));

        hboxLayout1->addWidget(cancellaButton);


        vboxLayout->addLayout(hboxLayout1);


        hboxLayout->addLayout(vboxLayout);


        retranslateUi(CaricaGioco);
        QObject::connect(cancellaButton, SIGNAL(clicked()), CaricaGioco, SLOT(reject()));
        QObject::connect(newButton, SIGNAL(clicked()), CaricaGioco, SLOT(accept()));

        QMetaObject::connectSlotsByName(CaricaGioco);
    } // setupUi

    void retranslateUi(QDialog *CaricaGioco)
    {
        CaricaGioco->setWindowTitle(QApplication::translate("CaricaGioco", "Carica Gioco", 0, QApplication::UnicodeUTF8));
        newButton->setText(QApplication::translate("CaricaGioco", "Nuovo...", 0, QApplication::UnicodeUTF8));
        caricaButton->setText(QApplication::translate("CaricaGioco", "Carica...", 0, QApplication::UnicodeUTF8));
        cancellaButton->setText(QApplication::translate("CaricaGioco", "Cancella", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class CaricaGioco: public Ui_CaricaGioco {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CARICAGIOCO_H
