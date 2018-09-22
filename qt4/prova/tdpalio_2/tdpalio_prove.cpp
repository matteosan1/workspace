//
// C++ Implementation: tdpalio_prove
//
// Description:
//
//
// Author: Matteo Sani <matteo.sani@cern.ch>, (C) 2007
//
// Copyright: See COPYING file that comes with this distribution
//
//

#include "tdpalio.h"
#include "strategiaprove.h"
#include "utility.h"

#include <qmessagebox.h>

#include <qdatetime.h>
#include <iostream>

void TDPalio::SceltaFantino() {

    int status[fantini.size()];
    for(unsigned int i=0; i<fantini.size(); ++i)
        status[i] = 0;

    for(int z=0; z<10; z++) {
        int gioc = barberi[z].getContrada()->giocatore();
        if (gioc != -1) {
            QStringList c, f;
            int status[fantini.size()];

            QString monta = "";
            if (barberi[z].getFantino() != 0)
                monta = barberi[z].getFantino()->getNome();

            for(int i=0; i<10; i++)
                if (i != gioc)
                    c.append(barberi[i].getContrada()->getNome());

            for(unsigned int i=0; i<fantini.size(); i++) {
                f.append(fantini[i].getNome());
                std::cout << fantini[i].correper() << std::endl;
                if (fantini[i].correper() != -1)
                    status[i] = 1;
            }

            StrategiaProve strp(this, "prove");
            strp.FillCombo(f, c, &barberi[z], status);
            strp.exec();
        } else {

            int faiOfferte = 3;
            bool giaFantino = false;
            bool inAttesa = false;

            // rete neurale per scelta fantino e scelta strategia per ogni prova
            // in realta` dovrebbe ritornare un vettore di probilita`
            int scelta = (QTime::currentTime().msec() % 21);

            if (barberi[z].getFantino() != 0)
                giaFantino = true;

            for(unsigned int i=0; i<fantini.size(); ++i) {
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
            //for(int i<0; i<faiOfferte; ++i)
                fantini[scelta].setOfferta(z, -1, fantini[scelta].prezzo(), -1);
        }
    }

    RisposteFantini();
}

void TDPalio::Segnatura() {

    for(int i=0; i<10; i++) {

        if (barberi[i].getFantino()->prontezza() == -1) {
            //segnaFantino = new SegnaFantino(barberi[i].getContrada()-$
            int ret = 0;//DialogBox(GetModuleHandle(NULL), MAKEINTRESOURC$
            if (ret == 0) {
                Fantino* f = barberi[i].getFantino();
                string nome = f->getNome();
                int a, b, c;
                a = Uniform_symmetric(5, 5, random);
                b = Uniform_symmetric(5, 5, random);
                c = Uniform_symmetric(5, 5, random);

                //fantini[nFantini].creaFantino(nome, a, b, c, f->corre$
                //nFantini++;
                //barberi[i].setFantino(&fantini[nFantini]);
            }
        }
    }
}

void TDPalio::RisposteFantini() {

    // calcola risposte
    // magari cambia feeling a secondo delle risposte

    for(unsigned int i=0; i<fantini.size(); i++) {

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

                QMessageBox::warning(0, "TDPalio News !", s);
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
                    QMessageBox::information(0, "TDPalio ERROR !", s);
                }

                fantini[i].clearOfferte(num[0]);
                fantini[i].setContrada(chi);
                barberi[chi].setFantino(&fantini[i]);
            }
        }
    }
}

void TDPalio::Prove() {

    // visualizzare in qualche modo l'ordine di ingresso per la prova
    // aggiungere che uno puo` mandare via un fantino perche` non compatibile con il cavallo

    for(int z=0; z<10; z++) {
        int gioc = barberi[z].getContrada()->giocatore();
        if (gioc != -1) {
            //strategiaProve = new StrategiaProve(io, s, c);
        }
        else {
            // semplice decisione per la strategia per le prove
            // incremento massimo ~30% ovvero 6% a prova
            // se forma > 75% lascia stare
            // se >50% prova 2 volte
            // <50% prova 4 volte
            // se < 30% tutte
            // ad ogni prova check delle precedenti con il risultato e conseguente decisione
        }
    }
}
