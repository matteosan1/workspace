#include "suborder.h"
#include "utilities.h"
#include "order_db.h"

#include <qsqldatabase.h>
#include <qsqlpropertymap.h>
#include <qsqlcursor.h>
//#include <qsqlform.h>
#include <qcombobox.h>
#include <qstringlist.h>
#include <qtable.h>
#include <qlineedit.h>
#include <qtextedit.h>
#include <qdatetime.h>
#include <qradiobutton.h>

#include <iostream>
#include <vector>

using namespace std;

subOrder::subOrder(QWidget* parent, const char* name) : Order(parent, name) {

  setCaption(tr("Insert new Order"));
  orderId = -1;
  newOrder = true;
  init();
}

subOrder::subOrder(int id, QWidget* parent, const char* name) : Order(parent, name) {
  setCaption(tr("Update Order"));
  orderId = id;
  newOrder = false;
  init();
}

subOrder::~subOrder() {}

void subOrder::FillCombo() {
  
  orderTable->setColumnWidth(1, 100);
  orderTable->setColumnWidth(2, 100);
  orderTable->setColumnStretchable(0, true);

  int i=0;
  QStringList lista_clienti;
  QSqlQuery query(db);
  query.exec("select indice, cognome, nome from clienti order by cognome, nome");
  if (query.isActive())
    while(query.next()) {
      lista_clienti.append(query.value(1).toString()+" " + query.value(2).toString());
      index_clienti[i] = query.value(0).toInt();
      i++;
    }
  clientCombo->insertStringList(lista_clienti);

  i=0;
  lista_cd = new QStringList();
  query.exec("select indice, artista, titolo from cd order by artista, titolo");
  if (query.isActive())
    while(query.next()) {
      lista_cd->append(query.value(1).toString()+" - " + query.value(2).toString());
      index_cd[i] = query.value(0).toInt();
      i++;
    }
}

void subOrder::newRow() {

  orderTable->insertRows(rows);
  orderTable->setItem(rows, 0, 
  		      new QComboTableItem(orderTable, *lista_cd));
  orderTable->setItem(rows, 1, 
  		      new QTableItem(orderTable, QTableItem::OnTyping, QString::number(1)));
  orderTable->setItem(rows, 2, 
  		      new QTableItem(orderTable, QTableItem::Never, QString::number(0.0)));
  
  rows++;
}

void subOrder::deleteRow() {
  if (rows > 0) {
    cout << rows << endl;
    int selection = orderTable->currentRow();
    orderTable->removeRow(selection);
    rows--;

    calculateTotPrice();
  }
}

void subOrder::valueChanged(int row, int column) {

  if (column == 0) {  

    QComboBox *combo  = (QComboBox*)orderTable->cellWidget(row,0);
    int indice = combo->currentItem();
    
    QSqlQuery query(db);
    query.exec("select prezzo_vendita from cd where indice ='" + QString::number(index_cd[indice])+"'");
    query.next();

    orderTable->item(row,2)->setText(QString::number(query.value(0).toDouble()));
    orderTable->updateCell(row, 2);
  }

  calculateTotPrice();
}

void subOrder::calculateTotPrice() {

  float total = 0;

  for(int i=0; i<rows; i++) {
    double p = orderTable->item(i,1)->text().toInt() * 
      orderTable->item(i,2)->text().toDouble();

    total += p;
  }

  // aggiungere spedizione
  total += shipmentEdit->text().toDouble();
  // togliere spedizione2
  total -= shipment2Edit->text().toDouble();
  // togliere eventuale sconto
  total -= reductionEdit->text().toDouble();
  // calcolare percentuale del VAT

  // aggiornare tutti gli edit
  priceEdit->setText(QString::number(total));
}

void subOrder::init() {

  connect((const QObject*)cancelButton, SIGNAL(clicked()), (const QObject*)this, SLOT(reject()));
  connect((const QObject*)okButton, SIGNAL(clicked()), (const QObject*)this, SLOT(accept()));
  connect((const QObject*)insertButton, SIGNAL(clicked()), (const QObject*) this, SLOT(newRow()));
  connect((const QObject*)deleteButton, SIGNAL(clicked()), (const QObject*) this, SLOT(deleteRow()));
  connect((const QObject*)orderTable, SIGNAL(valueChanged(int, int)), (const QObject*) this, SLOT(valueChanged(int, int)));

  db = QSqlDatabase::database("MICROSUONI");
  wrap = new order_db(db);

  cout << "1" << endl;
  
  FillCombo();
   
  cout << "2" << endl;

  if (orderId == -1)
    createNewOrder();
  else 
    FillDialog(orderId);
}

void subOrder::createNewOrder() {

  orderId = GenerateId("ordine_riepilogo", db);
  rows = 0;
}

void subOrder::accept() {

  FillBuffer();

  if (newOrder) 
    wrap->write();
  else 
    wrap->update(orderId);

  QDialog::accept();

  cout << "3" << endl;

}

void subOrder::reject() {
  QDialog::reject();
}

void subOrder::FillBuffer() {

  wrap->indice = orderId;
  wrap->quantita = rows;
  wrap->indice_cliente = index_clienti[clientCombo->currentItem()];
  wrap->indirizzo = primaryRadio->isChecked();
  wrap->prezzo = priceEdit->text().toDouble();
  wrap->spedizione = shipmentEdit->text().toDouble();
  wrap->spedizione_vera = shipment2Edit->text().toDouble();
  wrap->sconto = reductionEdit->text().toDouble();
  wrap->nota = noteTextEdit->text();

  wrap->date = QDate::currentDate(Qt::LocalTime);
  //wrap->trasporto
  //wrap->data_invio;
  //wrap->pagamento ???
  //wrap->pagato
  //wrap->spedito;
  //wrap->euroiva
  //wrap->porto
  //wrap->aspetto
  //wrap->colli
  //wrap->peso

  for(int i=0; i<rows; i++) {
    orderTable->setCurrentCell(i, 0);
    QComboBox *combo  = (QComboBox*)orderTable->cellWidget(i, 0);
    int indice = combo->currentItem();
    wrap->indice_CD.push_back(index_cd[indice]);
    wrap->quantita_unitaria.push_back(orderTable->item(i, 1)->text().toInt());
    wrap->prezzo_unitario.push_back(orderTable->item(i, 2)->text().toDouble());;
    //wrap->codice = ; aggiungere nella form per convenienza
  }
}

void subOrder::FillDialog(int id) { 
  
  cout << "5" << endl;
  rows = wrap->quantita;
  clientCombo->setCurrentItem(wrap->indice_cliente);
  primaryRadio->setChecked(wrap->indirizzo);
  priceEdit->setText(QString::number(wrap->prezzo));
  shipmentEdit->setText(QString::number(wrap->spedizione));
  shipment2Edit->setText(QString::number(wrap->spedizione_vera));
  reductionEdit->setText(QString::number(wrap->sconto));
  noteTextEdit->setText(wrap->nota);
  cout << "6" << endl;

  //wrap->date = QDate::currentDate(Qt::LocalTime);

  //wrap->trasporto
  //wrap->data_invio;
  //wrap->pagamento ???
  //wrap->pagato
  //wrap->spedito;
  //wrap->euroiva
  //wrap->porto
  //wrap->aspetto
  //wrap->colli
  //wrap->peso

  //  for(int i=0; i<rows; i++) {
  //  orderTable->setCurrentCell(i, 0);
  //  QComboBox *combo  = (QComboBox*)orderTable->cellWidget(i, 0);
  // int indice = combo->currentItem();
  //  wrap->indice_CD.push_back(index_cd[indice]);
  //  wrap->quantita_unitaria.push_back(orderTable->item(i, 1)->text().toInt());
  //  wrap->prezzo_unitario.push_back(orderTable->item(i, 2)->text().toDouble());
    //wrap->codice = ; aggiungere nella form per convenienza
  //}
}








