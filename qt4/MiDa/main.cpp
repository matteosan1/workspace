#include <qapplication.h>
#include <qsqldatabase.h>
#include <qinputdialog.h>

#include "mida.h"

bool createConnection() {
 
  QString text;
  //for(int i=0; i<3; i++) {
  //  text = QInputDialog::getText("MIcrosuoni DAtabase", 
//"Enter DB password:", 
//			       QLineEdit::Password, 
//QString::null);
//    if (!text.isEmpty() ) {
      QSqlDatabase *db = QSqlDatabase::addDatabase("QMYSQL3", "MICROSUONI");
      db->setDatabaseName("microsuoni");
      db->setUserName("root");
      //db->setPassword(text);
	db->setPassword("fisica");
      db->setHostName("localhost");

      if (db->open()) {
	return true;
      }
 //   }  
//  }
  
  return false;
}

int main(int argc, char* argv[]) {

  QApplication app(argc, argv);
  
  if (!createConnection())
    return 1;
  
  mida *mainDialog = new mida();
  app.setMainWidget(mainDialog);
  mainDialog->show();
  return app.exec();
}
