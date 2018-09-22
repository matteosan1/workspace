#ifndef UTILITIES_H
#define UTILITIES_H

#include <qsqldatabase.h>
#include <qstring.h>

inline int GenerateId(const QString &table, QSqlDatabase *db) {
  QSqlQuery query(db);
  query.exec("select max(indice) from " + table);
  query.next();
  return query.value(0).toInt() + 1;
}

#endif
