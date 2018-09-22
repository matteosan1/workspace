#ifndef MYDATATABLE_H
#define MYDATATABLE_H

#include <qdatatable.h>

class MyDataTable : public QDataTable {

 public:

  MyDataTable(QWidget *parent = 0, const char *name = 0 );
  ~MyDataTable();

  void paintField(QPainter * p, const QSqlField* field, const QRect & cr, bool 
		  selected );

  // void paintCell(QPainter *p, int row, int col, const QRect & cr, bool selected, const QColorGroup & cg);

};

#endif
