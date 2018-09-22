#include <QApplication>
#include <QInputDialog>

#include "tdpalioclient.h"

int main(int argc, char* argv[]) {

  QApplication app(argc, argv);

  TDPalioClient *mainDialog = new TDPalioClient();
  //app.setMainWidget(mainDialog);
  mainDialog->show();
  return app.exec();
}
