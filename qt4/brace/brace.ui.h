/****************************************************************************
** ui.h extension file, included from the uic-generated form implementation.
**
** If you want to add, delete, or rename functions or slots, use
** Qt Designer to update this file, preserving your code.
**
** You should not define a constructor or destructor in this file.
** Instead, write your code in functions called init() and destroy().
** These will automatically be called by the form's constructor and
** destructor.
*****************************************************************************/

#include "braciere.h"
#include "tavolo.h"
#include "subprenotazioni.h"

#include<iostream>

void brace::fileNew() {
    NewBraciere br;
    if (br.exec() == QDialog::Accepted) {
        ilBraciere.inizio = br.inizio;
        ilBraciere.fine = br.fine;
        ilBraciere.nome = br.nome;
        int diff = ilBraciere.inizio.daysTo(ilBraciere.fine);
        ilBraciere.leCene.resize(diff);
    } else {
        // pensare ad un messaggio di errore "Braciere non creato"
    }
}


//manca il menu per modificare e/o eliminare un tavolo 
// aggiungere e/o modificare i tavoli solo per determinate date ????
// possibilita` di aggiungere giorni al braciere (in caso di pioggia o giri rimandati ????

void brace::editTavolo() {
    NewTavolo t;
    if (t.exec() == QDialog::Accepted) {
        ilBraciere.iTavoli.push_back(t.tavolo); // inutile ???????
        for(unsigned int i=0; i<ilBraciere.leCene.size(); i++) 
            ilBraciere.leCene[i].push_back(t.tavolo);
    } else {
        // "Tavolo non creato"
    }
}

void brace::editPrenotazione() {
    subprenotazioni p(&ilBraciere, this, "B");
    if (p.exec() == QDialog::Accepted) {
    } else {
        // prenotazioni non cambiate
    }
}

void brace::fileOpen() {

}


void brace::fileSave() {

}


void brace::fileSaveAs() {

}


void brace::filePrint() {

}


void brace::fileExit() {

}


void brace::editUndo()
{

}


void brace::editRedo()
{

}


void brace::editCut()
{

}


void brace::editCopy()
{

}


void brace::editPaste()
{

}


void brace::editFind()
{

}


void brace::helpIndex()
{

}


void brace::helpContents()
{

}


void brace::helpAbout()
{

}
