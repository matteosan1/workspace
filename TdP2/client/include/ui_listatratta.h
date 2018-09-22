/********************************************************************************
** Form generated from reading ui file 'listatratta.ui'
**
** Created: Thu Jun 25 15:59:05 2009
**      by: Qt User Interface Compiler version 4.5.0
**
** WARNING! All changes made in this file will be lost when recompiling ui file!
********************************************************************************/

#ifndef UI_LISTATRATTA_H
#define UI_LISTATRATTA_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QDialogButtonBox>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QTextEdit>
#include <QtGui/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_ListaTratta
{
public:
    QHBoxLayout *horizontalLayout;
    QVBoxLayout *verticalLayout;
    QTextEdit *textEdit;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *ListaTratta)
    {
        if (ListaTratta->objectName().isEmpty())
            ListaTratta->setObjectName(QString::fromUtf8("ListaTratta"));
        ListaTratta->resize(413, 463);
        horizontalLayout = new QHBoxLayout(ListaTratta);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        textEdit = new QTextEdit(ListaTratta);
        textEdit->setObjectName(QString::fromUtf8("textEdit"));
        QFont font;
        font.setFamily(QString::fromUtf8("Courier New"));
        font.setPointSize(12);
        textEdit->setFont(font);
        textEdit->setReadOnly(true);

        verticalLayout->addWidget(textEdit);

        buttonBox = new QDialogButtonBox(ListaTratta);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        verticalLayout->addWidget(buttonBox);


        horizontalLayout->addLayout(verticalLayout);


        retranslateUi(ListaTratta);
        QObject::connect(buttonBox, SIGNAL(accepted()), ListaTratta, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), ListaTratta, SLOT(reject()));

        QMetaObject::connectSlotsByName(ListaTratta);
    } // setupUi

    void retranslateUi(QDialog *ListaTratta)
    {
        ListaTratta->setWindowTitle(QApplication::translate("ListaTratta", "Dialog", 0, QApplication::UnicodeUTF8));
        Q_UNUSED(ListaTratta);
    } // retranslateUi

};

namespace Ui {
    class ListaTratta: public Ui_ListaTratta {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LISTATRATTA_H
