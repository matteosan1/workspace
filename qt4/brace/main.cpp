#include <qapplication.h>
#include <qinputdialog.h>

#include "brace.h"


int main(int argc, char* argv[]) {

  QApplication app(argc, argv);
  
  
  brace *mainDialog = new brace();
  app.setMainWidget(mainDialog);
  mainDialog->show();
  return app.exec();
}
