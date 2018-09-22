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
#include "nuovogiocatore.h"
#include "utility.h"
//#include "tratta.h"
#include "helpbrowser.h"
//#include "strategiaprove.h"

#include <qmessagebox.h>
#include <qfiledialog.h>
#include <qinputdialog.h>
//#include <qcanvas.h>
//#include <qtextedit.h>
//#include "imageitem.h"

#include <qsound.h>

#include <fstream>
#include <iostream>

using namespace std;

void TDPalio::init() {

    if (QSound::isAvailable())
        soundWanted  = true;
    else {
        QMessageBox::warning(this,"No Sound",
                "<p><b>Sorry, no sound device available.</b>");

        opzioniEffetti_sonoriAction->setOn(false);
        opzioniEffetti_sonoriAction->setEnabled(false);
        soundWanted = false;
    }
    modificato = false;
    curFile = "";
    random = new TRandom(1001);
    mese = Luglio;
    fase = eEstrazione;
    nProva = 0;
    anno = 2007;
    contrade.resize(17);
    fantini.resize(16);
    cavalli.resize(21);
    barberi.resize(10);

    if (!QFile::exists("setup.dat")) {
	QMessageBox::critical(0, "TDPalio ERROR !",
			      "Errore irreversibile. TDPalio non riesce a trovare il file setup.dat.");
	abort();
    }

    ifstream fin("setup.dat");
    for(int i=0; i<17; ++i)
	   fin >> contrade[i];
    for(int i=0; i<16; ++i)
	   fin >> fantini[i];
    for(int i=0; i<21; ++i)
	   fin >> cavalli[i];
    fin.close();
}

void TDPalio::controller() {

    switch(fase) {
        case eInizio:
            break;
        case eEstrazione:
            switch(mese) {
                case Luglio:
                    for(int i=0; i<10; i++)
	                   barberi[i].setContrada(&contrade[luglio[i]]);
                break;
                case Agosto:
                    for(int i=0; i<10; i++)
	                   barberi[i].setContrada(&contrade[agosto[i]]);
                    break;
                case Straordinario:
                    for(int i=0; i<10; i++)
	                   barberi[i].setContrada(&contrade[settembre[i]]);
                    break;
                }
            visualizzaEstrazione();
            break;
        case eTratta:
            SceltaCavalli();
            SceltaStrategia();
            formaCavalli();
            break;
        case eProve:
            if (nProva == 0) {
                // Prima scelta del fantino (tutte le contrade devono avere un fantino prima di ogni prova
                SceltaFantino();
            }
            nProva++;
            Prove();
            InserisciPartito();
            SceltaFantino();
            break;
        case eSegnatura:
            Segnatura();
            break;
        case ePalio:
            break;
        case eFinePalio:
            break;
        }

    //for(int prove=0; prove<6; prove++) {
    //    Prove();
    //    InserisciPartito();
    //    SceltaFantino(prove);
    //}

    //Carriera
}

QString TDPalio::getData() {
    QString s = "Palio del ";

    switch(mese) {
        case Luglio:
            s += "2 Luglio ";
            break;
        case Agosto:
            s += "16 Agosto ";
            break;
        case Straordinario:
            // scegliere giorno e mese casuali
            s += "17 Settembre ";
            break;
    }
    s += QString::number(anno);
    return s;
}

void TDPalio::InserisciPartito() {

    for(int z=0; z<10; z++) {           // partiti per quelle che non$

        int gioc = barberi[z].getContrada()->giocatore();
        if (gioc != -1) {

            string c1[10], c2[17];
            int io1 = -1;//, io2 = -1;
            for(int i=0; i<10; i++) {

                if (barberi[i].getContrada()->giocatore() == gioc) {
                    io1 = i;
                    continue;
                }
                c1[i] = barberi[i].getContrada()->getNome();
            }
           for(int i=0; i<17; i++) {

                //if (barberi[z].getContrada()->getNome() == contrade[i$
                //    io2 = i;
                //    continue;
                //}
                c2[i] = contrade[i].getNome();
            }

            //nuovoPartito = new NuovoPartito(io1, io2, barberi[z], c1,$
            //int ret = DialogBox(GetModuleHandle(NULL), MAKEINTRESOURC$

            //if (ret == IDOK) {


            //}
        }
        else {
            // c'� bisogno della rete neurale per i partiti fatti dal$
        }
    }
   RispostePartiti();
}

void TDPalio::RispostePartiti() {

    for(int z=0; z<10; z++) {
        // raccogli le i partiti relativi ad ogni contrada e proponil$
    }
}

bool TDPalio::salvaCorrente() {
    if (modificato) {
	int ret = QMessageBox::warning(this, "TDPalio Avvertimento",
				       "Sei andato avanti nel giuoco.\nVuoi salvare i cambiamenti ?",
	QMessageBox::Yes | QMessageBox::Default,
	QMessageBox::No,
	QMessageBox::Cancel | QMessageBox::Escape);

	if (ret == QMessageBox::Yes)
	    return fileSave();
	else if (ret == QMessageBox::Cancel)
	    return false;
    }
    return true;
}

void TDPalio::fileNew() {

    if (salvaCorrente()) {
	   anno = QInputDialog::getInteger("TDPalio",
		  		            "Anno d'inizio:",
				            anno, 1650, 10000);

	   //mese = 1;
	   estrazione(0);
	   nuovoGiocatore();
	   modificato = true;
       eventLabel->setText(getData());
	   controller();
    }
}

void TDPalio::caricaFile(const QString& fileName) {
    curFile = fileName;
    int m, f;
    ifstream in(fileName);
    in >> anno;
    in >> m;
    mese = (Mese)m;
    in >> f;
    fase = (Fase)f;
    in >> nProva;
    for(int i=0; i<17; i++)
        in >> luglio[i];
    for(int i=0; i<17; i++)
        in >> agosto[i];
    for(int i=0; i<17; i++)
        in >> settembre[i];

    int nGiocatori, nFantini;
    in >> nGiocatori;
    giocatori.resize(nGiocatori);
    for(int i=0; i<nGiocatori; i++)
        in >> giocatori[i];
    for(int i=0; i<17; i++)
        in >> contrade[i];
    for(int i=0; i<21; i++)
        in >> cavalli[i];

    in >> nFantini;
    fantini.resize(nFantini);
    for(int i=0; i<nFantini; i++)
        in >> fantini[i];

    in.close();
}

void TDPalio::fileOpen() {

    QString fileFilters = "TDPalio files (*.pal)\nTutti (*.*)";
    if (salvaCorrente()) {
	QString fileName = QFileDialog::getOpenFileName(".", fileFilters, this);
	if (!fileName.isEmpty()) {
	    caricaFile(fileName);

	    QString mex = "Anno: " + QString::number(anno) + "\n";
	    for(unsigned int i=0; i<giocatori.size(); i++)
		mex += giocatori[i].nomeCompleto() + " capitano: " + contrade[giocatori[i].contrada()].getNome() + "\n";

	    QMessageBox::information(this, "TDPalio Info", mex);

	    //aggiungere possibilita di togliere giocatori
        eventLabel->setText(getData());
	}
    }
}

void TDPalio::salvaFile(const QString& fileName) {

    modificato = false;
    ofstream out(fileName);
    out << anno << '\n';
    out << mese << '\n';
    out << fase << '\n';
    out << nProva << '\n';
    for(int i=0; i<17; i++)
        out << luglio[i] << " ";
    out << "\n";
    for(int i=0; i<17; i++)
        out << agosto[i] << " ";
    out << "\n";
    for(int i=0; i<17; i++)
        out << settembre[i] << " ";
    out << "\n";
    out << giocatori.size() << '\n';
    for(unsigned int i=0; i<giocatori.size(); i++)
        out << giocatori[i];
    for(unsigned int i=0; i<17; i++)
        out << contrade[i];
    for(int i=0; i<21; i++)
        out << cavalli[i];
    out << fantini.size() << " \n";
    for(unsigned int i=0; i<fantini.size(); i++)
        out << fantini[i];

    out.close();
}

bool TDPalio::fileSave() {
    if (curFile.isEmpty()) {
	return fileSaveAs();
    } else {
	salvaFile(curFile);
	return true;
    }
}

bool TDPalio::fileSaveAs() {
    QString fileFilters = "TDPalio files (*.pal)\nTutti (*.*)";
    QString fileName = QFileDialog::getSaveFileName(".", fileFilters, this);

    if (fileName.isEmpty())
	return false;
    if (QFile::exists(fileName)) {
	int ret = QMessageBox::warning(this, "TDPalio Avvertimento",
				       tr("Il giuoco %1 esiste gia`.\nVuoi sovrascrivere ?").arg(QDir::convertSeparators(fileName)), QMessageBox::Yes | QMessageBox::Default,
				       QMessageBox::No | QMessageBox::Escape);
	if (ret == QMessageBox::No)
	    return false;
    }

    if (!fileName.isEmpty())
	salvaFile(fileName);
    return true;
}

void TDPalio::filePrint() {

}

void TDPalio::closeEvent(QCloseEvent *event) {
    if (salvaCorrente()) {
	//salva i settings
	event->accept();
    } else
	event->ignore();
}

void TDPalio::nuovoGiocatore() {

    QStringList lista;
    vector<int> indice;
    for(int i=0; i<17; i++) {
	bool gioca = false;
	for(unsigned int j=0; j<giocatori.size(); j++)
	    if (giocatori[j].contrada() == i)
		gioca = true;
	if (!gioca) {
	    indice.push_back(i);
	    lista.append(contrade[i].getNome());
	}
    }

    NuovoGiocatore ng(this, "Nuovo Giocatore");
    ng.setContrade(lista, indice);

    if (ng.exec() == QDialog::Accepted) {
 	giocatori.push_back(ng.getGiocatore());
	contrade[giocatori[giocatori.size()-1].contrada()].setGiocatore(giocatori.size()-1);
	QString mex = giocatori[giocatori.size()-1].nome() + " " + giocatori[giocatori.size()-1].cognome() +
		      " e` stato eletto Capitano della " + contrade[giocatori[giocatori.size()-1].contrada()].getNomeCompleto()+"\n";
	QMessageBox::information(this, "TDPalio Info", mex);
    }
}


void TDPalio::aiutoInformazioni() {
    QMessageBox::about(this, tr("Informazioni TDPalio"),
                       tr("<h2>TDPalio 2.0</h2>"
                          "<p>Copyright &copy 2007 MatteoSoftware<br>"
                          "<p>TDPalio e` il gioco manageriale del Palio di Siena"));

}

void TDPalio::estrazione(int n) {
    int con[17], sorte[10];
    switch(n) {
        case 0:
            OrdinaI(17, con, random);

            for(int i=0; i<17; i++)
                luglio[i] = con[i];

            OrdinaI(17, con, random);
            for(int i=0; i<17; i++)
                agosto[i] = con[i];

            for(int i=0; i<17; i++)
                settembre[i] = 0;
            break;
        case 1:
            if (mese == Luglio)
                for(int i=0; i<10; i++) {
                    corrono[i] = luglio[i];
                    sorte[i] = corrono[i];
                }
            if (mese == Agosto)
                for(int i=0; i<10; i++) {
                    corrono[i] = agosto[i];
                    sorte[i] = corrono[i];
                }
            for(int i=0; i<7; i++) {
                if (mese == Luglio)
                    luglio[i] = luglio[i+10];
                else
                    agosto[i] = agosto[i+10];
            }

            Ordina(10, sorte, random);
            for(int i=0; i<10; i++) {
                if (mese == Luglio)
                    luglio[i+7] = sorte[i];
               else
                    agosto[i+7] = sorte[i];
            }
            break;
        case 2:
            OrdinaI(17, settembre, random);
            break;
    }
}

void TDPalio::help() {
    HelpBrowser::showPage("index.html");
}


void TDPalio::abilitaSuono(bool a) {
    soundWanted = a;
}

void TDPalio::nuovaFase() {
    int f = (int)fase;
    f++;
    fase = (Fase)f;
    controller();
}
