/********************************************************************************
** Form generated from reading ui file 'strategiaprove.ui'
**
** Created: Mon Oct 22 19:03:29 2007
**      by: Qt User Interface Compiler version 4.3.2
**
** WARNING! All changes made in this file will be lost when recompiling ui file!
********************************************************************************/

#ifndef UI_STRATEGIAPROVE_H
#define UI_STRATEGIAPROVE_H

#include <Qt3Support/Q3GroupBox>
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
#include <QtGui/QProgressBar>
#include <QtGui/QPushButton>
#include <QtGui/QSpacerItem>
#include <QtGui/QSpinBox>
#include <QtGui/QVBoxLayout>
#include "barbero.h"

class Ui_StrategiaProve
{
public:
    QVBoxLayout *vboxLayout;
    QVBoxLayout *vboxLayout1;
    QLabel *contradaLabel;
    QLabel *montaLabel;
    QHBoxLayout *hboxLayout;
    QVBoxLayout *vboxLayout2;
    Q3GroupBox *scelta1Box;
    QHBoxLayout *hboxLayout1;
    QHBoxLayout *hboxLayout2;
    QVBoxLayout *vboxLayout3;
    QComboBox *scelta1Combo;
    QCheckBox *scelta1Check;
    QGridLayout *gridLayout;
    QComboBox *contrada1Combo;
    QSpinBox *scelta1Spin;
    QSpacerItem *spacerItem;
    Q3GroupBox *scelta2Group;
    QHBoxLayout *hboxLayout3;
    QHBoxLayout *hboxLayout4;
    QVBoxLayout *vboxLayout4;
    QComboBox *scelta2Combo;
    QCheckBox *scelta2Check;
    QVBoxLayout *vboxLayout5;
    QHBoxLayout *hboxLayout5;
    QSpacerItem *spacerItem1;
    QSpinBox *scelta2Spin;
    QComboBox *contrada2Combo;
    Q3GroupBox *scelta3Group;
    QHBoxLayout *hboxLayout6;
    QHBoxLayout *hboxLayout7;
    QVBoxLayout *vboxLayout6;
    QComboBox *scelta3Combo;
    QCheckBox *scelta3Check;
    QVBoxLayout *vboxLayout7;
    QHBoxLayout *hboxLayout8;
    QSpacerItem *spacerItem2;
    QSpinBox *scelta3Spin;
    QComboBox *contrada3Combo;
    QSpacerItem *spacerItem3;
    QVBoxLayout *vboxLayout8;
    Q3GroupBox *provaBox;
    QHBoxLayout *hboxLayout9;
    QHBoxLayout *hboxLayout10;
    QVBoxLayout *vboxLayout9;
    QLabel *primaLabel;
    QLabel *secondaLabel;
    QLabel *terzaLabel;
    QLabel *quartaLabel;
    QLabel *generaleLabel;
    QLabel *acciaLabel;
    QVBoxLayout *vboxLayout10;
    QComboBox *primaCombo;
    QComboBox *secondaCombo;
    QComboBox *terzaCombo;
    QComboBox *quartaCombo;
    QComboBox *generaleCombo;
    QComboBox *acciaCombo;
    QSpacerItem *spacerItem4;
    QLabel *cavalloLabel;
    QProgressBar *formaBar;
    QSpacerItem *spacerItem5;
    QHBoxLayout *hboxLayout11;
    QSpacerItem *spacerItem6;
    QPushButton *okButton;
    QSpacerItem *spacerItem7;
    QPushButton *cancelButton;
    QSpacerItem *spacerItem8;

    void setupUi(QDialog *StrategiaProve)
    {
    if (StrategiaProve->objectName().isEmpty())
        StrategiaProve->setObjectName(QString::fromUtf8("StrategiaProve"));
    StrategiaProve->resize(671, 441);
    vboxLayout = new QVBoxLayout(StrategiaProve);
    vboxLayout->setSpacing(6);
    vboxLayout->setMargin(11);
    vboxLayout->setObjectName(QString::fromUtf8("vboxLayout"));
    vboxLayout1 = new QVBoxLayout();
    vboxLayout1->setSpacing(6);
    vboxLayout1->setObjectName(QString::fromUtf8("vboxLayout1"));
    contradaLabel = new QLabel(StrategiaProve);
    contradaLabel->setObjectName(QString::fromUtf8("contradaLabel"));
    contradaLabel->setAlignment(Qt::AlignCenter);
    contradaLabel->setWordWrap(false);

    vboxLayout1->addWidget(contradaLabel);

    montaLabel = new QLabel(StrategiaProve);
    montaLabel->setObjectName(QString::fromUtf8("montaLabel"));
    montaLabel->setAlignment(Qt::AlignCenter);
    montaLabel->setWordWrap(false);

    vboxLayout1->addWidget(montaLabel);

    hboxLayout = new QHBoxLayout();
    hboxLayout->setSpacing(6);
    hboxLayout->setObjectName(QString::fromUtf8("hboxLayout"));
    vboxLayout2 = new QVBoxLayout();
    vboxLayout2->setSpacing(6);
    vboxLayout2->setObjectName(QString::fromUtf8("vboxLayout2"));
    scelta1Box = new Q3GroupBox(StrategiaProve);
    scelta1Box->setObjectName(QString::fromUtf8("scelta1Box"));
    scelta1Box->setColumnLayout(0, Qt::Vertical);
    scelta1Box->layout()->setSpacing(6);
    scelta1Box->layout()->setMargin(11);
    hboxLayout1 = new QHBoxLayout();
    QBoxLayout *boxlayout = qobject_cast<QBoxLayout *>(scelta1Box->layout());
    if (boxlayout)
        boxlayout->addLayout(hboxLayout1);
    hboxLayout1->setAlignment(Qt::AlignTop);
    hboxLayout1->setObjectName(QString::fromUtf8("hboxLayout1"));
    hboxLayout2 = new QHBoxLayout();
    hboxLayout2->setSpacing(6);
    hboxLayout2->setObjectName(QString::fromUtf8("hboxLayout2"));
    vboxLayout3 = new QVBoxLayout();
    vboxLayout3->setSpacing(6);
    vboxLayout3->setObjectName(QString::fromUtf8("vboxLayout3"));
    scelta1Combo = new QComboBox(scelta1Box);
    scelta1Combo->setObjectName(QString::fromUtf8("scelta1Combo"));
    scelta1Combo->setDuplicatesEnabled(false);

    vboxLayout3->addWidget(scelta1Combo);

    scelta1Check = new QCheckBox(scelta1Box);
    scelta1Check->setObjectName(QString::fromUtf8("scelta1Check"));

    vboxLayout3->addWidget(scelta1Check);


    hboxLayout2->addLayout(vboxLayout3);

    gridLayout = new QGridLayout();
    gridLayout->setSpacing(6);
    gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
    contrada1Combo = new QComboBox(scelta1Box);
    contrada1Combo->setObjectName(QString::fromUtf8("contrada1Combo"));
    contrada1Combo->setEnabled(false);

    gridLayout->addWidget(contrada1Combo, 1, 0, 1, 2);

    scelta1Spin = new QSpinBox(scelta1Box);
    scelta1Spin->setObjectName(QString::fromUtf8("scelta1Spin"));

    gridLayout->addWidget(scelta1Spin, 0, 1, 1, 1);

    spacerItem = new QSpacerItem(40, 20, QSizePolicy::Minimum, QSizePolicy::Expanding);

    gridLayout->addItem(spacerItem, 0, 0, 1, 1);


    hboxLayout2->addLayout(gridLayout);


    hboxLayout1->addLayout(hboxLayout2);


    vboxLayout2->addWidget(scelta1Box);

    scelta2Group = new Q3GroupBox(StrategiaProve);
    scelta2Group->setObjectName(QString::fromUtf8("scelta2Group"));
    scelta2Group->setColumnLayout(0, Qt::Vertical);
    scelta2Group->layout()->setSpacing(6);
    scelta2Group->layout()->setMargin(11);
    hboxLayout3 = new QHBoxLayout();
    QBoxLayout *boxlayout1 = qobject_cast<QBoxLayout *>(scelta2Group->layout());
    if (boxlayout1)
        boxlayout1->addLayout(hboxLayout3);
    hboxLayout3->setAlignment(Qt::AlignTop);
    hboxLayout3->setObjectName(QString::fromUtf8("hboxLayout3"));
    hboxLayout4 = new QHBoxLayout();
    hboxLayout4->setSpacing(6);
    hboxLayout4->setObjectName(QString::fromUtf8("hboxLayout4"));
    vboxLayout4 = new QVBoxLayout();
    vboxLayout4->setSpacing(6);
    vboxLayout4->setObjectName(QString::fromUtf8("vboxLayout4"));
    scelta2Combo = new QComboBox(scelta2Group);
    scelta2Combo->setObjectName(QString::fromUtf8("scelta2Combo"));
    scelta2Combo->setDuplicatesEnabled(false);

    vboxLayout4->addWidget(scelta2Combo);

    scelta2Check = new QCheckBox(scelta2Group);
    scelta2Check->setObjectName(QString::fromUtf8("scelta2Check"));

    vboxLayout4->addWidget(scelta2Check);


    hboxLayout4->addLayout(vboxLayout4);

    vboxLayout5 = new QVBoxLayout();
    vboxLayout5->setSpacing(6);
    vboxLayout5->setObjectName(QString::fromUtf8("vboxLayout5"));
    hboxLayout5 = new QHBoxLayout();
    hboxLayout5->setSpacing(6);
    hboxLayout5->setObjectName(QString::fromUtf8("hboxLayout5"));
    spacerItem1 = new QSpacerItem(40, 20, QSizePolicy::Minimum, QSizePolicy::Expanding);

    hboxLayout5->addItem(spacerItem1);

    scelta2Spin = new QSpinBox(scelta2Group);
    scelta2Spin->setObjectName(QString::fromUtf8("scelta2Spin"));

    hboxLayout5->addWidget(scelta2Spin);


    vboxLayout5->addLayout(hboxLayout5);

    contrada2Combo = new QComboBox(scelta2Group);
    contrada2Combo->setObjectName(QString::fromUtf8("contrada2Combo"));
    contrada2Combo->setEnabled(false);

    vboxLayout5->addWidget(contrada2Combo);


    hboxLayout4->addLayout(vboxLayout5);


    hboxLayout3->addLayout(hboxLayout4);


    vboxLayout2->addWidget(scelta2Group);

    scelta3Group = new Q3GroupBox(StrategiaProve);
    scelta3Group->setObjectName(QString::fromUtf8("scelta3Group"));
    scelta3Group->setColumnLayout(0, Qt::Vertical);
    scelta3Group->layout()->setSpacing(6);
    scelta3Group->layout()->setMargin(11);
    hboxLayout6 = new QHBoxLayout();
    QBoxLayout *boxlayout2 = qobject_cast<QBoxLayout *>(scelta3Group->layout());
    if (boxlayout2)
        boxlayout2->addLayout(hboxLayout6);
    hboxLayout6->setAlignment(Qt::AlignTop);
    hboxLayout6->setObjectName(QString::fromUtf8("hboxLayout6"));
    hboxLayout7 = new QHBoxLayout();
    hboxLayout7->setSpacing(6);
    hboxLayout7->setObjectName(QString::fromUtf8("hboxLayout7"));
    vboxLayout6 = new QVBoxLayout();
    vboxLayout6->setSpacing(6);
    vboxLayout6->setObjectName(QString::fromUtf8("vboxLayout6"));
    scelta3Combo = new QComboBox(scelta3Group);
    scelta3Combo->setObjectName(QString::fromUtf8("scelta3Combo"));
    scelta3Combo->setDuplicatesEnabled(false);

    vboxLayout6->addWidget(scelta3Combo);

    scelta3Check = new QCheckBox(scelta3Group);
    scelta3Check->setObjectName(QString::fromUtf8("scelta3Check"));

    vboxLayout6->addWidget(scelta3Check);


    hboxLayout7->addLayout(vboxLayout6);

    vboxLayout7 = new QVBoxLayout();
    vboxLayout7->setSpacing(6);
    vboxLayout7->setObjectName(QString::fromUtf8("vboxLayout7"));
    hboxLayout8 = new QHBoxLayout();
    hboxLayout8->setSpacing(6);
    hboxLayout8->setObjectName(QString::fromUtf8("hboxLayout8"));
    spacerItem2 = new QSpacerItem(40, 20, QSizePolicy::Minimum, QSizePolicy::Expanding);

    hboxLayout8->addItem(spacerItem2);

    scelta3Spin = new QSpinBox(scelta3Group);
    scelta3Spin->setObjectName(QString::fromUtf8("scelta3Spin"));

    hboxLayout8->addWidget(scelta3Spin);


    vboxLayout7->addLayout(hboxLayout8);

    contrada3Combo = new QComboBox(scelta3Group);
    contrada3Combo->setObjectName(QString::fromUtf8("contrada3Combo"));
    contrada3Combo->setEnabled(false);

    vboxLayout7->addWidget(contrada3Combo);


    hboxLayout7->addLayout(vboxLayout7);


    hboxLayout6->addLayout(hboxLayout7);


    vboxLayout2->addWidget(scelta3Group);


    hboxLayout->addLayout(vboxLayout2);

    spacerItem3 = new QSpacerItem(174, 20, QSizePolicy::Minimum, QSizePolicy::Expanding);

    hboxLayout->addItem(spacerItem3);

    vboxLayout8 = new QVBoxLayout();
    vboxLayout8->setSpacing(6);
    vboxLayout8->setObjectName(QString::fromUtf8("vboxLayout8"));
    provaBox = new Q3GroupBox(StrategiaProve);
    provaBox->setObjectName(QString::fromUtf8("provaBox"));
    provaBox->setColumnLayout(0, Qt::Vertical);
    provaBox->layout()->setSpacing(6);
    provaBox->layout()->setMargin(11);
    hboxLayout9 = new QHBoxLayout();
    QBoxLayout *boxlayout3 = qobject_cast<QBoxLayout *>(provaBox->layout());
    if (boxlayout3)
        boxlayout3->addLayout(hboxLayout9);
    hboxLayout9->setAlignment(Qt::AlignTop);
    hboxLayout9->setObjectName(QString::fromUtf8("hboxLayout9"));
    hboxLayout10 = new QHBoxLayout();
    hboxLayout10->setSpacing(6);
    hboxLayout10->setObjectName(QString::fromUtf8("hboxLayout10"));
    vboxLayout9 = new QVBoxLayout();
    vboxLayout9->setSpacing(6);
    vboxLayout9->setObjectName(QString::fromUtf8("vboxLayout9"));
    primaLabel = new QLabel(provaBox);
    primaLabel->setObjectName(QString::fromUtf8("primaLabel"));
    primaLabel->setWordWrap(false);

    vboxLayout9->addWidget(primaLabel);

    secondaLabel = new QLabel(provaBox);
    secondaLabel->setObjectName(QString::fromUtf8("secondaLabel"));
    secondaLabel->setWordWrap(false);

    vboxLayout9->addWidget(secondaLabel);

    terzaLabel = new QLabel(provaBox);
    terzaLabel->setObjectName(QString::fromUtf8("terzaLabel"));
    terzaLabel->setWordWrap(false);

    vboxLayout9->addWidget(terzaLabel);

    quartaLabel = new QLabel(provaBox);
    quartaLabel->setObjectName(QString::fromUtf8("quartaLabel"));
    quartaLabel->setWordWrap(false);

    vboxLayout9->addWidget(quartaLabel);

    generaleLabel = new QLabel(provaBox);
    generaleLabel->setObjectName(QString::fromUtf8("generaleLabel"));
    generaleLabel->setWordWrap(false);

    vboxLayout9->addWidget(generaleLabel);

    acciaLabel = new QLabel(provaBox);
    acciaLabel->setObjectName(QString::fromUtf8("acciaLabel"));
    acciaLabel->setWordWrap(false);

    vboxLayout9->addWidget(acciaLabel);


    hboxLayout10->addLayout(vboxLayout9);

    vboxLayout10 = new QVBoxLayout();
    vboxLayout10->setSpacing(6);
    vboxLayout10->setObjectName(QString::fromUtf8("vboxLayout10"));
    primaCombo = new QComboBox(provaBox);
    primaCombo->setObjectName(QString::fromUtf8("primaCombo"));

    vboxLayout10->addWidget(primaCombo);

    secondaCombo = new QComboBox(provaBox);
    secondaCombo->setObjectName(QString::fromUtf8("secondaCombo"));

    vboxLayout10->addWidget(secondaCombo);

    terzaCombo = new QComboBox(provaBox);
    terzaCombo->setObjectName(QString::fromUtf8("terzaCombo"));

    vboxLayout10->addWidget(terzaCombo);

    quartaCombo = new QComboBox(provaBox);
    quartaCombo->setObjectName(QString::fromUtf8("quartaCombo"));

    vboxLayout10->addWidget(quartaCombo);

    generaleCombo = new QComboBox(provaBox);
    generaleCombo->setObjectName(QString::fromUtf8("generaleCombo"));

    vboxLayout10->addWidget(generaleCombo);

    acciaCombo = new QComboBox(provaBox);
    acciaCombo->setObjectName(QString::fromUtf8("acciaCombo"));

    vboxLayout10->addWidget(acciaCombo);


    hboxLayout10->addLayout(vboxLayout10);


    hboxLayout9->addLayout(hboxLayout10);


    vboxLayout8->addWidget(provaBox);

    spacerItem4 = new QSpacerItem(20, 20, QSizePolicy::Minimum, QSizePolicy::Expanding);

    vboxLayout8->addItem(spacerItem4);

    cavalloLabel = new QLabel(StrategiaProve);
    cavalloLabel->setObjectName(QString::fromUtf8("cavalloLabel"));
    cavalloLabel->setWordWrap(false);

    vboxLayout8->addWidget(cavalloLabel);

    formaBar = new QProgressBar(StrategiaProve);
    formaBar->setObjectName(QString::fromUtf8("formaBar"));
    formaBar->setValue(24);

    vboxLayout8->addWidget(formaBar);

    spacerItem5 = new QSpacerItem(20, 20, QSizePolicy::Minimum, QSizePolicy::Expanding);

    vboxLayout8->addItem(spacerItem5);


    hboxLayout->addLayout(vboxLayout8);


    vboxLayout1->addLayout(hboxLayout);

    hboxLayout11 = new QHBoxLayout();
    hboxLayout11->setSpacing(6);
    hboxLayout11->setObjectName(QString::fromUtf8("hboxLayout11"));
    spacerItem6 = new QSpacerItem(40, 20, QSizePolicy::Minimum, QSizePolicy::Expanding);

    hboxLayout11->addItem(spacerItem6);

    okButton = new QPushButton(StrategiaProve);
    okButton->setObjectName(QString::fromUtf8("okButton"));

    hboxLayout11->addWidget(okButton);

    spacerItem7 = new QSpacerItem(40, 20, QSizePolicy::Minimum, QSizePolicy::Expanding);

    hboxLayout11->addItem(spacerItem7);

    cancelButton = new QPushButton(StrategiaProve);
    cancelButton->setObjectName(QString::fromUtf8("cancelButton"));

    hboxLayout11->addWidget(cancelButton);

    spacerItem8 = new QSpacerItem(40, 20, QSizePolicy::Minimum, QSizePolicy::Expanding);

    hboxLayout11->addItem(spacerItem8);


    vboxLayout1->addLayout(hboxLayout11);


    vboxLayout->addLayout(vboxLayout1);


    retranslateUi(StrategiaProve);
    QObject::connect(okButton, SIGNAL(clicked()), StrategiaProve, SLOT(accept()));
    QObject::connect(cancelButton, SIGNAL(clicked()), StrategiaProve, SLOT(reject()));
    QObject::connect(scelta1Check, SIGNAL(stateChanged(int)), StrategiaProve, SLOT(enableCombo1(int)));
    QObject::connect(scelta2Check, SIGNAL(stateChanged(int)), StrategiaProve, SLOT(enableCombo2(int)));
    QObject::connect(scelta3Check, SIGNAL(stateChanged(int)), StrategiaProve, SLOT(enableCombo3(int)));

    QMetaObject::connectSlotsByName(StrategiaProve);
    } // setupUi

    void retranslateUi(QDialog *StrategiaProve)
    {
    StrategiaProve->setWindowTitle(QApplication::translate("StrategiaProve", "Strategia Prove", 0, QApplication::UnicodeUTF8));
    contradaLabel->setText(QApplication::translate("StrategiaProve", "textLabel2", 0, QApplication::UnicodeUTF8));
    montaLabel->setText(QApplication::translate("StrategiaProve", "textLabel2", 0, QApplication::UnicodeUTF8));
    scelta1Box->setTitle(QApplication::translate("StrategiaProve", "Fantino: prima scelta", 0, QApplication::UnicodeUTF8));
    scelta1Check->setText(QApplication::translate("StrategiaProve", "Non montare:", 0, QApplication::UnicodeUTF8));
    scelta2Group->setTitle(QApplication::translate("StrategiaProve", "Fantino:seconda scelta", 0, QApplication::UnicodeUTF8));
    scelta2Check->setText(QApplication::translate("StrategiaProve", "Non montare:", 0, QApplication::UnicodeUTF8));
    scelta3Group->setTitle(QApplication::translate("StrategiaProve", "Fantino: terza scelta", 0, QApplication::UnicodeUTF8));
    scelta3Check->setText(QApplication::translate("StrategiaProve", "Non montare:", 0, QApplication::UnicodeUTF8));
    provaBox->setTitle(QApplication::translate("StrategiaProve", "Strategia Prove", 0, QApplication::UnicodeUTF8));
    primaLabel->setText(QApplication::translate("StrategiaProve", "Prima Prova:", 0, QApplication::UnicodeUTF8));
    secondaLabel->setText(QApplication::translate("StrategiaProve", "Seconda Prova:", 0, QApplication::UnicodeUTF8));
    terzaLabel->setText(QApplication::translate("StrategiaProve", "Terza Prova:", 0, QApplication::UnicodeUTF8));
    quartaLabel->setText(QApplication::translate("StrategiaProve", "Quarta Prova:", 0, QApplication::UnicodeUTF8));
    generaleLabel->setText(QApplication::translate("StrategiaProve", "Prova Generale:", 0, QApplication::UnicodeUTF8));
    acciaLabel->setText(QApplication::translate("StrategiaProve", "Provaccia:", 0, QApplication::UnicodeUTF8));
    cavalloLabel->setText(QApplication::translate("StrategiaProve", "textLabel1", 0, QApplication::UnicodeUTF8));
    okButton->setText(QApplication::translate("StrategiaProve", "OK", 0, QApplication::UnicodeUTF8));
    cancelButton->setText(QApplication::translate("StrategiaProve", "Cancella", 0, QApplication::UnicodeUTF8));
    Q_UNUSED(StrategiaProve);
    } // retranslateUi

};

namespace Ui {
    class StrategiaProve: public Ui_StrategiaProve {};
} // namespace Ui

#endif // UI_STRATEGIAPROVE_H
