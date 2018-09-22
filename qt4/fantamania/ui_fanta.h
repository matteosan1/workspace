/********************************************************************************
** Form generated from reading UI file 'fanta.ui'
**
** Created by: Qt User Interface Compiler version 4.8.7
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FANTA_H
#define UI_FANTA_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QMainWindow>
#include <QtGui/QMenu>
#include <QtGui/QMenuBar>
#include <QtGui/QStatusBar>
#include <QtGui/QTableView>
#include <QtGui/QToolBar>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_fanta
{
public:
    QAction *actionOpen;
    QAction *actionSave;
    QAction *actionNew;
    QAction *actionChiudi;
    QAction *actionNuovo_giocatore;
    QAction *actionModifica_Giocatore;
    QAction *actionElimina_Giocatore;
    QAction *actionFormazione;
    QAction *actionInserisci_Voti;
    QAction *actionProfilo_Squadra;
    QAction *actionMedie_Giocatori;
    QAction *actionFormazione_tipo;
    QWidget *centralwidget;
    QVBoxLayout *vboxLayout;
    QHBoxLayout *hboxLayout;
    QTableView *tableGiocatori;
    QMenuBar *menubar;
    QMenu *menuFile;
    QMenu *menuModifica;
    QMenu *menuGestione;
    QStatusBar *statusbar;
    QToolBar *toolBar;

    void setupUi(QMainWindow *fanta)
    {
        if (fanta->objectName().isEmpty())
            fanta->setObjectName(QString::fromUtf8("fanta"));
        fanta->resize(800, 600);
        const QIcon icon = QIcon(QString::fromUtf8("fanta.png"));
        fanta->setWindowIcon(icon);
        actionOpen = new QAction(fanta);
        actionOpen->setObjectName(QString::fromUtf8("actionOpen"));
        const QIcon icon1 = QIcon(QString::fromUtf8(":/icons/images/folder_orange_open.png"));
        actionOpen->setIcon(icon1);
        actionSave = new QAction(fanta);
        actionSave->setObjectName(QString::fromUtf8("actionSave"));
        const QIcon icon2 = QIcon(QString::fromUtf8(":/icons/images/filesave.png"));
        actionSave->setIcon(icon2);
        actionNew = new QAction(fanta);
        actionNew->setObjectName(QString::fromUtf8("actionNew"));
        const QIcon icon3 = QIcon(QString::fromUtf8(":/icons/images/filenew.png"));
        actionNew->setIcon(icon3);
        actionChiudi = new QAction(fanta);
        actionChiudi->setObjectName(QString::fromUtf8("actionChiudi"));
        actionNuovo_giocatore = new QAction(fanta);
        actionNuovo_giocatore->setObjectName(QString::fromUtf8("actionNuovo_giocatore"));
        const QIcon icon4 = QIcon(QString::fromUtf8(":/icons/images/add_user.png"));
        actionNuovo_giocatore->setIcon(icon4);
        actionModifica_Giocatore = new QAction(fanta);
        actionModifica_Giocatore->setObjectName(QString::fromUtf8("actionModifica_Giocatore"));
        const QIcon icon5 = QIcon(QString::fromUtf8(":/icons/images/edit_user.png"));
        actionModifica_Giocatore->setIcon(icon5);
        actionElimina_Giocatore = new QAction(fanta);
        actionElimina_Giocatore->setObjectName(QString::fromUtf8("actionElimina_Giocatore"));
        const QIcon icon6 = QIcon(QString::fromUtf8(":/icons/images/delete_user.png"));
        actionElimina_Giocatore->setIcon(icon6);
        actionFormazione = new QAction(fanta);
        actionFormazione->setObjectName(QString::fromUtf8("actionFormazione"));
        const QIcon icon7 = QIcon(QString::fromUtf8(":/icons/images/pencil.png"));
        actionFormazione->setIcon(icon7);
        actionInserisci_Voti = new QAction(fanta);
        actionInserisci_Voti->setObjectName(QString::fromUtf8("actionInserisci_Voti"));
        const QIcon icon8 = QIcon(QString::fromUtf8(":/icons/images/math_sum.png"));
        actionInserisci_Voti->setIcon(icon8);
        actionProfilo_Squadra = new QAction(fanta);
        actionProfilo_Squadra->setObjectName(QString::fromUtf8("actionProfilo_Squadra"));
        const QIcon icon9 = QIcon(QString::fromUtf8(":/icons/images/contents2.png"));
        actionProfilo_Squadra->setIcon(icon9);
        actionMedie_Giocatori = new QAction(fanta);
        actionMedie_Giocatori->setObjectName(QString::fromUtf8("actionMedie_Giocatori"));
        const QIcon icon10 = QIcon(QString::fromUtf8(":/icons/images/frac.png"));
        actionMedie_Giocatori->setIcon(icon10);
        actionFormazione_tipo = new QAction(fanta);
        actionFormazione_tipo->setObjectName(QString::fromUtf8("actionFormazione_tipo"));
        const QIcon icon11 = QIcon(QString::fromUtf8(":/icons/images/package_edutainment.png"));
        actionFormazione_tipo->setIcon(icon11);
        centralwidget = new QWidget(fanta);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        vboxLayout = new QVBoxLayout(centralwidget);
        vboxLayout->setObjectName(QString::fromUtf8("vboxLayout"));
        hboxLayout = new QHBoxLayout();
        hboxLayout->setObjectName(QString::fromUtf8("hboxLayout"));
        tableGiocatori = new QTableView(centralwidget);
        tableGiocatori->setObjectName(QString::fromUtf8("tableGiocatori"));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(tableGiocatori->sizePolicy().hasHeightForWidth());
        tableGiocatori->setSizePolicy(sizePolicy);
        tableGiocatori->setSelectionMode(QAbstractItemView::SingleSelection);

        hboxLayout->addWidget(tableGiocatori);


        vboxLayout->addLayout(hboxLayout);

        fanta->setCentralWidget(centralwidget);
        menubar = new QMenuBar(fanta);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 800, 29));
        menuFile = new QMenu(menubar);
        menuFile->setObjectName(QString::fromUtf8("menuFile"));
        menuModifica = new QMenu(menubar);
        menuModifica->setObjectName(QString::fromUtf8("menuModifica"));
        menuGestione = new QMenu(menubar);
        menuGestione->setObjectName(QString::fromUtf8("menuGestione"));
        fanta->setMenuBar(menubar);
        statusbar = new QStatusBar(fanta);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        fanta->setStatusBar(statusbar);
        toolBar = new QToolBar(fanta);
        toolBar->setObjectName(QString::fromUtf8("toolBar"));
        fanta->addToolBar(Qt::TopToolBarArea, toolBar);

        menubar->addAction(menuFile->menuAction());
        menubar->addAction(menuModifica->menuAction());
        menubar->addAction(menuGestione->menuAction());
        menuFile->addAction(actionNew);
        menuFile->addSeparator();
        menuFile->addAction(actionOpen);
        menuFile->addAction(actionSave);
        menuFile->addSeparator();
        menuFile->addAction(actionChiudi);
        menuModifica->addAction(actionNuovo_giocatore);
        menuModifica->addAction(actionModifica_Giocatore);
        menuModifica->addAction(actionElimina_Giocatore);
        menuGestione->addAction(actionFormazione);
        menuGestione->addAction(actionMedie_Giocatori);
        menuGestione->addAction(actionFormazione_tipo);
        toolBar->addAction(actionNew);
        toolBar->addAction(actionOpen);
        toolBar->addAction(actionSave);
        toolBar->addSeparator();
        toolBar->addAction(actionNuovo_giocatore);
        toolBar->addAction(actionModifica_Giocatore);
        toolBar->addAction(actionElimina_Giocatore);
        toolBar->addSeparator();
        toolBar->addAction(actionFormazione);
        toolBar->addAction(actionMedie_Giocatori);
        toolBar->addAction(actionFormazione_tipo);

        retranslateUi(fanta);

        QMetaObject::connectSlotsByName(fanta);
    } // setupUi

    void retranslateUi(QMainWindow *fanta)
    {
        fanta->setWindowTitle(QApplication::translate("fanta", "Fantamanager", 0, QApplication::UnicodeUTF8));
        actionOpen->setText(QApplication::translate("fanta", "Apri", 0, QApplication::UnicodeUTF8));
        actionSave->setText(QApplication::translate("fanta", "Salva", 0, QApplication::UnicodeUTF8));
        actionNew->setText(QApplication::translate("fanta", "Nuovo", 0, QApplication::UnicodeUTF8));
        actionChiudi->setText(QApplication::translate("fanta", "Chiudi", 0, QApplication::UnicodeUTF8));
        actionNuovo_giocatore->setText(QApplication::translate("fanta", "Nuovo Giocatore", 0, QApplication::UnicodeUTF8));
        actionModifica_Giocatore->setText(QApplication::translate("fanta", "Modifica Giocatore", 0, QApplication::UnicodeUTF8));
        actionElimina_Giocatore->setText(QApplication::translate("fanta", "Elimina Giocatore", 0, QApplication::UnicodeUTF8));
        actionFormazione->setText(QApplication::translate("fanta", "Formazione", 0, QApplication::UnicodeUTF8));
        actionInserisci_Voti->setText(QApplication::translate("fanta", "Inserisci Voti", 0, QApplication::UnicodeUTF8));
        actionProfilo_Squadra->setText(QApplication::translate("fanta", "Profilo Squadra", 0, QApplication::UnicodeUTF8));
        actionMedie_Giocatori->setText(QApplication::translate("fanta", "Medie Giocatori", 0, QApplication::UnicodeUTF8));
        actionFormazione_tipo->setText(QApplication::translate("fanta", "Formazione tipo", 0, QApplication::UnicodeUTF8));
        menuFile->setTitle(QApplication::translate("fanta", "File", 0, QApplication::UnicodeUTF8));
        menuModifica->setTitle(QApplication::translate("fanta", "Modifica", 0, QApplication::UnicodeUTF8));
        menuGestione->setTitle(QApplication::translate("fanta", "Gestione", 0, QApplication::UnicodeUTF8));
        toolBar->setWindowTitle(QApplication::translate("fanta", "toolBar", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        toolBar->setToolTip(QApplication::translate("fanta", "Nuova Formazione", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
    } // retranslateUi

};

namespace Ui {
    class fanta: public Ui_fanta {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FANTA_H
