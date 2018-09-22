/********************************************************************************
** Form generated from reading UI file 'regolamentodialog.ui'
**
** Created by: Qt User Interface Compiler version 4.8.7
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_REGOLAMENTODIALOG_H
#define UI_REGOLAMENTODIALOG_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QCheckBox>
#include <QtGui/QDialog>
#include <QtGui/QDialogButtonBox>
#include <QtGui/QGridLayout>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QPushButton>
#include <QtGui/QSpacerItem>
#include <QtGui/QSpinBox>
#include <QtGui/QTabWidget>
#include <QtGui/QTableView>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_RegolamentoDialog
{
public:
    QVBoxLayout *vboxLayout;
    QTabWidget *tabGiocatori;
    QWidget *tab_6;
    QVBoxLayout *vboxLayout1;
    QVBoxLayout *vboxLayout2;
    QHBoxLayout *hboxLayout;
    QTableView *tableView;
    QVBoxLayout *vboxLayout3;
    QPushButton *pushButton;
    QPushButton *pushButton_2;
    QSpacerItem *spacerItem;
    QWidget *tab_4;
    QWidget *layoutWidget;
    QHBoxLayout *hboxLayout1;
    QVBoxLayout *vboxLayout4;
    QLabel *label_11;
    QLabel *label_12;
    QLabel *label_13;
    QLabel *label_14;
    QLabel *label_15;
    QLabel *label_16;
    QLabel *label_10;
    QLabel *label_24;
    QLabel *label_25;
    QLabel *label_26;
    QVBoxLayout *vboxLayout5;
    QSpinBox *spinBox_7;
    QSpinBox *spinBox_8;
    QSpinBox *spinBox_9;
    QSpinBox *spinBox_10;
    QSpinBox *spinBox_11;
    QSpinBox *spinBox_12;
    QSpinBox *spinBox_20;
    QSpinBox *spinBox_21;
    QSpinBox *spinBox_22;
    QSpinBox *spinBox_6;
    QWidget *tab;
    QLabel *label_27;
    QWidget *layoutWidget1;
    QVBoxLayout *vboxLayout6;
    QCheckBox *checkBox_10;
    QCheckBox *checkBox_2;
    QCheckBox *checkBox_3;
    QCheckBox *checkBox_4;
    QCheckBox *checkBox_5;
    QCheckBox *checkBox_6;
    QCheckBox *checkBox_7;
    QCheckBox *checkBox_11;
    QCheckBox *checkBox_8;
    QWidget *tab_5;
    QWidget *layoutWidget2;
    QVBoxLayout *vboxLayout7;
    QCheckBox *checkBox_9;
    QCheckBox *checkBox_13;
    QCheckBox *checkBox_12;
    QWidget *layoutWidget3;
    QGridLayout *gridLayout;
    QLabel *label_23;
    QSpinBox *spinBox_19;
    QLabel *label_17;
    QSpinBox *spinBox_13;
    QLabel *label_18;
    QSpinBox *spinBox_14;
    QLabel *label_19;
    QSpinBox *spinBox_15;
    QLabel *label_20;
    QSpinBox *spinBox_16;
    QLabel *label_21;
    QSpinBox *spinBox_17;
    QLabel *label_22;
    QSpinBox *spinBox_18;
    QLabel *label_28;
    QSpinBox *spinBox_23;
    QLabel *label_29;
    QSpinBox *spinBox_24;
    QWidget *tab_2;
    QSpinBox *spinBox_5;
    QLabel *label_5;
    QLabel *label_6;
    QLabel *label_7;
    QLabel *label_8;
    QLabel *label_9;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *RegolamentoDialog)
    {
        if (RegolamentoDialog->objectName().isEmpty())
            RegolamentoDialog->setObjectName(QString::fromUtf8("RegolamentoDialog"));
        RegolamentoDialog->resize(624, 455);
        vboxLayout = new QVBoxLayout(RegolamentoDialog);
        vboxLayout->setObjectName(QString::fromUtf8("vboxLayout"));
        tabGiocatori = new QTabWidget(RegolamentoDialog);
        tabGiocatori->setObjectName(QString::fromUtf8("tabGiocatori"));
        tab_6 = new QWidget();
        tab_6->setObjectName(QString::fromUtf8("tab_6"));
        vboxLayout1 = new QVBoxLayout(tab_6);
        vboxLayout1->setObjectName(QString::fromUtf8("vboxLayout1"));
        vboxLayout2 = new QVBoxLayout();
        vboxLayout2->setObjectName(QString::fromUtf8("vboxLayout2"));
        hboxLayout = new QHBoxLayout();
        hboxLayout->setObjectName(QString::fromUtf8("hboxLayout"));
        tableView = new QTableView(tab_6);
        tableView->setObjectName(QString::fromUtf8("tableView"));
        tableView->setEditTriggers(QAbstractItemView::AnyKeyPressed);
        tableView->setCornerButtonEnabled(false);

        hboxLayout->addWidget(tableView);

        vboxLayout3 = new QVBoxLayout();
        vboxLayout3->setObjectName(QString::fromUtf8("vboxLayout3"));
        pushButton = new QPushButton(tab_6);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));

        vboxLayout3->addWidget(pushButton);

        pushButton_2 = new QPushButton(tab_6);
        pushButton_2->setObjectName(QString::fromUtf8("pushButton_2"));

        vboxLayout3->addWidget(pushButton_2);

        spacerItem = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        vboxLayout3->addItem(spacerItem);


        hboxLayout->addLayout(vboxLayout3);


        vboxLayout2->addLayout(hboxLayout);


        vboxLayout1->addLayout(vboxLayout2);

        tabGiocatori->addTab(tab_6, QString());
        tab_4 = new QWidget();
        tab_4->setObjectName(QString::fromUtf8("tab_4"));
        layoutWidget = new QWidget(tab_4);
        layoutWidget->setObjectName(QString::fromUtf8("layoutWidget"));
        layoutWidget->setGeometry(QRect(130, 30, 171, 297));
        hboxLayout1 = new QHBoxLayout(layoutWidget);
        hboxLayout1->setObjectName(QString::fromUtf8("hboxLayout1"));
        hboxLayout1->setContentsMargins(0, 0, 0, 0);
        vboxLayout4 = new QVBoxLayout();
        vboxLayout4->setObjectName(QString::fromUtf8("vboxLayout4"));
        label_11 = new QLabel(layoutWidget);
        label_11->setObjectName(QString::fromUtf8("label_11"));

        vboxLayout4->addWidget(label_11);

        label_12 = new QLabel(layoutWidget);
        label_12->setObjectName(QString::fromUtf8("label_12"));

        vboxLayout4->addWidget(label_12);

        label_13 = new QLabel(layoutWidget);
        label_13->setObjectName(QString::fromUtf8("label_13"));

        vboxLayout4->addWidget(label_13);

        label_14 = new QLabel(layoutWidget);
        label_14->setObjectName(QString::fromUtf8("label_14"));

        vboxLayout4->addWidget(label_14);

        label_15 = new QLabel(layoutWidget);
        label_15->setObjectName(QString::fromUtf8("label_15"));

        vboxLayout4->addWidget(label_15);

        label_16 = new QLabel(layoutWidget);
        label_16->setObjectName(QString::fromUtf8("label_16"));

        vboxLayout4->addWidget(label_16);

        label_10 = new QLabel(layoutWidget);
        label_10->setObjectName(QString::fromUtf8("label_10"));

        vboxLayout4->addWidget(label_10);

        label_24 = new QLabel(layoutWidget);
        label_24->setObjectName(QString::fromUtf8("label_24"));

        vboxLayout4->addWidget(label_24);

        label_25 = new QLabel(layoutWidget);
        label_25->setObjectName(QString::fromUtf8("label_25"));

        vboxLayout4->addWidget(label_25);

        label_26 = new QLabel(layoutWidget);
        label_26->setObjectName(QString::fromUtf8("label_26"));

        vboxLayout4->addWidget(label_26);


        hboxLayout1->addLayout(vboxLayout4);

        vboxLayout5 = new QVBoxLayout();
        vboxLayout5->setObjectName(QString::fromUtf8("vboxLayout5"));
        spinBox_7 = new QSpinBox(layoutWidget);
        spinBox_7->setObjectName(QString::fromUtf8("spinBox_7"));
        spinBox_7->setValue(66);

        vboxLayout5->addWidget(spinBox_7);

        spinBox_8 = new QSpinBox(layoutWidget);
        spinBox_8->setObjectName(QString::fromUtf8("spinBox_8"));
        spinBox_8->setValue(72);

        vboxLayout5->addWidget(spinBox_8);

        spinBox_9 = new QSpinBox(layoutWidget);
        spinBox_9->setObjectName(QString::fromUtf8("spinBox_9"));
        spinBox_9->setValue(78);

        vboxLayout5->addWidget(spinBox_9);

        spinBox_10 = new QSpinBox(layoutWidget);
        spinBox_10->setObjectName(QString::fromUtf8("spinBox_10"));
        spinBox_10->setValue(84);

        vboxLayout5->addWidget(spinBox_10);

        spinBox_11 = new QSpinBox(layoutWidget);
        spinBox_11->setObjectName(QString::fromUtf8("spinBox_11"));
        spinBox_11->setValue(90);

        vboxLayout5->addWidget(spinBox_11);

        spinBox_12 = new QSpinBox(layoutWidget);
        spinBox_12->setObjectName(QString::fromUtf8("spinBox_12"));
        spinBox_12->setValue(96);

        vboxLayout5->addWidget(spinBox_12);

        spinBox_20 = new QSpinBox(layoutWidget);
        spinBox_20->setObjectName(QString::fromUtf8("spinBox_20"));
        spinBox_20->setMaximum(120);
        spinBox_20->setValue(102);

        vboxLayout5->addWidget(spinBox_20);

        spinBox_21 = new QSpinBox(layoutWidget);
        spinBox_21->setObjectName(QString::fromUtf8("spinBox_21"));
        spinBox_21->setMaximum(120);
        spinBox_21->setValue(108);

        vboxLayout5->addWidget(spinBox_21);

        spinBox_22 = new QSpinBox(layoutWidget);
        spinBox_22->setObjectName(QString::fromUtf8("spinBox_22"));
        spinBox_22->setMaximum(120);
        spinBox_22->setValue(114);

        vboxLayout5->addWidget(spinBox_22);

        spinBox_6 = new QSpinBox(layoutWidget);
        spinBox_6->setObjectName(QString::fromUtf8("spinBox_6"));
        spinBox_6->setMaximum(130);
        spinBox_6->setValue(120);

        vboxLayout5->addWidget(spinBox_6);


        hboxLayout1->addLayout(vboxLayout5);

        tabGiocatori->addTab(tab_4, QString());
        tab = new QWidget();
        tab->setObjectName(QString::fromUtf8("tab"));
        label_27 = new QLabel(tab);
        label_27->setObjectName(QString::fromUtf8("label_27"));
        label_27->setGeometry(QRect(40, 150, 159, 18));
        layoutWidget1 = new QWidget(tab);
        layoutWidget1->setObjectName(QString::fromUtf8("layoutWidget1"));
        layoutWidget1->setGeometry(QRect(240, 40, 111, 281));
        vboxLayout6 = new QVBoxLayout(layoutWidget1);
        vboxLayout6->setObjectName(QString::fromUtf8("vboxLayout6"));
        vboxLayout6->setContentsMargins(0, 0, 0, 0);
        checkBox_10 = new QCheckBox(layoutWidget1);
        checkBox_10->setObjectName(QString::fromUtf8("checkBox_10"));

        vboxLayout6->addWidget(checkBox_10);

        checkBox_2 = new QCheckBox(layoutWidget1);
        checkBox_2->setObjectName(QString::fromUtf8("checkBox_2"));

        vboxLayout6->addWidget(checkBox_2);

        checkBox_3 = new QCheckBox(layoutWidget1);
        checkBox_3->setObjectName(QString::fromUtf8("checkBox_3"));

        vboxLayout6->addWidget(checkBox_3);

        checkBox_4 = new QCheckBox(layoutWidget1);
        checkBox_4->setObjectName(QString::fromUtf8("checkBox_4"));

        vboxLayout6->addWidget(checkBox_4);

        checkBox_5 = new QCheckBox(layoutWidget1);
        checkBox_5->setObjectName(QString::fromUtf8("checkBox_5"));

        vboxLayout6->addWidget(checkBox_5);

        checkBox_6 = new QCheckBox(layoutWidget1);
        checkBox_6->setObjectName(QString::fromUtf8("checkBox_6"));

        vboxLayout6->addWidget(checkBox_6);

        checkBox_7 = new QCheckBox(layoutWidget1);
        checkBox_7->setObjectName(QString::fromUtf8("checkBox_7"));

        vboxLayout6->addWidget(checkBox_7);

        checkBox_11 = new QCheckBox(layoutWidget1);
        checkBox_11->setObjectName(QString::fromUtf8("checkBox_11"));

        vboxLayout6->addWidget(checkBox_11);

        checkBox_8 = new QCheckBox(layoutWidget1);
        checkBox_8->setObjectName(QString::fromUtf8("checkBox_8"));

        vboxLayout6->addWidget(checkBox_8);

        tabGiocatori->addTab(tab, QString());
        tab_5 = new QWidget();
        tab_5->setObjectName(QString::fromUtf8("tab_5"));
        layoutWidget2 = new QWidget(tab_5);
        layoutWidget2->setObjectName(QString::fromUtf8("layoutWidget2"));
        layoutWidget2->setGeometry(QRect(290, 50, 191, 72));
        vboxLayout7 = new QVBoxLayout(layoutWidget2);
        vboxLayout7->setObjectName(QString::fromUtf8("vboxLayout7"));
        vboxLayout7->setContentsMargins(0, 0, 0, 0);
        checkBox_9 = new QCheckBox(layoutWidget2);
        checkBox_9->setObjectName(QString::fromUtf8("checkBox_9"));

        vboxLayout7->addWidget(checkBox_9);

        checkBox_13 = new QCheckBox(layoutWidget2);
        checkBox_13->setObjectName(QString::fromUtf8("checkBox_13"));

        vboxLayout7->addWidget(checkBox_13);

        checkBox_12 = new QCheckBox(layoutWidget2);
        checkBox_12->setObjectName(QString::fromUtf8("checkBox_12"));

        vboxLayout7->addWidget(checkBox_12);

        layoutWidget3 = new QWidget(tab_5);
        layoutWidget3->setObjectName(QString::fromUtf8("layoutWidget3"));
        layoutWidget3->setGeometry(QRect(30, 20, 211, 331));
        gridLayout = new QGridLayout(layoutWidget3);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        gridLayout->setContentsMargins(0, 0, 0, 0);
        label_23 = new QLabel(layoutWidget3);
        label_23->setObjectName(QString::fromUtf8("label_23"));

        gridLayout->addWidget(label_23, 0, 0, 1, 1);

        spinBox_19 = new QSpinBox(layoutWidget3);
        spinBox_19->setObjectName(QString::fromUtf8("spinBox_19"));
        spinBox_19->setMinimum(-10);
        spinBox_19->setValue(-1);

        gridLayout->addWidget(spinBox_19, 0, 1, 1, 1);

        label_17 = new QLabel(layoutWidget3);
        label_17->setObjectName(QString::fromUtf8("label_17"));

        gridLayout->addWidget(label_17, 1, 0, 1, 1);

        spinBox_13 = new QSpinBox(layoutWidget3);
        spinBox_13->setObjectName(QString::fromUtf8("spinBox_13"));
        spinBox_13->setValue(3);

        gridLayout->addWidget(spinBox_13, 1, 1, 1, 1);

        label_18 = new QLabel(layoutWidget3);
        label_18->setObjectName(QString::fromUtf8("label_18"));

        gridLayout->addWidget(label_18, 2, 0, 1, 1);

        spinBox_14 = new QSpinBox(layoutWidget3);
        spinBox_14->setObjectName(QString::fromUtf8("spinBox_14"));
        spinBox_14->setMinimum(-10);
        spinBox_14->setValue(-3);

        gridLayout->addWidget(spinBox_14, 2, 1, 1, 1);

        label_19 = new QLabel(layoutWidget3);
        label_19->setObjectName(QString::fromUtf8("label_19"));

        gridLayout->addWidget(label_19, 3, 0, 1, 1);

        spinBox_15 = new QSpinBox(layoutWidget3);
        spinBox_15->setObjectName(QString::fromUtf8("spinBox_15"));
        spinBox_15->setValue(3);

        gridLayout->addWidget(spinBox_15, 3, 1, 1, 1);

        label_20 = new QLabel(layoutWidget3);
        label_20->setObjectName(QString::fromUtf8("label_20"));

        gridLayout->addWidget(label_20, 4, 0, 1, 1);

        spinBox_16 = new QSpinBox(layoutWidget3);
        spinBox_16->setObjectName(QString::fromUtf8("spinBox_16"));
        spinBox_16->setValue(1);

        gridLayout->addWidget(spinBox_16, 4, 1, 1, 1);

        label_21 = new QLabel(layoutWidget3);
        label_21->setObjectName(QString::fromUtf8("label_21"));

        gridLayout->addWidget(label_21, 5, 0, 1, 1);

        spinBox_17 = new QSpinBox(layoutWidget3);
        spinBox_17->setObjectName(QString::fromUtf8("spinBox_17"));
        spinBox_17->setMinimum(-10);
        spinBox_17->setSingleStep(1);
        spinBox_17->setValue(-1);

        gridLayout->addWidget(spinBox_17, 5, 1, 1, 1);

        label_22 = new QLabel(layoutWidget3);
        label_22->setObjectName(QString::fromUtf8("label_22"));

        gridLayout->addWidget(label_22, 6, 0, 1, 1);

        spinBox_18 = new QSpinBox(layoutWidget3);
        spinBox_18->setObjectName(QString::fromUtf8("spinBox_18"));
        spinBox_18->setMinimum(-10);
        spinBox_18->setValue(-1);

        gridLayout->addWidget(spinBox_18, 6, 1, 1, 1);

        label_28 = new QLabel(layoutWidget3);
        label_28->setObjectName(QString::fromUtf8("label_28"));

        gridLayout->addWidget(label_28, 7, 0, 1, 1);

        spinBox_23 = new QSpinBox(layoutWidget3);
        spinBox_23->setObjectName(QString::fromUtf8("spinBox_23"));
        spinBox_23->setValue(3);

        gridLayout->addWidget(spinBox_23, 7, 1, 1, 1);

        label_29 = new QLabel(layoutWidget3);
        label_29->setObjectName(QString::fromUtf8("label_29"));

        gridLayout->addWidget(label_29, 8, 0, 1, 1);

        spinBox_24 = new QSpinBox(layoutWidget3);
        spinBox_24->setObjectName(QString::fromUtf8("spinBox_24"));
        spinBox_24->setMinimum(-10);
        spinBox_24->setValue(-2);

        gridLayout->addWidget(spinBox_24, 8, 1, 1, 1);

        tabGiocatori->addTab(tab_5, QString());
        tab_2 = new QWidget();
        tab_2->setObjectName(QString::fromUtf8("tab_2"));
        spinBox_5 = new QSpinBox(tab_2);
        spinBox_5->setObjectName(QString::fromUtf8("spinBox_5"));
        spinBox_5->setGeometry(QRect(130, 30, 50, 23));
        label_5 = new QLabel(tab_2);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        label_5->setGeometry(QRect(10, 30, 107, 18));
        label_6 = new QLabel(tab_2);
        label_6->setObjectName(QString::fromUtf8("label_6"));
        label_6->setGeometry(QRect(10, 90, 56, 18));
        label_7 = new QLabel(tab_2);
        label_7->setObjectName(QString::fromUtf8("label_7"));
        label_7->setGeometry(QRect(10, 120, 56, 18));
        label_8 = new QLabel(tab_2);
        label_8->setObjectName(QString::fromUtf8("label_8"));
        label_8->setGeometry(QRect(10, 150, 56, 18));
        label_9 = new QLabel(tab_2);
        label_9->setObjectName(QString::fromUtf8("label_9"));
        label_9->setGeometry(QRect(10, 190, 56, 18));
        tabGiocatori->addTab(tab_2, QString());

        vboxLayout->addWidget(tabGiocatori);

        buttonBox = new QDialogButtonBox(RegolamentoDialog);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::NoButton|QDialogButtonBox::Ok);

        vboxLayout->addWidget(buttonBox);


        retranslateUi(RegolamentoDialog);
        QObject::connect(buttonBox, SIGNAL(accepted()), RegolamentoDialog, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), RegolamentoDialog, SLOT(reject()));

        tabGiocatori->setCurrentIndex(2);


        QMetaObject::connectSlotsByName(RegolamentoDialog);
    } // setupUi

    void retranslateUi(QDialog *RegolamentoDialog)
    {
        RegolamentoDialog->setWindowTitle(QApplication::translate("RegolamentoDialog", "Regolamento", 0, QApplication::UnicodeUTF8));
        pushButton->setText(QApplication::translate("RegolamentoDialog", "Nuovo", 0, QApplication::UnicodeUTF8));
        pushButton_2->setText(QApplication::translate("RegolamentoDialog", "Rimuovi", 0, QApplication::UnicodeUTF8));
        tabGiocatori->setTabText(tabGiocatori->indexOf(tab_6), QApplication::translate("RegolamentoDialog", "Giocatori", 0, QApplication::UnicodeUTF8));
        label_11->setText(QApplication::translate("RegolamentoDialog", "1 Goal", 0, QApplication::UnicodeUTF8));
        label_12->setText(QApplication::translate("RegolamentoDialog", "2 Goal", 0, QApplication::UnicodeUTF8));
        label_13->setText(QApplication::translate("RegolamentoDialog", "3 Goal", 0, QApplication::UnicodeUTF8));
        label_14->setText(QApplication::translate("RegolamentoDialog", "4 Goal", 0, QApplication::UnicodeUTF8));
        label_15->setText(QApplication::translate("RegolamentoDialog", "5 Goal", 0, QApplication::UnicodeUTF8));
        label_16->setText(QApplication::translate("RegolamentoDialog", "6 Goal", 0, QApplication::UnicodeUTF8));
        label_10->setText(QApplication::translate("RegolamentoDialog", "7 Goal", 0, QApplication::UnicodeUTF8));
        label_24->setText(QApplication::translate("RegolamentoDialog", "8 Goal", 0, QApplication::UnicodeUTF8));
        label_25->setText(QApplication::translate("RegolamentoDialog", "9 Goal", 0, QApplication::UnicodeUTF8));
        label_26->setText(QApplication::translate("RegolamentoDialog", "10 Goal", 0, QApplication::UnicodeUTF8));
        tabGiocatori->setTabText(tabGiocatori->indexOf(tab_4), QApplication::translate("RegolamentoDialog", "Punteggi", 0, QApplication::UnicodeUTF8));
        label_27->setText(QApplication::translate("RegolamentoDialog", "Schemi di gioco consentiti", 0, QApplication::UnicodeUTF8));
        checkBox_10->setText(QApplication::translate("RegolamentoDialog", "6-3-1", 0, QApplication::UnicodeUTF8));
        checkBox_2->setText(QApplication::translate("RegolamentoDialog", "5-4-1", 0, QApplication::UnicodeUTF8));
        checkBox_3->setText(QApplication::translate("RegolamentoDialog", "5-3-2", 0, QApplication::UnicodeUTF8));
        checkBox_4->setText(QApplication::translate("RegolamentoDialog", "4-5-1", 0, QApplication::UnicodeUTF8));
        checkBox_5->setText(QApplication::translate("RegolamentoDialog", "4-4-2", 0, QApplication::UnicodeUTF8));
        checkBox_6->setText(QApplication::translate("RegolamentoDialog", "4-3-3", 0, QApplication::UnicodeUTF8));
        checkBox_7->setText(QApplication::translate("RegolamentoDialog", "3-6-1", 0, QApplication::UnicodeUTF8));
        checkBox_11->setText(QApplication::translate("RegolamentoDialog", "3-5-2", 0, QApplication::UnicodeUTF8));
        checkBox_8->setText(QApplication::translate("RegolamentoDialog", "3-4-3", 0, QApplication::UnicodeUTF8));
        tabGiocatori->setTabText(tabGiocatori->indexOf(tab), QApplication::translate("RegolamentoDialog", "Schemi", 0, QApplication::UnicodeUTF8));
        checkBox_9->setText(QApplication::translate("RegolamentoDialog", "6 politico a s.v.", 0, QApplication::UnicodeUTF8));
        checkBox_13->setText(QApplication::translate("RegolamentoDialog", "sost. \"automatica\" portiere", 0, QApplication::UnicodeUTF8));
        checkBox_12->setText(QApplication::translate("RegolamentoDialog", "Portiere s.v. = 6", 0, QApplication::UnicodeUTF8));
        label_23->setText(QApplication::translate("RegolamentoDialog", "Goal Subito", 0, QApplication::UnicodeUTF8));
        label_17->setText(QApplication::translate("RegolamentoDialog", "Rigore Parato", 0, QApplication::UnicodeUTF8));
        label_18->setText(QApplication::translate("RegolamentoDialog", "Rigore Sbagliato", 0, QApplication::UnicodeUTF8));
        label_19->setText(QApplication::translate("RegolamentoDialog", "Goal Segnato", 0, QApplication::UnicodeUTF8));
        label_20->setText(QApplication::translate("RegolamentoDialog", "Assist", 0, QApplication::UnicodeUTF8));
        label_21->setText(QApplication::translate("RegolamentoDialog", "Ammonizione", 0, QApplication::UnicodeUTF8));
        spinBox_17->setSuffix(QApplication::translate("RegolamentoDialog", " * 0.5", 0, QApplication::UnicodeUTF8));
        label_22->setText(QApplication::translate("RegolamentoDialog", "Espulsione", 0, QApplication::UnicodeUTF8));
        label_28->setText(QApplication::translate("RegolamentoDialog", "Rigore Segnato", 0, QApplication::UnicodeUTF8));
        label_29->setText(QApplication::translate("RegolamentoDialog", "Autogoal", 0, QApplication::UnicodeUTF8));
        tabGiocatori->setTabText(tabGiocatori->indexOf(tab_5), QApplication::translate("RegolamentoDialog", "Punteggi Giocatori", 0, QApplication::UnicodeUTF8));
        label_5->setText(QApplication::translate("RegolamentoDialog", "Fattore campo", 0, QApplication::UnicodeUTF8));
        label_6->setText(QApplication::translate("RegolamentoDialog", "TextLabel", 0, QApplication::UnicodeUTF8));
        label_7->setText(QApplication::translate("RegolamentoDialog", "TextLabel", 0, QApplication::UnicodeUTF8));
        label_8->setText(QApplication::translate("RegolamentoDialog", "TextLabel", 0, QApplication::UnicodeUTF8));
        label_9->setText(QApplication::translate("RegolamentoDialog", "TextLabel", 0, QApplication::UnicodeUTF8));
        tabGiocatori->setTabText(tabGiocatori->indexOf(tab_2), QApplication::translate("RegolamentoDialog", "Vantaggi", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class RegolamentoDialog: public Ui_RegolamentoDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_REGOLAMENTODIALOG_H
