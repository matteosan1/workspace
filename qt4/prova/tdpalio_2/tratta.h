/****************************************************************************
** Form interface generated from reading ui file 'tratta.ui'
**
** Created: Sun Jun 17 16:55:56 2007
**      by: The User Interface Compiler ($Id: qt/main.cpp   3.3.7   edited Aug 31 2005 $)
**
** WARNING! All changes made in this file will be lost!
****************************************************************************/

#ifndef TRATTA_H
#define TRATTA_H

#include <qvariant.h>
#include <qdialog.h>

class QVBoxLayout;
class QHBoxLayout;
class QGridLayout;
class QSpacerItem;
class QTable;
class QPushButton;

class Tratta : public QDialog
{
    Q_OBJECT

public:
    Tratta( QWidget* parent = 0, const char* name = 0, bool modal = FALSE, WFlags fl = 0 );
    ~Tratta();

    QTable* cavalliList;
    QPushButton* okButton;

    virtual int * getSelezione();

public slots:
    virtual void riempiLista( QStringList nomi, QStringList corsi, QStringList vinti, int l );
    virtual void accept();
    virtual void cambiaCaption( QString s );

protected:
    QVBoxLayout* TrattaLayout;
    QHBoxLayout* layout7;
    QSpacerItem* spacer7;
    QSpacerItem* spacer9;

protected slots:
    virtual void languageChange();

private:
    int selezione[21];
    int limite;

    void init();

};

#endif // TRATTA_H
