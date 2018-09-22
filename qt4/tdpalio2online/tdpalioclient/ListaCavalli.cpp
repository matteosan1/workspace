#include "ListaCavalli.h"

#include <QMessageBox>

ListaCavalli::ListaCavalli(QVector<QString>* c, QWidget* parent)
    : QDialog(parent), cavalli(c) {

    ui.setupUi(this);
    setWindowTitle("Cavalli Ammessi alla Tratta");

    writeEdit();
}

void ListaCavalli::writeEdit() {
  
  QString s = "<html><img src=\"./pictures/logo_comune.png\"><br><br>";
  // FIXME scrivici la data giusta
  s = s + "<div align=\"right\">Siena, XX Luglio 2008</div><br><br>";
  s = s + "<div align=\"center\">ELENCO CAVALLI AMMESSI ALLE BATTERIE DI SELEZIONE</div><br><br><br><br>";
  for(int i=0; cavalli->size(); i++) 
    s = s + QString("%1." + (*cavalli)[i].toUpper()+"<br>").arg(i);
  
  s = s + "</html>";
  
  ui.textEdit->setHtml(s);
}

ListaCavalli::~ListaCavalli()
{}

