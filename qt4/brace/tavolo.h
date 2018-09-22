/****************************************************************************
** Form interface generated from reading ui file 'tavolo.ui'
**
** Created: Sun May 6 13:25:49 2007
**      by: The User Interface Compiler ($Id: qt/main.cpp   3.3.7   edited Aug 31 2005 $)
**
** WARNING! All changes made in this file will be lost!
****************************************************************************/

#ifndef NEWTAVOLO_H
#define NEWTAVOLO_H

#include <qvariant.h>
#include <qdialog.h>
#include "oggetti.h"

class QVBoxLayout;
class QHBoxLayout;
class QGridLayout;
class QSpacerItem;
class QLabel;
class QLineEdit;
class QSpinBox;
class QComboBox;
class QPushButton;

class NewTavolo : public QDialog
{
    Q_OBJECT

public:
    NewTavolo( QWidget* parent = 0, const char* name = 0, bool modal = FALSE, WFlags fl = 0 );
    ~NewTavolo();

    QLabel* labelNumero;
    QLabel* labelPosti;
    QLabel* labelPosizione;
    QLineEdit* editNumero;
    QSpinBox* spinPosti;
    QComboBox* comboPosizione;
    QPushButton* buttonOK;
    QPushButton* buttonCancel;

    Tavolo tavolo;

public slots:
    virtual void accept();

protected:
    QHBoxLayout* NewTavoloLayout;
    QVBoxLayout* layout7;
    QSpacerItem* spacer6;
    QHBoxLayout* layout6;
    QSpacerItem* spacer5;
    QVBoxLayout* layout5;
    QVBoxLayout* layout4;
    QHBoxLayout* layout1;
    QSpacerItem* spacer1;
    QHBoxLayout* layout3;
    QSpacerItem* spacer3;
    QSpacerItem* spacer2;
    QSpacerItem* spacer4;

protected slots:
    virtual void languageChange();

private:
    void init();

};

#endif // NEWTAVOLO_H
