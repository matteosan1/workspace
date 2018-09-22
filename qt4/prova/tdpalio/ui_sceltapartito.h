/********************************************************************************
** Form generated from reading ui file 'sceltapartito.ui'
**
** Created: Mon Oct 22 19:03:28 2007
**      by: Qt User Interface Compiler version 4.3.2
**
** WARNING! All changes made in this file will be lost when recompiling ui file!
********************************************************************************/

#ifndef UI_SCELTAPARTITO_H
#define UI_SCELTAPARTITO_H

#include <Qt3Support/Q3ButtonGroup>
#include <Qt3Support/Q3MimeSourceFactory>
#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QComboBox>
#include <QtGui/QDialog>
#include <QtGui/QHBoxLayout>
#include <QtGui/QLabel>
#include <QtGui/QPushButton>
#include <QtGui/QRadioButton>
#include <QtGui/QSpacerItem>
#include <QtGui/QSpinBox>
#include <QtGui/QVBoxLayout>

class Ui_SceltaPartito
{
public:
    QVBoxLayout *vboxLayout;
    QVBoxLayout *vboxLayout1;
    QHBoxLayout *hboxLayout;
    QSpacerItem *spacerItem;
    QLabel *playerLabel;
    QSpacerItem *spacerItem1;
    QSpacerItem *spacerItem2;
    QHBoxLayout *hboxLayout1;
    QVBoxLayout *vboxLayout2;
    QSpacerItem *spacerItem3;
    QLabel *contLabel;
    QComboBox *comboContrade;
    QSpacerItem *spacerItem4;
    QLabel *offertaLabel;
    QSpinBox *spinBox1;
    QSpacerItem *spacerItem5;
    QSpacerItem *spacerItem6;
    Q3ButtonGroup *partitiGroup;
    QRadioButton *tipo1;
    QRadioButton *tipo3;
    QRadioButton *tipo2;
    QComboBox *comboContrade2;
    QSpacerItem *spacerItem7;
    QHBoxLayout *hboxLayout2;
    QSpacerItem *spacerItem8;
    QPushButton *okButton;
    QSpacerItem *spacerItem9;
    QPushButton *cancelButton;
    QSpacerItem *spacerItem10;

    void setupUi(QDialog *SceltaPartito)
    {
    if (SceltaPartito->objectName().isEmpty())
        SceltaPartito->setObjectName(QString::fromUtf8("SceltaPartito"));
    SceltaPartito->resize(625, 333);
    vboxLayout = new QVBoxLayout(SceltaPartito);
    vboxLayout->setSpacing(6);
    vboxLayout->setMargin(11);
    vboxLayout->setObjectName(QString::fromUtf8("vboxLayout"));
    vboxLayout1 = new QVBoxLayout();
    vboxLayout1->setSpacing(6);
    vboxLayout1->setObjectName(QString::fromUtf8("vboxLayout1"));
    hboxLayout = new QHBoxLayout();
    hboxLayout->setSpacing(6);
    hboxLayout->setObjectName(QString::fromUtf8("hboxLayout"));
    spacerItem = new QSpacerItem(61, 20, QSizePolicy::Minimum, QSizePolicy::Expanding);

    hboxLayout->addItem(spacerItem);

    playerLabel = new QLabel(SceltaPartito);
    playerLabel->setObjectName(QString::fromUtf8("playerLabel"));
    playerLabel->setWordWrap(false);

    hboxLayout->addWidget(playerLabel);

    spacerItem1 = new QSpacerItem(81, 20, QSizePolicy::Minimum, QSizePolicy::Expanding);

    hboxLayout->addItem(spacerItem1);


    vboxLayout1->addLayout(hboxLayout);

    spacerItem2 = new QSpacerItem(20, 21, QSizePolicy::Minimum, QSizePolicy::Expanding);

    vboxLayout1->addItem(spacerItem2);

    hboxLayout1 = new QHBoxLayout();
    hboxLayout1->setSpacing(6);
    hboxLayout1->setObjectName(QString::fromUtf8("hboxLayout1"));
    vboxLayout2 = new QVBoxLayout();
    vboxLayout2->setSpacing(6);
    vboxLayout2->setObjectName(QString::fromUtf8("vboxLayout2"));
    spacerItem3 = new QSpacerItem(20, 21, QSizePolicy::Minimum, QSizePolicy::Expanding);

    vboxLayout2->addItem(spacerItem3);

    contLabel = new QLabel(SceltaPartito);
    contLabel->setObjectName(QString::fromUtf8("contLabel"));
    contLabel->setWordWrap(false);

    vboxLayout2->addWidget(contLabel);

    comboContrade = new QComboBox(SceltaPartito);
    comboContrade->setObjectName(QString::fromUtf8("comboContrade"));

    vboxLayout2->addWidget(comboContrade);

    spacerItem4 = new QSpacerItem(20, 31, QSizePolicy::Minimum, QSizePolicy::Expanding);

    vboxLayout2->addItem(spacerItem4);

    offertaLabel = new QLabel(SceltaPartito);
    offertaLabel->setObjectName(QString::fromUtf8("offertaLabel"));
    offertaLabel->setWordWrap(false);

    vboxLayout2->addWidget(offertaLabel);

    spinBox1 = new QSpinBox(SceltaPartito);
    spinBox1->setObjectName(QString::fromUtf8("spinBox1"));
    spinBox1->setMinimum(10);
    spinBox1->setMaximum(1000);
    spinBox1->setSingleStep(10);

    vboxLayout2->addWidget(spinBox1);

    spacerItem5 = new QSpacerItem(20, 51, QSizePolicy::Minimum, QSizePolicy::Expanding);

    vboxLayout2->addItem(spacerItem5);


    hboxLayout1->addLayout(vboxLayout2);

    spacerItem6 = new QSpacerItem(41, 21, QSizePolicy::Minimum, QSizePolicy::Fixed);

    hboxLayout1->addItem(spacerItem6);

    partitiGroup = new Q3ButtonGroup(SceltaPartito);
    partitiGroup->setObjectName(QString::fromUtf8("partitiGroup"));
    tipo1 = new QRadioButton(partitiGroup);
    tipo1->setObjectName(QString::fromUtf8("tipo1"));
    tipo1->setGeometry(QRect(40, 40, 97, 20));
    tipo3 = new QRadioButton(partitiGroup);
    tipo3->setObjectName(QString::fromUtf8("tipo3"));
    tipo3->setGeometry(QRect(40, 120, 97, 20));
    tipo2 = new QRadioButton(partitiGroup);
    tipo2->setObjectName(QString::fromUtf8("tipo2"));
    tipo2->setGeometry(QRect(40, 80, 111, 20));
    comboContrade2 = new QComboBox(partitiGroup);
    comboContrade2->setObjectName(QString::fromUtf8("comboContrade2"));
    comboContrade2->setEnabled(false);
    comboContrade2->setGeometry(QRect(30, 160, 130, 21));
    comboContrade2->setDuplicatesEnabled(false);

    hboxLayout1->addWidget(partitiGroup);


    vboxLayout1->addLayout(hboxLayout1);

    spacerItem7 = new QSpacerItem(20, 50, QSizePolicy::Minimum, QSizePolicy::Expanding);

    vboxLayout1->addItem(spacerItem7);

    hboxLayout2 = new QHBoxLayout();
    hboxLayout2->setSpacing(6);
    hboxLayout2->setObjectName(QString::fromUtf8("hboxLayout2"));
    spacerItem8 = new QSpacerItem(40, 20, QSizePolicy::Minimum, QSizePolicy::Expanding);

    hboxLayout2->addItem(spacerItem8);

    okButton = new QPushButton(SceltaPartito);
    okButton->setObjectName(QString::fromUtf8("okButton"));

    hboxLayout2->addWidget(okButton);

    spacerItem9 = new QSpacerItem(40, 20, QSizePolicy::Minimum, QSizePolicy::Expanding);

    hboxLayout2->addItem(spacerItem9);

    cancelButton = new QPushButton(SceltaPartito);
    cancelButton->setObjectName(QString::fromUtf8("cancelButton"));

    hboxLayout2->addWidget(cancelButton);

    spacerItem10 = new QSpacerItem(40, 20, QSizePolicy::Minimum, QSizePolicy::Expanding);

    hboxLayout2->addItem(spacerItem10);


    vboxLayout1->addLayout(hboxLayout2);


    vboxLayout->addLayout(vboxLayout1);


    retranslateUi(SceltaPartito);
    QObject::connect(cancelButton, SIGNAL(clicked()), SceltaPartito, SLOT(reject()));
    QObject::connect(tipo3, SIGNAL(toggled(bool)), SceltaPartito, SLOT(enableCombo(bool)));

    QMetaObject::connectSlotsByName(SceltaPartito);
    } // setupUi

    void retranslateUi(QDialog *SceltaPartito)
    {
    SceltaPartito->setWindowTitle(QApplication::translate("SceltaPartito", "Offerta Partiti", 0, QApplication::UnicodeUTF8));
    playerLabel->setText(QApplication::translate("SceltaPartito", "textLabel1", 0, QApplication::UnicodeUTF8));
    contLabel->setText(QApplication::translate("SceltaPartito", "Contrada", 0, QApplication::UnicodeUTF8));
    offertaLabel->setText(QApplication::translate("SceltaPartito", "Offerta:", 0, QApplication::UnicodeUTF8));
    partitiGroup->setTitle(QApplication::translate("SceltaPartito", "Partito", 0, QApplication::UnicodeUTF8));
    tipo1->setText(QApplication::translate("SceltaPartito", "Rincartare", 0, QApplication::UnicodeUTF8));
    tipo3->setText(QApplication::translate("SceltaPartito", "Fermare", 0, QApplication::UnicodeUTF8));
    tipo2->setText(QApplication::translate("SceltaPartito", "Andare piano", 0, QApplication::UnicodeUTF8));
    okButton->setText(QApplication::translate("SceltaPartito", "OK", 0, QApplication::UnicodeUTF8));
    cancelButton->setText(QApplication::translate("SceltaPartito", "Cancel", 0, QApplication::UnicodeUTF8));
    Q_UNUSED(SceltaPartito);
    } // retranslateUi

};

namespace Ui {
    class SceltaPartito: public Ui_SceltaPartito {};
} // namespace Ui

#endif // UI_SCELTAPARTITO_H
