/****************************************************************************
** Form interface generated from reading ui file 'messaggio.ui'
**
** Created: Sun Jun 17 16:55:56 2007
**      by: The User Interface Compiler ($Id: qt/main.cpp   3.3.7   edited Aug 31 2005 $)
**
** WARNING! All changes made in this file will be lost!
****************************************************************************/

#ifndef MESSAGGIO_H
#define MESSAGGIO_H

#include <qvariant.h>
#include <qdialog.h>

class QVBoxLayout;
class QHBoxLayout;
class QGridLayout;
class QSpacerItem;
class QLabel;
class QPushButton;
class QListView;
class QListViewItem;

class Messaggio : public QDialog
{
    Q_OBJECT

public:
    Messaggio( QWidget* parent = 0, const char* name = 0, bool modal = FALSE, WFlags fl = 0 );
    ~Messaggio();

    QLabel* contradaLabel;
    QLabel* capitanoLabel;
    QPushButton* leggiButton;
    QListView* messaggiList;
    QPushButton* okButton;

public slots:
    virtual void InserisciMessaggio( QString mex, bool check );

protected:
    QVBoxLayout* MessaggioLayout;
    QVBoxLayout* layout86;
    QVBoxLayout* layout84;
    QHBoxLayout* layout83;
    QSpacerItem* spacer22;
    QSpacerItem* spacer22_2;
    QVBoxLayout* layout81;
    QHBoxLayout* layout85;
    QSpacerItem* spacer24;
    QSpacerItem* spacer25;

protected slots:
    virtual void languageChange();

private:
    void init();

};

#endif // MESSAGGIO_H
