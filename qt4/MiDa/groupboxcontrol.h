
#ifndef GROUPBOXCONTROL_H
#define GROUPBOXCONTROL_H

#include <qbuttongroup.h>

class groupBoxControl : public QButtonGroup {
   
  Q_OBJECT
  Q_PROPERTY(int stato READ status WRITE setStatus)

 public:
  groupBoxControl(QWidget *parent=0, const char *name=0);
  ~groupBoxControl() {};

  int status() const;
  void setStatus(int id);
  void getStatus();

  private:
  int theStatus;
};

#endif
