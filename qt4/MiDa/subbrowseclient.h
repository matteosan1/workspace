
#ifndef SUBBROWSECLIENT_H
#define SUBBROWSECLIENT_H

#include "browseclient.h"

class QSqlDatabase;
class QSqlCursor;
class QSqlForm;

class subBrowseClient : public browseClient {
   
Q_OBJECT

 public:
  subBrowseClient(int id, QWidget* parent=0, const char* name=0);
  subBrowseClient(QWidget* parent=0, const char* name=0);
  ~subBrowseClient();

  void init();
  void createNewClient();

  protected slots:
  void accept();
  void reject();
  
  private:
  QSqlDatabase *db;
  QSqlCursor *sqlCursor;
  QSqlForm *sqlForm;
  int clientId;
  bool newClient;
};
#endif
