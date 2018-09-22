/********************************************************************************
** Form generated from reading UI file 'profilo.ui'
**
** Created by: Qt User Interface Compiler version 4.8.7
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PROFILO_H
#define UI_PROFILO_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QGridLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QPushButton>
#include <QtGui/QSpacerItem>

QT_BEGIN_NAMESPACE

class Ui_ProfiloDialog
{
public:
    QGridLayout *gridLayout;
    QLabel *label;
    QLineEdit *lineNome;
    QLabel *label_2;
    QLineEdit *lineCognome;
    QSpacerItem *horizontalSpacer;
    QLabel *label_3;
    QLineEdit *lineUsername;
    QPushButton *pushButton;
    QSpacerItem *horizontalSpacer_2;

    void setupUi(QDialog *ProfiloDialog)
    {
        if (ProfiloDialog->objectName().isEmpty())
            ProfiloDialog->setObjectName(QString::fromUtf8("ProfiloDialog"));
        ProfiloDialog->resize(425, 300);
        gridLayout = new QGridLayout(ProfiloDialog);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        label = new QLabel(ProfiloDialog);
        label->setObjectName(QString::fromUtf8("label"));

        gridLayout->addWidget(label, 0, 0, 1, 1);

        lineNome = new QLineEdit(ProfiloDialog);
        lineNome->setObjectName(QString::fromUtf8("lineNome"));

        gridLayout->addWidget(lineNome, 0, 1, 1, 1);

        label_2 = new QLabel(ProfiloDialog);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        gridLayout->addWidget(label_2, 1, 0, 1, 1);

        lineCognome = new QLineEdit(ProfiloDialog);
        lineCognome->setObjectName(QString::fromUtf8("lineCognome"));

        gridLayout->addWidget(lineCognome, 1, 1, 1, 1);

        horizontalSpacer = new QSpacerItem(166, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer, 1, 2, 1, 1);

        label_3 = new QLabel(ProfiloDialog);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        gridLayout->addWidget(label_3, 2, 0, 1, 1);

        lineUsername = new QLineEdit(ProfiloDialog);
        lineUsername->setObjectName(QString::fromUtf8("lineUsername"));

        gridLayout->addWidget(lineUsername, 2, 1, 1, 1);

        pushButton = new QPushButton(ProfiloDialog);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));

        gridLayout->addWidget(pushButton, 3, 2, 1, 1);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_2, 3, 1, 1, 1);


        retranslateUi(ProfiloDialog);

        QMetaObject::connectSlotsByName(ProfiloDialog);
    } // setupUi

    void retranslateUi(QDialog *ProfiloDialog)
    {
        ProfiloDialog->setWindowTitle(QApplication::translate("ProfiloDialog", "Profilo Giocatore", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("ProfiloDialog", "Nome:", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("ProfiloDialog", "Cognome:", 0, QApplication::UnicodeUTF8));
        label_3->setText(QApplication::translate("ProfiloDialog", "Username:", 0, QApplication::UnicodeUTF8));
        pushButton->setText(QApplication::translate("ProfiloDialog", "OK", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class ProfiloDialog: public Ui_ProfiloDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PROFILO_H
