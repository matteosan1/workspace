#include "engine.h"

Engine::Engine() {
  acc.resize(10);
  speeds.resize(10);
  mouses.resize(0);

  for(int i=0; i<10; i++)
    speeds[i] = 0;
  
}

void Engine::move() {

  for(int i=0; i<10; i++) {
    speeds[i] += acc[i];
    if (speeds[i] > 40) {
      speeds[i] = 40;
      acc[i] = 0;
    }
  }
}

void Engine::start(QVector<Mouse*> m) {

  mouses = m;
  for(int i=0; i<10; i++) {
    acc[i] = (5+i*2);
  }
}

void Engine::updatePos() {
  
  move();
  for(int i=0; i<10; i++) {
    mouses[i]->moveBy(getSpeed(i), 0);
  }
}
