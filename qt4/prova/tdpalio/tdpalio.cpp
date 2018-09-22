#include "tdpalio.h"

#include "utility.h"
#include "nuovogiocatore.h"
#include "TRandom.h"

#include <QMessageBox>
#include <QFileDialog>
#include <QInputDialog>
#include <QSound>

#include <iostream>
using namespace std;

TDPalio::TDPalio(QWidget* parent) : QMainWindow(parent) {

    ui.setupUi(this);
    setWindowTitle("Tempo di Palio II");

    // signals and slots connections
    connect(ui.actionNew, SIGNAL(activated()), this, SLOT(fileNew()));
    connect(ui.actionOpen, SIGNAL(activated()), this, SLOT(fileOpen()));
    connect(ui.actionSave, SIGNAL(activated()), this, SLOT(fileSave()));
    connect(ui.actionSave_As, SIGNAL(activated()), this, SLOT(fileSaveAs()));
    connect(ui.actionPrint, SIGNAL(activated()), this, SLOT(filePrint()));
    connect(ui.actionExit, SIGNAL(activated()), this, SLOT(close()));
    connect(ui.actionInserisci_Giocatore, SIGNAL(activated()), this, SLOT(nuovoGiocatore()));
    //connect(ui.aiutoInformazioniAction, SIGNAL(activated()), this, SLOT(aiutoInformazioni()));
    //connect(ui.aiutoAiutoAction, SIGNAL(activated()), this, SLOT(help()));
    connect(ui.actionEffetti_sonori, SIGNAL(toggled(bool)), this, SLOT(abilitaSuono(bool)));
    connect(ui.actionAvanti, SIGNAL(activated()), this, SLOT(nuovaFase()));

    if (QSound::isAvailable())
        soundWanted  = true;
    else {
        QMessageBox::warning(this,"No Sound",
                             "<p><b>Sorry, no sound device available.</b>");

        ui.actionEffetti_sonori->setChecked(false);
        ui.actionEffetti_sonori->setEnabled(false);
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

    QFile file("setup.dat");
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QMessageBox::critical(0, "TDPalio ERROR !",
                              "Errore irreversibile. TDPalio non riesce a trovare il file setup.dat.");
        abort();
    }

    QTextStream fin(&file);

    for(int i=0; i<17; ++i)
        fin >> contrade[i];
    for(int i=0; i<16; ++i)
        fin >> fantini[i];
    for(int i=0; i<21; ++i)
        fin >> cavalli[i];
    file.close();
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
                // FIXME Prima scelta del fantino (tutte le contrade devono avere un fantino prima di ogni prova
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
        anno = QInputDialog::getInteger(this, QString("TDPalio"),
                                        QString("Anno d'inizio: "),
                                        2000, 1650, 10000);

       //mese = 1;
        estrazione(0);
        nuovoGiocatore();
        modificato = true;
        statusBar()->showMessage(getData());
        controller();
    }
}

void TDPalio::caricaFile(const QString& fileName) {
    curFile = fileName;
    int m, f;

    QFile file(fileName);
    QTextStream in(&file);
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

    for(int i=0; i<10; ++i) {
        in >> barberi[i];
        barberi[i].setContrada(&contrade[barberi[i].getIndice(0)]);
        barberi[i].setFantino(&fantini[barberi[i].getIndice(1)]);
        barberi[i].setCavallo(&cavalli[barberi[i].getIndice(2)]);
    }

    //in.close();
}

void TDPalio::fileOpen() {

    QString fileFilters = "TDPalio files (*.pal);; Tutti (*.*)";
    if (salvaCorrente()) {
        QString fileName = QFileDialog::getOpenFileName(this, tr("Load File"), "/home/sani/data", fileFilters);

        if (!fileName.endsWith(".pal"))
            fileName = fileName + ".pal";

        if (!fileName.isEmpty()) {
            caricaFile(fileName);

            QString mex = "Anno: " + QString::number(anno) + "\n";
            for(int i=0; i<giocatori.size(); i++)
                mex += giocatori[i].nomeCompleto() + " capitano: " + contrade[giocatori[i].contrada()].getNome() + "\n";

            QMessageBox::information(this, "TDPalio Info", mex);

           //FIXME aggiungere possibilita di togliere giocatori
            statusBar()->showMessage(getData());
        }
    }
}

void TDPalio::salvaFile(const QString& fileName) {

    modificato = false;
    QFile file(fileName);

    QTextStream out(&file);
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
    for(int i=0; i<giocatori.size(); i++)
        out << giocatori[i];
    for(int i=0; i<17; i++)
        out << contrade[i];
    for(int i=0; i<21; i++)
        out << cavalli[i];
    out << fantini.size() << " \n";
    for(int i=0; i<fantini.size(); i++)
        out << fantini[i];

    for(int i=0; i<10; ++i)
        out << barberi[i];

    //out.close();
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
    QString fileFilters = "TDPalio files (*.pal);; Tutti (*.*)";
    QString fileName = QFileDialog::getOpenFileName(this, tr("Save File"), "/home/sani/data", fileFilters);

    if (!fileName.endsWith(".pal"))
        fileName = fileName + ".pal";

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

void TDPalio::close() {

    salvaCorrente();
    QMainWindow::close();
}

void TDPalio::nuovoGiocatore() {

    QStringList lista;
    QVector<int> indice;
    for(int i=0; i<17; i++) {
        bool gioca = false;
        for(int j=0; j<giocatori.size(); j++)
            if (giocatori[j].contrada() == i)
                gioca = true;
        if (!gioca) {
            indice.push_back(i);
            lista.append(contrade[i].getNome());
        }
    }

    NuovoGiocatoreDialog ng(this);
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
    int con[17], sorte[17];
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
                for(int i=0; i<17; i++) {
                corrono[i] = luglio[i];
                sorte[i] = corrono[i];
                }
                if (mese == Agosto)
                    for(int i=0; i<17; i++) {
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

void TDPalio::abilitaSuono(bool a) {
    soundWanted = a;
}

void TDPalio::nuovaFase() {
    int f = (int)fase;
    f++;
    fase = (Fase)f;
    controller();
}
