#include "subbrowsecd.h"
#include "groupBoxControl.h"
#include "utilities.h"

#include <qsqldatabase.h>
#include <qsqlpropertymap.h>
#include <qsqlcursor.h>
#include <qsqlform.h>
#include <qcombobox.h>
#include <qtextedit.h>

using namespace std;

subBrowseCD::subBrowseCD(QWidget* parent, const char* name) : browseCD(parent, name) {
  setCaption(tr("Insert new CD"));
  cdId = -1;
  newCd = true;
  init();
}

subBrowseCD::subBrowseCD(int id, QWidget* parent, const char* name) : browseCD(parent, name) {
  setCaption(tr("Update CD"));
  cdId = id;
  newCd = false;
  init();
}

subBrowseCD::~subBrowseCD()
{}

void subBrowseCD::init() {

  connect((const QObject*)cancelButton, SIGNAL(clicked()), (const QObject*)this, SLOT(reject()));
  connect((const QObject*)okButton, SIGNAL(clicked()), (const QObject*)this, SLOT(accept()));

  db = QSqlDatabase::database("MICROSUONI");
  
  sqlCursor = new QSqlCursor("cd", true, db);
  sqlCursor1 = new QSqlCursor("note", true, db);

  if (cdId == -1)
    createNewCD();
  else {
    sqlCursor->select("indice ='" + QString::number(cdId)+"'");
    sqlCursor1->select("indice ='" + QString::number(cdId)+"'");
    sqlCursor->next();
    sqlCursor1->next();
  }
  
  sqlForm = new QSqlForm(this);
  QSqlPropertyMap *pMap = new QSqlPropertyMap();
  pMap->insert("groupBoxControl", "stato");
  sqlForm->installPropertyMap(pMap);
  sqlForm->setRecord(sqlCursor->primeUpdate());
  sqlForm->insert((QWidget*)authorEdit, "artista");
  sqlForm->insert((QWidget*)titleEdit, "titolo");
  sqlForm->insert((QWidget*)supplierEdit, "etichetta");
  sqlForm->insert((QWidget*)companyEdit, "fornitore");
  sqlForm->insert((QWidget*)formatEdit, "formato");
  sqlForm->insert((QWidget*)codeEdit, "codice");
  sqlForm->insert((QWidget*)statusBox, "stato");
  sqlForm->insert((QWidget*)retailPriceEdit, "prezzo_acquisto");
  sqlForm->insert((QWidget*)sellingPriceEdit, "prezzo_vendita");
  sqlForm->insert((QWidget*)specialPriceEdit, "prezzo_offerta");
  sqlForm->insert((QWidget*)stockEdit, "quantita");
  sqlForm->insert((QWidget*)orderedEdit, "prenotazioni");
  sqlForm->insert((QWidget*)soldEdit, "venduti");
  sqlForm->readFields();
  noteTextEdit->setText(sqlCursor1->value("note").toString());
}

void subBrowseCD::createNewCD() {
  //statusBox->setStatus(2); SE NE DEVE OCCUPARE IL DB
  cdId = GenerateId("cd", db);
}

void subBrowseCD::accept() {
  statusBox->getStatus();
  sqlForm->writeFields();
  if (newCd) {
    sqlCursor->insert();
    QSqlRecord *buffer = sqlCursor1->primeInsert();
    buffer->setValue("indice", cdId);
    buffer->setValue("note", noteTextEdit->text());
    sqlCursor1->insert();
  }
  else {
    sqlCursor->update();
    QSqlRecord *buffer = sqlCursor1->primeUpdate();
    buffer->setValue("indice", cdId);
    buffer->setValue("note", noteTextEdit->text());
    sqlCursor1->update();
  }

  QDialog::accept();
}

void subBrowseCD::reject() {
  QDialog::reject();
}








