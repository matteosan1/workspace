/********************************************************************************
** Form generated from reading UI file 'lineup.ui'
**
** Created by: Qt User Interface Compiler version 5.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LINEUP_H
#define UI_LINEUP_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_lineup
{
public:
    QDialogButtonBox *buttonBox;
    QTabWidget *tabWidget;
    QWidget *tab;
    QComboBox *comboBoxPortiere;
    QWidget *layoutWidget;
    QHBoxLayout *horizontalLayout;
    QLabel *labelPo_2;
    QComboBox *comboBoxModulo;
    QWidget *layoutWidget1;
    QHBoxLayout *horizontalLayout_2;
    QComboBox *comboBoxAttaccanteDx;
    QSpacerItem *horizontalSpacer;
    QComboBox *comboBoxAttaccanteCx;
    QSpacerItem *horizontalSpacer_2;
    QComboBox *comboBoxAttaccanteSx;
    QWidget *layoutWidget2;
    QHBoxLayout *horizontalLayout_3;
    QComboBox *comboBoxCentrocampistaDx;
    QSpacerItem *horizontalSpacer_3;
    QComboBox *comboBoxCentrocampistaCx3;
    QSpacerItem *horizontalSpacer_4;
    QComboBox *comboBoxCentrocampistaSx;
    QWidget *layoutWidget3;
    QHBoxLayout *horizontalLayout_4;
    QComboBox *comboBoxCentrocampistaCx1;
    QSpacerItem *horizontalSpacer_5;
    QComboBox *comboBoxCentrocampistaCx2;
    QWidget *layoutWidget4;
    QHBoxLayout *horizontalLayout_5;
    QComboBox *comboBoxDifensoreDx;
    QSpacerItem *horizontalSpacer_6;
    QComboBox *comboBoxDifensoreCx3;
    QSpacerItem *horizontalSpacer_7;
    QComboBox *comboBoxDifensoreSx;
    QWidget *layoutWidget5;
    QHBoxLayout *horizontalLayout_6;
    QComboBox *comboBoxDifensoreCx1;
    QSpacerItem *horizontalSpacer_8;
    QComboBox *comboBoxDifensoreCx2;
    QWidget *tab_2;
    QLabel *labelPo_4;
    QComboBox *comboBoxPanchinari;
    QPushButton *pushButtonAggiungii;
    QListWidget *listPanchinari;
    QWidget *layoutWidget6;
    QHBoxLayout *horizontalLayout_7;
    QLabel *labelPo_3;
    QComboBox *comboBoxCapitano;

    void setupUi(QDialog *lineup)
    {
        if (lineup->objectName().isEmpty())
            lineup->setObjectName(QStringLiteral("lineup"));
        lineup->resize(682, 640);
        QSizePolicy sizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(lineup->sizePolicy().hasHeightForWidth());
        lineup->setSizePolicy(sizePolicy);
        lineup->setMaximumSize(QSize(4800, 16777215));
        buttonBox = new QDialogButtonBox(lineup);
        buttonBox->setObjectName(QStringLiteral("buttonBox"));
        buttonBox->setEnabled(false);
        buttonBox->setGeometry(QRect(360, 580, 81, 63));
        buttonBox->setOrientation(Qt::Vertical);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);
        tabWidget = new QTabWidget(lineup);
        tabWidget->setObjectName(QStringLiteral("tabWidget"));
        tabWidget->setGeometry(QRect(30, 80, 661, 600));
        sizePolicy.setHeightForWidth(tabWidget->sizePolicy().hasHeightForWidth());
        tabWidget->setSizePolicy(sizePolicy);
        tab = new QWidget();
        tab->setObjectName(QStringLiteral("tab"));
        comboBoxPortiere = new QComboBox(tab);
        comboBoxPortiere->setObjectName(QStringLiteral("comboBoxPortiere"));
        comboBoxPortiere->setEnabled(false);
        comboBoxPortiere->setGeometry(QRect(400, 30, 151, 32));
        comboBoxPortiere->setEditable(false);
        comboBoxPortiere->setFrame(false);
        layoutWidget = new QWidget(tab);
        layoutWidget->setObjectName(QStringLiteral("layoutWidget"));
        layoutWidget->setGeometry(QRect(10, 0, 201, 51));
        horizontalLayout = new QHBoxLayout(layoutWidget);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        labelPo_2 = new QLabel(layoutWidget);
        labelPo_2->setObjectName(QStringLiteral("labelPo_2"));

        horizontalLayout->addWidget(labelPo_2);

        comboBoxModulo = new QComboBox(layoutWidget);
        comboBoxModulo->setObjectName(QStringLiteral("comboBoxModulo"));

        horizontalLayout->addWidget(comboBoxModulo);

        layoutWidget1 = new QWidget(tab);
        layoutWidget1->setObjectName(QStringLiteral("layoutWidget1"));
        layoutWidget1->setGeometry(QRect(0, 400, 571, 41));
        horizontalLayout_2 = new QHBoxLayout(layoutWidget1);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        horizontalLayout_2->setContentsMargins(0, 0, 0, 0);
        comboBoxAttaccanteDx = new QComboBox(layoutWidget1);
        comboBoxAttaccanteDx->setObjectName(QStringLiteral("comboBoxAttaccanteDx"));
        comboBoxAttaccanteDx->setEnabled(false);
        comboBoxAttaccanteDx->setEditable(false);
        comboBoxAttaccanteDx->setFrame(false);

        horizontalLayout_2->addWidget(comboBoxAttaccanteDx);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer);

        comboBoxAttaccanteCx = new QComboBox(layoutWidget1);
        comboBoxAttaccanteCx->setObjectName(QStringLiteral("comboBoxAttaccanteCx"));
        comboBoxAttaccanteCx->setEnabled(false);
        comboBoxAttaccanteCx->setEditable(false);
        comboBoxAttaccanteCx->setFrame(false);

        horizontalLayout_2->addWidget(comboBoxAttaccanteCx);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_2);

        comboBoxAttaccanteSx = new QComboBox(layoutWidget1);
        comboBoxAttaccanteSx->setObjectName(QStringLiteral("comboBoxAttaccanteSx"));
        comboBoxAttaccanteSx->setEnabled(false);
        comboBoxAttaccanteSx->setEditable(false);
        comboBoxAttaccanteSx->setFrame(false);

        horizontalLayout_2->addWidget(comboBoxAttaccanteSx);

        layoutWidget2 = new QWidget(tab);
        layoutWidget2->setObjectName(QStringLiteral("layoutWidget2"));
        layoutWidget2->setGeometry(QRect(10, 310, 571, 41));
        horizontalLayout_3 = new QHBoxLayout(layoutWidget2);
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        horizontalLayout_3->setContentsMargins(0, 0, 0, 0);
        comboBoxCentrocampistaDx = new QComboBox(layoutWidget2);
        comboBoxCentrocampistaDx->setObjectName(QStringLiteral("comboBoxCentrocampistaDx"));
        comboBoxCentrocampistaDx->setEnabled(false);
        comboBoxCentrocampistaDx->setEditable(false);
        comboBoxCentrocampistaDx->setFrame(false);

        horizontalLayout_3->addWidget(comboBoxCentrocampistaDx);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_3);

        comboBoxCentrocampistaCx3 = new QComboBox(layoutWidget2);
        comboBoxCentrocampistaCx3->setObjectName(QStringLiteral("comboBoxCentrocampistaCx3"));
        comboBoxCentrocampistaCx3->setEnabled(false);
        comboBoxCentrocampistaCx3->setEditable(false);
        comboBoxCentrocampistaCx3->setFrame(false);

        horizontalLayout_3->addWidget(comboBoxCentrocampistaCx3);

        horizontalSpacer_4 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_4);

        comboBoxCentrocampistaSx = new QComboBox(layoutWidget2);
        comboBoxCentrocampistaSx->setObjectName(QStringLiteral("comboBoxCentrocampistaSx"));
        comboBoxCentrocampistaSx->setEnabled(false);
        comboBoxCentrocampistaSx->setEditable(false);
        comboBoxCentrocampistaSx->setFrame(false);

        horizontalLayout_3->addWidget(comboBoxCentrocampistaSx);

        layoutWidget3 = new QWidget(tab);
        layoutWidget3->setObjectName(QStringLiteral("layoutWidget3"));
        layoutWidget3->setGeometry(QRect(320, 235, 331, 41));
        horizontalLayout_4 = new QHBoxLayout(layoutWidget3);
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        horizontalLayout_4->setContentsMargins(0, 0, 0, 0);
        comboBoxCentrocampistaCx1 = new QComboBox(layoutWidget3);
        comboBoxCentrocampistaCx1->setObjectName(QStringLiteral("comboBoxCentrocampistaCx1"));
        comboBoxCentrocampistaCx1->setEnabled(false);
        comboBoxCentrocampistaCx1->setEditable(false);
        comboBoxCentrocampistaCx1->setFrame(false);

        horizontalLayout_4->addWidget(comboBoxCentrocampistaCx1);

        horizontalSpacer_5 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer_5);

        comboBoxCentrocampistaCx2 = new QComboBox(layoutWidget3);
        comboBoxCentrocampistaCx2->setObjectName(QStringLiteral("comboBoxCentrocampistaCx2"));
        comboBoxCentrocampistaCx2->setEnabled(false);
        comboBoxCentrocampistaCx2->setEditable(false);
        comboBoxCentrocampistaCx2->setFrame(false);

        horizontalLayout_4->addWidget(comboBoxCentrocampistaCx2);

        layoutWidget4 = new QWidget(tab);
        layoutWidget4->setObjectName(QStringLiteral("layoutWidget4"));
        layoutWidget4->setGeometry(QRect(200, 155, 571, 41));
        horizontalLayout_5 = new QHBoxLayout(layoutWidget4);
        horizontalLayout_5->setObjectName(QStringLiteral("horizontalLayout_5"));
        horizontalLayout_5->setContentsMargins(0, 0, 0, 0);
        comboBoxDifensoreDx = new QComboBox(layoutWidget4);
        comboBoxDifensoreDx->setObjectName(QStringLiteral("comboBoxDifensoreDx"));
        comboBoxDifensoreDx->setEnabled(false);
        comboBoxDifensoreDx->setEditable(false);
        comboBoxDifensoreDx->setFrame(false);

        horizontalLayout_5->addWidget(comboBoxDifensoreDx);

        horizontalSpacer_6 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_5->addItem(horizontalSpacer_6);

        comboBoxDifensoreCx3 = new QComboBox(layoutWidget4);
        comboBoxDifensoreCx3->setObjectName(QStringLiteral("comboBoxDifensoreCx3"));
        comboBoxDifensoreCx3->setEnabled(false);
        comboBoxDifensoreCx3->setEditable(false);
        comboBoxDifensoreCx3->setFrame(false);

        horizontalLayout_5->addWidget(comboBoxDifensoreCx3);

        horizontalSpacer_7 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_5->addItem(horizontalSpacer_7);

        comboBoxDifensoreSx = new QComboBox(layoutWidget4);
        comboBoxDifensoreSx->setObjectName(QStringLiteral("comboBoxDifensoreSx"));
        comboBoxDifensoreSx->setEnabled(false);
        comboBoxDifensoreSx->setEditable(false);
        comboBoxDifensoreSx->setFrame(false);

        horizontalLayout_5->addWidget(comboBoxDifensoreSx);

        layoutWidget5 = new QWidget(tab);
        layoutWidget5->setObjectName(QStringLiteral("layoutWidget5"));
        layoutWidget5->setGeometry(QRect(320, 100, 331, 41));
        horizontalLayout_6 = new QHBoxLayout(layoutWidget5);
        horizontalLayout_6->setObjectName(QStringLiteral("horizontalLayout_6"));
        horizontalLayout_6->setContentsMargins(0, 0, 0, 0);
        comboBoxDifensoreCx1 = new QComboBox(layoutWidget5);
        comboBoxDifensoreCx1->setObjectName(QStringLiteral("comboBoxDifensoreCx1"));
        comboBoxDifensoreCx1->setEnabled(false);
        comboBoxDifensoreCx1->setEditable(false);
        comboBoxDifensoreCx1->setFrame(false);

        horizontalLayout_6->addWidget(comboBoxDifensoreCx1);

        horizontalSpacer_8 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_6->addItem(horizontalSpacer_8);

        comboBoxDifensoreCx2 = new QComboBox(layoutWidget5);
        comboBoxDifensoreCx2->setObjectName(QStringLiteral("comboBoxDifensoreCx2"));
        comboBoxDifensoreCx2->setEnabled(false);
        comboBoxDifensoreCx2->setEditable(false);
        comboBoxDifensoreCx2->setFrame(false);

        horizontalLayout_6->addWidget(comboBoxDifensoreCx2);

        tabWidget->addTab(tab, QString());
        tab_2 = new QWidget();
        tab_2->setObjectName(QStringLiteral("tab_2"));
        labelPo_4 = new QLabel(tab_2);
        labelPo_4->setObjectName(QStringLiteral("labelPo_4"));
        labelPo_4->setGeometry(QRect(210, 50, 91, 20));
        comboBoxPanchinari = new QComboBox(tab_2);
        comboBoxPanchinari->setObjectName(QStringLiteral("comboBoxPanchinari"));
        comboBoxPanchinari->setGeometry(QRect(40, 100, 141, 26));
        pushButtonAggiungii = new QPushButton(tab_2);
        pushButtonAggiungii->setObjectName(QStringLiteral("pushButtonAggiungii"));
        pushButtonAggiungii->setGeometry(QRect(50, 160, 113, 32));
        listPanchinari = new QListWidget(tab_2);
        listPanchinari->setObjectName(QStringLiteral("listPanchinari"));
        listPanchinari->setGeometry(QRect(210, 70, 161, 181));
        listPanchinari->setEditTriggers(QAbstractItemView::DoubleClicked|QAbstractItemView::EditKeyPressed|QAbstractItemView::SelectedClicked);
        layoutWidget6 = new QWidget(tab_2);
        layoutWidget6->setObjectName(QStringLiteral("layoutWidget6"));
        layoutWidget6->setGeometry(QRect(10, 10, 201, 26));
        horizontalLayout_7 = new QHBoxLayout(layoutWidget6);
        horizontalLayout_7->setObjectName(QStringLiteral("horizontalLayout_7"));
        horizontalLayout_7->setContentsMargins(0, 0, 0, 0);
        labelPo_3 = new QLabel(layoutWidget6);
        labelPo_3->setObjectName(QStringLiteral("labelPo_3"));

        horizontalLayout_7->addWidget(labelPo_3);

        comboBoxCapitano = new QComboBox(layoutWidget6);
        comboBoxCapitano->setObjectName(QStringLiteral("comboBoxCapitano"));

        horizontalLayout_7->addWidget(comboBoxCapitano);

        tabWidget->addTab(tab_2, QString());

        retranslateUi(lineup);

        tabWidget->setCurrentIndex(1);


        QMetaObject::connectSlotsByName(lineup);
    } // setupUi

    void retranslateUi(QDialog *lineup)
    {
        lineup->setWindowTitle(QApplication::translate("lineup", "Inserisci formazione", 0));
        labelPo_2->setText(QApplication::translate("lineup", "Modulo", 0));
        tabWidget->setTabText(tabWidget->indexOf(tab), QApplication::translate("lineup", "Formazione", 0));
        labelPo_4->setText(QApplication::translate("lineup", "Panchina", 0));
        pushButtonAggiungii->setText(QApplication::translate("lineup", "Aggiungi", 0));
        labelPo_3->setText(QApplication::translate("lineup", "Capitano", 0));
        tabWidget->setTabText(tabWidget->indexOf(tab_2), QApplication::translate("lineup", "Panchina", 0));
    } // retranslateUi

};

namespace Ui {
    class lineup: public Ui_lineup {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LINEUP_H
