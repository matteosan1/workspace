/****************************************************************************
** Form interface generated from reading ui file 'prenotazioni.ui'
**
** Created: Sun May 6 13:25:49 2007
**      by: The User Interface Compiler ($Id: qt/main.cpp   3.3.7   edited Aug 31 2005 $)
**
** WARNING! All changes made in this file will be lost!
****************************************************************************/

#ifndef PRENOTAZIONI_H
#define PRENOTAZIONI_H

#include <qvariant.h>
#include <qdialog.h>
#include <qdatetime.h>
#include "oggetti.h"

class QVBoxLayout;
class QHBoxLayout;
class QGridLayout;
class QSpacerItem;
class QComboBox;
class QTable;
class QPushButton;

class prenotazioni : public QDialog
{
    Q_OBJECT

public:
    prenotazioni( QWidget* parent = 0, const char* name = 0, bool modal = FALSE, WFlags fl = 0 );
    ~prenotazioni();

    QComboBox* comboData;
    QTable* tablePrenotazioni;
    QPushButton* buttonOK;
    QPushButton* buttonCancel;

    QDate fine;
    QDate inizio;
    std::vector< std::vector<Prenotazione> >* pre;

public slots:
    virtual void cambioData(int index);

protected:
    QHBoxLayout* prenotazioniLayout;
    QVBoxLayout* layout4;
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
