/********************************************************************************
** Form generated from reading ui file 'insertplayer.ui'
**
** Created: Sat Jan 19 02:46:41 2008
**      by: Qt User Interface Compiler version 4.3.2
**
** WARNING! All changes made in this file will be lost when recompiling ui file!
********************************************************************************/

#ifndef UI_INSERTPLAYER_H
#define UI_INSERTPLAYER_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QDialogButtonBox>
#include <QtGui/QTableView>
#include <QtGui/QVBoxLayout>

class Ui_InsertPlayer
{
public:
    QVBoxLayout *vboxLayout;
    QTableView *tableView;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *InsertPlayer)
    {
    if (InsertPlayer->objectName().isEmpty())
        InsertPlayer->setObjectName(QString::fromUtf8("InsertPlayer"));
    InsertPlayer->resize(400, 300);
    vboxLayout = new QVBoxLayout(InsertPlayer);
    vboxLayout->setObjectName(QString::fromUtf8("vboxLayout"));
    tableView = new QTableView(InsertPlayer);
    tableView->setObjectName(QString::fromUtf8("tableView"));

    vboxLayout->addWidget(tableView);

    buttonBox = new QDialogButtonBox(InsertPlayer);
    buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
    buttonBox->setOrientation(Qt::Horizontal);
    buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::NoButton|QDialogButtonBox::Ok);

    vboxLayout->addWidget(buttonBox);


    retranslateUi(InsertPlayer);
    QObject::connect(buttonBox, SIGNAL(accepted()), InsertPlayer, SLOT(accept()));
    QObject::connect(buttonBox, SIGNAL(rejected()), InsertPlayer, SLOT(reject()));

    QMetaObject::connectSlotsByName(InsertPlayer);
    } // setupUi

    void retranslateUi(QDialog *InsertPlayer)
    {
    InsertPlayer->setWindowTitle(QApplication::translate("InsertPlayer", "Insert Players", 0, QApplication::UnicodeUTF8));
    Q_UNUSED(InsertPlayer);
    } // retranslateUi

};

namespace Ui {
    class InsertPlayer: public Ui_InsertPlayer {};
} // namespace Ui

#endif // UI_INSERTPLAYER_H
