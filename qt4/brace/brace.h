/****************************************************************************
** Form interface generated from reading ui file 'brace.ui'
**
** Created: Sun May 6 13:25:49 2007
**      by: The User Interface Compiler ($Id: qt/main.cpp   3.3.7   edited Aug 31 2005 $)
**
** WARNING! All changes made in this file will be lost!
****************************************************************************/

#ifndef BRACE_H
#define BRACE_H

#include <qvariant.h>
#include <qpixmap.h>
#include <qmainwindow.h>
#include <qdatetime.h>
#include <vector>
#include "oggetti.h"

class QVBoxLayout;
class QHBoxLayout;
class QGridLayout;
class QSpacerItem;
class QAction;
class QActionGroup;
class QToolBar;
class QPopupMenu;

class brace : public QMainWindow
{
    Q_OBJECT

public:
    brace( QWidget* parent = 0, const char* name = 0, WFlags fl = WType_TopLevel );
    ~brace();

    QMenuBar *MenuBar;
    QPopupMenu *fileMenu;
    QPopupMenu *editMenu;
    QPopupMenu *helpMenu;
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
    QAction* editFindAction;
    QAction* helpContentsAction;
    QAction* helpIndexAction;
    QAction* helpAboutAction;
    QAction* editTavoloAction;
    QAction* editPrenotazioneAction;

public slots:
    virtual void fileNew();
    virtual void editTavolo();
    virtual void editPrenotazione();
    virtual void fileOpen();
    virtual void fileSave();
    virtual void fileSaveAs();
    virtual void filePrint();
    virtual void fileExit();
    virtual void editUndo();
    virtual void editRedo();
    virtual void editCut();
    virtual void editCopy();
    virtual void editPaste();
    virtual void editFind();
    virtual void helpIndex();
    virtual void helpContents();
    virtual void helpAbout();

protected:

protected slots:
    virtual void languageChange();

private:
    Braciere ilBraciere;

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

};

#endif // BRACE_H
