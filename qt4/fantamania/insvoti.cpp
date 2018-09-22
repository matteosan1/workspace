//#include <QtNetwork>
#include "insvoti.h"

#include <QFile>
#include <QTextStream>
#include <QRegExp>
#include <QMessageBox>
#include <QInputDialog>
#include <QProgressDialog>
#include <QApplication>

#include <iostream>
//#include "ui_authenticationdialog.h"

InsVoti::InsVoti(QStringList& l, vector<Giocatore>* g, Punteggi* p, int np,
                 int gio, QString& us, QString& pw) : list(l), giocatori(g),
						      punteggi(p), giornata(gio), num_partite(np), username(us), password(pw) {}

bool InsVoti::Connection() {
  while(1) {
    bool ok;
    if (username == "")
      username = QInputDialog::getText(0, QString("Collegamento Fantagazzetta"),
				       QString("User name: "), QLineEdit::Normal, QString(""), &ok);
    else
      ok = true;
    
    if (ok && !username.isEmpty()) {
      if (password == "")
	password = QInputDialog::getText(0, QString("Collegamento Fantagazzetta"),
					 QString("Password: "), QLineEdit::Password, QString(""), &ok);
      
      QString arg1 = "curl -s -c cookie -d user="+username+" -d password="+password+" -d ricorda=SI http://www.fantagazzetta.com/login.asp > dump";
      int dummy;
      dummy = system(arg1.toLatin1());

      if (Error() == 0)
	break;
      
      if (Error() == 2) {
	QMessageBox::critical(0, "Fantamania Errore",
			      "La rete non e` disponibile.");
	return false;
      }
      
      if (Error() == 1) {
	QMessageBox::critical(0, "Fantamania Errore", "L'autenticazione e` sbagliata.");
	username = "";
	password = "";
      }
    }
  }
  
  QApplication::setOverrideCursor(QCursor(Qt::WaitCursor));
  int dummy;
  if (giornata == -1) {
    dummy = system("curl -s -b cookie http://www.fantagazzetta.com/voti_fantagazzetta_serie_a.asp > voti.html");
  } else {
    QString arg2 = "curl -s -b cookie http://www.fantagazzetta.com/voti_fantagazzetta_serie_a.asp?g="+QString("%1").arg(giornata)+" > voti.html";
    
    dummy = system(arg2.toLatin1());
  }

  QApplication::restoreOverrideCursor();
  
  return true;
}

int InsVoti::Error() {

  QFile file("./dump");
  if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
    std::cerr << "File not found" << std::endl;
    return false;
  }
  
  QTextStream in(&file);
  QString s = in.readAll();
  
  if (s == "")
    return 2;
  
  if (s.contains("error"))
    return 1;
  
  return 0;
}

bool InsVoti::SetVoti() {
  // parsa il file e salva le informazioni per giocatore
  QFile file("./voti.html");
  if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
    std::cerr << "File not found" << std::endl;
    return false;
  }
  
  QTextStream in(&file);
  QRegExp rx("<td width=\"30\">(\\w{1,1})<");
  QRegExp rx1("Fantagazzetta\\s(\\d+)\\sgiornata");
  while (!in.atEnd()) {
    bool isPortiere = false;
    QString line = in.readLine();
    QString g;
    // Check della giornata giusta
    if (giornata == -1) {
      int pos = rx1.indexIn(line);
      if (pos > -1) {
	giornata = rx1.cap(1).toInt();
	if (giornata <= num_partite) {
	  QMessageBox::warning(0, "Fantamania Avvertimento",
			       "I voti non sono stati ancora messi in rete.",
			       QMessageBox::Yes | QMessageBox::Default,
			       QMessageBox::No | QMessageBox::Escape);
	  return false;
	}
      }
    }
    //std::cout << (const char*)line.toLatin1() << std::endl;
    if (line.contains(rx)) {
      int pos = rx.indexIn(line);
      if (pos > -1) {
	g = rx.cap(1);
	if (g == "P")
	  isPortiere = true;
      }
      QStringList l;
      for(int i=0; i<11; ++i) {
	line = in.readLine();
	l << line;
      }
      Parser(l, isPortiere);
    }
  }
  
  vector<Giocatore>::iterator it;
  int formazione[11];
  int panchina[6];
  for(int i=0; i<11; ++i)
    formazione[i] = -1;
  
  for(int i=0; i<6; ++i)
    panchina[i] = -1;
  
  int portieri=0, difensori=0, centrocampisti=0, attaccanti=0;
  for(int i=0; i<list.size(); ++i) {
    int j=0;
    for(it = giocatori->begin(); it != giocatori->end(); ++it) {
      QString nome = it->GetNomeCompleto();
      nome = nome.toUpper();
      it->GetPartita(giornata-1).SetNonHaGiocato();

      if (nome == list[i]) {
	if (i<11) {
	  it->GetPartita(giornata-1).SetFormazione(1);
	  if (it->GetRuolo() == 0)
	    portieri++;
	  if (it->GetRuolo() == 1)
	    difensori++;
	  if (it->GetRuolo() == 2)
	    centrocampisti++;
	  if (it->GetRuolo() == 3)
	    attaccanti++;
	  formazione[i] = j;
	} else {
	  it->GetPartita(giornata-1).SetFormazione(2);
	  int indice = 0;
	  if (i == 11)
	    indice = 0;
	  if (i == 13)
	    indice = 1;
	  if (i == 15)
	    indice = 2;
	  if (i == 12)
	    indice = 3;
	  if (i == 14)
	    indice = 4;
	  if (i == 16)
	    indice = 5;
	  panchina[indice] = j;
	}
      } 
      j++;
    }
  }
  
  for(int k=0; k<2; ++k) {
    for(int i=0+k*3; i<2+k*3; ++i) {
      for(int j=i+1; j<3+k*3; ++j) {
	if ((panchina[i] == -1) || (panchina[j] == -1))
	  continue;
	if ((*giocatori)[panchina[i]].GetPartita(giornata-1).GetVoto() <
	    (*giocatori)[panchina[j]].GetPartita(giornata-1).GetVoto()) {
	  int temp = panchina[i];
	  panchina[i] = panchina[j];
	  panchina[j] = temp;
	}
      }
    }
  }
  
  for(int i=0; i<11; ++i) {
    if ((*giocatori)[formazione[i]].GetPartita(giornata-1).GetVoto() != 0)
      (*giocatori)[formazione[i]].GetPartita(giornata-1).SetHaGiocato();
  }
  
  int numero_sostituzioni = 0;
  for(int j=0; j<11; ++j) {
    if (numero_sostituzioni == 3)
      break;
    if ((*giocatori)[formazione[j]].GetPartita(giornata-1).HaGiocato()==0) {
      for(int i=0; i<6; ++i) {
	if (panchina[i] == -1)
	  continue;
	int ruolo = (*giocatori)[panchina[i]].GetRuolo();
	if ((*giocatori)[formazione[j]].GetRuolo() == ruolo) {
	  if ((*giocatori)[panchina[i]].GetPartita(giornata-1).GetVoto() != 0)
	    (*giocatori)[panchina[i]].GetPartita(giornata-1).SetHaGiocato();
	  panchina[i] = -1;
	  numero_sostituzioni++;
	  break;
	}
      }
    }
  }
  
  float voto=0;
  int giocano=0;
  for(it = giocatori->begin(); it != giocatori->end(); ++it) {
    if (it->GetPartita(giornata-1).HaGiocato() == 1) {
      //std::cout << "Voto singolo" << it->GetVoto(giornata-1, punteggi) << std::endl;
      voto += it->GetVoto(giornata-1, punteggi);
      giocano++;
    }
  }
  
  //std::cout << "Voto: " << voto << std::endl;
  modulo =   QString("%1-%2-%3").arg(difensori).arg(centrocampisti).arg(attaccanti);
  giocavano = QString("%1").arg(giocano);
  totale =  QString("%1").arg(voto);

  //std::cout << giornata << std::endl;

  return true;
}

bool InsVoti::Parser(QStringList lines, bool isPortiere) {
  
  QString nome;
  float voto;
  int pos, sanzioni, dati[7];
  QRegExp r, r1;
  
  r = QRegExp("<td class=\"sinistra\">((\\w+)|(\\w+\\s\\w+)|(\\w+'\\w+\\s\\w\\.)|(\\w+'\\w+)|(\\w+\\s\\w+\\s\\w\\.)|(\\w+\\s\\w\\.))");
  pos = r.indexIn(lines[0]);
  if (pos > -1)
    nome = r.cap(1);
  else
    return false;
  
  sanzioni = 0;
  r = QRegExp("Ammonito");
  pos = r.indexIn(lines[0]);
  if (pos > -1)
    sanzioni = 1;
  
  r = QRegExp("Espulso");
  pos = r.indexIn(lines[0]);
  if (pos > -1)
    sanzioni = 2;
  
  r = QRegExp("<td class=\"verde\" width=\"30\">((\\d)|(\\d\\,\\d))<");
  r1 = QRegExp("<td class=\"grigio\" width=\"30\">sv<");
  pos = r.indexIn(lines[1]);
  int pos1 = r1.indexIn(lines[1]);
  
  if (pos > -1) {
    QString temp = r.cap(1).replace(",", ".");
    voto = temp.toFloat();
  } else if ((pos1 > -1) && isPortiere && (punteggi->sv_portiere == 1)){
    QString temp = r1.cap(1).replace(",", ".");
    voto = 6;
  } else
    return false;
  
  for(int i=2; i<9; ++i) {
    r = QRegExp("<td class=\"(\\w+)\" width=\"\\d+\">(\\d)<");
    pos = r.indexIn(lines[i]);
    if (pos > -1)
      dati[i-2] = r.cap(2).toInt();
    else
      dati[i-2] = 0;
  }
  
  vector<Giocatore>::iterator it;
  
  for(it=giocatori->begin(); it != giocatori->end(); ++it) {
    QString nome_giocatore1, nome_giocatore2;
    nome_giocatore2 = it->GetNomeCompleto();
    if (nome_giocatore2.endsWith("."))
      nome_giocatore1 = nome_giocatore2.left(nome_giocatore2.length()-3);
    else
      nome_giocatore1 = nome_giocatore2;
    nome_giocatore1 = nome_giocatore1.toUpper();
    nome_giocatore2 = nome_giocatore2.toUpper();
    
    if (((nome.endsWith(".")) && (nome_giocatore2 == nome)) ||
	((!nome.endsWith(".")) && (nome_giocatore1 == nome))) {
      //std::cout << (const char*)nome_giocatore1.toLatin1() << voto << std::endl;
      it->SetPartita(giornata-1, sanzioni, dati, voto);
      return true;
    }
  }
  //std::cout << giornata-1 << std::endl;
  return false;
}
