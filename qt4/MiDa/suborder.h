
#ifndef SUBORDER_H
#define SUBORDER_H

#include "order.h"

class QSqlDatabase;
class QSqlCursor;
class QStringList;
class order_db;

class subOrder : public Order {
   
Q_OBJECT

 public:
  subOrder(int id, QWidget* parent=0, const char* name=0);
  subOrder(QWidget* parent=0, const char* name=0);
  ~subOrder();

  void init();
  void createNewOrder();
  void FillCombo();
  void FillBuffer();
  void FillDialog(int id);
  void calculateTotPrice();	

  protected slots:
  void accept();
  void reject();
  void newRow();
  void deleteRow();
  void valueChanged(int, int);
  
  private:
  QSqlDatabase *db;
  //QSqlCursor *sqlCursor;
  QStringList *lista_cd;
  int orderId;
  bool newOrder;
  int index_clienti[1000];// usare vettori meglio perche` resizable
  int index_cd[1000];
  int rows;
  order_db *wrap;
};

#endif
