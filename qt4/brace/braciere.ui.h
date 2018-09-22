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

void braciere::init() { 
    dateInizio->setOrder(QDateEdit::DMY);
    dateFine->setOrder(QDateEdit::DMY);
    QDate temp = QDate::currentDate();
    dateInizio->setDate(temp);
    dateFine->setDate(temp.addDays(7));
}

void braciere::accept() {
    inizio = dateInizio->date();
    fine = dateFine->date();
    nome = editNome->text();
    QDialog::accept();
}
