#include "tdpalio.h"

#include "utility.h"
#include "tratta.h"

#include <iostream>

using namespace std;

void TDPalio::SceltaCavalli() {
    statusBar()->showMessage("I capitani si riuniscono per la scelta dei cavalli...");

    int *selezione_giocatore;
    int cav[21], cav2[10], cav1[21], fascia[21];
    float media[21];
    OrdinaI(21, cav, random);

    for(int i=0; i<21; i++)
        media[i] = cavalli[i].media();

    OrdinaF_fixed(21, cav1, media);

    for(int i=0; i<21; i++) {
        for(int j=0; j<21; j++) {
            if (cav[i] == cav1[j]) {
                if (j < 7)
                    fascia[i] = 2;
                else if (j>14)
                    fascia[i] = 0;
                else
                    fascia[i] = 1;
            }
        }
    }

    // DECIDERE 334 o 055 in base alla strategia della contrada
    //for(int i=0; i<21; i++) {
//  cout << cav[i] << " " << cavalli[cav[i]].getNome() << "  " << cavalli[cav[i]].media() << "  " << fascia[i] << endl;
//    }

    int voti[21], selezione[21];
    // per il momento le volte non sono considerate
    int volte = 0, totale = 0;

    //for(int i=0; i<21; i++)
    //    selezione[i] = 0;

    while(1) {
        for(int i=0; i<21; i++)
            voti[i] = 0;

        for(int c=0; c<10; ++c) {

            if (contrade[corrono[c]].giocatore() != -1) {
                QStringList nomi, corsi, vinti;

                for(int j =0; j<21; j++) {
                    if (selezione[j] == 0) {
                        // aggiungere icona sulle capacita` del cavallo
                        // avvertire quanti cavalli devi ancora scegliere
                        nomi.append(cavalli[cav[j]].getNome());
                        corsi.append(QString::number(cavalli[cav[j]].paliCorsi()));
                        vinti.append(QString::number(cavalli[cav[j]].paliVinti()));
                    }
                }

                TrattaDialog t(&cavalli);
                //t.cambiaCaption(contrade[corrono[c]].getNomeCompleto());
                t.exec();

                QVector<int> selezione = t.getSelection();

                for(int j=0; j<selezione.size(); j++)
                    voti[selezione[j]]++;
            } else {
                int strategia[3];
                strategia[0] = 3; strategia[1] = 3; strategia[2] = 4;
                int scelte = 10 - totale;
                while (scelte > 0) {
                    for(int j=0; j<21; j++) {
                        if (selezione[j] == 0) {
                            if (strategia[fascia[j]] != 0) {
                                int center = 50 - cavalli[cav[j]].paliCorsi() + cavalli[cav[j]].paliVinti()*5;
                                int punti = random->Integer(100);
                                if (punti > center) {
                                    voti[j]++;
                                    strategia[fascia[j]]--;
                                    scelte--;
                                }
                            }
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

            if (voti[i] < 2)
                selezione[i] = -1;
            if (totale == 10)
                break;
        }

        //for(int i=0; i<21; i++)
        //    cout << cavalli[cav[i]].getNome() << "  " << voti[i] << endl;

        if (totale == 10)
            break;

        volte++;
    }

    int y=0;
    for(int i=0; i<21; i++)  {
        if (selezione[i] == 1)  {
            cav2[y] = cav[i];
            //cout << cavalli[cav[i]].getNome() << "  " << fascia[i] << "  " << voti[i]<< endl;
            y++;
        }
    }

    Assegnazione(cav2);
}

void TDPalio::Assegnazione(int* cav) {
    statusBar()->showMessage("Assegnazione");

    /*
    QCanvas *canvas = new QCanvas(centralFrame);
    canvas->resize(centralFrame->width(), centralFrame->height());
    QCanvasView *cv = new QCanvasView(canvas, centralFrame);
    cv->resize(centralFrame->width(), centralFrame->height());
    cv->setVScrollBarMode(QScrollView::AlwaysOff);
    cv->setHScrollBarMode(QScrollView::AlwaysOff);

    // mostra immagine griglie
    ImageItem *i = new ImageItem(QPixmap("./pictures/lupa_1.png"), canvas);
    i->show();

    if (soundWanted)
        QSound::play("./sound/chiarine.wav");
    ImageItem *bandiere[10];
    for(int i=0; i<10; ++i) {
    QString s = "./pictures/" + barberi[i].getContrada()->getNome() + "_1.png";
    bandiere[i] = new ImageItem(QPixmap(s), canvas);
    bandiere[i]->move(10*i, 0);
    bandiere[i]->show();

    cv->show();
    */

    cout << "******** ASSEGNAZIONE **********" << endl;

    int n1[10], n2[10];
    OrdinaI(10, n1, random);
    OrdinaI(10, n2, random);

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

void TDPalio::formaCavalli() {
    for(int i=0; i<10; i++) {
        float f = random->Gaus(50, 20);
        barberi[i].setForma((int)f);
    }
}

int TDPalio::Avversaria(int io) {
    for(int i=0; i<10; i++) {
        if (contrade[io].avversaria() == corrono[i])
            return corrono[i];
    }
    return -1;
}

void TDPalio::SceltaStrategia() {
    // separare tabella strategia...
    //Strategia strategia;
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
