#include "ScrollBarConnector.h"

ScrollBarConnector::ScrollBarConnector(QScrollBar *bar1, QScrollBar* bar2):
  QObject(), _bar1(bar1), _bar2(bar2) {

  //_bar2->hide();
  _bar2->setVisible(false);
  connect(_bar1, SIGNAL(valueChanged(int)), this, SLOT(bar1_changed(int)));
  connect(_bar2, SIGNAL(valueChanged(int)), this, SLOT(bar2_changed(int)));
}

void ScrollBarConnector::bar1_changed(int value) {

  _bar2->setValue(value);
}

void ScrollBarConnector::bar2_changed(int value) {

  _bar1->setValue(value);
}
