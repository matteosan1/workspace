/****************************************************************************
** Form interface generated from reading ui file 'findclient.ui'
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
class QLabel;
class QLineEdit;
class QCheckBox;
class QPushButton;

class findClient : public QDialog
{
    Q_OBJECT

public:
    findClient( QWidget* parent = 0, const char* name = 0, bool modal = FALSE, WFlags fl = 0 );
    ~findClient();


protected:

protected slots:
    virtual void languageChange();

};

#endif // _H
