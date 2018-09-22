#include <QtGui>

#include <QTimer>
#include <QObject>

#include "engine.h"
#include "mouse.h"

#include <math.h>
#include <iostream>

static const int MouseCount = 10;

int main(int argc, char **argv) {
  QApplication app(argc, argv);
  qsrand(QTime(0,0,0).secsTo(QTime::currentTime()));

  QGraphicsScene scene;
  scene.setSceneRect(0, 0, 630, 380);
  scene.setItemIndexMethod(QGraphicsScene::NoIndex);

  QVector<Mouse*> mouses;

  for (int i = 0; i < MouseCount; ++i) {
    mouses.push_back(new Mouse);
    mouses[i]->setPos(20, 25+40*i);
    scene.addItem(mouses[i]);     
  }

  QGraphicsView view(&scene);
  view.setRenderHint(QPainter::Antialiasing);
  //view.setBackgroundBrush(QPixmap(":piazza.png"));
  view.setCacheMode(QGraphicsView::CacheBackground);
  //view.setDragMode(QGraphicsView::ScrollHandDrag);
  view.setWindowTitle(QT_TRANSLATE_NOOP(QGraphicsView, "Tempo di Palio II (prova)"));
  view.resize(630, 380);
  view.show();

  QTimer *timer = new QTimer();

  Engine* e = new Engine();
  QObject::connect(timer, SIGNAL(timeout()), e, SLOT(updatePos()));
  e->start(mouses);
  timer->start(1000);

  return app.exec();
}
