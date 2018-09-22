#ifndef SubPrenotazioni_H
#define SubPrenotazioni_H

#include "prenotazioni.h"

class QSqlDatabase;
class QSqlCursor;
class QSqlForm;

class subprenotazioni : public prenotazioni {
  
  Q_OBJECT
    
 public:
  subprenotazioni(Braciere* br, QWidget* parent=0, const char* name=0);
  subprenotazioni(QWidget* parent=0, const char* name=0);
  virtual ~subprenotazioni();
  
  void init();
  
  protected slots:
    //void accept();
    //void reject();
    void cambioData(int index);
    
 private:
  Braciere* braciere;
  std::vector<Prenotazione>* p_day;

};

#endif
