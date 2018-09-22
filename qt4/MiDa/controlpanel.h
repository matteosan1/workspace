/****************************************************************************
** Form interface generated from reading ui file 'controlpanel.ui'
**
** Created: Fri Dec 22 19:24:45 2006
**      by: The User Interface Compiler ($Id: qt/main.cpp   3.3.6   edited Aug 31 2005 $)
**
** WARNING! All changes made in this file will be lost!
****************************************************************************/

#ifndef _H
#define _H

#include <qvariant.h>
#include <qdialog.h>

class QVBoxLayout;
class QHBoxLayout;
class QGridLayout;
class QSpacerItem;
class Q3ListBox;
class Q3GroupBox;
class QLineEdit;
class QPushButton;

class ControlPanel : public QDialog
{
    Q_OBJECT

public:
    ControlPanel( QWidget* parent = 0, const char* name = 0, bool modal = FALSE, WFlags fl = 0 );
    ~ControlPanel();


protected:

protected slots:
    virtual void languageChange();

};

#endif // _H
