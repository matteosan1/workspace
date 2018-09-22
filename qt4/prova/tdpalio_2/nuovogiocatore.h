/****************************************************************************
** Form interface generated from reading ui file 'nuovogiocatore.ui'
**
** Created: Sun Jun 17 16:55:56 2007
**      by: The User Interface Compiler ($Id: qt/main.cpp   3.3.7   edited Aug 31 2005 $)
**
** WARNING! All changes made in this file will be lost!
****************************************************************************/

#ifndef NUOVOGIOCATORE_H
#define NUOVOGIOCATORE_H

#include <qvariant.h>
#include <qdialog.h>
#include <vector>
#include "giocatore.h"

class QVBoxLayout;
class QHBoxLayout;
class QGridLayout;
class QSpacerItem;
class QLabel;
class QLineEdit;
class QCheckBox;
class QComboBox;
class QPushButton;

class NuovoGiocatore : public QDialog
{
    Q_OBJECT

public:
    NuovoGiocatore( QWidget* parent = 0, const char* name = 0, bool modal = FALSE, WFlags fl = 0 );
    ~NuovoGiocatore();

    QLabel* cognomeLabel;
    QLabel* nomeLabel;
    QLineEdit* nomeEdit;
    QLineEdit* cognomeEdit;
    QCheckBox* randomCheck;
    QComboBox* contradaCombo;
    QPushButton* okButton;
    QPushButton* cancellaButton;

    virtual Giocatore getGiocatore();

public slots:
    virtual void enableCombo( int state );
    virtual void accept();
    virtual void setContrade( QStringList lista, vector<int> index );
    virtual int assegnaContrada();

protected:
    QVBoxLayout* NuovoGiocatoreLayout;
    QVBoxLayout* layout6;
    QSpacerItem* spacer5;
    QHBoxLayout* layout3;
    QSpacerItem* spacer6;
    QGridLayout* layout1;
    QVBoxLayout* layout2;
    QHBoxLayout* layout4;
    QSpacerItem* spacer1;
    QSpacerItem* spacer3;
    QSpacerItem* spacer4;

protected slots:
    virtual void languageChange();

private:
    vector<int> indice;
    Giocatore g;

};

#endif // NUOVOGIOCATORE_H
