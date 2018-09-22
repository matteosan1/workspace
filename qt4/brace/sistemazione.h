/****************************************************************************
** Form interface generated from reading ui file 'sistemazione.ui'
**
** Created: Sun May 6 13:25:49 2007
**      by: The User Interface Compiler ($Id: qt/main.cpp   3.3.7   edited Aug 31 2005 $)
**
** WARNING! All changes made in this file will be lost!
****************************************************************************/

#ifndef SISTEMAZIONE_H
#define SISTEMAZIONE_H

#include <qvariant.h>
#include <qdialog.h>

class QVBoxLayout;
class QHBoxLayout;
class QGridLayout;
class QSpacerItem;
class QPushButton;
class QLabel;
class QComboBox;
class QListView;
class QListViewItem;

class sistemazione : public QDialog
{
    Q_OBJECT

public:
    sistemazione( QWidget* parent = 0, const char* name = 0, bool modal = FALSE, WFlags fl = 0 );
    ~sistemazione();

    QPushButton* buttonAuto;
    QLabel* labelData;
    QComboBox* comboData;
    QListView* listTavoli;
    QListView* listPrenotazioni;
    QPushButton* buttonOK;
    QPushButton* buttonCancel;

protected:
    QHBoxLayout* sistemazioneLayout;
    QVBoxLayout* layout4;
    QHBoxLayout* layout1;
    QSpacerItem* spacer1;
    QSpacerItem* spacer2;
    QSpacerItem* spacer3;
    QHBoxLayout* layout3;
    QHBoxLayout* layout2;
    QSpacerItem* spacer5;
    QSpacerItem* spacer5_2;
    QSpacerItem* spacer5_3;

protected slots:
    virtual void languageChange();

};

#endif // SISTEMAZIONE_H
