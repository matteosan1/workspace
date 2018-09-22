/********************************************************************************
** Form generated from reading ui file 'listagenerica.ui'
**
** Created: Thu Jun 25 15:59:05 2009
**      by: Qt User Interface Compiler version 4.5.0
**
** WARNING! All changes made in this file will be lost when recompiling ui file!
********************************************************************************/

#ifndef UI_LISTAGENERICA_H
#define UI_LISTAGENERICA_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QDialogButtonBox>
#include <QtGui/QHeaderView>
#include <QtGui/QTableWidget>
#include <QtGui/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_ListaGenerica
{
public:
    QVBoxLayout *verticalLayout;
    QTableWidget *tableView;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *ListaGenerica)
    {
        if (ListaGenerica->objectName().isEmpty())
            ListaGenerica->setObjectName(QString::fromUtf8("ListaGenerica"));
        ListaGenerica->setWindowModality(Qt::WindowModal);
        ListaGenerica->resize(400, 300);
        verticalLayout = new QVBoxLayout(ListaGenerica);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        tableView = new QTableWidget(ListaGenerica);
        tableView->setObjectName(QString::fromUtf8("tableView"));

        verticalLayout->addWidget(tableView);

        buttonBox = new QDialogButtonBox(ListaGenerica);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        verticalLayout->addWidget(buttonBox);


        retranslateUi(ListaGenerica);
        QObject::connect(buttonBox, SIGNAL(accepted()), ListaGenerica, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), ListaGenerica, SLOT(reject()));

        QMetaObject::connectSlotsByName(ListaGenerica);
    } // setupUi

    void retranslateUi(QDialog *ListaGenerica)
    {
        ListaGenerica->setWindowTitle(QApplication::translate("ListaGenerica", "Dialog", 0, QApplication::UnicodeUTF8));
        Q_UNUSED(ListaGenerica);
    } // retranslateUi

};

namespace Ui {
    class ListaGenerica: public Ui_ListaGenerica {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LISTAGENERICA_H
