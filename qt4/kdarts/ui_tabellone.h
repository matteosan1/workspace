/********************************************************************************
** Form generated from reading ui file 'tabellone.ui'
**
** Created: Tue Jan 15 23:11:39 2008
**      by: Qt User Interface Compiler version 4.3.2
**
** WARNING! All changes made in this file will be lost when recompiling ui file!
********************************************************************************/

#ifndef UI_TABELLONE_H
#define UI_TABELLONE_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QLCDNumber>
#include <QtGui/QLabel>
#include <QtGui/QVBoxLayout>

class Ui_Dialog
{
public:
    QVBoxLayout *vboxLayout;
    QVBoxLayout *vboxLayout1;
    QLCDNumber *lcdNumber;
    QLabel *label;

    void setupUi(QDialog *Dialog)
    {
    if (Dialog->objectName().isEmpty())
        Dialog->setObjectName(QString::fromUtf8("Dialog"));
    Dialog->resize(357, 234);
    vboxLayout = new QVBoxLayout(Dialog);
    vboxLayout->setObjectName(QString::fromUtf8("vboxLayout"));
    vboxLayout1 = new QVBoxLayout();
    vboxLayout1->setObjectName(QString::fromUtf8("vboxLayout1"));
    lcdNumber = new QLCDNumber(Dialog);
    lcdNumber->setObjectName(QString::fromUtf8("lcdNumber"));
    lcdNumber->setFrameShadow(QFrame::Raised);
    lcdNumber->setLineWidth(0);
    lcdNumber->setNumDigits(3);
    lcdNumber->setSegmentStyle(QLCDNumber::Filled);
    lcdNumber->setProperty("intValue", QVariant(501));

    vboxLayout1->addWidget(lcdNumber);

    label = new QLabel(Dialog);
    label->setObjectName(QString::fromUtf8("label"));
    QFont font;
    font.setPointSize(34);
    label->setFont(font);
    label->setAlignment(Qt::AlignCenter);

    vboxLayout1->addWidget(label);


    vboxLayout->addLayout(vboxLayout1);


    retranslateUi(Dialog);

    QMetaObject::connectSlotsByName(Dialog);
    } // setupUi

    void retranslateUi(QDialog *Dialog)
    {
    Dialog->setWindowTitle(QApplication::translate("Dialog", "Dialog", 0, QApplication::UnicodeUTF8));
    label->setText(QApplication::translate("Dialog", "Florentina", 0, QApplication::UnicodeUTF8));
    Q_UNUSED(Dialog);
    } // retranslateUi

};

namespace Ui {
    class Dialog: public Ui_Dialog {};
} // namespace Ui

#endif // UI_TABELLONE_H
