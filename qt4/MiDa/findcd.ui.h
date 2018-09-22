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

void FindCD::init() {
    exact = 0;
}

void FindCD::enableOkButton(const QString &text) {
    
  bool cond = !text.isEmpty() | !artistEdit->text().isEmpty() 
    | !companyEdit->text().isEmpty() | !supplierEdit->text().isEmpty() 
    | !quantityEdit->text().isEmpty() | !formatEdit->text().isEmpty();
 
  okButton->setEnabled(cond);
}


void FindCD::setExactMatch(int state) {
    exact = state;	
}

void FindCD::passSearchString() {
    std::vector<QString> v;
    v.push_back(artistEdit->text());
    v.push_back(companyEdit->text());
    v.push_back(supplierEdit->text());
    v.push_back(quantityEdit->text());
    v.push_back(codeEdit->text());
    v.push_back(formatEdit->text());
    emit fireFind(v, exact);
}
