#include "fanta.h"

#include "GiocatoriList.h"
#include "formdialog.h"
#include "insvoti.h"
#include "insgiocatore.h"
#include "regole.h"
#include "formtipo.h"

#include <QFileDialog>
#include <QTextStream>
#include <QMessageBox>
#include <QInputDialog>

#include <QList>

#include <iostream>

FantaDialog::FantaDialog(QWidget *parent)
  : QMainWindow(parent) {

    username = "";
    password = "";
    model = 0;
    isModified = false;
    m_punteggi = new Punteggi();
    labelSq = new QLabel();

    ui.setupUi(this);
    ui.actionSave->setEnabled(false);
    ui.actionNuovo_giocatore->setEnabled(false);
    ui.actionElimina_Giocatore->setEnabled(false);
    ui.actionModifica_Giocatore->setEnabled(false);
    ui.actionInserisci_Voti->setEnabled(false);
    ui.actionMedie_Giocatori->setEnabled(false);
    ui.actionProfilo_Squadra->setEnabled(false);
    ui.actionFormazione->setEnabled(false);
    ui.actionFormazione_tipo->setEnabled(false);

    ui.actionMedie_Giocatori->setCheckable(true);
    ui.actionMedie_Giocatori->setChecked(false);

    ui.statusbar->addWidget(labelSq, 1);

    connect(ui.actionOpen, SIGNAL(activated()), this, SLOT(fileOpen()));
    connect(ui.actionSave, SIGNAL(activated()), this, SLOT(fileSave()));
    connect(ui.actionFormazione, SIGNAL(activated()), this, SLOT(insFormazione()));
    connect(ui.actionChiudi, SIGNAL(activated()), this, SLOT(close()));
    connect(ui.actionMedie_Giocatori, SIGNAL(toggled(bool)), this, SLOT(changeView(bool)));
    connect(ui.actionNuovo_giocatore, SIGNAL(activated()), this, SLOT(addPlayer()));
    connect(ui.actionModifica_Giocatore, SIGNAL(activated()), this, SLOT(modifyPlayer()));
    connect(ui.actionElimina_Giocatore, SIGNAL(activated()), this, SLOT(killPlayer()));
    connect(ui.actionNew, SIGNAL(activated()), this, SLOT(nuovaSquadra()));
    connect(ui.actionFormazione_tipo, SIGNAL(activated()), this, SLOT(tipo()));
    connect(ui.tableGiocatori, SIGNAL(doubleClicked(const QModelIndex&)),
            this, SLOT(riassunto(const QModelIndex&)));
}

void FantaDialog::closeEvent(QCloseEvent *event) {
  if (isModified) {
    int ret = QMessageBox::warning(this, "Fantamania Avvertimento",
				   tr("Vuoi salvare i cambiamenti ?"),
				   QMessageBox::Yes | QMessageBox::Default,
				   QMessageBox::No | QMessageBox::Escape);
    if (ret == QMessageBox::Yes)
      fileSave();
  }
}


void FantaDialog::riassunto(const QModelIndex& index) {

    GiocatoriList* model = dynamic_cast<GiocatoriList*>(ui.tableGiocatori->model());
    if (!model->isToggled()) {
        Giocatore* temp = m_giocatori[index.row()];
        Prestazione pre = temp->GetPartita(index.column());
        QString s = QString("<b>Riepilogo Giornata %1</b><br><br>").arg(index.column()+1);
        s = s + QString("Voto: %1<br>").arg(pre.GetVoto());

        if (pre.isAmmonizione())
            s = s + "Ammonito<br>";
        if (pre.isEspulsione())
            s = s + "Espulso<br>";
        if ((temp->GetRuolo() != 0) && (temp->GetRuolo() != 5)) {
            s = s + QString("Goal Segnati:     %1<br>").arg(pre.Goal());
            s = s + QString("Rigori Segnati:   %1<br>").arg(pre.GoalRigore());
            s = s + QString("Rigori Sbagliati: %1<br>").arg(pre.RigoriSbagliati());
            s = s + QString("Assist:           %1<br>").arg(pre.Assist());
            s = s + QString("Autogoal:         %1<br>").arg(pre.Autogoal());
        } else {
            s = s + QString("Goal Subiti:      %1<br>").arg(pre.GoalSubiti());
            s = s + QString("Rigori Parati:    %1<br>").arg(pre.RigoriParati());
            s = s + QString("Assist:           %1<br>").arg(pre.Assist());
            s = s + QString("Autogoal:         %1<br>").arg(pre.Autogoal());
        }
        QMessageBox::information(this, temp->GetNomeCompleto(), s,
                                          QMessageBox::Yes | QMessageBox::Default,
                                          QMessageBox::No | QMessageBox::Escape);
    }
}

void FantaDialog::tipo() {
  FormTipo t(m_giocatori, this, m_punteggi);
  if (t.exec() == QDialog::Accepted) {
    return;
  }
}

void FantaDialog::nuovaSquadra() {
  
  if (isModified) {
    int ret = QMessageBox::warning(this, "Fantamania Avvertimento",
				   tr("Vuoi salvare i cambiamenti ?"),
				   QMessageBox::Yes | QMessageBox::Default,
				   QMessageBox::No | QMessageBox::Escape);
    if (ret == QMessageBox::Yes)
      fileSave();
  }
  
  bool ok;
  QString nome1 = QInputDialog::getText(0, QString("Nuova Squadra"),
					QString("Nome della squadra: "), QLineEdit::Normal,
					QString(""), &ok);
  
  if (ok) {
    if (nome1.isEmpty())
      nome1 = "SQUADRA";
    
    num_partite = -1;
    username = "";
    password = "";
    
    //FIXME Anno in qualche modo o inserito o automatico
    //FIXME sostituzione portiere
    QString anno1 = "2007/2008";
    
    Regole r(this, m_punteggi);
    if (r.exec() == QDialog::Accepted) {
      
      m_giocatori = r.GetGiocatori();
      num_giocatori = m_giocatori.size();
      
      for(int i=0; i<num_giocatori; ++i) {
    if (m_giocatori[i]->GetCognome() == "")
      m_giocatori[i]->SetCognome(QString("GIOCATORE %d").arg(i));
    if (m_giocatori[i]->GetNome() == "")
      m_giocatori[i]->SetNome(" ");
    if (m_giocatori[i]->GetSquadra() == "")
      m_giocatori[i]->SetSquadra(" ");
      }
      
      isModified = true;
      nome = nome1;
      anno = anno1;
      ordina();
      fillList(ui.actionMedie_Giocatori->isChecked());
      ui.actionSave->setEnabled(false);
      
    } else {
      QMessageBox::critical(this, "Fantamania Errore",
			    tr("Nessuna squadra e` stata salvata."));
      return;
    }
  } else {
    QMessageBox::critical(this, "Fantamania Errore",
			  tr("Nessuna squadra e` stata salvata."));
    return;
  }
  
  ui.actionNuovo_giocatore->setEnabled(true);
  ui.actionElimina_Giocatore->setEnabled(true);
  ui.actionModifica_Giocatore->setEnabled(true);
  ui.actionInserisci_Voti->setEnabled(true);
  ui.actionMedie_Giocatori->setEnabled(true);
  ui.actionProfilo_Squadra->setEnabled(true);
  ui.actionFormazione_tipo->setEnabled(true);
  ui.actionFormazione->setEnabled(true);
  
  setWindowTitle("Fantamanager ("+nome+")");
}

void FantaDialog::killPlayer() {
  QStringList nomi;
  for(unsigned int i=0; i<m_giocatori.size(); ++i) {
    if (m_giocatori[i]->GetRuolo() < 4)
      nomi << m_giocatori[i]->GetNomeCompleto();
  }
  
  int k;
  bool ok;
  QString item = QInputDialog::getItem(this, tr("Elimina giocatore"),
				       tr("Nome giocatore: "), nomi, 0, false, &ok);
  
  if (ok && !item.isEmpty()) {
    for(int i=0; i<nomi.size(); ++i) {
      if (nomi[i] == item) {
	k = i;
	break;
      }
    }
    
    int ret = QMessageBox::warning(this, "Fantamania Avvertimento",
                   tr("Vuoi mettere il giocatore %1 fuori rosa ?").arg(m_giocatori[k]->GetNomeCompleto()),
				   QMessageBox::Yes | QMessageBox::Default,
				   QMessageBox::No | QMessageBox::Escape);
    if (ret == QMessageBox::Yes) {
      int ruolo = m_giocatori[k]->GetRuolo();
      m_giocatori[k]->SetRuolo(ruolo+5);
      ordina();
      fillList(ui.actionMedie_Giocatori->isChecked());
      isModified = true;
      ui.actionSave->setEnabled(true);
    }
  }
}

void FantaDialog::modifyPlayer() {
  
  QStringList nomi;
  for(unsigned int i=0; i<m_giocatori.size(); ++i)
    nomi << m_giocatori[i]->GetNomeCompleto();
  
  int k;
  bool ok;
  QString item = QInputDialog::getItem(this, tr("Elimina giocatore"),
				       tr("Nome giocatore: "), nomi, 0, false, &ok);
  
  if (ok && !item.isEmpty()) {
    for(int i=0; i<nomi.size(); ++i) {
      if (nomi[i] == item) {
	k = i;
	break;
      }
    }
    
    InsGiocatore j(&m_giocatori[k]);
    if (j.exec() == QDialog::Accepted) {
      m_giocatori[k] = *(j.GetGiocatore());
      ordina();
      fillList(ui.actionMedie_Giocatori->isChecked());
      isModified = true;
      ui.actionSave->setEnabled(true);
    }
  }
}

void FantaDialog::addPlayer() {
  
  InsGiocatore i;
  if (i.exec() == QDialog::Accepted) {
    if (i.GetGiocatore()->GetNome() == "")
      i.GetGiocatore()->SetNome("_");
    
    if (i.GetGiocatore()->GetSquadra() == "")
      i.GetGiocatore()->SetSquadra("_");
    
    m_giocatori.push_back(*(i.GetGiocatore()));
    num_giocatori = m_giocatori.size();
    ordina();
    // TODO cerca tutti i voti per il giocatore inserito
    // TODO controllare se i voti vengono dati anche a quelli fuori rosa
    fillList(ui.actionMedie_Giocatori->isChecked());
    isModified = true;
    ui.actionSave->setEnabled(true);
  }
}

void FantaDialog::changeView(bool toggleState) {
  fillList(toggleState);
}

// TODO controllare il fuoco delle varie finestre
// TODO aggiungere il riferimento con indice secondo il sito
// TODO togliere eventuali spazi bianchi dalla formazione
// TODO mettere report punteggio squadra
// TODO mettere squadra consigliata
// TODO cambiare label nelle varie finestre
// TODO cambiare i colori per ruolo

float FantaDialog::mediaTotale() {
  
  float total = 0;
  int partite = num_partite;
  vector<Giocatore>::const_iterator it;
  for(int g=0; g<num_partite; ++g) {
    float result = 0;
    for(it = m_giocatori.begin(); it != m_giocatori.end(); ++it) {
      Giocatore temp = *it;
      if (temp.GetPartita(g).HaGiocato())
    result += temp.GetVoto(g, m_punteggi);
    }
    
    if (result == 0)
      partite--;
    total += result;
  }
  
  if (partite <= 0)
    return 0;
  
  return total/(float)partite;
}

void FantaDialog::fileSave() {
  if (curFile.isEmpty())
    fileSaveAs();
  else {
    salvaFile();
    isModified = false;
    ui.actionSave->setEnabled(false);
  }
}

void FantaDialog::fileSaveAs() {
  QString fileFilters = "Fantamania files (*.fnm);; Tutti (*.*)";
  QString fileName = QFileDialog::getSaveFileName(this, tr("Save file"), "/home/sani/Documents/Fantamaniaco", fileFilters);
  
  if (fileName.isEmpty())
    return;
  if (QFile::exists(fileName)) {
    int ret = QMessageBox::warning(this, "Fantamania Avvertimento",
				   tr("Il giuoco %1 esiste gia`.\nVuoi sovrascrivere ?").arg(fileName),
				   QMessageBox::Yes | QMessageBox::Default,
				   QMessageBox::No | QMessageBox::Escape);
    if (ret == QMessageBox::No)
      return;
  }
  
  if (!fileName.isEmpty()) {
    curFile = fileName;
    salvaFile();
  }
}

void FantaDialog::salvaFile() {
  
  QFile file(curFile);
  if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
    std::cerr << "File not found" << std::endl;
    return;
  }
  
  QTextStream out(&file);
  
  out << nome << "\n";
  out << anno << "\n";
  
  out << num_giocatori << "\n";
  
  for(int i=0; i<num_giocatori; i++)
    out << m_giocatori[i];
  
  out << num_partite << "\n";
  out << (*m_punteggi);
}

void FantaDialog::insFormazione() {
  
    QList<Giocatore*> gioc;
    for (int i=0; i<m_giocatori.size(); i++)
    {
        gioc.append(&m_giocatori[i]);
    }

  FormDialog f(gioc, m_punteggi, num_partite, this);
  
  if (f.exec() == QDialog::Accepted) {
    QStringList s = f.readLines().split("\n");
    //std::cout << "fanta.cpp" << f.giornata << std::endl;
    InsVoti i(s, &m_giocatori, m_punteggi, num_partite, f.getGiornata(), username, password);
    if (i.Connection()) {
      if (i.SetVoti()) {
	if (i.giornata > num_partite)
	  num_partite = i.giornata;
	
	username = i.username;
	password = i.password;
    QString a1 = "m_punteggieggio Giornata: " + QString("%1").arg(num_partite);
	QString a2 = "Modulo schierato: " + i.modulo + "\n";
	if (i.giocavano.toInt() < 11)
	  a2 += "Sfortunatamente hai giocato con soli " + i.giocavano + " giocatori.\n";
    a2 += "m_punteggieggio totale: " + i.totale;
	
	QMessageBox::information(this, a1, a2);
	fillList(ui.actionMedie_Giocatori->isChecked());
	isModified = true;
	ui.actionSave->setEnabled(true);
      }
    }
  }
}

void FantaDialog::ordina() {
  for(unsigned int i=0; i<m_giocatori.size()-1; ++i) {
    for(unsigned int j=i+1; j<m_giocatori.size(); ++j) {
      if ((m_giocatori[i].GetRuolo() > m_giocatori[j].GetRuolo()) ||
      ((m_giocatori[i].GetNomeCompleto() > m_giocatori[j].GetNomeCompleto()) &&
       (m_giocatori[i].GetRuolo() == m_giocatori[j].GetRuolo()))) {
    Giocatore temp = m_giocatori[i];
    m_giocatori[i] = m_giocatori[j];
    m_giocatori[j] = temp;
      }
    }
  }
}

void FantaDialog::fileOpen() {
  
  QString fileFilters = "Fantamania files (*.fnm);; Tutti (*.*)";
  if (isModified)
    fileSave();
  
  QString fileName = QFileDialog::getOpenFileName(this, tr("Open file"), "/home/sani/Documents/Fantamaniaco", fileFilters);
  if (!fileName.isEmpty()) {
    m_giocatori.clear();
    caricaFile(fileName);
    ordina();
    fillList(ui.actionMedie_Giocatori->isChecked());
    isModified = false;
    ui.actionSave->setEnabled(false);
    ui.actionNuovo_giocatore->setEnabled(true);
    ui.actionElimina_Giocatore->setEnabled(true);
    ui.actionModifica_Giocatore->setEnabled(true);
    ui.actionInserisci_Voti->setEnabled(true);
    ui.actionMedie_Giocatori->setEnabled(true);
    ui.actionProfilo_Squadra->setEnabled(true);
    ui.actionFormazione_tipo->setEnabled(true);
    ui.actionFormazione->setEnabled(true);
    setWindowTitle("Fantamanager ("+nome+")");
  }
}

void FantaDialog::fillList(bool toggleState) {

    model = new GiocatoriList(num_partite, m_giocatori, toggleState, m_punteggi);
    /*
    QItemSelectionModel* selection = new QItemSelectionModel(model);
    if (!toggleState)
        ui.tablem_giocatori->setSelectionModel(selection);
    else
        ui.tablem_giocatori->setSelectionModel(selection);
     */
    ui.tablem_giocatori->setModel(model);
    ui.tableGiocatori->show();
    QString note = "Giornate: " + QString("%1").arg(num_partite) +
            ", Media: " + QString("%1").arg(mediaTotale(), 0, 'f', 2);
    labelSq->setText(note);
}

bool FantaDialog::caricaFile(QString fileName) {

    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        std::cerr << "File not found" << std::endl;
        return false;
    }
    QTextStream in(&file);

    nome = in.readLine();
    anno = in.readLine();
    num_giocatori = in.readLine().toInt();

    Giocatore g;

    for(int i=0; i<num_giocatori; i++) {
        in >> g;
        m_giocatori.push_back(g);
    }

    in >> num_partite;
    in >> (*m_punteggi);
    //fin >> schema;
    //for(int i=0; i<17; i++)
    //fin >> form[i];
    //for(int i=0; i<50; i++)
    //fin >> sch[i] >> punteggio[i];
    //fin.close();
    curFile = fileName;
    return true;
}
