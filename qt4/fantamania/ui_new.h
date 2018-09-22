/********************************************************************************
** Form generated from reading UI file 'new.ui'
**
** Created by: Qt User Interface Compiler version 4.8.7
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_NEW_H
#define UI_NEW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QDialogButtonBox>
#include <QtGui/QGridLayout>
#include <QtGui/QGroupBox>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QSpinBox>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_NewDialog
{
public:
    QDialogButtonBox *buttonBox;
    QLabel *labelNome;
    QLineEdit *lineNome;
    QLabel *labelAnno;
    QLineEdit *lineAnno;
    QGroupBox *groupGiocatori;
    QWidget *widget;
    QGridLayout *gridLayout;
    QLabel *label_3;
    QSpinBox *spinPortieri;
    QLabel *label_4;
    QSpinBox *spinDifensori;
    QLabel *label_5;
    QSpinBox *spinCentrocampisti;
    QLabel *label_6;
    QSpinBox *spinAttaccanti;

    void setupUi(QDialog *NewDialog)
    {
        if (NewDialog->objectName().isEmpty())
            NewDialog->setObjectName(QString::fromUtf8("NewDialog"));
        NewDialog->resize(465, 294);
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(NewDialog->sizePolicy().hasHeightForWidth());
        NewDialog->setSizePolicy(sizePolicy);
        buttonBox = new QDialogButtonBox(NewDialog);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        buttonBox->setGeometry(QRect(110, 240, 341, 32));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::NoButton|QDialogButtonBox::Ok);
        labelNome = new QLabel(NewDialog);
        labelNome->setObjectName(QString::fromUtf8("labelNome"));
        labelNome->setGeometry(QRect(20, 40, 122, 18));
        lineNome = new QLineEdit(NewDialog);
        lineNome->setObjectName(QString::fromUtf8("lineNome"));
        lineNome->setGeometry(QRect(20, 60, 161, 23));
        labelAnno = new QLabel(NewDialog);
        labelAnno->setObjectName(QString::fromUtf8("labelAnno"));
        labelAnno->setGeometry(QRect(20, 110, 56, 18));
        lineAnno = new QLineEdit(NewDialog);
        lineAnno->setObjectName(QString::fromUtf8("lineAnno"));
        lineAnno->setGeometry(QRect(20, 130, 113, 23));
        groupGiocatori = new QGroupBox(NewDialog);
        groupGiocatori->setObjectName(QString::fromUtf8("groupGiocatori"));
        groupGiocatori->setGeometry(QRect(240, 30, 191, 171));
        widget = new QWidget(groupGiocatori);
        widget->setObjectName(QString::fromUtf8("widget"));
        widget->setGeometry(QRect(20, 30, 148, 115));
        gridLayout = new QGridLayout(widget);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        gridLayout->setContentsMargins(0, 0, 0, 0);
        label_3 = new QLabel(widget);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        gridLayout->addWidget(label_3, 0, 0, 1, 1);

        spinPortieri = new QSpinBox(widget);
        spinPortieri->setObjectName(QString::fromUtf8("spinPortieri"));
        spinPortieri->setValue(1);

        gridLayout->addWidget(spinPortieri, 0, 1, 1, 1);

        label_4 = new QLabel(widget);
        label_4->setObjectName(QString::fromUtf8("label_4"));

        gridLayout->addWidget(label_4, 1, 0, 1, 1);

        spinDifensori = new QSpinBox(widget);
        spinDifensori->setObjectName(QString::fromUtf8("spinDifensori"));
        spinDifensori->setValue(8);

        gridLayout->addWidget(spinDifensori, 1, 1, 1, 1);

        label_5 = new QLabel(widget);
        label_5->setObjectName(QString::fromUtf8("label_5"));

        gridLayout->addWidget(label_5, 2, 0, 1, 1);

        spinCentrocampisti = new QSpinBox(widget);
        spinCentrocampisti->setObjectName(QString::fromUtf8("spinCentrocampisti"));
        spinCentrocampisti->setValue(8);

        gridLayout->addWidget(spinCentrocampisti, 2, 1, 1, 1);

        label_6 = new QLabel(widget);
        label_6->setObjectName(QString::fromUtf8("label_6"));

        gridLayout->addWidget(label_6, 3, 0, 1, 1);

        spinAttaccanti = new QSpinBox(widget);
        spinAttaccanti->setObjectName(QString::fromUtf8("spinAttaccanti"));
        spinAttaccanti->setValue(5);

        gridLayout->addWidget(spinAttaccanti, 3, 1, 1, 1);


        retranslateUi(NewDialog);
        QObject::connect(buttonBox, SIGNAL(accepted()), NewDialog, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), NewDialog, SLOT(reject()));

        QMetaObject::connectSlotsByName(NewDialog);
    } // setupUi

    void retranslateUi(QDialog *NewDialog)
    {
        NewDialog->setWindowTitle(QApplication::translate("NewDialog", "Inserimento nuova squadra", 0, QApplication::UnicodeUTF8));
        labelNome->setText(QApplication::translate("NewDialog", "Nome della Squadra", 0, QApplication::UnicodeUTF8));
        labelAnno->setText(QApplication::translate("NewDialog", "Anno", 0, QApplication::UnicodeUTF8));
        groupGiocatori->setTitle(QApplication::translate("NewDialog", "Giocatori", 0, QApplication::UnicodeUTF8));
        label_3->setText(QApplication::translate("NewDialog", "Portieri", 0, QApplication::UnicodeUTF8));
        label_4->setText(QApplication::translate("NewDialog", "Difensori", 0, QApplication::UnicodeUTF8));
        label_5->setText(QApplication::translate("NewDialog", "Centrocampisti", 0, QApplication::UnicodeUTF8));
        label_6->setText(QApplication::translate("NewDialog", "Attaccanti", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class NewDialog: public Ui_NewDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_NEW_H
