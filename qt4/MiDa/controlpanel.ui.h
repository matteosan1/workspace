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
#include <qsqldatabase.h>
#include <qsqlquery.h>

#include <iostream>

void ControlPanel::init() {
    
    inserimenti = -1;
    
    db = QSqlDatabase::database("MICROSUONI");    
     QSqlQuery query(db);
    query.exec("select * from pannello_controllo");
	std::cout << query.numRowsAffected() << std::endl;
     query.first();
	int i =0;
	while (query.next())	 {
	    i++;
	    std::cout << i << std::endl;
	    std::cout << query.value(2).toString() << std::endl;
	    list[query.value(1).toInt()].append(query.value(2).toString());
	}
  
    std::cout << db << std::endl;
    
    for(unsigned int i=0; i<list[0].size(); i++) 
	payListBox->insertItem(*list[0].at(i));
    std::cout << db << std::endl;
    
    for(unsigned int i=0; i<list[1].size(); i++) 
	carListBox->insertItem(*list[1].at(i));
    std::cout << db << std::endl;
    
    for(unsigned int i=0; i<list[2].size(); i++) 
	appListBox->insertItem(*list[2].at(i));
}

void ControlPanel::enablePayInsert( const QString & s) {
    payButton->setEnabled(!s.isEmpty());
}

void ControlPanel::enableAppInsert( const QString & s) {
    appButton->setEnabled(!s.isEmpty());
}

void ControlPanel::enableCarInsert( const QString & s) {
    carButton->setEnabled(!s.isEmpty());
}

void ControlPanel::insertPay() {
    inserimenti++;
    combo[inserimenti] = 0;
    indice[inserimenti] = findMax(0);
    edit[inserimenti] = payEdit->text();
    payEdit->setText("");
    okButton->setEnabled(true);
    payListBox->insertItem(edit[inserimenti]);
}

void ControlPanel::insertApp() {
    inserimenti++;
    combo[inserimenti] = 2;
    indice[inserimenti] = findMax(2);
    edit[inserimenti] = appEdit->text();
    appEdit->setText("");
    okButton->setEnabled(true);
    appListBox->insertItem(edit[inserimenti]);
}

void ControlPanel::insertCar() {
    inserimenti++;
    combo[inserimenti] = 1;
    indice[inserimenti] = findMax(1);
    edit[inserimenti] = carEdit->text();
    carEdit->setText("");
    okButton->setEnabled(true);
    carListBox->insertItem(edit[inserimenti]);
}

void ControlPanel::accept() {
    db = QSqlDatabase::database("MICROSUONI");    
    
    for(int i=0; i<inserimenti+1; i++) {
	std::cout << combo[i] << indice[i] << edit[i] << std::endl;
	
	QString q = "insert into pannello_controllo (indice, combo, edit) values (";
	q += QString::number(indice[i]) + ", ";
	q += QString::number(combo[i]) + ", \"";
	q += edit[i] + "\");";
	std::cout << q << std::endl;
	QSqlQuery query(db);
	if (!query.isActive())
	    std::cout << query.lastError().text() << std::endl;
	query.exec(q);
	
   }
    
    QDialog::accept();
}

void ControlPanel::reject() {
    QDialog::reject();
}

int ControlPanel::findMax(int cat) {
    
    QSqlQuery query(db);
    query.exec("select max(indice) from pannello_controllo where combo = '"+QString::number(cat) +"'");
    query.next();
    return query.value(0).toInt() + 1;    
}
