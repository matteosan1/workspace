/********************************************************************************
** Form generated from reading ui file 'tdpalio.ui'
**
** Created: Mon Oct 22 19:24:19 2007
**      by: Qt User Interface Compiler version 4.3.2
**
** WARNING! All changes made in this file will be lost when recompiling ui file!
********************************************************************************/

#ifndef UI_TDPALIO_H
#define UI_TDPALIO_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QFrame>
#include <QtGui/QGraphicsView>
#include <QtGui/QMainWindow>
#include <QtGui/QMenu>
#include <QtGui/QMenuBar>
#include <QtGui/QStatusBar>
#include <QtGui/QToolBar>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

class Ui_MainWindow
{
public:
    QAction *actionNew;
    QAction *actionOpen;
    QAction *actionSave;
    QAction *actionSave_As;
    QAction *actionPrint;
    QAction *actionExit;
    QAction *actionInserisci_Giocatore;
    QAction *actionEffetti_sonori;
    QAction *actionAvanti;
    QWidget *centralwidget;
    QVBoxLayout *vboxLayout;
    QFrame *frame;
    QVBoxLayout *vboxLayout1;
    QGraphicsView *graphicsView;
    QMenuBar *menubar;
    QMenu *menuFile;
    QMenu *menuInserisci;
    QMenu *menuOpzioni;
    QStatusBar *statusbar;
    QToolBar *toolBar;

    void setupUi(QMainWindow *MainWindow)
    {
    if (MainWindow->objectName().isEmpty())
        MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
    MainWindow->resize(800, 600);
    actionNew = new QAction(MainWindow);
    actionNew->setObjectName(QString::fromUtf8("actionNew"));
    actionNew->setIcon(QIcon(QString::fromUtf8(":/icons/pictures/filenew.png")));
    actionOpen = new QAction(MainWindow);
    actionOpen->setObjectName(QString::fromUtf8("actionOpen"));
    actionSave = new QAction(MainWindow);
    actionSave->setObjectName(QString::fromUtf8("actionSave"));
    actionSave_As = new QAction(MainWindow);
    actionSave_As->setObjectName(QString::fromUtf8("actionSave_As"));
    actionPrint = new QAction(MainWindow);
    actionPrint->setObjectName(QString::fromUtf8("actionPrint"));
    actionExit = new QAction(MainWindow);
    actionExit->setObjectName(QString::fromUtf8("actionExit"));
    actionInserisci_Giocatore = new QAction(MainWindow);
    actionInserisci_Giocatore->setObjectName(QString::fromUtf8("actionInserisci_Giocatore"));
    actionEffetti_sonori = new QAction(MainWindow);
    actionEffetti_sonori->setObjectName(QString::fromUtf8("actionEffetti_sonori"));
    actionEffetti_sonori->setCheckable(true);
    actionEffetti_sonori->setChecked(true);
    actionAvanti = new QAction(MainWindow);
    actionAvanti->setObjectName(QString::fromUtf8("actionAvanti"));
    actionAvanti->setIcon(QIcon(QString::fromUtf8(":/icons/pictures/avanti.png")));
    centralwidget = new QWidget(MainWindow);
    centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
    vboxLayout = new QVBoxLayout(centralwidget);
    vboxLayout->setObjectName(QString::fromUtf8("vboxLayout"));
    frame = new QFrame(centralwidget);
    frame->setObjectName(QString::fromUtf8("frame"));
    frame->setFrameShape(QFrame::StyledPanel);
    frame->setFrameShadow(QFrame::Raised);
    vboxLayout1 = new QVBoxLayout(frame);
    vboxLayout1->setObjectName(QString::fromUtf8("vboxLayout1"));
    graphicsView = new QGraphicsView(frame);
    graphicsView->setObjectName(QString::fromUtf8("graphicsView"));

    vboxLayout1->addWidget(graphicsView);


    vboxLayout->addWidget(frame);

    MainWindow->setCentralWidget(centralwidget);
    menubar = new QMenuBar(MainWindow);
    menubar->setObjectName(QString::fromUtf8("menubar"));
    menubar->setGeometry(QRect(0, 0, 800, 29));
    menuFile = new QMenu(menubar);
    menuFile->setObjectName(QString::fromUtf8("menuFile"));
    menuInserisci = new QMenu(menubar);
    menuInserisci->setObjectName(QString::fromUtf8("menuInserisci"));
    menuOpzioni = new QMenu(menubar);
    menuOpzioni->setObjectName(QString::fromUtf8("menuOpzioni"));
    MainWindow->setMenuBar(menubar);
    statusbar = new QStatusBar(MainWindow);
    statusbar->setObjectName(QString::fromUtf8("statusbar"));
    MainWindow->setStatusBar(statusbar);
    toolBar = new QToolBar(MainWindow);
    toolBar->setObjectName(QString::fromUtf8("toolBar"));
    MainWindow->addToolBar(Qt::TopToolBarArea, toolBar);

    menubar->addAction(menuFile->menuAction());
    menubar->addAction(menuInserisci->menuAction());
    menubar->addAction(menuOpzioni->menuAction());
    menuFile->addAction(actionNew);
    menuFile->addAction(actionOpen);
    menuFile->addAction(actionSave);
    menuFile->addAction(actionSave_As);
    menuFile->addAction(actionPrint);
    menuFile->addAction(actionExit);
    menuInserisci->addAction(actionInserisci_Giocatore);
    menuOpzioni->addAction(actionEffetti_sonori);
    toolBar->addAction(actionNew);
    toolBar->addAction(actionAvanti);

    retranslateUi(MainWindow);

    QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
    MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", 0, QApplication::UnicodeUTF8));
    actionNew->setText(QApplication::translate("MainWindow", "New", 0, QApplication::UnicodeUTF8));
    actionOpen->setText(QApplication::translate("MainWindow", "Open", 0, QApplication::UnicodeUTF8));
    actionSave->setText(QApplication::translate("MainWindow", "Save", 0, QApplication::UnicodeUTF8));
    actionSave_As->setText(QApplication::translate("MainWindow", "Save As", 0, QApplication::UnicodeUTF8));
    actionPrint->setText(QApplication::translate("MainWindow", "Print", 0, QApplication::UnicodeUTF8));
    actionExit->setText(QApplication::translate("MainWindow", "Exit", 0, QApplication::UnicodeUTF8));
    actionInserisci_Giocatore->setText(QApplication::translate("MainWindow", "Giocatore", 0, QApplication::UnicodeUTF8));
    actionEffetti_sonori->setText(QApplication::translate("MainWindow", "Effetti sonori", 0, QApplication::UnicodeUTF8));
    actionAvanti->setText(QApplication::translate("MainWindow", "Avanti", 0, QApplication::UnicodeUTF8));
    menuFile->setTitle(QApplication::translate("MainWindow", "File", 0, QApplication::UnicodeUTF8));
    menuInserisci->setTitle(QApplication::translate("MainWindow", "Inserisci", 0, QApplication::UnicodeUTF8));
    menuOpzioni->setTitle(QApplication::translate("MainWindow", "Opzioni", 0, QApplication::UnicodeUTF8));
    toolBar->setWindowTitle(QApplication::translate("MainWindow", "toolBar", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

#endif // UI_TDPALIO_H
