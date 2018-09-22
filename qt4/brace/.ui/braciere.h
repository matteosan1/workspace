/****************************************************************************
** Form interface generated from reading ui file 'braciere.ui'
**
** Created: Fri May 4 20:39:05 2007
**      by: The User Interface Compiler ($Id: qt/main.cpp   3.3.7   edited Aug 31 2005 $)
**
** WARNING! All changes made in this file will be lost!
****************************************************************************/

#ifndef BRACIERE_H
#define BRACIERE_H

#include <qvariant.h>
#include <qdialog.h>

class QVBoxLayout;
class QHBoxLayout;
class QGridLayout;
class QSpacerItem;
class QLabel;
class QLineEdit;
class QDateEdit;
class QPushButton;

class braciere : public QDialog
{
    Q_OBJECT

public:
    braciere( QWidget* parent = 0, const char* name = 0, bool modal = FALSE, WFlags fl = 0 );
    ~braciere();

    QLabel* labelNome;
    QLineEdit* editNome;
    QLabel* labelInizio;
    QDateEdit* dateInizio;
    QLabel* labelFine;
    QDateEdit* dateFine;
    QPushButton* buttonOK;
    QPushButton* buttonCancel;

protected:
    QHBoxLayout* braciereLayout;
    QVBoxLayout* layout14;
    QSpacerItem* spacer17;
    QSpacerItem* spacer19;
    QHBoxLayout* layout13;
    QSpacerItem* spacer18;
    QHBoxLayout* layout12;
    QSpacerItem* spacer16;
    QHBoxLayout* layout11;
    QSpacerItem* spacer14;
    QSpacerItem* spacer13;
    QSpacerItem* spacer15;

protected slots:
    virtual void languageChange();

};

#endif // BRACIERE_H
