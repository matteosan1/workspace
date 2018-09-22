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

void findClient::init() {
    exact = 0;
}

void findClient::enableOkButton(const QString &text) {
    
  bool cond = !text.isEmpty() | !surnameEdit->text().isEmpty() 
    | !cityEdit->text().isEmpty() | !countryEdit->text().isEmpty(); 
  
  okButton->setEnabled(cond);
}


void findClient::setExactMatch(int state) {
    exact = state;	
}

void findClient::passSearchString() {
    std::vector<QString> v;
    v.push_back(surnameEdit->text());
    v.push_back(cityEdit->text());
    v.push_back(countryEdit->text());
    emit fireFind(v, exact);
}
