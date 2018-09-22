/****************************************************************************
** Form interface generated from reading ui file 'prenotazioni.ui'
**
** Created: Fri May 4 20:39:05 2007
**      by: The User Interface Compiler ($Id: qt/main.cpp   3.3.7   edited Aug 31 2005 $)
**
** WARNING! All changes made in this file will be lost!
****************************************************************************/

#ifndef PRENOTAZIONI_H
#define PRENOTAZIONI_H

#include <qvariant.h>
#include <qdialog.h>

class QVBoxLayout;
class QHBoxLayout;
class QGridLayout;
class QSpacerItem;
class QComboBox;
class QListView;
class QListViewItem;
class QPushButton;

class prenotazioni : public QDialog
{
    Q_OBJECT

public:
    prenotazioni( QWidget* parent = 0, const char* name = 0, bool modal = FALSE, WFlags fl = 0 );
    ~prenotazioni();

    QComboBox* comboData;
    QListView* listPrenotazioni;
    QPushButton* buttonO;
    QPushButton* buttonCancel;

protected:
    QVBoxLayout* prenotazioniLayout;
    QVBoxLayout* layout10;
    QHBoxLayout* layout8;
    QSpacerItem* spacer7;
    QHBoxLayout* layout9;
    QSpacerItem* spacer9;
    QSpacerItem* spacer10;
    QSpacerItem* spacer11;

protected slots:
    virtual void languageChange();

};

#endif // PRENOTAZIONI_H
