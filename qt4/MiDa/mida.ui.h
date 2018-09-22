/****************************************************************************
** ui.h extension file, included from the uic-generated form implementation.
**
** If you want to add, delete, or rename functions or slots, use
** Qt Designer to update this file, preserving your code.
**
** You should not define a constructor or destructor in this file.
** Instead, write your code in functions called init() and destroy().
** These will automatically be called by the form's constructor and
** destructor.
*****************************************************************************/
#include "findclient.h"
#include "findcd.h"
#include "subbrowseclient.h"
#include "subbrowsecd.h"
#include "suborder.h"
#include "controlpanel.h"

#include <iostream>

#include <qsqldatabase.h>
#include <qsqlcursor.h>
#include <qmessagebox.h>

using namespace std;

void mida::init() {
    findcd = 0;
    findCl = 0;
    sborder = 0;

    db = QSqlDatabase::database("MICROSUONI");

    sqlCursor1 = new QSqlCursor("clienti", true, db);
    sqlCursor1->setMode(QSqlCursor::ReadOnly);

    sqlCursor2 = new QSqlCursor("ordine_riepilogo", true, db);
    sqlCursor2->setMode(QSqlCursor::ReadOnly);

    sqlCursor = new QSqlCursor("cd", true, db);
    sqlCursor->setMode(QSqlCursor::ReadOnly);

    cdTable->setSqlCursor(sqlCursor, false);
    cdTable->addColumn("titolo", tr("Title"));
    cdTable->addColumn("artista", tr("Artist"));
    cdTable->addColumn("etichetta", tr("Company"));
    cdTable->addColumn("fornitore", tr("Supplier"));
    cdTable->addColumn("quantita", tr("Pieces"));
    cdTable->addColumn("codice", tr("Code"));
    cdTable->setAutoDelete(true);
    cdTable->setConfirmDelete(true);
    cdTable->setSorting(true);
    cdTable->refresh();

    clientTable->setSqlCursor(sqlCursor1, false);
    clientTable->addColumn("nome", tr("Name"));
    clientTable->addColumn("cognome", tr("Surname"));
    clientTable->addColumn("citta1", tr("City"));
    clientTable->addColumn("stato1", tr("Country"));
    clientTable->addColumn("email", tr("Email"));
    clientTable->addColumn("telefono", tr("Phone"));
    clientTable->addColumn("cellulare", tr("Mobile"));
    clientTable->setAutoDelete(true);
    clientTable->setConfirmDelete(true);
    clientTable->setSorting(true);
    clientTable->refresh();

    orderTable->setSqlCursor(sqlCursor2, false);
    orderTable->addColumn("data", tr("Date"));
    orderTable->addColumn("quantita", tr("Articles"));
    orderTable->addColumn("prezzo", tr("Cost"));
    orderTable->addColumn("sconto", tr("Reduction"));
    orderTable->addColumn("pagato", tr("Paid"));
    orderTable->addColumn("spedito", tr("Sent"));
    orderTable->addColumn("nota", tr("Note"));
    orderTable->setColumnWidth(4, 50);
    orderTable->setColumnWidth(5, 50);
    orderTable->setColumnStretchable(6, true);
    orderTable->setAutoDelete(true);
    orderTable->setConfirmDelete(true);
    orderTable->setSorting(true);
}

void mida::filePrint() {

}


void mida::fileExit() {

}

void mida::controlPanel() {
   ControlPanel cp(this, "controlpanel");
    cp.exec();
}

void mida::searchCD() {
    if (!findcd) {
	findcd  = new FindCD(0);
	connect(findcd, SIGNAL(fireFind(std::vector<QString>, bool)), this, SLOT(fireFindCD(std::vector<QString>, bool)));
    }
    
    findcd->show();
    findcd->raise();
    findcd->setActiveWindow();
}


void mida::searchClient() {
    if (!findCl) {
	findCl = new findClient(0);
	connect(findCl, SIGNAL(fireFind(std::vector<QString>, bool)), this, SLOT(fireFindClient(std::vector<QString>, bool)));	
    }
    
    findCl->show();
    findCl->raise();
    findCl->setActiveWindow();
}

void mida::fireFindCD(std::vector<QString> v, bool exact) {

  char* field[6] = {"artista", "etichetta", "fornitore", "quantita", "codice", "formato"};
  QString query = "";
  QString match = "";
  
  if (!exact) 
    match = "%";
  
  bool first = true;
  for(int i=0; i<6; i++) {

    if (v[i] != "") {
      if (first) {
	query = query + field[i] + " like '" + match + v[i] + match + "'"; 
	  first = false;
      } else {
	query = query + " and " + field[i] + " like '" + match + v[i] + match + "'";
      }
    }
  }
  
  sqlCursor->select(query);
  //sqlCursor->next();
  cdTable->setFilter(sqlCursor->filter());
  cdTable->refresh();  
}

void mida::fireFindClient(std::vector<QString> v, bool exact) {
  
  char* field[3] = {"cognome", "citta1", "nazione1"};
  QString query = "";
  QString match = "";
  
  if (!exact) 
    match = "%";
  
  bool first = true;
  for(int i=0; i<3; i++) {

    if (v[i] != "") {
      if (first) {
	query = query + field[i] + " like '" + match + v[i] + match + "'"; 
	  first = false;
      } else {
	query = query + " and " + field[i] + " like '" + match + v[i] + match + "'";
      }
    }
  }
  
  sqlCursor->select(query);
  //sqlCursor->next();
  cdTable->setFilter(sqlCursor->filter());
  cdTable->refresh();  
}

void mida::about() {
    QMessageBox::about(this, tr("About MiDa"),
		       tr("<h2>MiDa 3.0</h2>"
			  "<p>Copyright &copy 2005 MatteoSoftware<br>"
			  "<p>MiDa is a GUI for the <b>Microsuoni Database</b><br>"));
}


void mida::newClient() {
    subBrowseClient sbc(this, "insert");
    sbc.exec();
    clientTable->refresh();
}


void mida::updateClient(int row, int a, int b, const QPoint& p) {
    if (sqlCursor1->isSelect()) {
	sqlCursor1->seek(row);
	int id = sqlCursor1->value("indice").toInt();
	subBrowseClient sbc(id, this, "update");	
	if (sbc.exec() == QDialog::Accepted)
	    clientTable->refresh();
    }
}


void mida::updateOrderTable(QSqlRecord *record) {
    //int id = record->value(0).toInt();
    sqlCursor2->select("indice_cliente = '" + record->value(0).toString() + "'");
    orderTable->setFilter(sqlCursor2->filter());		
    orderTable->refresh();
}


void mida::newCD() {
    subBrowseCD sbcd(this, "insert");
    sbcd.exec();
    cdTable->refresh();
}


void mida::updateCD( int row, int a, int b, const QPoint &p ) {
        if (sqlCursor->isSelect()) {
	sqlCursor->seek(row);
	int id = sqlCursor->value("indice").toInt();
	subBrowseCD sbcd(id, this, "update");	
	if (sbcd.exec() == QDialog::Accepted)
	    cdTable->refresh();
    }
}


void mida::newOrder() {
  if (!sborder) {
    sborder = new subOrder(0, "new_order");
    //connect(findCl, SIGNAL(fireFind(std::vector<QString>, bool)), this, SLOT(fireFindClient(std::vector<QString>, bool)));	
  }
  sborder->show();
  sborder->raise();
  sborder->setActiveWindow();
}

void mida::updateOrder( int row, int a, int b, const QPoint & p ) {
       if (sqlCursor2->isSelect()) {
	sqlCursor2->seek(row);
	int id = sqlCursor2->value("indice").toInt();
	subOrder sbcd(id, this, "update");	
	if (sbcd.exec() == QDialog::Accepted)
	    orderTable->refresh();
    }
}

