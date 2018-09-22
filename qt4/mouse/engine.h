#ifndef ENGINE_H
#define ENGINE_H

#include <QObject>
#include <QVector>

#include "mouse.h"

class Engine : public QObject {
  Q_OBJECT

 public:
  Engine();

  void start(QVector<Mouse*>);
  void move();

  qreal getSpeed(int i) { return speeds[i]; };

 public slots:
  void updatePos();

 private:
  QVector<qreal> speeds;
  QVector<qreal> acc;
  QVector<Mouse*> mouses;
};

#endif
