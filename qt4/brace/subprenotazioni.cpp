#include "subprenotazioni.h"

#include <qcombobox.h>
#include <qstringlist.h>
#include <qtable.h>

#include <iostream>

using namespace std;

subprenotazioni::subprenotazioni(QWidget* parent, const char* name) : prenotazioni(parent, name) {

}

subprenotazioni::subprenotazioni(Braciere* br, QWidget* parent, const char* name) : prenotazioni(parent, name) {
  braciere = br;
  init();
}

subprenotazioni::~subprenotazioni()
{}

void subprenotazioni::init() {
  
  QStringList list;
  int diff = braciere->inizio.daysTo(braciere->fine);
  for(int i=0; i<diff; i++) {
    list.append(braciere->inizio.addDays(i).toString());
    cout << braciere->inizio.addDays(i).toString() << endl;
  }

  comboData->insertStringList(list);
   
  p_day = &((*pre)[0]);

  for(unsigned int row = 0; row<p_day->size(); row++) {
    tablePrenotazioni->setItem(row, 0, new QTableItem
		   (tablePrenotazioni, QTableItem::OnTyping, 
		    (*p_day)[row].GetNome()));
  }
}

void subprenotazioni::cambioData(int index) {
  
  // provare a modificare il vettore on the fly
  p_day->resize(tablePrenotazioni->numRows());

  for (int row=0; row<tablePrenotazioni->numRows(); row++) {
    Prenotazione temp;
    temp.SetNome(tablePrenotazioni->item(row,0)->text());
    (*p_day)[row] = temp;
  }
    
  tablePrenotazioni->setNumRows(0);
  p_day = &((*pre)[index]);

  for(unsigned int row = 0; row<p_day->size(); row++) {
    tablePrenotazioni->setItem(row, 0, new QTableItem
		   (tablePrenotazioni, QTableItem::WhenCurrent, 
		    (*p_day)[row].GetNome()));
  }
  
}







