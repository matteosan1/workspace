#include "mouse.h"

#include <QGraphicsScene>
#include <QPainter>
#include <QStyleOption>

#include <math.h>

static const double Pi = 3.14159265358979323846264338327950288419717;
static double TwoPi = 2.0 * Pi;

static qreal normalizeAngle(qreal angle) {
  while (angle < 0)
    angle += TwoPi;
  while (angle > TwoPi)
    angle -= TwoPi;
  return angle;
}

Mouse::Mouse()
  : angle(0), speed(0), mouseEyeDirection(0) {
  // FIXME questo puo` essere utile per la mossa
  //rotate(qrand() % (360 * 16));
  // FIXME questo ancora non lo so se e` utile
  //startTimer(1000 / 33);
}

QRectF Mouse::boundingRect() const {
  // FIXME questo in teoria no dovrebbe servire
  
  qreal adjust = 0.5;
  return QRectF(-15 - adjust, -15 - adjust,
		15 + adjust, 15 + adjust);
  
}

QPainterPath Mouse::shape() const {
  // FIXME come prima non credo che serva
  
  QPainterPath path;
  path.addRect(-15, -15, 15, 15);
  return path;
}

void Mouse::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *) {
  painter->drawImage(QPointF(0,0), QImage(":istrice.png"));
}

void Mouse::movement(qreal speed, int dir) {
    
}

void Mouse::timerEvent(QTimerEvent *) {

  // Don't move too far away
  /*
  QLineF lineToCenter(QPointF(0, 0), mapFromScene(0, 0));
  if (lineToCenter.length() > 10) {
    qreal angleToCenter = ::acos(lineToCenter.dx() / lineToCenter.length());
    if (lineToCenter.dy() < 0)
      angleToCenter = TwoPi - angleToCenter;
    angleToCenter = normalizeAngle((Pi - angleToCenter) + Pi / 2);
    
    if (angleToCenter < Pi && angleToCenter > Pi / 4) {
      // Rotate left
      angle += (angle < -Pi / 2) ? 0.25 : -0.25;
    } else if (angleToCenter >= Pi && angleToCenter < (Pi + Pi / 2 + Pi / 4)) {
      // Rotate right
      angle += (angle < Pi / 2) ? 0.25 : -0.25;
    }
  } else if (::sin(angle) < 0) {
    angle += 0.25;
  } else if (::sin(angle) > 0) {
    angle -= 0.25;
  }
  
  // Try not to crash with any other mice
  QList<QGraphicsItem *> dangerMice = scene()->items(QPolygonF()
						     << mapToScene(0, 0)
						     << mapToScene(-30, -50)
						     << mapToScene(30, -50));
  foreach (QGraphicsItem *item, dangerMice) {
    if (item == this)
      continue;
    
    QLineF lineToMouse(QPointF(0, 0), mapFromItem(item, 0, 0));
    qreal angleToMouse = ::acos(lineToMouse.dx() / lineToMouse.length());
    if (lineToMouse.dy() < 0)
      angleToMouse = TwoPi - angleToMouse;
    angleToMouse = normalizeAngle((Pi - angleToMouse) + Pi / 2);
    
    if (angleToMouse >= 0 && angleToMouse < Pi / 2) {
      // Rotate right
      angle += 0.5;
    } else if (angleToMouse <= TwoPi && angleToMouse > (TwoPi - Pi / 2)) {
      // Rotate left
      angle -= 0.5;
    }
  }
  
  // Add some random movement
  if (dangerMice.size() > 1 && (qrand() % 10) == 0) {
    if (qrand() % 1)
      angle += (qrand() % 100) / 500.0;
    else
      angle -= (qrand() % 100) / 500.0;
  }
  
  speed += (-50 + qrand() % 100) / 100.0;
  
  qreal dx = ::sin(angle) * 10;
  mouseEyeDirection = (qAbs(dx / 5) < 1) ? 0 : dx / 5;
  
  rotate(dx);
  setPos(mapToParent(0, -(3 + sin(speed) * 3)));
  */
}
