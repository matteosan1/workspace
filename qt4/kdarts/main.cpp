#include <QApplication>

#include "InsertPlayerDialog.h"

int main(int argc, char *argv[]) {

  QApplication app(argc, argv);
  InsertPlayerDialog* insert = new InsertPlayerDialog();
  insert->exec();

  // chiama il dialog per la scelta del gioco
  // mettere insieme a quello sopra ?
  // chiamare il dialog del segnapunti
  // chiamare i tabelloni (1 per giocatore)

  //FantaDialog *window = new FantaDialog();

  //window->show();
  //return app.exec();
}
