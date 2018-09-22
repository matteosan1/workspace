/********************************************************************************
** Form generated from reading ui file 'messaggio.ui'
**
** Created: Mon Oct 22 19:03:28 2007
**      by: Qt User Interface Compiler version 4.3.2
**
** WARNING! All changes made in this file will be lost when recompiling ui file!
********************************************************************************/

#ifndef UI_MESSAGGIO_H
#define UI_MESSAGGIO_H

#include <Qt3Support/Q3Header>
#include <Qt3Support/Q3ListView>
#include <Qt3Support/Q3MimeSourceFactory>
#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QHBoxLayout>
#include <QtGui/QLabel>
#include <QtGui/QPushButton>
#include <QtGui/QSpacerItem>
#include <QtGui/QVBoxLayout>

class Ui_Messaggio
{
public:
    QVBoxLayout *vboxLayout;
    QVBoxLayout *vboxLayout1;
    QVBoxLayout *vboxLayout2;
    QHBoxLayout *hboxLayout;
    QSpacerItem *spacerItem;
    QVBoxLayout *vboxLayout3;
    QLabel *contradaLabel;
    QLabel *capitanoLabel;
    QPushButton *leggiButton;
    QSpacerItem *spacerItem1;
    Q3ListView *messaggiList;
    QHBoxLayout *hboxLayout1;
    QSpacerItem *spacerItem2;
    QPushButton *okButton;
    QSpacerItem *spacerItem3;

    void setupUi(QDialog *Messaggio)
    {
    if (Messaggio->objectName().isEmpty())
        Messaggio->setObjectName(QString::fromUtf8("Messaggio"));
    Messaggio->resize(630, 475);
    QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
    sizePolicy.setHorizontalStretch(0);
    sizePolicy.setVerticalStretch(0);
    sizePolicy.setHeightForWidth(Messaggio->sizePolicy().hasHeightForWidth());
    Messaggio->setSizePolicy(sizePolicy);
    Messaggio->setBaseSize(QSize(500, 0));
    vboxLayout = new QVBoxLayout(Messaggio);
    vboxLayout->setSpacing(6);
    vboxLayout->setMargin(11);
    vboxLayout->setObjectName(QString::fromUtf8("vboxLayout"));
    vboxLayout1 = new QVBoxLayout();
    vboxLayout1->setSpacing(6);
    vboxLayout1->setObjectName(QString::fromUtf8("vboxLayout1"));
    vboxLayout2 = new QVBoxLayout();
    vboxLayout2->setSpacing(6);
    vboxLayout2->setObjectName(QString::fromUtf8("vboxLayout2"));
    hboxLayout = new QHBoxLayout();
    hboxLayout->setSpacing(6);
    hboxLayout->setObjectName(QString::fromUtf8("hboxLayout"));
    spacerItem = new QSpacerItem(130, 20, QSizePolicy::Minimum, QSizePolicy::Expanding);

    hboxLayout->addItem(spacerItem);

    vboxLayout3 = new QVBoxLayout();
    vboxLayout3->setSpacing(6);
    vboxLayout3->setObjectName(QString::fromUtf8("vboxLayout3"));
    contradaLabel = new QLabel(Messaggio);
    contradaLabel->setObjectName(QString::fromUtf8("contradaLabel"));
    QSizePolicy sizePolicy1(QSizePolicy::MinimumExpanding, QSizePolicy::Preferred);
    sizePolicy1.setHorizontalStretch(0);
    sizePolicy1.setVerticalStretch(0);
    sizePolicy1.setHeightForWidth(contradaLabel->sizePolicy().hasHeightForWidth());
    contradaLabel->setSizePolicy(sizePolicy1);
    QFont font;
    font.setPointSize(18);
    contradaLabel->setFont(font);
    contradaLabel->setAlignment(Qt::AlignCenter);
    contradaLabel->setWordWrap(false);

    vboxLayout3->addWidget(contradaLabel);

    capitanoLabel = new QLabel(Messaggio);
    capitanoLabel->setObjectName(QString::fromUtf8("capitanoLabel"));
    QFont font1;
    font1.setPointSize(12);
    capitanoLabel->setFont(font1);
    capitanoLabel->setAlignment(Qt::AlignCenter);
    capitanoLabel->setWordWrap(false);

    vboxLayout3->addWidget(capitanoLabel);

    leggiButton = new QPushButton(Messaggio);
    leggiButton->setObjectName(QString::fromUtf8("leggiButton"));
    leggiButton->setCheckable(true);

    vboxLayout3->addWidget(leggiButton);


    hboxLayout->addLayout(vboxLayout3);

    spacerItem1 = new QSpacerItem(110, 20, QSizePolicy::Minimum, QSizePolicy::Expanding);

    hboxLayout->addItem(spacerItem1);


    vboxLayout2->addLayout(hboxLayout);

    messaggiList = new Q3ListView(Messaggio);
    messaggiList->addColumn(QApplication::translate("Messaggio", "Column 1", 0, QApplication::UnicodeUTF8));
    messaggiList->setObjectName(QString::fromUtf8("messaggiList"));

    vboxLayout2->addWidget(messaggiList);


    vboxLayout1->addLayout(vboxLayout2);

    hboxLayout1 = new QHBoxLayout();
    hboxLayout1->setSpacing(6);
    hboxLayout1->setObjectName(QString::fromUtf8("hboxLayout1"));
    spacerItem2 = new QSpacerItem(40, 20, QSizePolicy::Minimum, QSizePolicy::Expanding);

    hboxLayout1->addItem(spacerItem2);

    okButton = new QPushButton(Messaggio);
    okButton->setObjectName(QString::fromUtf8("okButton"));

    hboxLayout1->addWidget(okButton);

    spacerItem3 = new QSpacerItem(40, 20, QSizePolicy::Minimum, QSizePolicy::Expanding);

    hboxLayout1->addItem(spacerItem3);


    vboxLayout1->addLayout(hboxLayout1);


    vboxLayout->addLayout(vboxLayout1);


    retranslateUi(Messaggio);
    QObject::connect(okButton, SIGNAL(clicked()), Messaggio, SLOT(accept()));
    QObject::connect(leggiButton, SIGNAL(toggled(bool)), messaggiList, SLOT(setShown(bool)));
    QObject::connect(leggiButton, SIGNAL(toggled(bool)), okButton, SLOT(setShown(bool)));

    QMetaObject::connectSlotsByName(Messaggio);
    } // setupUi

    void retranslateUi(QDialog *Messaggio)
    {
    Messaggio->setWindowTitle(QApplication::translate("Messaggio", "Messaggio", 0, QApplication::UnicodeUTF8));
    contradaLabel->setText(QApplication::translate("Messaggio", "Contrada Sovrana dell'Istrice", 0, QApplication::UnicodeUTF8));
    capitanoLabel->setText(QApplication::translate("Messaggio", "textLabel5", 0, QApplication::UnicodeUTF8));
    leggiButton->setText(QApplication::translate("Messaggio", "Leggi messaggio", 0, QApplication::UnicodeUTF8));
    messaggiList->header()->setLabel(0, QApplication::translate("Messaggio", "Column 1", 0, QApplication::UnicodeUTF8));
    okButton->setText(QApplication::translate("Messaggio", "OK", 0, QApplication::UnicodeUTF8));
    Q_UNUSED(Messaggio);
    } // retranslateUi

};

namespace Ui {
    class Messaggio: public Ui_Messaggio {};
} // namespace Ui

#endif // UI_MESSAGGIO_H
