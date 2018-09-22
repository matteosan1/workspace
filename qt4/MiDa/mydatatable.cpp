#include "mydatatable.h"

#include <qrect.h>
#include <qpainter.h>
#include <qimage.h>
#include <qsqlfield.h>

#include <iostream>

MyDataTable::MyDataTable(QWidget *parent, const char *name)
  :QDataTable(parent, name) {}

MyDataTable::~MyDataTable() 
{}

void MyDataTable::paintField(QPainter * p, const QSqlField* field, const QRect & cr, bool selected ) {
 
  QString status;
  if ((field->name() == "pagato") || (field->name() == "spedito")) {
    if (field->value() == 1) {
      p->setPen(QColor(255,255,255));
      p->setBrush(QColor(0,255,0));
      status = "OK";
    } else {
      p->setPen(QColor(255,255,255));
      p->setBrush(QColor(255,0,0));
      status = "???";
    }

    p->drawRect(0,0, cr.width(), cr.height());
    p->drawText( 2,2, cr.width()-4, cr.height()-4, Qt::AlignVCenter|Qt::AlignHCenter, status);  
  }
  else 
    QDataTable::paintField(p, field, cr, selected);
}

/*
void MyDataTable::paintField(QPainter *p, int row, int col, const QRect & cr, bool selected, const QColorGroup & cg) {
  if ((col != 4) && (col != 5)) {
    QDataTable::paintCell(p, row, col, cr, selected, cg);
  } else {

    p->setPen(QColor(255,0,0));
    p->setBrush(QColor(0,100,0));
    p->drawRect(0,0, cr.width(), cr.height());
    QDataTable::painCell(p, row, col, cr, selected, cg);
  }
}
*/
