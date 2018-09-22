#ifndef ENGINE_H
#define ENGINE_H

#include <QObject>

class VoceSindaco : public QObject {
  Q_OBJECT

 public:
  VoceSindaco();
  ~VoceSindaco() {};

  caricaSuoni(QString, QString);

 public slots:
  void playSound();

 private:
  QVector<QString> numeri;
  QVector<QString> nomi;
  int counter;
};

#endif
