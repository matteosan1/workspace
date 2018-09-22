#include "groupboxcontrol.h"
#include <iostream>

using namespace std;

groupBoxControl::groupBoxControl(QWidget *parent, const char *name) : QButtonGroup(parent, name) {

  theStatus = 0;
}

int groupBoxControl::status() const {
  return theStatus;
}

void groupBoxControl::getStatus() {
  theStatus = QButtonGroup::selectedId();
}

void groupBoxControl::setStatus(int id) {
  theStatus = id;
  QButtonGroup::setButton(id);
}







