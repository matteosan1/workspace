#include "order_db.h"

#include <qsqldatabase.h>
#include <qsqlcursor.h>
#include <qstring.h>

order_db::order_db(QSqlDatabase *d):db(d)
{}

void order_db::write() {
  
  QSqlCursor cur("ordine_riepilogo", true, db);
  QSqlRecord *buffer = cur.primeInsert();
  FillBuffer(buffer);
  cur.insert();
}

void order_db::update(int id) {

  QSqlCursor cur("ordine_riepilogo", true, db);
  cur.select("indice = '" + QString::number(id)+"'");
  if (cur.next()) {
    QSqlRecord *buffer = cur.primeUpdate();
    FillBuffer(buffer);
    cur.update();
  }
}

void order_db::FillBuffer(QSqlRecord *buffer) {

  buffer->setValue("indice", indice);
  //buffer->setValue("fatture", indice); ????? mettere autoincrement nel db
  buffer->setValue("data", date);
  buffer->setValue("quantita", quantita);
  buffer->setValue("indice_cliente", indice_cliente);
  buffer->setValue("indirizzo", indirizzo);
  buffer->setValue("pagamento", pagamento);
  buffer->setValue("prezzo", prezzo);
  buffer->setValue("spedizione", spedizione);
  buffer->setValue("spedizione_vera", spedizione_vera);
  buffer->setValue("sconto", sconto);
  buffer->setValue("nota", nota);
  buffer->setValue("pagato", pagato);
  buffer->setValue("spedito", spedito);
  buffer->setValue("euriova", euroiva);
  buffer->setValue("porto", porto);
  buffer->setValue("aspetto", aspetto);
  buffer->setValue("colli", colli);
  buffer->setValue("peso", peso);
  buffer->setValue("data_invio",data_invio);
  buffer->setValue("trasporto", trasporto);
}

void order_db::read(int id) {
  
  QSqlCursor cur("ordine_riepilogo", true, db);
  cur.select("indice = '" + QString::number(id)+"'");
  /*
  if (cur.next()) {
 
    indice = cur->value("indice", indice);
    //fattura = cur->value("fatture", indice); ????? mettere autoincrement nel db
    date = cur->value("data").toDate();
    quantita = cur->value("quantita").toInt();
    indice_cliente = cur->value("indice_cliente").toInt();
    indirizzo = cur->value("indirizzo").toInt();
    pagamento = cur->value("pagamento").toInt();
    prezzo = cur->value("prezzo").toDouble();
    spedizione = cur->value("spedizione").toDouble();
    spedizione_vera = cur->value("spedizione_vera").toDouble();
    sconto = cur->value("sconto").toDouble();
    nota = cur->value("nota").toString();
    pagato = cur->value("pagato").toInt();
    spedito = cur->value("spedito").toInt();
    euroiva = cur->value("euriova").toInt();
    porto = cur->value("porto").toInt();
    aspetto = cur->value("aspetto").toInt();
    colli = cur->value("colli").toInt();
    peso = cur->value("peso").toDouble();
    data_invio = cur->value("data_invio").toDate();
    trasporto = cur->value("trasporto").toString();
  }
  */
}
