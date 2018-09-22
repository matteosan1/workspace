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
#include <qmessagebox.h>
#include <qcheckbox.h>

void Tratta::init() {    
    cavalliList->setColumnWidth(1, 38);
    cavalliList->setColumnWidth(2, 38);
    cavalliList->setColumnWidth(3, 25);
    cavalliList->setColumnStretchable(0, true);
    cavalliList->setLeftMargin(0);
    cavalliList->setNumRows(21);
}

void Tratta::riempiLista(QStringList nomi, QStringList corsi, QStringList vinti, int l) {
    limite = l;
    for(unsigned int i=0; i<nomi.size(); i++) {
	cavalliList->setText(i, 0, nomi[i]);
	cavalliList->setText(i, 1, corsi[i]);
	cavalliList->setText(i, 2, vinti[i]);
	cavalliList->setItem(i, 3, new QCheckTableItem(cavalliList, ""));
    }	
}	

void Tratta::accept() {
    
    int tot = 0;
    for(int i=0; i<21; i++) {
	cavalliList->setCurrentCell(i, 3);
	QCheckBox *check  = (QCheckBox*)cavalliList->cellWidget(i,3);
	selezione[i] = check->isChecked();
	tot += check->isChecked();
    }

    if (tot != limite)  {
	QString mex = "Devi scegliere " + QString::number(limite) + " cavalli.";
	QMessageBox::information(this, "TDPalio Info", mex);	
    }
    else
	QDialog::accept();    
}
    
void Tratta::cambiaCaption(QString s) {    
    QString cap = "Scelta Cavalli - " + s;
    setCaption(cap);
}

int* Tratta::getSelezione() {
    return selezione;
}
