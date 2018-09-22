#ifndef ORDER_DB_H
#define ORDER_DB_H

#include <qdatetime.h>

#include <vector>

class QSqlDatabase;
class QSqlRecord;
class QString;

class order_db {

 public:
  order_db(QSqlDatabase *d);
  ~order_db() {};

  void write();
  void update(int id);
  void FillBuffer(QSqlRecord* b);
  void read(int id);

  int indice, quantita, indice_cliente, indirizzo, pagamento;
  int pagato, spedito, euroiva, porto, aspetto, colli;
  float prezzo, spedizione, spedizione_vera, sconto, peso;
  std::vector<int> indice_CD, quantita_unitaria;
  std::vector<float> prezzo_unitario;
  std::vector<QString> codice;
  QString trasporto, nota;
  QDate data_invio, date;
    
 private:
  QSqlDatabase *db;
};

#endif
