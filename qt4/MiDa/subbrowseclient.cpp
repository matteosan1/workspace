#include "subbrowseclient.h"
#include "utilities.h"

#include<iostream>

#include <qsqldatabase.h>
#include <qsqlcursor.h>
#include <qsqlform.h>

using namespace std;

subBrowseClient::subBrowseClient(QWidget* parent, const char* name) : browseClient(parent, name) {
  setCaption(tr("Insert new client"));
  clientId = -1;
  newClient = true;
  init();

}

subBrowseClient::subBrowseClient(int id, QWidget* parent, const char* name) : browseClient(parent, name) {
  setCaption(tr("Update client"));
  clientId = id;
  newClient = false;
  init();
}

subBrowseClient::~subBrowseClient()
{}

void subBrowseClient::init() {
  connect((const QObject*)cancelButton, SIGNAL(clicked()), (const QObject*)this, SLOT(reject()));
  connect((const QObject*)okButton, SIGNAL(clicked()), (const QObject*)this, SLOT(accept()));

  db = QSqlDatabase::database("MICROSUONI");

  sqlCursor = new QSqlCursor("clienti", true, db);
  if (clientId == -1)
    createNewClient();
  
  sqlCursor->select("indice = " + QString::number(clientId));
  sqlCursor->next();
  sqlForm = new QSqlForm(this);
  sqlForm->setRecord(sqlCursor->primeUpdate());
  sqlForm->insert((QWidget*)nameEdit, "nome");
  sqlForm->insert((QWidget*)surnameEdit, "cognome");
  sqlForm->insert((QWidget*)city1Edit, "citta1");
  sqlForm->insert((QWidget*)address1Edit, "via1");
  sqlForm->insert((QWidget*)state1Edit, "stato1");
  sqlForm->insert((QWidget*)cap1Edit, "cap1");
  sqlForm->insert((QWidget*)address2Edit, "via2");
  sqlForm->insert((QWidget*)city2Edit, "citta2");
  sqlForm->insert((QWidget*)state2Edit, "stato2");
  sqlForm->insert((QWidget*)cap2Edit, "cap2");
  sqlForm->insert((QWidget*)country1Edit, "nazione1");
  sqlForm->insert((QWidget*)country2Edit, "nazione2");
  sqlForm->insert((QWidget*)vatEdit, "iva");
  sqlForm->insert((QWidget*)cardEdit, "carta");
  sqlForm->insert((QWidget*)emailEdit, "email");
  sqlForm->insert((QWidget*)phoneEdit, "telefono");
  sqlForm->insert((QWidget*)mobileEdit, "cellulare");
  sqlForm->insert((QWidget*)coEdit, "presso");
  sqlForm->insert((QWidget*)noteTextEdit, "note");

  sqlForm->readFields();

}

void subBrowseClient::createNewClient() {
  clientId = GenerateId("clienti", db);
}

void subBrowseClient::accept() {
  sqlForm->writeFields();

  if (newClient)
    sqlCursor->insert();
  else
    sqlCursor->update();

  QDialog::accept();
}

void subBrowseClient::reject() {
  QDialog::reject();
}








