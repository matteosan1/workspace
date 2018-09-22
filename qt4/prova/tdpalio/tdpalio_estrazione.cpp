#include "tdpalio.h"

//#include "imageitem.h"

/*
#include <q3canvas.h>
#include <qlabel.h>
//Added by qt3to4:
#include <QPixmap>
#include "imageitem.h"
#include <QSound>
*/

#include <QGraphicsScene>
#include <QGraphicsPixmapItem>
#include <QSound>

#include <iostream>
using namespace std;

void TDPalio::visualizzaEstrazione() {

    int posx[17] = {140, 190, 240, 290, 340, 390, 440, 490, 550, 625, 190, 240, 290, 340, 390, 440, 490};
    int posy[17] = {440, 440, 440, 440, 440, 440, 440, 440, 440, 440, 220, 220, 220, 220, 220, 220, 215};

    statusBar()->showMessage("Estrazione delle Contrade");
    //ui.label->show();

    estrazione(1);

    QGraphicsPixmapItem* bandiere[17];
    QGraphicsScene* scene = new QGraphicsScene(ui.frame);

    for(int i=0; i<17; ++i) {
        QString s = ":/estrazione/pictures/" + contrade[corrono[i]].getNome() + "_1.gif";
        bandiere[i] = scene->addPixmap(s);
        bandiere[i]->setPos(posx[i], posy[i]);
    }
    scene->setSceneRect(0, 0, 906, 616);

    ui.graphicsView->setScene(scene);
    ui.graphicsView->setRenderHint(QPainter::Antialiasing);
    ui.graphicsView->setBackgroundBrush(QPixmap(":/estrazione/pictures/palazzo_comunale.jpg"));
    //view.setCacheMode(QGraphicsView::CacheBackground);
    //view.setDragMode(QGraphicsView::ScrollHandDrag);
    // FIXME dimensioni rispetto
    ui.graphicsView->scale((float)ui.graphicsView->width()/906., (float)ui.graphicsView->height()/616.);
    ui.graphicsView->show();

    for(int i=0; i<7; ++i)
        bandiere[i]->show();
    //if (soundWanted)
    //    QSound::play("./sound/chiarine.wav");
    //sleep(10);

    for(int i=7; i<10; ++i) {
        bandiere[i]->show();
        //sleep(3);
    }
}
