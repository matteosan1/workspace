#include <QApplication>
#include <QInputDialog>

#include "tdpalio.h"

int main(int argc, char* argv[]) {

  QApplication app(argc, argv);

  TDPalio *mainDialog = new TDPalio();
  //app.setMainWidget(mainDialog);
  mainDialog->show();
  return app.exec();
}
