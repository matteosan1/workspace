/****************************************************************************
** Form interface generated from reading ui file 'braciere.ui'
**
** Created: Sun May 6 13:25:49 2007
**      by: The User Interface Compiler ($Id: qt/main.cpp   3.3.7   edited Aug 31 2005 $)
**
** WARNING! All changes made in this file will be lost!
****************************************************************************/

#ifndef NEWBRACIERE_H
#define NEWBRACIERE_H

#include <qvariant.h>
#include <qdialog.h>
#include <qdatetime.h>

class QVBoxLayout;
class QHBoxLayout;
class QGridLayout;
class QSpacerItem;
class QLabel;
class QLineEdit;
class QDateEdit;
class QPushButton;

class NewBraciere : public QDialog
{
    Q_OBJECT

public:
    NewBraciere( QWidget* parent = 0, const char* name = 0, bool modal = FALSE, WFlags fl = 0 );
    ~NewBraciere();

    QLabel* labelNome;
    QLineEdit* editNome;
    QLabel* labelInizio;
    QDateEdit* dateInizio;
    QLabel* labelFine;
    QDateEdit* dateFine;
    QPushButton* buttonOK;
    QPushButton* buttonCancel;

    QDate inizio;
    QDate fine;
    QString nome;

public slots:
    virtual void accept();

protected:
    QHBoxLayout* NewBraciereLayout;
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

private:
    void init();

};

#endif // NEWBRACIERE_H
