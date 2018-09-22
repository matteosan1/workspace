/********************************************************************************
** Form generated from reading UI file 'tdpalio.ui'
**
** Created by: Qt User Interface Compiler version 4.8.7
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TDPALIO_H
#define UI_TDPALIO_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QFrame>
#include <QtGui/QGraphicsView>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QMainWindow>
#include <QtGui/QMenu>
#include <QtGui/QMenuBar>
#include <QtGui/QProgressBar>
#include <QtGui/QSpacerItem>
#include <QtGui/QStatusBar>
#include <QtGui/QTabWidget>
#include <QtGui/QTableWidget>
#include <QtGui/QTextEdit>
#include <QtGui/QToolBar>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

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
    QAction *actionConnessione;
    QAction *actionAvvia_gioco;
    QAction *actionScegli_Contrada;
    QAction *actionSpettatore;
    QAction *actionContrada;
    QAction *actionVittorie;
    QAction *actionCuffia;
    QAction *actionFantini;
    QAction *actionCavalli;
    QWidget *centralwidget;
    QVBoxLayout *vboxLayout;
    QFrame *frame;
    QTableWidget *tableWidget_contrade;
    QGraphicsView *graphicsView;
    QTextEdit *chatEdit;
    QTabWidget *tabWidget_Panel;
    QWidget *tab;
    QWidget *layoutWidget;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QLabel *label_pngContrada;
    QLabel *label_nomeContrada;
    QLabel *label_carica;
    QLabel *label_gradimento;
    QWidget *tab_2;
    QWidget *layoutWidget1;
    QVBoxLayout *verticalLayout_3;
    QLabel *label_fantino;
    QLabel *label_fantinoCorsi;
    QLabel *label_fantinoVinti;
    QWidget *tab_3;
    QWidget *layoutWidget2;
    QVBoxLayout *verticalLayout_2;
    QLabel *label_cavallo;
    QLabel *label_cavalloCorsi;
    QLabel *label_cavalloVinti;
    QHBoxLayout *horizontalLayout_2;
    QSpacerItem *horizontalSpacer;
    QProgressBar *progressBar_forma;
    QSpacerItem *horizontalSpacer_2;
    QLineEdit *lineEdit_chat;
    QMenuBar *menubar;
    QMenu *menuFile;
    QMenu *menuInserisci;
    QMenu *menuOpzioni;
    QMenu *menuServer;
    QMenu *menuTabelle;
    QToolBar *toolBar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(835, 643);
        QIcon icon;
        icon.addFile(QString::fromUtf8("../../splashscreen/tdp.png"), QSize(), QIcon::Normal, QIcon::Off);
        MainWindow->setWindowIcon(icon);
        actionNew = new QAction(MainWindow);
        actionNew->setObjectName(QString::fromUtf8("actionNew"));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/icons/pictures/filenew.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionNew->setIcon(icon1);
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
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/icons/pictures/avanti.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionAvanti->setIcon(icon2);
        actionConnessione = new QAction(MainWindow);
        actionConnessione->setObjectName(QString::fromUtf8("actionConnessione"));
        QIcon icon3;
        icon3.addFile(QString::fromUtf8(":/icons/pictures/connect_no.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionConnessione->setIcon(icon3);
        actionAvvia_gioco = new QAction(MainWindow);
        actionAvvia_gioco->setObjectName(QString::fromUtf8("actionAvvia_gioco"));
        QIcon icon4;
        icon4.addFile(QString::fromUtf8(":/icons/pictures/history.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionAvvia_gioco->setIcon(icon4);
        actionScegli_Contrada = new QAction(MainWindow);
        actionScegli_Contrada->setObjectName(QString::fromUtf8("actionScegli_Contrada"));
        actionSpettatore = new QAction(MainWindow);
        actionSpettatore->setObjectName(QString::fromUtf8("actionSpettatore"));
        actionContrada = new QAction(MainWindow);
        actionContrada->setObjectName(QString::fromUtf8("actionContrada"));
        actionVittorie = new QAction(MainWindow);
        actionVittorie->setObjectName(QString::fromUtf8("actionVittorie"));
        actionCuffia = new QAction(MainWindow);
        actionCuffia->setObjectName(QString::fromUtf8("actionCuffia"));
        actionFantini = new QAction(MainWindow);
        actionFantini->setObjectName(QString::fromUtf8("actionFantini"));
        actionCavalli = new QAction(MainWindow);
        actionCavalli->setObjectName(QString::fromUtf8("actionCavalli"));
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        vboxLayout = new QVBoxLayout(centralwidget);
        vboxLayout->setObjectName(QString::fromUtf8("vboxLayout"));
        frame = new QFrame(centralwidget);
        frame->setObjectName(QString::fromUtf8("frame"));
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Raised);
        tableWidget_contrade = new QTableWidget(frame);
        if (tableWidget_contrade->columnCount() < 3)
            tableWidget_contrade->setColumnCount(3);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        tableWidget_contrade->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        tableWidget_contrade->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        tableWidget_contrade->setHorizontalHeaderItem(2, __qtablewidgetitem2);
        if (tableWidget_contrade->rowCount() < 10)
            tableWidget_contrade->setRowCount(10);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        tableWidget_contrade->setVerticalHeaderItem(0, __qtablewidgetitem3);
        QTableWidgetItem *__qtablewidgetitem4 = new QTableWidgetItem();
        tableWidget_contrade->setVerticalHeaderItem(1, __qtablewidgetitem4);
        QTableWidgetItem *__qtablewidgetitem5 = new QTableWidgetItem();
        tableWidget_contrade->setVerticalHeaderItem(2, __qtablewidgetitem5);
        QTableWidgetItem *__qtablewidgetitem6 = new QTableWidgetItem();
        tableWidget_contrade->setVerticalHeaderItem(3, __qtablewidgetitem6);
        QTableWidgetItem *__qtablewidgetitem7 = new QTableWidgetItem();
        tableWidget_contrade->setVerticalHeaderItem(4, __qtablewidgetitem7);
        QTableWidgetItem *__qtablewidgetitem8 = new QTableWidgetItem();
        tableWidget_contrade->setVerticalHeaderItem(5, __qtablewidgetitem8);
        QTableWidgetItem *__qtablewidgetitem9 = new QTableWidgetItem();
        tableWidget_contrade->setVerticalHeaderItem(6, __qtablewidgetitem9);
        QTableWidgetItem *__qtablewidgetitem10 = new QTableWidgetItem();
        tableWidget_contrade->setVerticalHeaderItem(7, __qtablewidgetitem10);
        QTableWidgetItem *__qtablewidgetitem11 = new QTableWidgetItem();
        tableWidget_contrade->setVerticalHeaderItem(8, __qtablewidgetitem11);
        tableWidget_contrade->setObjectName(QString::fromUtf8("tableWidget_contrade"));
        tableWidget_contrade->setGeometry(QRect(540, 261, 261, 238));
        QSizePolicy sizePolicy(QSizePolicy::Maximum, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(tableWidget_contrade->sizePolicy().hasHeightForWidth());
        tableWidget_contrade->setSizePolicy(sizePolicy);
        tableWidget_contrade->setMinimumSize(QSize(0, 0));
        tableWidget_contrade->setMaximumSize(QSize(16777215, 238));
        QFont font;
        font.setPointSize(6);
        tableWidget_contrade->setFont(font);
        tableWidget_contrade->setFocusPolicy(Qt::NoFocus);
        tableWidget_contrade->setAutoScroll(false);
        tableWidget_contrade->setSelectionMode(QAbstractItemView::NoSelection);
        tableWidget_contrade->setIconSize(QSize(20, 20));
        tableWidget_contrade->setShowGrid(true);
        tableWidget_contrade->setGridStyle(Qt::SolidLine);
        tableWidget_contrade->setWordWrap(false);
        tableWidget_contrade->setCornerButtonEnabled(false);
        tableWidget_contrade->setRowCount(10);
        graphicsView = new QGraphicsView(frame);
        graphicsView->setObjectName(QString::fromUtf8("graphicsView"));
        graphicsView->setEnabled(false);
        graphicsView->setGeometry(QRect(8, 8, 501, 483));
        chatEdit = new QTextEdit(frame);
        chatEdit->setObjectName(QString::fromUtf8("chatEdit"));
        chatEdit->setEnabled(true);
        chatEdit->setGeometry(QRect(20, 20, 241, 81));
        QSizePolicy sizePolicy1(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(chatEdit->sizePolicy().hasHeightForWidth());
        chatEdit->setSizePolicy(sizePolicy1);
        chatEdit->setFrameShadow(QFrame::Plain);
        chatEdit->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
        chatEdit->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        chatEdit->setReadOnly(true);
        tabWidget_Panel = new QTabWidget(frame);
        tabWidget_Panel->setObjectName(QString::fromUtf8("tabWidget_Panel"));
        tabWidget_Panel->setGeometry(QRect(550, 10, 251, 211));
        sizePolicy1.setHeightForWidth(tabWidget_Panel->sizePolicy().hasHeightForWidth());
        tabWidget_Panel->setSizePolicy(sizePolicy1);
        tab = new QWidget();
        tab->setObjectName(QString::fromUtf8("tab"));
        layoutWidget = new QWidget(tab);
        layoutWidget->setObjectName(QString::fromUtf8("layoutWidget"));
        layoutWidget->setGeometry(QRect(10, 10, 217, 94));
        verticalLayout = new QVBoxLayout(layoutWidget);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        label_pngContrada = new QLabel(layoutWidget);
        label_pngContrada->setObjectName(QString::fromUtf8("label_pngContrada"));
        sizePolicy1.setHeightForWidth(label_pngContrada->sizePolicy().hasHeightForWidth());
        label_pngContrada->setSizePolicy(sizePolicy1);
        label_pngContrada->setMinimumSize(QSize(50, 50));
        label_pngContrada->setMaximumSize(QSize(50, 50));

        horizontalLayout->addWidget(label_pngContrada);

        label_nomeContrada = new QLabel(layoutWidget);
        label_nomeContrada->setObjectName(QString::fromUtf8("label_nomeContrada"));
        sizePolicy.setHeightForWidth(label_nomeContrada->sizePolicy().hasHeightForWidth());
        label_nomeContrada->setSizePolicy(sizePolicy);
        label_nomeContrada->setFont(font);

        horizontalLayout->addWidget(label_nomeContrada);


        verticalLayout->addLayout(horizontalLayout);

        label_carica = new QLabel(layoutWidget);
        label_carica->setObjectName(QString::fromUtf8("label_carica"));
        sizePolicy.setHeightForWidth(label_carica->sizePolicy().hasHeightForWidth());
        label_carica->setSizePolicy(sizePolicy);
        label_carica->setFont(font);

        verticalLayout->addWidget(label_carica);

        label_gradimento = new QLabel(layoutWidget);
        label_gradimento->setObjectName(QString::fromUtf8("label_gradimento"));
        sizePolicy.setHeightForWidth(label_gradimento->sizePolicy().hasHeightForWidth());
        label_gradimento->setSizePolicy(sizePolicy);
        label_gradimento->setFont(font);

        verticalLayout->addWidget(label_gradimento);

        tabWidget_Panel->addTab(tab, QString());
        tab_2 = new QWidget();
        tab_2->setObjectName(QString::fromUtf8("tab_2"));
        layoutWidget1 = new QWidget(tab_2);
        layoutWidget1->setObjectName(QString::fromUtf8("layoutWidget1"));
        layoutWidget1->setGeometry(QRect(30, 20, 96, 58));
        verticalLayout_3 = new QVBoxLayout(layoutWidget1);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        verticalLayout_3->setContentsMargins(0, 0, 0, 0);
        label_fantino = new QLabel(layoutWidget1);
        label_fantino->setObjectName(QString::fromUtf8("label_fantino"));
        sizePolicy.setHeightForWidth(label_fantino->sizePolicy().hasHeightForWidth());
        label_fantino->setSizePolicy(sizePolicy);
        label_fantino->setFont(font);

        verticalLayout_3->addWidget(label_fantino);

        label_fantinoCorsi = new QLabel(layoutWidget1);
        label_fantinoCorsi->setObjectName(QString::fromUtf8("label_fantinoCorsi"));
        sizePolicy.setHeightForWidth(label_fantinoCorsi->sizePolicy().hasHeightForWidth());
        label_fantinoCorsi->setSizePolicy(sizePolicy);
        label_fantinoCorsi->setFont(font);

        verticalLayout_3->addWidget(label_fantinoCorsi);

        label_fantinoVinti = new QLabel(layoutWidget1);
        label_fantinoVinti->setObjectName(QString::fromUtf8("label_fantinoVinti"));
        sizePolicy.setHeightForWidth(label_fantinoVinti->sizePolicy().hasHeightForWidth());
        label_fantinoVinti->setSizePolicy(sizePolicy);
        label_fantinoVinti->setFont(font);

        verticalLayout_3->addWidget(label_fantinoVinti);

        tabWidget_Panel->addTab(tab_2, QString());
        tab_3 = new QWidget();
        tab_3->setObjectName(QString::fromUtf8("tab_3"));
        layoutWidget2 = new QWidget(tab_3);
        layoutWidget2->setObjectName(QString::fromUtf8("layoutWidget2"));
        layoutWidget2->setGeometry(QRect(30, 30, 179, 87));
        verticalLayout_2 = new QVBoxLayout(layoutWidget2);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(0, 0, 0, 0);
        label_cavallo = new QLabel(layoutWidget2);
        label_cavallo->setObjectName(QString::fromUtf8("label_cavallo"));
        label_cavallo->setFont(font);

        verticalLayout_2->addWidget(label_cavallo);

        label_cavalloCorsi = new QLabel(layoutWidget2);
        label_cavalloCorsi->setObjectName(QString::fromUtf8("label_cavalloCorsi"));
        label_cavalloCorsi->setFont(font);

        verticalLayout_2->addWidget(label_cavalloCorsi);

        label_cavalloVinti = new QLabel(layoutWidget2);
        label_cavalloVinti->setObjectName(QString::fromUtf8("label_cavalloVinti"));
        label_cavalloVinti->setFont(font);

        verticalLayout_2->addWidget(label_cavalloVinti);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer);

        progressBar_forma = new QProgressBar(layoutWidget2);
        progressBar_forma->setObjectName(QString::fromUtf8("progressBar_forma"));
        progressBar_forma->setFont(font);
        progressBar_forma->setValue(24);

        horizontalLayout_2->addWidget(progressBar_forma);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_2);


        verticalLayout_2->addLayout(horizontalLayout_2);

        tabWidget_Panel->addTab(tab_3, QString());
        lineEdit_chat = new QLineEdit(frame);
        lineEdit_chat->setObjectName(QString::fromUtf8("lineEdit_chat"));
        lineEdit_chat->setEnabled(true);
        lineEdit_chat->setGeometry(QRect(100, 410, 331, 29));
        sizePolicy1.setHeightForWidth(lineEdit_chat->sizePolicy().hasHeightForWidth());
        lineEdit_chat->setSizePolicy(sizePolicy1);

        vboxLayout->addWidget(frame);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 835, 27));
        menuFile = new QMenu(menubar);
        menuFile->setObjectName(QString::fromUtf8("menuFile"));
        menuInserisci = new QMenu(menubar);
        menuInserisci->setObjectName(QString::fromUtf8("menuInserisci"));
        menuOpzioni = new QMenu(menubar);
        menuOpzioni->setObjectName(QString::fromUtf8("menuOpzioni"));
        menuServer = new QMenu(menubar);
        menuServer->setObjectName(QString::fromUtf8("menuServer"));
        menuTabelle = new QMenu(menubar);
        menuTabelle->setObjectName(QString::fromUtf8("menuTabelle"));
        MainWindow->setMenuBar(menubar);
        toolBar = new QToolBar(MainWindow);
        toolBar->setObjectName(QString::fromUtf8("toolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, toolBar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainWindow->setStatusBar(statusbar);

        menubar->addAction(menuFile->menuAction());
        menubar->addAction(menuInserisci->menuAction());
        menubar->addAction(menuOpzioni->menuAction());
        menubar->addAction(menuServer->menuAction());
        menubar->addAction(menuTabelle->menuAction());
        menuFile->addAction(actionNew);
        menuFile->addAction(actionOpen);
        menuFile->addAction(actionSave);
        menuFile->addAction(actionSave_As);
        menuFile->addAction(actionPrint);
        menuFile->addAction(actionExit);
        menuInserisci->addAction(actionInserisci_Giocatore);
        menuOpzioni->addAction(actionEffetti_sonori);
        menuServer->addAction(actionAvvia_gioco);
        menuServer->addAction(actionScegli_Contrada);
        menuServer->addAction(actionSpettatore);
        menuTabelle->addAction(actionContrada);
        menuTabelle->addAction(actionVittorie);
        menuTabelle->addAction(actionCuffia);
        menuTabelle->addAction(actionFantini);
        menuTabelle->addAction(actionCavalli);
        toolBar->addAction(actionNew);
        toolBar->addAction(actionAvanti);
        toolBar->addSeparator();
        toolBar->addAction(actionConnessione);
        toolBar->addAction(actionAvvia_gioco);
        toolBar->addSeparator();
        toolBar->addAction(actionExit);

        retranslateUi(MainWindow);

        tabWidget_Panel->setCurrentIndex(0);


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
        actionConnessione->setText(QApplication::translate("MainWindow", "Connessione", 0, QApplication::UnicodeUTF8));
        actionAvvia_gioco->setText(QApplication::translate("MainWindow", "Avvia gioco", 0, QApplication::UnicodeUTF8));
        actionScegli_Contrada->setText(QApplication::translate("MainWindow", "Scegli Contrada", 0, QApplication::UnicodeUTF8));
        actionSpettatore->setText(QApplication::translate("MainWindow", "Spettatore", 0, QApplication::UnicodeUTF8));
        actionContrada->setText(QApplication::translate("MainWindow", "Contrada", 0, QApplication::UnicodeUTF8));
        actionVittorie->setText(QApplication::translate("MainWindow", "Vittorie", 0, QApplication::UnicodeUTF8));
        actionCuffia->setText(QApplication::translate("MainWindow", "Cuffia", 0, QApplication::UnicodeUTF8));
        actionFantini->setText(QApplication::translate("MainWindow", "Fantini", 0, QApplication::UnicodeUTF8));
        actionCavalli->setText(QApplication::translate("MainWindow", "Cavalli", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem = tableWidget_contrade->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QApplication::translate("MainWindow", "New Column", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem1 = tableWidget_contrade->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QApplication::translate("MainWindow", "New Column", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem2 = tableWidget_contrade->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QApplication::translate("MainWindow", "New Column", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem3 = tableWidget_contrade->verticalHeaderItem(0);
        ___qtablewidgetitem3->setText(QApplication::translate("MainWindow", "New Row", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem4 = tableWidget_contrade->verticalHeaderItem(1);
        ___qtablewidgetitem4->setText(QApplication::translate("MainWindow", "New Row", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem5 = tableWidget_contrade->verticalHeaderItem(2);
        ___qtablewidgetitem5->setText(QApplication::translate("MainWindow", "New Row", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem6 = tableWidget_contrade->verticalHeaderItem(3);
        ___qtablewidgetitem6->setText(QApplication::translate("MainWindow", "New Row", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem7 = tableWidget_contrade->verticalHeaderItem(4);
        ___qtablewidgetitem7->setText(QApplication::translate("MainWindow", "New Row", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem8 = tableWidget_contrade->verticalHeaderItem(5);
        ___qtablewidgetitem8->setText(QApplication::translate("MainWindow", "New Row", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem9 = tableWidget_contrade->verticalHeaderItem(6);
        ___qtablewidgetitem9->setText(QApplication::translate("MainWindow", "New Row", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem10 = tableWidget_contrade->verticalHeaderItem(7);
        ___qtablewidgetitem10->setText(QApplication::translate("MainWindow", "New Row", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem11 = tableWidget_contrade->verticalHeaderItem(8);
        ___qtablewidgetitem11->setText(QApplication::translate("MainWindow", "New Row", 0, QApplication::UnicodeUTF8));
        label_pngContrada->setText(QApplication::translate("MainWindow", "Pic", 0, QApplication::UnicodeUTF8));
        label_nomeContrada->setText(QApplication::translate("MainWindow", "Imperiale Contrada della Giraffa", 0, QApplication::UnicodeUTF8));
        label_carica->setText(QApplication::translate("MainWindow", "Mandato:3", 0, QApplication::UnicodeUTF8));
        label_gradimento->setText(QApplication::translate("MainWindow", "Gradimento: 100%", 0, QApplication::UnicodeUTF8));
        tabWidget_Panel->setTabText(tabWidget_Panel->indexOf(tab), QApplication::translate("MainWindow", "Contrada", 0, QApplication::UnicodeUTF8));
        label_fantino->setText(QApplication::translate("MainWindow", "Fantino: Gazzelloro", 0, QApplication::UnicodeUTF8));
        label_fantinoCorsi->setText(QApplication::translate("MainWindow", "Corsi: 40", 0, QApplication::UnicodeUTF8));
        label_fantinoVinti->setText(QApplication::translate("MainWindow", "Vinti: 10", 0, QApplication::UnicodeUTF8));
        tabWidget_Panel->setTabText(tabWidget_Panel->indexOf(tab_2), QApplication::translate("MainWindow", "Fantino", 0, QApplication::UnicodeUTF8));
        label_cavallo->setText(QApplication::translate("MainWindow", "Cavallo: Saltalamacchia", 0, QApplication::UnicodeUTF8));
        label_cavalloCorsi->setText(QApplication::translate("MainWindow", "Corsi: 40", 0, QApplication::UnicodeUTF8));
        label_cavalloVinti->setText(QApplication::translate("MainWindow", "Vinti: 20", 0, QApplication::UnicodeUTF8));
        tabWidget_Panel->setTabText(tabWidget_Panel->indexOf(tab_3), QApplication::translate("MainWindow", "Cavallo", 0, QApplication::UnicodeUTF8));
        menuFile->setTitle(QApplication::translate("MainWindow", "File", 0, QApplication::UnicodeUTF8));
        menuInserisci->setTitle(QApplication::translate("MainWindow", "Inserisci", 0, QApplication::UnicodeUTF8));
        menuOpzioni->setTitle(QApplication::translate("MainWindow", "Opzioni", 0, QApplication::UnicodeUTF8));
        menuServer->setTitle(QApplication::translate("MainWindow", "Server", 0, QApplication::UnicodeUTF8));
        menuTabelle->setTitle(QApplication::translate("MainWindow", "Tabelle", 0, QApplication::UnicodeUTF8));
        toolBar->setWindowTitle(QApplication::translate("MainWindow", "toolBar", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TDPALIO_H
