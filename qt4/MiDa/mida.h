/****************************************************************************
** Form interface generated from reading ui file 'mida.ui'
**
** Created: Tue Dec 12 23:08:59 2006
**      by: The User Interface Compiler ($Id: qt/main.cpp   3.3.6   edited Aug 31 2005 $)
**
** WARNING! All changes made in this file will be lost!
****************************************************************************/

#ifndef MIDA_H
#define MIDA_H

#include <qvariant.h>
#include <qpixmap.h>
#include <qmainwindow.h>

#include <vector>

class QVBoxLayout;
class QHBoxLayout;
class QGridLayout;
class QSpacerItem;
class QAction;
class QActionGroup;
class QToolBar;
class QPopupMenu;
class QTabWidget;
class QWidget;
class QFrame;
class QDataTable;
class MyDataTable;
class QSqlRecord;
class FindCD;
class findClient;
class QSqlDatabase;
class QSqlCursor;
class subOrder;

class mida : public QMainWindow
{
    Q_OBJECT

public:
    mida( QWidget* parent = 0, const char* name = 0, WFlags fl = WType_TopLevel );
    ~mida();

    QTabWidget* mainTab;
    QWidget* tab;
    QFrame* frame4_2;
    QDataTable* cdTable;
    QWidget* tab_2;
    QFrame* frame9;
    QDataTable* clientTable;
    QFrame* frame10;
    MyDataTable* orderTable;
    QMenuBar *MenuBar;
    QPopupMenu *DB;
    QPopupMenu *Insert;
    QPopupMenu *Search;
    QPopupMenu *popupMenu_15;
    QPopupMenu *Inventory;
    QToolBar *toolBar;
    QAction* fileNewAction;
    QAction* fileOpenAction;
    QAction* fileSaveAction;
    QAction* fileSaveAsAction;
    QAction* filePrintAction;
    QAction* fileExitAction;
    QAction* editUndoAction;
    QAction* editRedoAction;
    QAction* editCutAction;
    QAction* editCopyAction;
    QAction* editPasteAction;
    QAction* searchSearch_CDAction;
    QAction* helpContentsAction;
    QAction* helpIndexAction;
    QAction* helpAboutAction;
    QAction* fileControlPanelAction;
    QAction* fileAboutAction;
    QAction* insertInsert_CDAction;
    QAction* insertInsert_ClientAction;
    QAction* insertInsert_OrderAction;
    QAction* searchSearch_ClientAction;
    QAction* searchSearch_Single_OrderAction;
    QAction* searchSearch_OrdersAction;
    QActionGroup* ActionGroup;
    QAction* searchSearch_OrdersNot_SentAction;
    QAction* searchSearch_OrdersNot_paidAction;

public slots:
    virtual void polish();

    virtual void filePrint();
    virtual void fileExit();
    virtual void fireFindCD( std::vector<QString> v, bool exact );
    virtual void fireFindClient( std::vector<QString> v, bool exact );
    virtual void about();
    virtual void newClient();
    virtual void updateClient( int row, int a, int b, const QPoint & p );
    virtual void updateOrderTable( QSqlRecord * record );
    virtual void newCD();
    virtual void updateCD( int row, int a, int b, const QPoint & p );
    virtual void newOrder();
    virtual void updateOrder( int row, int a, int b, const QPoint & p );
    virtual void controlPanel();

protected:
    QHBoxLayout* midaLayout;
    QHBoxLayout* tabLayout;
    QHBoxLayout* frame4_2Layout;
    QHBoxLayout* tabLayout_2;
    QVBoxLayout* layout1;
    QHBoxLayout* frame9Layout;
    QHBoxLayout* frame10Layout;

protected slots:
    virtual void languageChange();

private:
    QSqlCursor *sqlCursor2;
    QSqlCursor* sqlCursor1;
    QSqlCursor *sqlCursor;
    QSqlDatabase *db;
    findClient *findCl;
    FindCD *findcd;
    subOrder *sborder;

    QPixmap image0;
    QPixmap image1;
    QPixmap image2;
    QPixmap image3;
    QPixmap image4;
    QPixmap image5;
    QPixmap image6;
    QPixmap image7;
    QPixmap image8;
    QPixmap image9;
    QPixmap image10;

    void init();

private slots:
    virtual void searchCD();
    virtual void searchClient();

};

#endif // MIDA_H
