/********************************************************************************
** Form generated from reading ui file 'tratta.ui'
**
** Created: Mon Oct 22 19:03:29 2007
**      by: Qt User Interface Compiler version 4.3.2
**
** WARNING! All changes made in this file will be lost when recompiling ui file!
********************************************************************************/

#ifndef UI_TRATTA_H
#define UI_TRATTA_H

#include <Qt3Support/Q3MimeSourceFactory>
#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QHBoxLayout>
#include <QtGui/QPushButton>
#include <QtGui/QTableWidget>
#include <QtGui/QVBoxLayout>

class Ui_Tratta
{
public:
    QVBoxLayout *vboxLayout;
    QTableWidget *cavalliView;
    QHBoxLayout *hboxLayout;
    QPushButton *okButton;

    void setupUi(QDialog *Tratta)
    {
    if (Tratta->objectName().isEmpty())
        Tratta->setObjectName(QString::fromUtf8("Tratta"));
    Tratta->resize(463, 481);
    vboxLayout = new QVBoxLayout(Tratta);
    vboxLayout->setSpacing(6);
    vboxLayout->setMargin(11);
    vboxLayout->setObjectName(QString::fromUtf8("vboxLayout"));
    cavalliView = new QTableWidget(Tratta);
    cavalliView->setObjectName(QString::fromUtf8("cavalliView"));

    vboxLayout->addWidget(cavalliView);

    hboxLayout = new QHBoxLayout();
    hboxLayout->setSpacing(6);
    hboxLayout->setObjectName(QString::fromUtf8("hboxLayout"));
    okButton = new QPushButton(Tratta);
    okButton->setObjectName(QString::fromUtf8("okButton"));
    okButton->setEnabled(true);

    hboxLayout->addWidget(okButton);


    vboxLayout->addLayout(hboxLayout);


    retranslateUi(Tratta);
    QObject::connect(okButton, SIGNAL(clicked()), Tratta, SLOT(accept()));

    QMetaObject::connectSlotsByName(Tratta);
    } // setupUi

    void retranslateUi(QDialog *Tratta)
    {
    Tratta->setWindowTitle(QApplication::translate("Tratta", "Scelta Cavalli", 0, QApplication::UnicodeUTF8));
    okButton->setText(QApplication::translate("Tratta", "OK", 0, QApplication::UnicodeUTF8));
    Q_UNUSED(Tratta);
    } // retranslateUi

};

namespace Ui {
    class Tratta: public Ui_Tratta {};
} // namespace Ui

#endif // UI_TRATTA_H
