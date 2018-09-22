#include "tdpalioaiclient.h"

#include <QtNetwork>

#include "../tdpaliocommon/utility.h"
#include "../tdpaliocommon/TRandom.h"

#include <iostream>
using namespace std;

TDPalioAiClient::TDPalioAiClient(int a, TRandom* r) : QObject(), random(r) {

  // FIXME serve ??????
  tcpSocket = 0;
  openConnection(a);
  
  myStreamer = new MyStreamer();
}

void TDPalioAiClient::openConnection(int a) {

  tcpSocket = new QTcpSocket(this);
  tcpSocket->abort(); // FIXME perche` fa subito abort ?????
  tcpSocket->connectToHost(QHostAddress::LocalHost, a);

  // legge i dati in arrivo
  connect(tcpSocket, SIGNAL(readyRead()), this, SLOT(incomingMessage()));
  // Connette alcuni slot
  connect(tcpSocket, SIGNAL(error(QAbstractSocket::SocketError)),
	  this, SLOT(displayError(QAbstractSocket::SocketError)));
}

void TDPalioAiClient::incomingMessage() {

    QDataStream in(tcpSocket);
    in.setVersion(QDataStream::Qt_4_0);
    processMessage(in);
}

void TDPalioAiClient::displayError(QAbstractSocket::SocketError socketError) {
  switch (socketError) {
  case QAbstractSocket::RemoteHostClosedError:
    std::cerr << "RemoteHostClosedError" << std::endl;
    break;
  case QAbstractSocket::HostNotFoundError:
    std::cerr << "The host was not found. Please check the name and port settings." << std::endl;
    break;
  case QAbstractSocket::ConnectionRefusedError:
    std::cerr << "The connection was refused by the peer. makee sure the fortune server is running, and check that the host name and port settings are correct." << std::endl;
    break;
  default:
    std::cerr << qPrintable(tcpSocket->errorString()) << std::endl;
  }
}

void TDPalioAiClient::processMessage(QDataStream& in) {

  //QString mex;
  
  while(1) {
    in >> (*myStreamer);
    //int code;
    //QString s;
    //in >> code;
    std::cout << "CODICE AI RECV:" << myStreamer->code << std::endl;
    switch((int)myStreamer->code) {
	case Message:
	std::cout << "chiu chiu" << std::endl;
	break;
      //case Estrazione:
      //    break;
      
    case Initialize:
      // FIXME definire il socket_number magari puo` fare comodo
      //    in >> socket_number;
      //    in >> isChoosing;     // condizionare il tasto di avvio
      break;
    case ScegliFantino:
      {
	sceltaFantino(myStreamer->intStream[0],
		      myStreamer->fantinoStream);
	break;
      }
    case Tratta:
      {
	sceltaCavalli(myStreamer->intStream[0], myStreamer->cavalloStream);
	break;
      }
    }
    
    
    if (in.atEnd())
      break;
  }
}
















void TDPalioAiClient::sendMessage(MessageCode code) {

    std::cout << "CODICE AI SEND: " << code << std::endl;
    QByteArray block;
    QDataStream out(&block, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_4_0);
    myStreamer->socket_number = socket_number;
    myStreamer->code = code;

    switch ((int)code) {
    case Tratta:
      {
	break;
      }
    }

    out << (*myStreamer);
    tcpSocket->write(block);
}








void TDPalioAiClient::sceltaFantino(int a, QVector<Fantino> fantini) {
  
  // FIXME dove lo prende round ???
  round = 0;
  int contrada = barbero->getContrada()->indice();
  
  // FIXME strategia alcune volte e` 0-1-2 altre 2-1-0
  // FIXME al primo giro consenti 2 scelte ??????????
  if (round == 0) {
    if (barbero->strategia() == 2) {
      for(int i=0; i<fantini.size(); i++) {
	for(int j=0; j<fantini.size(); j++) {
	  int indicei = fantini[i].killer()*10/3 + 10*amicizia(fantini[i].feeling(contrada));
	  int indicej = fantini[j].killer()*10/3 + 10*amicizia(fantini[j].feeling(contrada));
	  
	  if (indicei < indicej) {
	    Fantino temp = fantini[i];
	    fantini[i] = fantini[j];
	    fantini[j] = temp;
	  }
	}
      }
    }
    
    if (barbero->strategia() != 2) {
      for(int i=0; i<fantini.size()-1; i++) {
	for(int j=i+1; j<fantini.size(); j++) {
	  
	  float capi = 70 * fantini[i].media()/10 + amicizia(fantini[i].feeling(contrada))
	    + compatibilita(fantini[i].caratteristiche(), barbero->getCavallo()->caratteristiche());
	  float capj = 70 * fantini[j].media()/10 + amicizia(fantini[j].feeling(contrada))
	    + compatibilita(fantini[j].caratteristiche(), barbero->getCavallo()->caratteristiche());
	  if (capi < capj) {
	    Fantino temp = fantini[i];
	    fantini[i] = fantini[j];
	    fantini[j] = temp;
	  }
	}
      }
    }
    
    int tot = 0;
    int llim = 0;
    if (barbero->strategia() == 0) {
      tot = 5;
      llim = 0;
    }
    
    if (barbero->strategia() == 1) {
      tot = fantini.size();
      llim = 5;
    }
    if (barbero->strategia() == 2) {
      tot = fantini.size();
      llim = 0;
    }

    int fan = random->Integer(tot - llim) + llim;
    Offerta off;
    // FIXME riempi il numero per ogni barbero
    off.setOfferta(barbero->getNumero(), 0, 0, 0);
    // FIXME FORSE AZZERA STREAMER
    myStreamer->intStream[0] = fan;
    myStreamer->offertaStream.push_back(off);
    sendMessage(ScegliFantino);
  }

  // FIXME piu` di un round ?????????
  if (round == 1) {
    // ricalcola sigma_cf
    // ordina i fantini come prima, se il secondo in lizza e` meno compatibile di solo il 10%
    // scegli casuale al 50%+-simpatia se rilanciare o fare offerta al secondo
    // se no rilancia di un fattore casuale tanto piu` grande quanto minore e` la simpatia
    
    // rimanda messaggio al server
  }
}

void TDPalioAiClient::sceltaCavalli(int scelti, QVector<Cavallo> cavalli) {
 
  // FIXME PER LA VERSIONE BETA SCEGLI 334 SEMPRE

  std::cout << "SCELTI AI:" << scelti << std::endl;
  QVector<int> selezione;
  selezione.resize(cavalli.size());

  int cav[cavalli.size()], fascia[cavalli.size()];
  float media[cavalli.size()];  
  int strategia[3];
  
  // ordina i cavalli per bravura
  for(int i=0; i<cavalli.size(); i++) 
    media[i] = 10-cavalli[i].media();
   
  OrdinaF_fixed(21, cav, media);
  //std::cout << "ORDINE PER MEDIA" << std::endl;
  //for(int i=0; i<cavalli.size(); i++)
  //  std::cout << cav[i] << "  " << cavalli[i].media() << std::endl;

  for(int i=0; i<21; i++) {
    if (i < 6)
      fascia[cav[i]] = 0;
    else if (i>10)
      fascia[cav[i]] = 2;
    else
      fascia[cav[i]] = 1;
  }
  
  // scegline 3 fra i primi 5
  // 3 fra 5 e 10
  // 4 fra i restanti 11

  strategia[0] = 3; strategia[1] = 3; strategia[2] = 4;
  if (scelti < 0) {
    for(int i=0; i<21; i++) {
      if (cavalli[i].selezione() != 0)
	selezione[i] = -1;
      //	strategia[fascia[i]]--;
      //else 
    }
  } else {
    for(int i=0; i<21; i++) { 
      if (cavalli[i].selezione() != 0) {
	strategia[fascia[i]]--;
	selezione[i] = -1;
      }
    }
  }
  

  // FIXME aggiungere bonus ogni turno di scelta per scegliere quello piu` forte
  int scelte = strategia[0] + strategia[1] + strategia[2];
  while (scelte > 0) {
    for(int j=0; j<21; j++) {
      if (selezione[j] == 0) {
	if (strategia[fascia[j]] != 0) {
	  int center = 50 - cavalli[cav[j]].paliCorsi() + cavalli[cav[j]].paliVinti()*5;
	  int punti = random->Integer(100);
	  if (punti > center) {
	    selezione[j] = 1;
	    strategia[fascia[j]]--;
	    scelte--;
	  }
	}
      }
    }
  }
  /*
  } else {
    while (scelte < 0) {
      for(int j=0; j<21; j++) {
	if (selezione[j] == 0) {
	  if (strategia[fascia[j]] != 0) {
	    int center = 50 - cavalli[cav[j]].paliCorsi() + cavalli[cav[j]].paliVinti()*5;
	    int punti = random->Integer(100);
	    if (punti < center) {
	      selezione[j] = 1;
	      strategia[fascia[j]]++;
	      scelte++;
	    }
	  }
	}
      }
    }
  }
  */
  myStreamer->intStream = selezione;
  sendMessage(Tratta);
}

void TDPalioAiClient::inserisciPartito(QVector<Barbero> barberi) {
  
  QVector<int> ind;
  QVector<Partito> par = barbero->getPartiti();
  for(int i=0; i<par.size(); i++)
    ind.push_back(par[i].getFermata());

  QVector<Barbero> bar_v, bar_p, bar_n;
  for(int i=0; i<10; i++) {
    if (i == barbero->getNumero()) 
      continue;
    
    bool skippa = false;
    for(int j=0; j<ind.size(); j++)
      if (ind[j] == i) 
	skippa = true;

    if (skippa)
      continue;
    
    if (barberi[i].strategia() == 0)
      bar_v.push_back(barberi[i]);
    if (barberi[i].strategia() == 1 && !barberi[i].partitiAccettati())
      bar_n.push_back(barberi[i]);

    // FIXME togli quelle che hanno la nemica in campo 
    // aggiungere un metodo in barberi
    // FIXME togli anche la nemica del client !!!!!!!!!!!
    if (barberi[i].strategia() == 2 && !barberi[i].partitiAccettati())
      bar_v.push_back(barberi[i]);
  }
  
  for (int i=0; i<bar_v.size()-1; i++) {
    for(int j=i+1; j<bar_v.size(); j++) {
      float brav1 = sqrt(pow(bar_v[i].getCavallo()->media(), 2) +
			 pow(bar_v[i].getFantino()->media(), 2));

      float brav2 = sqrt(pow(bar_v[j].getCavallo()->media(), 2) +
			 pow(bar_v[j].getFantino()->media(), 2));
      if (brav1 < brav2) {
	Barbero temp = bar_v[i];
	bar_v[i] = bar_v[j];
	bar_v[j] = temp;
      }
    }
  }

  for (int i=0; i<bar_n.size()-1; i++) {
    for(int j=i+1; j<bar_n.size(); j++) {
      float brav1 = sqrt(pow(bar_n[i].getCavallo()->media(), 2) +
			 pow(bar_n[i].getFantino()->media(), 2));

      float brav2 = sqrt(pow(bar_n[j].getCavallo()->media(), 2) +
			 pow(bar_n[j].getFantino()->media(), 2));
      if (brav1 < brav2) {
	Barbero temp = bar_n[i];
	bar_n[i] = bar_n[j];
	bar_n[j] = temp;
      }
    }
  }
  
  for (int i=0; i<bar_p.size()-1; i++) {
    for(int j=i+1; j<bar_p.size(); j++) {
      float brav1 = 60*fantini[i].killer()/3 + 20*amicizia(bar_p[i].getContrada()->feeling(barbero->getContrada()->indice())) + 20*amicizia(1-bar_p[i].getContrada()->feeling(bar_v[0].getContrada()->indice()));

      float brav2 = 60*fantini[i].killer()/3 + 20*amicizia(bar_p[j].getContrada()->feeling(barbero->getContrada()->indice())) + 20*amicizia(1-bar_p[j].getContrada()->feeling(bar_v[0].getContrada()->indice()));

      if (brav1 < brav2) {
	Barbero temp = bar_p[i];
	bar_p[i] = bar_p[j];
	bar_p[j] = temp;
      }
    }
  }
  // FIXME come determina il suo stesso indice del barbero intendo ????
  // FIXME azzera partitoStreamer
  Partito p1, p2;
  p1.setPartito(bar_p[0].estrazione(), bar_v[0].estrazione(), 1, 0);
  p2.setPartito(bar_n[0].estrazione(), bar_n[0].estrazione(), 2, 0);
  
  myStreamer->partitoStream.push_back(p1);
  myStreamer->partitoStream.push_back(p2);
  sendMessage(Partiti);
}

void TDPalioAiClient::rispostePartiti(QVector<Barbero> barberi) {

  QVector<Partito> par = myStreamer->partitoStream;

  for(int i=0; i<par.size()-1; i++) {
    for(int j=i+1; j<par.size(); j++) {
      int brav1 = 0, brav2 = 0;
      if (barbero->strategia() == 1) {
	brav1 = 70*sqrt(pow(barberi[par[i].getContrada()].getCavallo()->media(), 2) + pow(barberi[par[i].getContrada()].getFantino()->media(), 2)) + 
	  30*amicizia(barbero->getContrada()->feeling(barberi[par[i].getContrada()].getContrada()->indice()));
        brav2 = 70*sqrt(pow(barberi[par[j].getContrada()].getCavallo()->media(), 2) + pow(barberi[par[j].getContrada()].getFantino()->media(), 2)) + 
	  30*amicizia(barbero->getContrada()->feeling(barberi[par[j].getContrada()].getContrada()->indice()));
      }

      if (barbero->strategia() == 2) {
	brav1 = 60*sqrt(pow(barberi[par[i].getContrada()].getCavallo()->media(), 2) + pow(barberi[par[i].getContrada()].getFantino()->media(), 2)) + 
	  20*amicizia(barbero->getContrada()->feeling(barberi[par[i].getContrada()].getContrada()->indice())) +
	  20*amicizia(1-barbero->getContrada()->feeling(barberi[par[i].getContrada()].getContrada()->indice()));

	brav2 = 60*sqrt(pow(barberi[par[j].getContrada()].getCavallo()->media(), 2) + pow(barberi[par[j].getContrada()].getFantino()->media(), 2)) + 
	  20*amicizia(barbero->getContrada()->feeling(barberi[par[j].getContrada()].getContrada()->indice())) +
	  20*amicizia(1-barbero->getContrada()->feeling(barberi[par[j].getFermata()].getContrada()->indice()));
	
      }
      
      if (brav1 < brav2) {
	Partito temp = par[i];
	par[i] = par[j];
	par[j] = temp;
      }
    } 
  }

  // FIXME fissa la scelta per considerare anche il pagamento.
  myStreamer->partitoStream[0] = par[0];
  sendMessage(Partiti);
}
