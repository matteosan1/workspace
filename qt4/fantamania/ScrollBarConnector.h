#ifndef SCROLLBARCONNECTOR_H
#define SCROLLBARCONNECTOR_H
#include <QObject>
#include <QScrollBar>

class ScrollBarConnector : public QObject {
  Q_OBJECT

 public:
  ScrollBarConnector(QScrollBar *bar1, QScrollBar *bar2);

  protected slots:
  void bar1_changed(int value);
  void bar2_changed(int value);

 private:
  QScrollBar *_bar1, *_bar2;
};

#endif
