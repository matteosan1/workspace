/****************************************************************************
** Form interface generated from reading ui file 'tdpalio.ui'
**
** Created: Fri Oct 12 19:43:44 2007
**      by: The User Interface Compiler ($Id: qt/main.cpp   3.3.7   edited Aug 31 2005 $)
**
** WARNING! All changes made in this file will be lost!
****************************************************************************/

#ifndef TDPALIO_H
#define TDPALIO_H

#include <qvariant.h>
#include <qpixmap.h>
#include <qmainwindow.h>
#include <vector>
#include "giocatore.h"
#include "contrada.h"
#include "fantino.h"
#include "cavallo.h"
#include "barbero.h"

class QVBoxLayout;
class QHBoxLayout;
class QGridLayout;
class QSpacerItem;
class QAction;
class QActionGroup;
class QToolBar;
class QPopupMenu;
class QFrame;
class QLabel;
class QToolButton;
class TRandom;

class TDPalio : public QMainWindow
{
    Q_OBJECT

public:
    TDPalio( QWidget* parent = 0, const char* name = 0, WFlags fl = WType_TopLevel );
    ~TDPalio();

    QFrame* centralFrame;
    QLabel* eventLabel;
    QToolButton* toolGoAhead;
    QMenuBar *MenuBar;
    QPopupMenu *fileMenu;
    QPopupMenu *Insersci;
    QPopupMenu *Opzioni;
    QPopupMenu *Aiuto;
    QToolBar *toolBar;
    QToolBar *Toolbar;
    QAction* fileNewAction;
    QAction* fileOpenAction;
    QAction* fileSaveAction;
    QAction* fileSaveAsAction;
    QAction* filePrintAction;
    QAction* fileExitAction;
    QAction* insersciGiocatoreAction;
    QAction* aiutoInformazioniAction;
    QAction* aiutoAiutoAction;
    QAction* opzioniEffetti_sonoriAction;

    enum Mese {Luglio, Agosto, Straordinario};
    enum Fase {eInizio, eEstrazione, eTratta, eProve, eSegnatura, ePalio, eFinePalio};

    virtual int Avversaria( int io );
    virtual bool salvaCorrente();

public slots:
    virtual void controller();
    virtual void formaCavalli();
    virtual QString getData();
    virtual void visualizzaEstrazione();
    virtual void SceltaStrategia();
    virtual void SceltaCavalli();
    virtual void Assegnazione( int * cav );
    virtual void SceltaFantino();
    virtual void Segnatura();
    virtual void RisposteFantini();
    virtual void InserisciPartito();
    virtual void RispostePartiti();
    virtual void Prove();
    virtual void fileNew();
    virtual void caricaFile( const QString & fileName );
    virtual void fileOpen();
    virtual void salvaFile( const QString & fileName );
    virtual bool fileSave();
    virtual bool fileSaveAs();
    virtual void filePrint();
    virtual void closeEvent( QCloseEvent * event );
    virtual void nuovoGiocatore();
    virtual void aiutoInformazioni();
    virtual void estrazione( int n );
    virtual void help();
    virtual void abilitaSuono( bool a );
    virtual void nuovaFase();

protected:
    int ordine_prove[10][6];

    QVBoxLayout* TDPalioLayout;

protected slots:
    virtual void languageChange();

private:
    int nProva;
    Mese mese;
    int anno;
    bool modificato;
    int corrono[10];
    vector<Contrada> contrade;
    vector<Giocatore> giocatori;
    vector<Fantino> fantini;
    vector<Cavallo> cavalli;
    int luglio[17], agosto[17], settembre[17];
    TRandom *random;
    vector<Barbero> barberi;
    QString curFile;
    bool soundWanted;
    Fase fase;

    QPixmap image0;
    QPixmap image1;
    QPixmap image2;
    QPixmap image3;
    QPixmap image4;
    QPixmap image5;

    void init();

};

#endif // TDPALIO_H
