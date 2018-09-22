#include <qapplication.h>
#include <qsqldatabase.h>
#include <qsqlcursor.h>

#include <iostream>

int main( int argc, char *argv[] )
{
  QApplication app( argc, argv, FALSE );
  
  QSqlDatabase *defaultDB = QSqlDatabase::addDatabase("QMYSQL3");
  defaultDB->setDatabaseName("palio");
  defaultDB->setUserName("root");
  defaultDB->setPassword("fisica");
  defaultDB->setHostName("localhost");
  
  if ( defaultDB->open() ) {
    // Database successfully opened; we can now issue SQL commands.
    std:: cout << "ALE" << std::endl;
  }
  else {
    qWarning("Failed to open database: " + defaultDB->lastError().text());
    return 1;
  }
  
  QSqlQuery query("select * from masgalani", defaultDB);
  if (query.isActive())
    while (query.next()) 
      std::cout << query.value(0).toString() << "  " << query.value(1).toString() << std::endl;
  
  QSqlCursor cur("masgalani");
  cur.select("data = '2003'");
  while(cur.next()) {
    qDebug(cur.value("contrada").toString());
  }





  return 0;
}
