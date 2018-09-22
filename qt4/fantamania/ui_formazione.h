/********************************************************************************
** Form generated from reading UI file 'formazione.ui'
**
** Created by: Qt User Interface Compiler version 4.8.7
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FORMAZIONE_H
#define UI_FORMAZIONE_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QComboBox>
#include <QtGui/QDialog>
#include <QtGui/QDialogButtonBox>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QTextEdit>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Formazione
{
public:
    QDialogButtonBox *buttonBox;
    QTextEdit *textFormazione;
    QComboBox *comboPortieri;
    QComboBox *comboDifensori;
    QComboBox *comboCentrocampisti;
    QComboBox *comboAttaccanti;
    QLabel *labelDi;
    QLabel *labelCe;
    QLabel *labelAt;
    QLabel *labelPo;
    QWidget *layoutWidget;
    QVBoxLayout *vboxLayout;
    QLabel *label_5;
    QComboBox *giornataCombo;
    QComboBox *comboBoxModulo;
    QComboBox *comboBoxPortiere;
    QComboBox *comboBoxDifensoreDx;
    QComboBox *comboBoxDifensoreCx1;
    QComboBox *comboBoxDifensoreCx2;
    QComboBox *comboBoxDifensoreCx3;
    QComboBox *comboBoxDifensoreSx;
    QComboBox *comboBoxCentrocampistaSx;
    QComboBox *comboBoxCentrocampistaCx3;
    QComboBox *comboBoxCentrocampistaDx;
    QComboBox *comboBoxCentrocampistaCx2;
    QComboBox *comboBoxCentrocampistaCx1;
    QComboBox *comboBoxAttaccanteCx;
    QComboBox *comboBoxAttaccanteDx;
    QComboBox *comboBoxAttaccanteSx;

    void setupUi(QDialog *Formazione)
    {
        if (Formazione->objectName().isEmpty())
            Formazione->setObjectName(QString::fromUtf8("Formazione"));
        Formazione->resize(782, 597);
        buttonBox = new QDialogButtonBox(Formazione);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        buttonBox->setEnabled(false);
        buttonBox->setGeometry(QRect(430, 198, 81, 63));
        buttonBox->setOrientation(Qt::Vertical);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);
        textFormazione = new QTextEdit(Formazione);
        textFormazione->setObjectName(QString::fromUtf8("textFormazione"));
        textFormazione->setGeometry(QRect(20, 30, 171, 241));
        comboPortieri = new QComboBox(Formazione);
        comboPortieri->setObjectName(QString::fromUtf8("comboPortieri"));
        comboPortieri->setGeometry(QRect(230, 50, 121, 22));
        comboDifensori = new QComboBox(Formazione);
        comboDifensori->setObjectName(QString::fromUtf8("comboDifensori"));
        comboDifensori->setGeometry(QRect(230, 100, 121, 22));
        comboCentrocampisti = new QComboBox(Formazione);
        comboCentrocampisti->setObjectName(QString::fromUtf8("comboCentrocampisti"));
        comboCentrocampisti->setGeometry(QRect(230, 150, 121, 22));
        comboAttaccanti = new QComboBox(Formazione);
        comboAttaccanti->setObjectName(QString::fromUtf8("comboAttaccanti"));
        comboAttaccanti->setGeometry(QRect(230, 200, 121, 22));
        labelDi = new QLabel(Formazione);
        labelDi->setObjectName(QString::fromUtf8("labelDi"));
        labelDi->setGeometry(QRect(230, 80, 101, 18));
        labelCe = new QLabel(Formazione);
        labelCe->setObjectName(QString::fromUtf8("labelCe"));
        labelCe->setGeometry(QRect(230, 130, 121, 18));
        labelAt = new QLabel(Formazione);
        labelAt->setObjectName(QString::fromUtf8("labelAt"));
        labelAt->setGeometry(QRect(230, 180, 111, 18));
        labelPo = new QLabel(Formazione);
        labelPo->setObjectName(QString::fromUtf8("labelPo"));
        labelPo->setGeometry(QRect(230, 30, 91, 18));
        layoutWidget = new QWidget(Formazione);
        layoutWidget->setObjectName(QString::fromUtf8("layoutWidget"));
        layoutWidget->setGeometry(QRect(410, 30, 115, 58));
        vboxLayout = new QVBoxLayout(layoutWidget);
        vboxLayout->setObjectName(QString::fromUtf8("vboxLayout"));
        vboxLayout->setContentsMargins(0, 0, 0, 0);
        label_5 = new QLabel(layoutWidget);
        label_5->setObjectName(QString::fromUtf8("label_5"));

        vboxLayout->addWidget(label_5);

        giornataCombo = new QComboBox(layoutWidget);
        giornataCombo->setObjectName(QString::fromUtf8("giornataCombo"));
        giornataCombo->setEnabled(false);

        vboxLayout->addWidget(giornataCombo);

        comboBoxModulo = new QComboBox(Formazione);
        comboBoxModulo->setObjectName(QString::fromUtf8("comboBoxModulo"));
        comboBoxModulo->setGeometry(QRect(30, 300, 121, 32));
        comboBoxPortiere = new QComboBox(Formazione);
        comboBoxPortiere->setObjectName(QString::fromUtf8("comboBoxPortiere"));
        comboBoxPortiere->setEnabled(false);
        comboBoxPortiere->setGeometry(QRect(230, 300, 121, 32));
        comboBoxPortiere->setEditable(false);
        comboBoxPortiere->setFrame(false);
        comboBoxDifensoreDx = new QComboBox(Formazione);
        comboBoxDifensoreDx->setObjectName(QString::fromUtf8("comboBoxDifensoreDx"));
        comboBoxDifensoreDx->setEnabled(false);
        comboBoxDifensoreDx->setGeometry(QRect(80, 390, 121, 32));
        comboBoxDifensoreDx->setEditable(false);
        comboBoxDifensoreDx->setFrame(false);
        comboBoxDifensoreCx1 = new QComboBox(Formazione);
        comboBoxDifensoreCx1->setObjectName(QString::fromUtf8("comboBoxDifensoreCx1"));
        comboBoxDifensoreCx1->setEnabled(false);
        comboBoxDifensoreCx1->setGeometry(QRect(160, 350, 121, 32));
        comboBoxDifensoreCx1->setEditable(false);
        comboBoxDifensoreCx1->setFrame(false);
        comboBoxDifensoreCx2 = new QComboBox(Formazione);
        comboBoxDifensoreCx2->setObjectName(QString::fromUtf8("comboBoxDifensoreCx2"));
        comboBoxDifensoreCx2->setEnabled(false);
        comboBoxDifensoreCx2->setGeometry(QRect(290, 350, 121, 32));
        comboBoxDifensoreCx2->setEditable(false);
        comboBoxDifensoreCx2->setFrame(false);
        comboBoxDifensoreCx3 = new QComboBox(Formazione);
        comboBoxDifensoreCx3->setObjectName(QString::fromUtf8("comboBoxDifensoreCx3"));
        comboBoxDifensoreCx3->setEnabled(false);
        comboBoxDifensoreCx3->setGeometry(QRect(230, 390, 121, 32));
        comboBoxDifensoreCx3->setEditable(false);
        comboBoxDifensoreCx3->setFrame(false);
        comboBoxDifensoreSx = new QComboBox(Formazione);
        comboBoxDifensoreSx->setObjectName(QString::fromUtf8("comboBoxDifensoreSx"));
        comboBoxDifensoreSx->setEnabled(false);
        comboBoxDifensoreSx->setGeometry(QRect(380, 390, 121, 32));
        comboBoxDifensoreSx->setEditable(false);
        comboBoxDifensoreSx->setFrame(false);
        comboBoxCentrocampistaSx = new QComboBox(Formazione);
        comboBoxCentrocampistaSx->setObjectName(QString::fromUtf8("comboBoxCentrocampistaSx"));
        comboBoxCentrocampistaSx->setEnabled(false);
        comboBoxCentrocampistaSx->setGeometry(QRect(380, 470, 121, 32));
        comboBoxCentrocampistaSx->setEditable(false);
        comboBoxCentrocampistaSx->setFrame(false);
        comboBoxCentrocampistaCx3 = new QComboBox(Formazione);
        comboBoxCentrocampistaCx3->setObjectName(QString::fromUtf8("comboBoxCentrocampistaCx3"));
        comboBoxCentrocampistaCx3->setEnabled(false);
        comboBoxCentrocampistaCx3->setGeometry(QRect(230, 470, 121, 32));
        comboBoxCentrocampistaCx3->setEditable(false);
        comboBoxCentrocampistaCx3->setFrame(false);
        comboBoxCentrocampistaDx = new QComboBox(Formazione);
        comboBoxCentrocampistaDx->setObjectName(QString::fromUtf8("comboBoxCentrocampistaDx"));
        comboBoxCentrocampistaDx->setEnabled(false);
        comboBoxCentrocampistaDx->setGeometry(QRect(80, 470, 121, 32));
        comboBoxCentrocampistaDx->setEditable(false);
        comboBoxCentrocampistaDx->setFrame(false);
        comboBoxCentrocampistaCx2 = new QComboBox(Formazione);
        comboBoxCentrocampistaCx2->setObjectName(QString::fromUtf8("comboBoxCentrocampistaCx2"));
        comboBoxCentrocampistaCx2->setEnabled(false);
        comboBoxCentrocampistaCx2->setGeometry(QRect(290, 430, 121, 32));
        comboBoxCentrocampistaCx2->setEditable(false);
        comboBoxCentrocampistaCx2->setFrame(false);
        comboBoxCentrocampistaCx1 = new QComboBox(Formazione);
        comboBoxCentrocampistaCx1->setObjectName(QString::fromUtf8("comboBoxCentrocampistaCx1"));
        comboBoxCentrocampistaCx1->setEnabled(false);
        comboBoxCentrocampistaCx1->setGeometry(QRect(160, 430, 121, 32));
        comboBoxCentrocampistaCx1->setEditable(false);
        comboBoxCentrocampistaCx1->setFrame(false);
        comboBoxAttaccanteCx = new QComboBox(Formazione);
        comboBoxAttaccanteCx->setObjectName(QString::fromUtf8("comboBoxAttaccanteCx"));
        comboBoxAttaccanteCx->setEnabled(false);
        comboBoxAttaccanteCx->setGeometry(QRect(230, 530, 121, 32));
        comboBoxAttaccanteCx->setEditable(false);
        comboBoxAttaccanteCx->setFrame(false);
        comboBoxAttaccanteDx = new QComboBox(Formazione);
        comboBoxAttaccanteDx->setObjectName(QString::fromUtf8("comboBoxAttaccanteDx"));
        comboBoxAttaccanteDx->setEnabled(false);
        comboBoxAttaccanteDx->setGeometry(QRect(80, 530, 121, 32));
        comboBoxAttaccanteDx->setEditable(false);
        comboBoxAttaccanteDx->setFrame(false);
        comboBoxAttaccanteSx = new QComboBox(Formazione);
        comboBoxAttaccanteSx->setObjectName(QString::fromUtf8("comboBoxAttaccanteSx"));
        comboBoxAttaccanteSx->setEnabled(false);
        comboBoxAttaccanteSx->setGeometry(QRect(380, 530, 121, 32));
        comboBoxAttaccanteSx->setEditable(false);
        comboBoxAttaccanteSx->setFrame(false);

        retranslateUi(Formazione);
        QObject::connect(buttonBox, SIGNAL(accepted()), Formazione, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), Formazione, SLOT(reject()));
        QObject::connect(comboPortieri, SIGNAL(activated(QString)), textFormazione, SLOT(append(QString)));
        QObject::connect(comboDifensori, SIGNAL(activated(QString)), textFormazione, SLOT(append(QString)));
        QObject::connect(comboCentrocampisti, SIGNAL(activated(QString)), textFormazione, SLOT(append(QString)));
        QObject::connect(comboAttaccanti, SIGNAL(activated(QString)), textFormazione, SLOT(append(QString)));

        QMetaObject::connectSlotsByName(Formazione);
    } // setupUi

    void retranslateUi(QDialog *Formazione)
    {
        Formazione->setWindowTitle(QApplication::translate("Formazione", "Inserisci formazione", 0, QApplication::UnicodeUTF8));
        labelDi->setText(QApplication::translate("Formazione", "Difensori", 0, QApplication::UnicodeUTF8));
        labelCe->setText(QApplication::translate("Formazione", "Centrocampisti", 0, QApplication::UnicodeUTF8));
        labelAt->setText(QApplication::translate("Formazione", "Attacanti", 0, QApplication::UnicodeUTF8));
        labelPo->setText(QApplication::translate("Formazione", "Portieri", 0, QApplication::UnicodeUTF8));
        label_5->setText(QApplication::translate("Formazione", "Scegli giornata:", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class Formazione: public Ui_Formazione {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FORMAZIONE_H
