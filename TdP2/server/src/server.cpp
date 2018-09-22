#include <QtNetwork>

#include "tdpalioserver.h"
#include "../tdpaliocommon/utility.h"
#include <iostream>

TDPalioServer::TDPalioServer(int a) : QObject() {
  
  // FIXME definisci il seed
  random = new TRandom();

  tcpServer = new QTcpServer();
  if (!tcpServer->listen(QHostAddress::Any, a)) {
    QString s("TDPalio Server. Non e` possibile avviare il server: "+ tcpServer->errorString());
    qDebug(qPrintable(s));
    abort();
  }
  
  QString s = QString("TDPalio Server. Il server e` attivo sulla porta: %1.").arg(tcpServer->serverPort());
  qDebug(qPrintable(s));
  
  // Aperto il server aspetta le connessioni
  QObject::connect(tcpServer, SIGNAL(newConnection()), this, SLOT(acceptConnection()));
  
  // Definisce le variabili iniziali e le prime 10 contrade che corrono
  
  //**isChoosing = 0;

  // FIXME perche` mese e nProva non va dentro a fase ????????????
  fase = new FaseGioco(this);
  //fase = eInizio;
  mese = Luglio;
  nProva = 0;
  
  estrazione(0); // inizializza le prime 10 contrade che corrono
  giocatori.resize(0);
  contrade.resize(17);
  fantini.resize(16);
  cavalli.resize(21);
  barberi.resize(10);
  
  myStreamerIn = new MyStreamer();
  myStreamerOut = new MyStreamer();
  
  // Legge il file delle definizioni
  QFile file("../tdpalioserver/setup.dat");
  if (!file.open(QIODevice::ReadOnly)) {
    qDebug("Errore irreversibile. TDPalio Server non riesce a trovare il file setup.dat.");
    abort();
  }
  
  // FIXME mettere tutto in binario
  QTextStream in(&file);
  //in.setVersion(QDataStream::Qt_4_0);
  
  for(int i=0; i<17; ++i)
    in >> contrade[i];
  
  for(int i=0; i<16; ++i)
    in >> fantini[i];

  for(int i=0; i<21; ++i) 
    in >> cavalli[i];

  file.close();
  
  // Avvia 17 client artificiali
  for(int i=0; i<17; ++i)
    aiclients.push_back(new TDPalioAiClient(a, random));
}

void TDPalioServer::acceptConnection() {
  
  // definisce la connessione con i nuovi client 
  if (sockets.size() < 17) {
    MySocket* s = new MySocket(AI);
    s->socket = tcpServer->nextPendingConnection();
    connect(s->socket, SIGNAL(readyRead()), this, SLOT(incomingMessage()));
    connect(s->socket, SIGNAL(error(QAbstractSocket::SocketError)),
	     this, SLOT(error(QAbstractSocket::SocketError)));
    sendMessage(Initialize, s);
    s->state = sockets.size();
    sockets.push_back(s);

    return;
  }

  // Connette i nuovi giocatori umani, di default aggiunge spettatori
  MySocket* s = new MySocket(Human);
  s->state = Spectator;
  s->socket = tcpServer->nextPendingConnection();
  
  connect(s->socket, SIGNAL(readyRead()), this, SLOT(incomingMessage()));
  connect(s->socket, SIGNAL(error(QAbstractSocket::SocketError)),
	   this, SLOT(error(QAbstractSocket::SocketError)));

  // FIXME NON C"E` IL BLOCCO SE GIA` 17 umani ?????????????
  int temp = -1;
  for(int i=0; i<sockets.size(); ++i) {
    if (sockets[i]->state == Disconnected) {
      temp = i;
      break;
    }
  }
  
  if (temp == -1) {
    sockets.push_back(s);
    temp = sockets.size()-1;
  } else {
    sockets[temp] = s;
  }
  
  // FIXME ci vuole ???
  //myStreamerOut->clear();
  myStreamerOut->socket_number = temp;
  sendMessage(Initialize, s);
  
  myStreamerOut->stringStream.push_back("Un nuovo giocatore si e` connesso al server.");
  for(int i=0; i<sockets.size(); ++i)
    if (sockets[i]->type == Human)
      sendMessage(Message, sockets[i]);
}











void TDPalioServer::incomingMessage() {
  for(int i=0; i<sockets.size(); ++i) {
    if (sockets[i]->socket->bytesAvailable() > 0) {
      std::cout << "Socket number" << i << std::endl;
      QDataStream in(sockets[i]->socket);
      in.setVersion(QDataStream::Qt_4_0);
      processMessage(in);
    }
  }
}

void TDPalioServer::processMessage(QDataStream& in) {
  
  while(1) {
    myStreamerIn->clear();
    myStreamerOut->clear();
    
    in >> (*myStreamerIn);

    int socket_number = myStreamerIn->socket_number;
    std::cout << "socket_numbet" <<socket_number << std::endl;
    
    std::cout << "CODICE Server RECV: " << myStreamerIn->code << std::endl;
    switch((int)myStreamerIn->code) {
    case ScriviChat:
      {
	for(int i=0; i<sockets.size(); i++) {
	  if (sockets[i]->username == myStreamerIn->stringStream[0]) {
	    myStreamerOut->stringStream.resize(3);
	    myStreamerOut->stringStream = myStreamerIn->stringStream;
	    sendMessage(LeggiChat, sockets[i]);
	  }
	}
	break;
      }
    case AggiornaContradaPanel:
      {
	sendMessage(AggiornaContradaPanel, sockets[socket_number]);
	break;
      }
    case UserName:
      {
	sockets[socket_number]->username = myStreamerIn->stringStream[0];
	break;
      }
    case Ready:
      {
	//if (sockets[socket_number]->answered == false) {
	fase->newAnswer();
	  //  sockets[socket_number]->answered = true;
	  //}
	/*
	  bool allAnswered = true;
	  std::cout << socket_number << std::endl;
	  sockets[socket_number]->answered = true;
	  for(int i=0; i<sockets.size(); ++i)
	  if (sockets[i]->type == Human)
	  if (sockets[i]->answered = false)
	  allAnswered = false;
	  
	  if (allAnswered) {
	  // FIXME compattare
	  int a = (int)fase;
	  a++;
	  fase = (Fase)a;
	  controller();
	  }
	*/
	break;
      }
    case Start:
      {
	if (isChoosing == 0) {
	  isChoosing = 1;
	  myStreamerOut->stringStream.push_back("E` stato chiamato un nuovo gioco.");
	  for(int i=0; i<sockets.size(); ++i) {
	    if (sockets[i]->type == Human) {
	      sendMessage(Message, sockets[i]);
	    }
	  }
	  sendMessage(ChooseGame, sockets[socket_number]);
	  // FIXME E` necessario ?????????
	  sockets[socket_number]->answered = false;
	}
	break;
      }
    case Spettatore:
      {
	int contrada = sockets[socket_number]->state;
	for(int i=0; i<sockets.size(); ++i)
	  if (sockets[i]->type == AI)
	    if (sockets[i]->state == Spectator) {
	      sockets[i]->state = contrada;
	      break;
	    }
	
	sockets[socket_number]->state = Spectator;
	Giocatore g = giocatori[contrade[contrada].giocatore()];
	myStreamerOut->stringStream.push_back(g.nome() + " " + g.cognome() + " e` tornato spettatore.");
	for(int i=0; i<sockets.size(); ++i)
	  if (sockets[i]->type == Human)
	    sendMessage(Message, sockets[i]);

	// FIXME siamo sicuri di rimuovere il giocatore ????
	// adesso ci sono i giocatori "giocanti" no ????
	giocatori.remove(contrade[contrada].giocatore());
	contrade[contrada].setGiocatore(-1);
	break;
      }
    case FileName:
      {
	int index = myStreamerIn->intStream[0];
	fileName = myStreamerIn->stringStream[0];

	if (index == 2) {
	  myStreamerOut->stringStream.push_back("E` stato scelto il gioco: " + fileName);
	  for(int i=0; i<sockets.size(); ++i)
	    if (sockets[i]->type == Human)
	      sendMessage(Message, sockets[i]);
	  
	  bool result = caricaFile();
	  if (!result)
	    index = 3;
	}

	if (index == 1) {
	  myStreamerOut->stringStream.push_back("Si riparte da zero !!!");
	  
	  for(int i=0; i<sockets.size(); ++i)
	    if (sockets[i]->type == Human)
	      sendMessage(Message, sockets[i]);
	}

	if ((index == 1) || (index == 2)) {
	  for(int i=0; i<sockets.size(); ++i) {
	    if (sockets[i]->type == Human) {
	      // FIXME e` necessario ???
	      sockets[i]->state = Waiting;
	      scegliContrada(i);
	      fase->waiting();
	      //sockets[i]->answered = false;
	    }
	  }
	}

	if (index == 3) {
	  isChoosing = 0;
	  myStreamerOut->stringStream.push_back("Nessun gioco e` stato scelto.");
	  for(int i=0; i<sockets.size(); ++i)
	    if (sockets[i]->type == Human)
	      sendMessage(Message, sockets[i]);
	}
	break;
      }
    case AddPlayer:
      {
	// FIXME da ristudiare bisogna considerare i giocatori "giocanti"...
	if (giocatori.size() == 17) {
	  myStreamerOut->stringStream.push_back("Spiacente, ma ci sono gia` 17 giocatori.");
	  sendMessage(PopupMessage, sockets[socket_number]);
	}
	
	if (fase->currentPhase() != eInizio) {
	  // FIXME si ricorda chi e` in attesa ???
	  myStreamerOut->stringStream.push_back("Spiacente ma puoi iniziare a giocare solo dopo questa carriera.");
	  sendMessage(PopupMessage, sockets[socket_number]);
	  break;
	}
	
	scegliContrada(socket_number);
	fase->waiting();
	// FIXME ci vuole ???????
	sockets[socket_number]->answered = false;
	break;
      }
    case NewPlayer:
      {
	Giocatore g = myStreamerIn->giocatoreStream;
	
	bool choosen = false;
	if (!g.gioca()) {
	  for(int i=0; i<giocatori.size(); ++i) {
	    if (giocatori[i].contrada() == g.contrada()) {
	      myStreamerOut->stringStream.insert(0, "Questa contrada e` gia` stata scelta...");
	      sendMessage(PopupMessage, sockets[socket_number]);
	      scegliContrada(socket_number);
	      fase->waiting();
	      // FIXME ci vuole ???????
	      sockets[socket_number]->answered = false;
	      choosen = true;
	    }
	  }
	}
	
	if (!choosen) {
	  if (!g.gioca()) {
	    giocatori.push_back(g);
	    contrade[g.contrada()].setGiocatore(giocatori.size()-1);
	  }

	  sockets[socket_number]->state = g.contrada();
	  myStreamerOut->stringStream.insert(0, g.nome() + " " + g.cognome() + " e` stato eletto Capitano della " + contrade[g.contrada()].getNomeCompleto());
	  for(int i=0; i<sockets.size(); ++i) {
	    // FIXME MANDA ANCHE IL NUMERO DELLA CONTRADA PER LA CHAT
	    if (sockets[i]->type == Human) {
	      sendMessage(Message, sockets[i]);
	      sendMessage(AggiornaListaChat, sockets[i]);
	    }
	    if ((sockets[i]->type == AI) &&
		(sockets[i]->state == g.contrada()))
	      sockets[i]->state = Spectator;
	  }
	  
	  /*
	  bool waiting = false;
	  for(int i=0; i<sockets.size(); ++i)
	    if ((sockets[i]->type == Human) &&
		(sockets[i]->state == Waiting))
	      waiting = true;
	  
	  if (!waiting) {
	    fase = eEstrazione;
	    controller();
	  }
	  */
	}
	break;
      }
    case Disconnect:
      {
	myStreamerOut->stringStream.push_back("Un giocatore si e` disconnesso.");
	for(int i=0; i<sockets.size(); ++i)
	  if (sockets[i]->type == Human)
	    sendMessage(Message, sockets[i]);
	
	disconnection(socket_number);
	break;
      }
    case Vittorie:
      sendMessage(Vittorie, sockets[socket_number]);      
      break;
    case Tratta:
      {
	/*
	int risposte = 0;
	sockets[socket_number]->answered = true;
	QVector<int> risposta = myStreamerIn->intStream;
		
	for(int i=0; i<cavalli.size(); ++i)
	  if (risposta[i] == 1) {
	    // FIXME che cazzo e` ?
	    //cavalli[i].selezione++;
	  }
	
	for(int i=0; i<10; ++i) {
	  for(int j=0; j<sockets.size(); ++j) {
	    if (sockets[j]->state == corrono[i])
	      if (sockets[j]->answered)
		risposte++;
	  }
	}
	
	if (risposte == 10)
	*/
	sceltaCavalli();
	break;
      }
    }
    
    if (in.atEnd())
      break;
  }
}

//void TDPalioServer::controller() {
  // FIXME questo in teoria dovrebbe sparire
  //fase = f;
  //controller();
//  fase->newPhase();
//}

void TDPalioServer::controller() {
  
  switch(fase->currentPhase()) {
  case eSegnatura:
    break;
  case eInizio:
    break;
  case eEstrazione:
    {
      if (!fase->isCaricato()) {
	estrazione(1);
	for(int i=0; i<10; i++) {
	  barberi[i].setContrada(&contrade[corrono[i]]);
	  barberi[i].setEstrazione(i);
	}
      }
      /*
      switch(mese) {
      case Luglio:
	for(int i=0; i<10; i++) {
	  barberi[i].setContrada(&contrade[luglio[i]]);
	  barberi[i].setEstrazione(i);
	}
	break;
      case Agosto:
	for(int i=0; i<10; i++) {
	  barberi[i].setContrada(&contrade[agosto[i]]);
	  barberi[i].setEstrazione(i);
	}
	break;
      case Straordinario:
	for(int i=0; i<10; i++) {
	  barberi[i].setContrada(&contrade[settembre[i]]);
	  barberi[i].setEstrazione(i);
	}
	break;
      }
      */
      // FIXME aspetta la risposta da tutti quelli che giocano "Umani"
      // domanda: serve sapere l'ultimo messaggio inviato ????
      // e sopratutto serve sapere chi non ha risposto ????
      for(int i=0; i<sockets.size(); ++i) {
	if (sockets[i]->type == Human) {
	  if (sockets[i]->state > -1) {
	    sendMessage(Estrazione, sockets[i]);
	    sockets[i]->lastMessage = Estrazione;
	    sockets[i]->answered = false;
	    fase->waiting();
	  }
	}
      }
      break;
    }
  case eTratta:
    preTratta();
    break;
  case eSceltaFantino:
    {
      if (nProva == 0) {
	// FIXME Prima scelta del fantino (tutte le contrade devono avere un fantino prima di ogni prova
	// FIXME questo in teoria dovrebbe sparire
	//azzeraSockets();
	preSceltaFantino();
      }
      break;
    }
  case eProve:
    // FIXME questo in teoria dovrebbe sparire
    azzeraSockets();
    if (nProva == 7)
      segnatura();
    prove();
    inserisciPartito();
    sceltaFantino();
    break;
  case ePalio:
    palio();
    break;
  case eFinePalio:
    finePalio();
    break;
  }
}

void TDPalioServer::sendMessage(MessageCode code, int a) {
    sendMessage(code, sockets[a]);
}

void TDPalioServer::sendMessage(MessageCode code, MySocket* mySocket) {

  QTcpSocket* s = mySocket->socket;
  mySocket->lastMessage = code;
  
  QVector<int> index;
  QStringList list;
  QByteArray block;
  QDataStream out(&block, QIODevice::WriteOnly);
  out.setVersion(QDataStream::Qt_4_0);
  myStreamerOut->code = code;
  
  std::cout << "CODICE Server SEND: " << code << std::endl;
  
  switch((int)code) {
  case LeggiChat:
    break;
  case AggiornaListaChat:
    {
      // FIXME aggiornare lista chat quando un giocatore esce...
      QString s;
      QStringList list;
      myStreamerOut->stringListStream.clear();
      for(int i=0; i<sockets.size(); i++) {
	if (sockets[i]->type == Human) {
	  s = sockets[i]->username;
	  if (sockets[i]->state >= 0) { 
	    s = s + " - " + contrade[sockets[i]->state].getNome();
	  }
	  list << s;
	} 
	
      }
      if (list.size() > 1)
	list << "Tutti";
      
      myStreamerOut->stringListStream.push_back(list);
      break;
    }
  case AggiornaCavalloPanel:
    {
      break;
    }
  case AggiornaContradaPanel:
    {
      myStreamerOut->contradaStream.resize(1);
      myStreamerOut->contradaStream[0] = contrade[mySocket->state];
      break;
    }
  case Vittorie:
    myStreamerOut->contradaStream = contrade;
    break;
  case Tratta:
    break;
  case Initialize:
    // FIXME ci vuole ????
    //myStreamerOut->intStream.push_back(0);
    myStreamerOut->intStream.push_back(isChoosing);
    break;
  case ChooseGame:
    {
      QStringList nomi, date;
      
      QDir dir("giochi");
      dir.setFilter(QDir::Files | QDir::Hidden | QDir::NoSymLinks);
      //dir.setSorting(QDir::Size | QDir::Reversed);
      
      QFileInfoList fileNames = dir.entryInfoList();
      for(int i=0; i<fileNames.size(); ++i) {
	QFileInfo fileInfo = fileNames.at(i);
	nomi << fileInfo.fileName();
	date << fileInfo.created().toString();
      }
      myStreamerOut->stringListStream.push_back(nomi);
      myStreamerOut->stringListStream.push_back(date);
      break;
    }
  case Message:
    std::cout << "MESSAGGIO" << std::endl;
    break;
  case PopupMessage:
    break;
  case ChooseContrada:
    break;
  case Estrazione:
    {
      for(int i=0; i<17; ++i)
	list << contrade[corrono[i]].getNome();
      
      myStreamerOut->stringListStream.push_back(list);
      break;
    }
  case Assegnazione:
    {
    }
    break;
  case NomeAlFantino:
    {
    }
    break;
  case Segnatura:
    {
    }
    break;
  }
  
  out << (*myStreamerOut);
  s->write(block);
}

void TDPalioServer::scegliContrada(int sn) {

  QStringList list;
  QVector<int> index;

  bool giocava = false;
  myStreamerOut->clear();
  for(int i=0; i<giocatori.size(); ++i) {
    if (giocatori[i].userName() == sockets[sn]->username) {
      giocatori[i].setGioca();
      list << contrade[giocatori[i].contrada()].getNomeCompleto();
      myStreamerOut->stringListStream.push_back(list);
      myStreamerOut->intStream.push_back(-1);
      myStreamerOut->intStream.push_back(contrade[giocatori[i].contrada()].indice());
      giocava = true;
      fase->waiting();
      sockets[sn]->answered = true;
      break;
    }
  }  
	
  if (!giocava) {
    for(int i=0; i<contrade.size(); i++) {
      if (contrade[i].giocatore() == -1) {
        list << contrade[i].getNome();
	index << i;
      }
    }
    
    if (list.size() == 0) {
      for(int i=0; i<contrade.size(); i++) {
	for(int j=0; j<giocatori.size(); j++) {
	  if (giocatori[i].gioca() && giocatori[i].contrada() == i)
	    continue;
	  list << contrade[i].getNome();
	  index << i;
	}
      }
    }  
    
    myStreamerOut->stringListStream.push_back(list);
    myStreamerOut->intStream = index;  
  }
  
  sendMessage(ChooseContrada, sockets[sn]);
}

void TDPalioServer::error(QAbstractSocket::SocketError socketError) {
    switch (socketError) {
    case QAbstractSocket::RemoteHostClosedError:
    {
      int index = -1;
      for(int i=0; i<sockets.size(); ++i)
	if (sockets[i]->socket->isValid() == 0)
	  index = i;
      
      disconnection(index);
      break;
    }
    case QAbstractSocket::ConnectionRefusedError:
      qDebug("The connection was refused by the peer.");
      break;
    default:
      qDebug("The following error occurred: ");
      //			     .arg(tcpSocket->errorString()));
    }
}

void TDPalioServer::disconnection(int a) {
  
  if (sockets[a]->state > -1) {
    for(int i=0; i<sockets.size(); ++i)
      if (sockets[i]->type == AI)
	if (sockets[i]->state == Spectator) {
	  sockets[i]->state = sockets[a]->state;
	  // FIXME metti al corrente della situazione il client AI
	  // FIXME prova a ripartire dall'ultimo messaggio inviato
	  break;
	}
    
    /*
    for(int i=0; i<giocatori.size(); ++i)
      if (giocatori[i].contrada() == sockets[a]->state)
	giocatori.remove(i);

    contrade[sockets[a]->state].setGiocatore(-1);
    */
  }
  // FIXME forse e` meglio eliminare il socket direttamente piuttosto che lasciarlo
  // li disconnesso ?????
  sockets[a]->state = Disconnected;
  
  bool lastPlayer = true;
  for(int i=0; i<sockets.size(); ++i)
    if (sockets[i]->type == Human)
      if (sockets[i]->state > -1) {
	lastPlayer = false;
	break;
      }
  
  if (lastPlayer) {
    salvaFile();
    // FIXME a questo punto si potrebbe spengere il server...
    // magari ricordati se e` partito localmente oppure no.
    abort();
  }
}

void TDPalioServer::salvaFile() {
  std::cout << "SALVA" << std::endl;
  // FIXME perche` rimetto all'inizio la fase ?????
  //fase = eInizio;
  //isChoosing = 0;
  
  if (!fileName.endsWith(".tdp"))
    fileName = fileName + ".tdp";

  QFile file(QString("./giochi/") + fileName);
  if (!file.open(QIODevice::WriteOnly))
    std::cout << "NON POSSO SALVARE IL GIOCO..." << std::endl;
  
  // FIXME ricambia in QDataStream
  QTextStream out(&file);
  //out.setVersion(QDataStream::Qt_4_0);
  out << anno << " ";
  out << mese << " ";
  out << fase->currentPhase() << " ";
  out << nProva << "\n";
  
  for(int i=0; i<17; i++)
    out << corrono[i] << " ";
  out << "\n";

  for(int i=0; i<17; i++)
    out << luglio[i] << " ";
  out << "\n";
  
  for(int i=0; i<17; i++)
    out << agosto[i] << " ";
  out << "\n";
  
  for(int i=0; i<17; i++)
    out << settembre[i] << " ";
  out << "\n";
  
  out << giocatori.size() << "\n";
  for(int i=0; i<giocatori.size(); i++)
    out << giocatori[i];
  
  for(int i=0; i<17; i++)
    out << contrade[i];
  
  for(int i=0; i<21; i++)
    out << cavalli[i];
  
  out << fantini.size() << "\n";
  for(int i=0; i<fantini.size(); i++)
    out << fantini[i];
  
  for(int i=0; i<10; ++i)
    out << barberi[i];
  
  file.close();
}

bool TDPalioServer::caricaFile() {
  
  int m, f;
  QString path = "giochi/" + fileName;
  QFile file(path);
  if (!file.open(QIODevice::ReadOnly)) {
    std::cout << "NON POSSO CARICA QUESTO GIOCO" << std::endl;
    QString mex("NON POSSO CARICARE QUESTO GIOCO...");
    myStreamerOut->stringStream[0] = mex;
    for(int i=0; i<sockets.size(); ++i) {
      sendMessage(PopupMessage, sockets[i]);
      return false;
    }
  }

  QTextStream in(&file);
  //in.setVersion(QDataStream::Qt_4_0);
  
  in >> anno;
  //std::cout << anno <<std::endl;
  in >> m;
  mese = (Mese)m;
  in >> f;
  fase->setPhase((Fase)f);
  fase->setCaricato();
  //fase = (Fase)f;

  //std::cout << "FASE " << fase << std::endl;
  in >> nProva;

  for(int i=0; i<17; i++)
    in >> corrono[i];
  
  for(int i=0; i<17; i++)
    in >> luglio[i];
  
  for(int i=0; i<17; i++)
    in >> agosto[i];
  
  for(int i=0; i<17; i++)
    in >> settembre[i];
  
  int nGiocatori, nFantini;
  in >> nGiocatori;
  //std::cout << "Numero giocatori" << nGiocatori << std::endl;
  giocatori.resize(nGiocatori);
  for(int i=0; i<nGiocatori; i++)
    in >> giocatori[i];
  
  for(int i=0; i<17; i++)
    in >> contrade[i];
  
  for(int i=0; i<21; i++) {
    in >> cavalli[i];
    //std::cout << (const char*)cavalli[i].getNome().toLatin1() << std::endl;
  }

  in >> nFantini;
  fantini.resize(nFantini);
  for(int i=0; i<nFantini; i++)
    in >> fantini[i];
  
  for(int i=0; i<10; ++i) {
    in >> barberi[i];
    if (barberi[i].getIndice(0) != 0) 
      barberi[i].setContrada(&contrade[barberi[i].getIndice(0)]);
    if (barberi[i].getIndice(1) != 0) 
      barberi[i].setFantino(&fantini[barberi[i].getIndice(1)]);
    if (barberi[i].getIndice(2) != 0) 
      barberi[i].setCavallo(&cavalli[barberi[i].getIndice(2)]);
  }
  
  file.close();
  
  return true;
}
  
void TDPalioServer::estrazione(int n) {
  
  int con[17], sorte[17];
  switch(n) {
  case 0:   // Inizio
    OrdinaI(17, con, random);
    
    for(int i=0; i<17; i++)
      luglio[i] = con[i];
    
    OrdinaI(17, con, random);
    for(int i=0; i<17; i++)
      agosto[i] = con[i];
    
    for(int i=0; i<17; i++)
      settembre[i] = 0;
    break;
  case 1:   // Palio Regolare
    if (mese == Luglio)
      for(int i=0; i<17; i++) {
	corrono[i] = luglio[i];
	sorte[i] = corrono[i];
      }
    
    if (mese == Agosto)
      for(int i=0; i<17; i++) {
	corrono[i] = agosto[i];
	sorte[i] = corrono[i];
      }
    
    for(int i=0; i<7; i++) {
      if (mese == Luglio)
	luglio[i] = luglio[i+10];
      else
	agosto[i] = agosto[i+10];
    }
    
    Ordina(10, sorte, random);
    for(int i=0; i<10; i++) {
      if (mese == Luglio)
	luglio[i+7] = sorte[i];
      else
	agosto[i+7] = sorte[i];
    }
    break;
  case 2:   // Palio Straordinario
    OrdinaI(17, settembre, random);
    break;
  }
}

void TDPalioServer::sceltaCavalli() {
  
  fase->newAnswerNoSkip();
  
  QVector<int> risposta = myStreamerIn->intStream;
  for(int i=0; i<cavalli.size(); ++i) {

    //std::cout << i << " " << risposta[i] << std::endl;
    if (risposta[i] == 1)
      cavalli[i].setSelezione();
  }
   
  if (fase->answers() == 0) {
    int scelti = 0;
    for(int i=0; i<cavalli.size(); i++) {
      //std::cout << i << " " << cavalli[i].selezione() << std::endl;
      if (cavalli[i].selezione() > 5)
	scelti++;
    }

    if (scelti == 10) {
      assegnazione();
      return;
    }

    for(int i=0; i<cavalli.size(); i++) {
      if (scelti > 10) 
	if (cavalli[i].selezione() > 5)
	  cavalli[i].noSelezione();

      if (scelti < 10) 
	if (cavalli[i].selezione() < 6)
	  cavalli[i].noSelezione();
    }
    
    
    myStreamerOut->intStream.resize(1);
    myStreamerOut->intStream[0] = 10-scelti;

    myStreamerOut->cavalloStream = cavalli;
    for(int i=0; i<10; ++i) {
      for(int j=0; j<sockets.size(); ++j) {
	if (sockets[j]->state == corrono[i]) {
	  sendMessage(Tratta, sockets[j]);
	  // FIXME forse lo devi levare...anche da MySocket
	  sockets[j]->answered = false;
	  fase->waiting();
	}
      }
    }
  }
  
  return;
}

void TDPalioServer::assegnazione() {
  
  QVector<Cavallo*> cavalli_scelti;
  
  for(int i=0; i<cavalli.size(); i++)
    if (cavalli[i].selezione() > 5.)
      cavalli_scelti.push_back(&cavalli[i]);
  
  for(int i=0; i<cavalli_scelti.size()-1; i++) {
    for(int j=i+1; j<cavalli_scelti.size(); j++) {
      if (cavalli_scelti[i]->coscia() > cavalli_scelti[j]->coscia()) {
	Cavallo* temp = cavalli_scelti[i];
	cavalli_scelti[i] = cavalli_scelti[j];
	cavalli_scelti[j] = temp;
      }
    }
  }
  
  int n1[10], n2[10];
  OrdinaI(10, n1, random); // contrada
  OrdinaI(10, n2, random); // cavallo
  
  for(int i=0; i<10; i++) {
    barberi[n1[i]].setCavallo(cavalli_scelti[i]);

    ordine_prove[i][0] = corrono[i];                //estrazione
    ordine_prove[i][1] = corrono[9-i];
    ordine_prove[i][2] = corrono[n2[i]];            //assegnazione
    ordine_prove[i][3] = corrono[n2[9-i]];
    ordine_prove[i][4] = corrono[n1[i]];            // numero d'orecchio
    ordine_prove[i][5] = corrono[n1[9-i]];         
  }
  
  myStreamerOut->clear();
  
  for(int i=0; i<10; i++)
    myStreamerOut->intStream.push_back(n1[i]);
  for(int i=0; i<10; i++)
    myStreamerOut->intStream.push_back(n2[i]);
  for(int i=0; i<10; i++)
    myStreamerOut->stringStream.push_back(barberi[i].getContrada()->getNome());
  for(int i=0; i<10; i++) 
    myStreamerOut->cavalloStream.push_back(*(cavalli_scelti[i]));
  
  // messaggio da mandare a tutti i client
  for(int i=0; i<sockets.size(); ++i) {
    if (sockets[i]->type == Human) {
      sendMessage(Assegnazione, sockets[i]);
      fase->waiting();
      //for(int j=0; j<10; j++) {
      //if (sockets[i]->state == corrono[j]) {
      //  sockets[j]->answered = false;
      //}
      //}
    }
  }

  sceltaStrategia();
  formaCavalli();
  
  for(int i=0; i<10; ++i) {
    for(int j=0; j<sockets.size(); ++j) {
      if (sockets[j]->state == barberi[i].getContrada()->indice()) {
	if (sockets[j]->type == Human) {
	  myStreamerOut->cavalloStream.resize(1);
	  myStreamerOut->cavalloStream[0] = *(barberi[i].getCavallo());
	  sendMessage(AggiornaCavalloPanel, sockets[j]);
	}
      }
    }
  }
  //statusBar()->showMessage("Assegnazione");
  /*
    QCanvas *canvas = new QCanvas(centralFrame);
    canvas->resize(centralFrame->width(), centralFrame->height());
    QCanvasView *cv = new QCanvasView(canvas, centralFrame);
    cv->resize(centralFrame->width(), centralFrame->height());
    cv->setVScrollBarMode(QScrollView::AlwaysOff);
    cv->setHScrollBarMode(QScrollView::AlwaysOff);

    // mostra immagine griglie
    ImageItem *i = new ImageItem(QPixmap("./pictures/lupa_1.png"), canvas);
    i->show();

    if (soundWanted)
    QSound::play("./sound/chiarine.wav");
    ImageItem *bandiere[10];
    for(int i=0; i<10; ++i) {
    QString s = "./pictures/" + barberi[i].getContrada()->getNome() + "_1.png";
    bandiere[i] = new ImageItem(QPixmap(s), canvas);
    bandiere[i]->move(10*i, 0);
    bandiere[i]->show();

    cv->show();
  */
					   
}

void TDPalioServer::sceltaStrategia() {

  int strategy[] = { 0, 1, 0, 0, 0,
		     1, 2, 1, 0, 0,
		     2, 2, 2, 1, 0};
  
  for(int i=0; i<10; i++) {
    int cuffia = barberi[i].getContrada()->cuffia();
    float media = barberi[i].getCavallo()->media();
    int index1 = 0;
    if (media < 5)
      index1 = 2;
    else if (media > 6)
      index1 = 0;
    else
      index1 = 1;
    
    int index2;
    if (cuffia < 2)
      index2 = 0;
    else if ((cuffia > 1) && (cuffia < 11))
      index2 = 1;
    else if ((cuffia > 10) && (cuffia < 21))
      index2 = 2;
    else if ((cuffia > 20) && (cuffia < 31))
      index2 = 3;
    else
      index2 = 4;
    
    barberi[i].setStrategia(strategy[index2 + index1*5]);
  }
  
  // TODO strategia migliore con informazione sull'avversaria e sugli amici in corsa
  /*
    
    for(int i=0; i<10; i++) {
    
    float media1, media2;
    int cuffia1, cuffia2;
    
    int avversaria = Avversaria(corrono[i]);
    barberi[i].setAvversaria(avversaria);
    
    media1 = barberi[i].getCavallo()->media();
    cuffia1 = barberi[i].getContrada()->cuffia();
    
    if (avversaria != -1) {
    media2 = barberi[avversaria].getCavallo()->media();
    cuffia2 = barberi[avversaria].getContrada()->cuffia();
    } else {
    media2 = 0;
    cuffia2 = 0;
    }
    
    int amici = 0;
    for(int j=0; j<10; j++)
    if (j == i)
    continue;
    else
    if (barberi[i].getContrada()->feeling(barberi[j].getContrada()->indice()) > 6)
    amici++;
    
    int rate1, rate2;
    rate1 = Strategia(cuffia1, media1);
    if (media2 != 0)
    rate2 = Strategia(cuffia2, media2);
    else
    rate2 = -1;
    
    if ((rate1 && 1) && (rate2 & 8)) {
    barberi[i].setStrategia(0);
    continue;
    }
    
    if ((rate1 & 12) && (amici > 2)) {
    barberi[i].setStrategia(3);
    continue;
    }
    
    barberi[i].setStrategia(rate1);
    }
  */
}

QVector<Fantino> TDPalioServer::filtroFantini(Barbero b) {

  // FIXME si puo` velocizzare l'algoritmo
  QVector<Fantino> temp = fantini;
  for(int i=0; i<temp.size()-1; i++) {
    for(int j=i+1; j < temp.size(); j++) {
      if (temp[i].media() < temp[j].media()) {
	Fantino tempFantino = temp[i];
	temp[i] = temp[j];
	temp[j] = tempFantino;
      }
    }
  }
  
  QVector<Fantino> result;
  for(int i=0; i<temp.size(); i++) {
    if (temp[i].feeling(b.getContrada()->indice())  > 4.)
      result.push_back(temp[i]);   
  }

  return result;
}

void TDPalioServer::preSceltaFantino() {

  nProva++;
  //for(int i=0; i<fantini.size(); i++)
  //  myStreamerOut->fantinoStream.push_back(fantini[i]);
  QString mex("Le Contrade che corrono stanno scegliendo i fantini...");  
  myStreamerOut->stringStream[0] = mex;    
   
  for(int i=0; i<sockets.size(); i++) {
    bool corre = false;
    for(int j=0; j<10; j++) {
      if (sockets[i]->state == corrono[j]) {
	myStreamerOut->clear();
	myStreamerOut->fantinoStream = filtroFantini(barberi[j]);
	myStreamerOut->stringStream.resize(1);    
    	sendMessage(ScegliFantino, sockets[i]);
	fase->waiting();
	corre = true;
	break;
      } 
    }
    
    if (!corre)
      sendMessage(PopupMessage, sockets[i]);
  }
  
  return;
}

void TDPalioServer::sceltaFantino() {

  fase->newAnswerNoSkip();

  // FIXME non so se quello che mando e` compatibile
  for(int i=0; i<myStreamerIn->intStream.size(); i++) 
    fantini[myStreamerIn->intStream[i]].setOfferta(myStreamerIn->offertaStream[i]);

  if (fase->answers() == 0)
    rispostaFantino();

  return;    
}

void TDPalioServer::rispostaFantino() {
  
  for(int z=0; z<fantini.size(); z++) {
    QVector<Offerta> off = fantini[z].getOfferte();
    
    if (off.size() > 1) {
      for(int nOff = 0; nOff<off.size(); nOff++) {
	float coeff = ((2. - (float)barberi[off[nOff].chi()].strategia())/2.)*33. +
	  33 * (1 - pow(2, (fantini[z].feeling(off[nOff].chi()/10.)))) +
	  15 * (barberi[off[nOff].chi()].getCavallo()->media()/10.) +
	  15 * compatibilita(fantini[z].caratteristiche(), barberi[off[nOff].chi()].getCavallo()->caratteristiche())/ 20.;
	
	off[nOff].setCoefficiente(coeff);
      }
      
      for(int i=0; i<off.size()-1; i++) {
	for(int j=i+1; j<off.size(); j++) {
	  if (off[i].coefficiente() < off[j].coefficiente()) {
	    Offerta temp = off[i];
	    off[i] = off[j];
	    off[j] = temp;
	  }
	}
      }
      
      // FIXME PER IL MOMENTO NON C'E` BALLOTTAGGIO
      //float diff = (off[0].coefficiente() - off[1].coefficiente())/off[0].coeffic\iente();
    
      //if (diff < 10) {
      // AVVERTI DEL BALLOTTAGGIO
      //continue;
      //}

      fantini[z].setContrada(barberi[off[0].chi()].getContrada()->indice());
      barberi[off[0].chi()].setFantino(&fantini[z]);

      for(int i=0; i< off.size(); i++) {
	for(int i=0; i<sockets.size(); i++) {
	  if (sockets[i]->state == barberi[off[0].chi()].getContrada()->indice()) {
	    if (sockets[i]->type == Human) {
	      if (i==0) {
		QString mex("Il Fantino ");
		mex = mex + fantini[z].getNome() + " ha accettato la tua offerta.";
		myStreamerOut->stringStream[0] = mex;    
		sendMessage(PopupMessage, sockets[i]);
	      } else {
		QString mex("Il Fantino ");
		mex = mex + fantini[z].getNome() + " ha rifiutato la tua offerta.";
		myStreamerOut->stringStream[0] = mex;    
		sendMessage(PopupMessage, sockets[i]);
	      }
	    }
	  }
	}
      }
    }
  }

  // FIXME vedere se si vuole fare un secondo turno
  fase->newPhase(eProve);
  //controller(eProve);
}

void TDPalioServer::prove() {
  
  fase->newAnswerNoSkip();

  if (fase->answers() == 10) {
    for(int i=0; i<10; ++i)
      for(int j=0; j<sockets.size(); ++j) 
	if (sockets[j]->state == corrono[i])
	  sendMessage(StrategiaProve, sockets[j]);
    
    return;
  }

  if (fase->answers() == 0) {
    QString report;
    // FIXME aggiungere vincitore della prova
    miglioramentoProve(report);

    for(int j=0; j<sockets.size(); j++) 
      if (sockets[j]->type == Human) 
	sendMessage(ReportProva, sockets[j]);    

    azzeraSockets();
    inserisciPartito();
  }
}

void TDPalioServer::miglioramentoProve(QString& report) {

  for(int i=0; i<10; i++) {
    ProveStrategie strate = barberi[i].getProve();
    int limite = 0;
 
    switch (strate[nProva].first) {
    case 0:
      break;
    case 1:
      {
	report += barberi[i].getContrada()->getNome() + " prova lo Spunto ";
	limite = 50 + (7 - barberi[i].forma(1)) * 5;
	break;
      }
    case 2:
      {
	// FIXME questo dipendera` dal posto ????
	// sicuramente da togliere se e` di rincorsa
	report += barberi[i].getContrada()->getNome() + " prova la Mossa ";
	limite = 50 + (7 - barberi[i].forma(2)) * 5;
	break;
      }
    case 3:
      {
	report += barberi[i].getContrada()->getNome() + " prova le Curve ";
	limite = 50 + (7 - barberi[i].forma(3)) * 5;
	break;
      }
    }

    int esito = random->Integer(100);
    if (esito < limite) {
      barberi[i].setForma(strate[nProva].first, 11);
      report += "con esito positivo.\n";
    }
    else {
      barberi[i].setForma(strate[nProva].first, -11);
      report += "con esito negativo.\n";
    }

    if ((esito > 98) && (strate[nProva].first == 3)) {
      report += "con esito negativo.\n";
      report += "Caduta rovinosa !!!\n";
      int info1 = random->Integer(100);
      int info2 = random->Integer(100);

      if ((info1 > 70) && (info1 < 95)) {
	barberi[i].getFantino()->setInfortunio(1);
	report += "Lieve infortunio per il Fantino.\n";
      } else if (info1 > 94) {
	barberi[i].getFantino()->setInfortunio(2);
	report += "Grave infortunio per il Fantino !!!\n";
      } else 
	report += "Fortunatamente nessuna conseguenza per il Fantino.\n";

      if ((info2 > 70) && (info2 < 95)) {
	barberi[i].getCavallo()->setInfortunio(1);
	report += "Lieve infortunio per il Cavallo.\n";
      } else if (info2 > 94) {
	barberi[i].getCavallo()->setInfortunio(2);
	report += "Grave infortunio per il Cavallo !!!\n";
      } else 
	report += "Fortunatamente nessuna conseguenza per il Cavallo.\n";
    }
  }
}

void TDPalioServer::inserisciPartito() {

  int risposte = 0;
  for(int i=0; i<sockets.size(); i++) {
    for(int j=0; j<10; j++) 
      if (sockets[i]->state == corrono[j])
	if(sockets[j]->answered)
	  risposte++;
  }
  
  if (risposte == 0) {
    for(int i=0; i<10; ++i)
      for(int j=0; j<sockets.size(); ++j) 
	if (sockets[j]->state == corrono[i])
	  sendMessage(Partiti, sockets[j]);
    
    return;
  }

  for(int i=0; i<myStreamerIn->intStream.size(); i++) 
    barberi[myStreamerIn->intStream[i]].setPartito(myStreamerIn->partitoStream[i]);

  if (risposte == 10) {
    azzeraSockets();
    rispostaPartito();
  }

  return;    
}

void TDPalioServer::rispostaPartito() {

  for(int z=0; z<barberi.size(); z++) {

    if (barberi[z].strategia() != 2) {
      barberi[z].clearPartiti();
      continue;
    }
    
    QVector<Partito> par = barberi[z].getPartiti();
    myStreamerOut->partitoStream.clear();    
        
    if (par.size() > 1) {
      for(int j=0; j<par.size();j++) {
	// FIXME FORSE NON FUNZIONA !!!!!
	if (barberi[par[j].getContrada()].strategia() != 0)
	  par.remove(j);
      }
    }  
    
    for(int i=0; i<sockets.size(); i++) {
      if (sockets[i]->state == (int)barberi[z].getContrada()->indice()) {
	myStreamerOut->partitoStream = par;    
	sendMessage(Partiti, sockets[i]);
      }
    }
  }
}

void TDPalioServer::segnatura() {

  int battesimi = 0;
  for(int i=0; i<10; i++)
    if (barberi[i].getFantino()->getNome() == "FantinoNuovo")
      battesimi++;

  if (battesimi > 0) {
    for(int i=0; i<10; i++) {
      if (barberi[i].getFantino()->getNome() == "FantinoNuovo") {
	for(int j=0; j<sockets.size(); j++) {
	  if (sockets[j]->state == (int)barberi[i].getContrada()->indice()) {
	    myStreamerOut->intStream[0]++;
	    if (sockets[j]->type == Human) {
	      sendMessage(NomeAlFantino, sockets[i]);
	    } else {
	      int ind[17];
	      for(int z=0; z<17; z++)
		ind[z] = -1;

	      for(int z=0; z<sockets.size(); z++) {
		if (sockets[z]->type == Human) {
		  ind[z] = z;
		}
	      }
		
	      OrdinaI(17, ind, random);
	      for(int z=0; z<17; z++) {
		if (ind[z] != -1) {
		  sendMessage(NomeAlFantino, sockets[ind[z]]);
		  break;
		}
	      }
	    }
	  }
	}
      }
    }
  } else {
    for(int j=0; j<sockets.size(); j++) 
      if (sockets[j]->type == Human) 
	sendMessage(Segnatura, sockets[j]);
  }
}

void TDPalioServer::palio() {

  // prima cosa la mossa
  // partiti mossa
  // con i soliti numeri casuali fai il loop principale della corsa
  // simula partiti ed eventi della corsa
  // alla fine avverti i clienti di chi ha vinto

  // FIXME per la versione alfa niente grafica
  // FIXME magari prima ci puoi mettere la scelta della strategia di corsa
}

void TDPalioServer::mossa() {

  // decidi mossa
  // falla vedere ai client
  // manda messaggio dei partiti per la mossa
  // ricevi i partiti qui oppure adatta il pezzo generale dei partiti
}

void TDPalioServer::finePalio() {
  // FIXME aggiorna tutte le classifiche
  // i soldi dei partiti e per la vittoria
  // controlla se si ritira qualche fantino e cavallo
  // mettere eta ingresso fantino casuale
  // avverti i vari client
  // controlla se ci devono essere delle elezioni
  // eventualmente gestisci il cambio di contrada
 }

void TDPalioServer::formaCavalli() {
  //FIXME per il momento la forma e` veramente casuale da 3 a 10
  // poi si cambiera`

  for(int i=0; i<10; i++) {
    int forma = random->Integer(7) + 3;
    barberi[i].getCavallo()->setForma(forma);
  }
}

void TDPalioServer::preTratta() {
  
  int cav[21];
  OrdinaI(21, cav, random);

  for(int i=0; i<cavalli.size(); i++) {
    cavalli[i].setCoscia(cav[i]);
    cavalli[i].noSelezione();
  }

  // FIXME credo non serva piu` a niente
  azzeraSockets();

  myStreamerOut->intStream.resize(1);
  myStreamerOut->intStream[0] = 10;
  myStreamerOut->cavalloStream = cavalli;
  //for(int i=0; i<cavalli.size(); i++)
  //  std::cout << (const char*) cavalli[i].getNome().toLatin1() << std::endl;

  for(int i=0; i<10; ++i) {
    for(int j=0; j<sockets.size(); ++j) {
      //std::cout << "STATO:" << sockets[j]->state << std::endl;
      if (sockets[j]->state == corrono[i]) {
	sendMessage(Tratta, sockets[j]);
	//sockets[j]->answered = false;
	fase->waiting();
      }
    }
  }
}

void TDPalioServer::azzeraSockets() {
  
  for(int i=0; i<sockets.size(); i++) 
    for(int j=0; j<10; j++) 
      if (sockets[i]->state == corrono[j])
	sockets[i]->answered = false;
}
