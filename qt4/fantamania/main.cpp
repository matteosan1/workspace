
#include <QApplication>
#include "fanta.h"


int main(int argc, char *argv[]) {

  //Q_INIT_RESOURCE(application);

  QApplication app(argc, argv);
  
  FantaDialog *window = new FantaDialog();
  
  window->show();
  return app.exec();
}
