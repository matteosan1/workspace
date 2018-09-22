#include "TRandom.h"
#include "fantino.h"
#include "contrada.h"
#include "cavallo.h"
#include "barbero.h"
#include "utility.h"

#include <QTime>

#include <iostream>

using namespace std;

enum Fase {eInizio, eEstrazione, eTratta, eProve, eSegnatura, ePalio, eFinePalio};
enum Mese {Luglio, Agosto, Straordinario};

Fase fase;
QVector<Barbero> barberi;
TRandom *ran;
int luglio[17], agosto[17], settembre[17];
QVector<Cavallo> cavalli;
QVector<Fantino> fantini;
QVector<Contrada> contrade;
int corrono[17];
Mese mese;
int nProva;
int ordine_prove[6][10];

void estrazione(int n) {
    qDebug("estrazione");
    int con[17], sorte[17];
    switch(n) {
        case 0:
            OrdinaI(17, con, ran);

            for(int i=0; i<17; i++)
                luglio[i] = con[i];

            OrdinaI(17, con, ran);
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

                    Ordina(10, sorte, ran);
                    for(int i=0; i<10; i++) {
                        if (mese == Luglio)
                            luglio[i+7] = sorte[i];
                        else
                            agosto[i+7] = sorte[i];
                    }
                    break;
        case 2:
            OrdinaI(17, settembre, ran);
            break;
    }
}

void formaCavalli() {
    qDebug("forma");
    for(int i=0; i<21; i++) {
        float f = ran->Gaus(50, 20);
        cavalli[i].setForma((int)f);
    }
}

void Assegnazione(int* cav) {
    qDebug("Assegnazione");

    int n1[10], n2[10];
    OrdinaI(10, n1, ran);
    OrdinaI(10, n2, ran);

    for(int i=0; i<10; i++) {
       // visualizzazione assegnazione
        //cout << barberi[n1[i]].getContrada()->getNome() << "  " << cavalli[cav[n2[i]]].getNome() << endl;
        barberi[n1[i]].setCavallo(&cavalli[cav[n2[i]]]);
    }

    for(int i=0; i<10; i++) {
        ordine_prove[i][0] = corrono[i];                //estrazione
        ordine_prove[i][1] = corrono[9-i];
        ordine_prove[i][2] = corrono[n2[i]];            //assegnazione
        ordine_prove[i][3] = corrono[n2[9-i]];
        for(int j=0; j<10; j++) {
            if (n1[j] == i)
                ordine_prove[i][4] = corrono[n2[j]];    // numero d'orecchio
            if (n1[j] == 9-i)
                ordine_prove[i][5] = corrono[n2[j]];
        }
    }
}

int Avversaria(int io) {
    qDebug("Avversaria");
    for(int i=0; i<10; i++) {
        if (contrade[io].avversaria() == corrono[i])
            return corrono[i];
    }
    return -1;
}

void SceltaCavalli() {

    qDebug("I capitani si riuniscono per la scelta dei cavalli...");

    int cav[21], cavalli_scelti[10], cav1[21], fascia[21], forma[21];
    float media[21];

    // Da il numero di coscia per la tratta
    OrdinaI(21, cav, ran);
    //for(int i=0; i<21; ++i)
    //    cav[i] = i;

    // Assegna un numero di fascia ad ogni cavallo
    // ordinare per fascia+formafisica
    for(int i=0; i<21; i++)
        media[i] = cavalli[i].media();

    OrdinaF_fixed(21, cav1, media);

    for(int i=0; i<21; ++i)
        if (j < 7)
            fascia[i] = 2;
        else if (j>14)
            fascia[i] = 0;
        else
            fascia[i] = 1;

    for(int i=0; i<21; ++i)
        forma[i] = cavalli[cav1].forma();

    for(int i=0; i<20; ++i)
        for(int j=i+i; j<21; ++j)
            if ((forma[i] < forma[j]) &&
                 (fascia[i] == fascia[j])) {
                int temp = cav1[i];
                cav1[i] = cav1[j];
                cav1[j] = temp;

                temp = forma[i];
                forma[i] = forma[j];
                forma[j] = temp;

                temp = fascia[i];
                fascia[i] = fascia[j];
                fascia[j] = temp;
            }

    //TODO DECIDERE 334 o 055 in base alla strategia della contrada

    //for(int i=0; i<21; i++) {
    //  cout << cav[i] << " " << cavalli[cav[i]].getNome() << "  " << cavalli[cav[i]].media() << "  " << fascia[i] << endl;
    //}

    int voti[21], selezione[21];
    int volte = 0, totale = 0;

    //for(int i=0; i<21; i++)
    //    selezione[i] = 0;

    int strategia[3];
    while(1) {
        for(int i=0; i<21; i++)
            voti[i] = 0;

        for(int c=0; c<10; ++c) {
            strategia[0] = 3; strategia[1] = 3; strategia[2] = 4;
            //int scelte = 10 - totale;

            while (strategia[0] + strategia[1] + strategia[2] != 0) {
                for(int i=0; i<21; ++i) {
                    if (strategia[fascia[i]] > 0) {
                        // tira un numero casuale dipendente dalla forma
                        if (punti > center) {
                            voti[j]++;
                            strategia[fascia[i]]--;
                        }
                    }
                }
            }
        }

        totale = 0;
        for(int i=0; i<21; i++)  {
            if (voti[i] > 5) {
                selezione[i] = 1;
                totale++;
            }
       }

       std::cout << totale << std::endl;
       //for(int i=0; i<21; i++)
       //    cout << cavalli[cav[i]].getNome() << "  " << voti[i] << endl;

       if (totale == 10)
           break;

       volte++;
    }

    int y=0;
    for(int i=0; i<21; i++)  {
        if (selezione[i] == 1)  {
            cavalli_scelti[y] = cav[i];
            //cout << cavalli[cav[i]].getNome() << "  " << fascia[i] << "  " << voti[i]<< endl;
            y++;
        }
    }

    Assegnazione(cavalli_scelti);
}

void SceltaStrategia() {
    qDebug("scelta strategia");
    for(int i=0; i<10; i++) {

        float media1, media2;
        int cuffia1, cuffia2;

        int avversaria = Avversaria(corrono[i]);
        barberi[i].setAvversaria(avversaria);

        media1 = barberi[i].getCavallo()->media();
        cuffia1 = barberi[i].getContrada()->cuffia();

        if (avversaria != -1) {
            media2 = barberi[avversaria].getCavallo()->media();
            cuffia2 = barberi[avversaria].getContrada()->cuffia();
        } else {
            media2 = 0;
            cuffia2 = 0;
        }

        int amici = 0;
        for(int j=0; j<10; j++)
            if (j == i)
                continue;
        else
            if (barberi[i].getContrada()->feeling(barberi[j].getContrada()->indice()) > 6)
                amici++;

        int rate1, rate2;
        rate1 = Strategia(cuffia1, media1);
        if (media2 != 0)
            rate2 = Strategia(cuffia2, media2);
        else
            rate2 = -1;

        if ((rate1 && 1) && (rate2 & 8)) {
            barberi[i].setStrategia(0);
            continue;
        }

        if ((rate1 & 12) && (amici > 2)) {
            barberi[i].setStrategia(3);
            continue;
        }

        barberi[i].setStrategia(rate1);
    }
}

void RisposteFantini() {
    qDebug("risposte fantini");
    // calcola risposte
    // magari cambia feeling a secondo delle risposte

    for(int i=0; i<fantini.size(); i++) {

        float decisione[17];
        int num[fantini[i].nOfferte()];

        if (fantini[i].nOfferte() != 0) {
            for(unsigned int j=0; j<fantini[i].nOfferte(); j++) {

                // manca rete neurale per decidere delle offerte
                // per ora dai un punteggio casuale alle offerte e scegli la/le migliori
            }

            OrdinaF_fixed(fantini.size(), num, decisione);

            // se niente maggiore di 0.5 prende tempo
            // se i primi due entro 10% prende tempo
            // se gia` fantino nuova offerta maggiore del 20%

            // diminuisce in funzione delle prova il limite ?????
            if (decisione[0] < 0.5)
                continue;

            float aumento = (float)(decisione[0]-decisione[1])/(float)(decisione[1]);
            if ((fantini[i].correper() != -1) && (aumento > 0.2)) {
                // prendi in considerazione il cambio di fantino
            }

            if ((fantini[i].correper() == 0) && (aumento < 0.1)) {

                int chi1 = fantini[i].getOfferta(num[0]).getChi();
                int chi2 = fantini[i].getOfferta(num[1]).getChi();
                int g1 = barberi[chi1].getContrada()->giocatore();
                int g2 = barberi[chi2].getContrada()->giocatore();

                QString s = "Il fantino ";
                s += fantini[i].getNome();
                s += " avverte i capitani delle seguenti contrade non sono sufficienti:\n";
                if (g1 != -1)
                    s += barberi[chi1].getContrada()->getNomeCompleto() + "\n";
                if (g2 != -1)
                    s += barberi[chi2].getContrada()->getNomeCompleto() + "\n";

                qDebug((const char*)s.toLatin1());
                fantini[i].clearOfferte(num[0], num[1]);
            }

            if ((fantini[i].correper() == 0) && (aumento >= 0.1)) {

                int chi = fantini[i].getOfferta(num[0]).getChi();
                int g = barberi[chi].getContrada()->giocatore();
                if (g != -1) {
                    // avverte la contrada interessata che ha accettato
                    QString s = "Il fantino " + fantini[i].getNome();
                    s += " avverte il capitano della " + barberi[chi].getContrada()->getNomeCompleto();
                    s += " che accetta l'offerta !!!";
                    qDebug((const char*)s.toLatin1());
                }

                fantini[i].clearOfferte(num[0]);
                fantini[i].setContrada(chi);
                barberi[chi].setFantino(&fantini[i]);
            }
        }
    }

}


void SceltaFantino() {
     qDebug("scelta fantino");
    int status[fantini.size()];
    for(int i=0; i<fantini.size(); ++i)
        status[i] = 0;

    for(int z=0; z<10; z++) {
        int faiOfferte = 3;
        bool giaFantino = false;
        bool inAttesa = false;

        // rete neurale per scelta fantino e scelta strategia per ogni prova
        // in realta` dovrebbe ritornare un vettore di probilita`
        int scelta = (QTime::currentTime().msec() % 21);

        if (barberi[z].getFantino() != 0)
            giaFantino = true;

        for(int i=0; i<fantini.size(); ++i) {
            if (fantini[i].nOfferte() == 2) {
                for(unsigned int j=0; j<2; ++j) {
                    Offerta a = fantini[i].getOfferta(j);
                    if (a.getChi() == z) {
                        inAttesa = true;
                        break;
                    }
                }
            }
        }

        if (inAttesa)
            faiOfferte = 0;

        if ((giaFantino) && (faiOfferte)) {
            // fare il for su tutte le scelte e vedere se ci sono fantini disponibili
            // migliori del mio e accessibili economicamente
        }

        // mettere un peso ai soldi in base alla disponibilita` ed alla prova
        // for(int i<0; i<faiOfferte; ++i)
        //     fantini[scelta].setOfferta(z, -1, fantini[scelta].prezzo(), -1);
    }

    RisposteFantini();
}

void Prove() {
    qDebug("prova");
    // chiamare scelta fantino ????
    // visualizzare in qualche modo l'ordine di ingresso per la prova
    // aggiungere che uno puo` mandare via un fantino perche` non compatibile con il cavallo

    int status[fantini.size()];
    for(int i=0; i<fantini.size(); ++i)
        status[i] = 0;

    for(int z=0; z<10; z++) {
            // semplice decisione per la strategia per le prove
            // incremento massimo ~30% ovvero 6% a prova
            // se forma > 75% lascia stare
            // se >50% prova 2 volte
            // <50% prova 4 volte
            // se < 30% tutte
            // ad ogni prova check delle precedenti con il risultato e conseguente decisione
    }

}

void RispostePartiti() {
    qDebug("Risposte Partiti");
    for(int z=0; z<10; z++) {
        // raccogli i partiti relativi ad ogni contrada e proponil$
    }
}


void InserisciPartito() {
    qDebug("Inerisci Partiti");
    for(int z=0; z<10; z++) {           // partiti per quelle che non corrono ?????

    }

    RispostePartiti();
}

void Segnatura() {
    qDebug("segnatura");
    for(int i=0; i<10; i++) {

        if (barberi[i].getFantino()->prontezza() == -1) {
            QString label = "Nome di battaglia per il fantino della " + barberi[i].getContrada()->getNomeCompleto() + ": ";

            while (1) {
                bool ok;
    /*
                QString nome = QInputDialog::getText("TDPalio",
                label, QLineEdit::Normal,
                QString::null, &ok, this);

                if (ok && !nome.isEmpty()) {
                int a = Uniform_symmetric(5, 5, random);
                int b = Uniform_symmetric(5, 5, random);
                int c = Uniform_symmetric(5, 5, random);
                    // secondo me non funziona
                    //f->creaFantino(fantini.size(), nome, a, b, c, i);
                break;
            }
    */
            }
        }
    }
}

