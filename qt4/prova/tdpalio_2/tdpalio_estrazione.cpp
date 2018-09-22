//
// C++ Implementation: tdpalio_estrazione
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
#include <qcanvas.h>
#include <qlabel.h>
#include "imageitem.h"

#include <qsound.h>

#include <iostream>

void TDPalio::visualizzaEstrazione() {
    eventLabel->setText("Estrazione delle Contrade");
    eventLabel->show();

    estrazione(1);
    /*
    QCanvas *canvas = new QCanvas(centralFrame);
    canvas->resize(centralFrame->width(), centralFrame->height());
    QCanvasView *cv = new QCanvasView(canvas, centralFrame);
    cv->resize(centralFrame->width(), centralFrame->height());
    cv->setVScrollBarMode(QScrollView::AlwaysOff);
    cv->setHScrollBarMode(QScrollView::AlwaysOff);

    // mostra immagine palazzo comunale
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
}
    cv->show();
    */
    cout << "******** ESTRAZIONE ********" << endl;
    for(int i=0; i<10; i++) {
        cout << barberi[i].getContrada()->getNome()<< endl;
    }
}
