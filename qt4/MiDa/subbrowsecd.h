
#ifndef SUBBROWSECD_H
#define SUBBROWSECD_H

#include "browsecd.h"

class QSqlDatabase;
class QSqlCursor;
class QSqlForm;

class subBrowseCD : public browseCD {
   
Q_OBJECT

 public:
  subBrowseCD(int id, QWidget* parent=0, const char* name=0);
  subBrowseCD(QWidget* parent=0, const char* name=0);
  ~subBrowseCD();

  void init();
  void createNewCD();

  protected slots:
  void accept();
  void reject();
  
  private:
  QSqlDatabase *db;
  QSqlCursor *sqlCursor, *sqlCursor1;
  QSqlForm *sqlForm;
  int cdId;
  bool newCd;
};

#endif
