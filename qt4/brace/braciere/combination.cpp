#include <vector>
//#include <map>
#include <iostream>
#include <fstream>
//#include <algorithm>
//#include <bitset>

#include "prenotazioni.h"
#include "combgen.h"

using namespace std;

void LoadData(Mappa<Tavolo>& t, Mappa<Prenotazione>& p) {
  
  int j=0;

  // definisci i tavoli vuoti
  int dummy, zone;
  char pippo[50];
  ifstream f1("tavoli.txt");
  Tavolo tav_temp;
  while(!f1.eof()) {
    f1 >> dummy >> zone;
    tav_temp.SetPosti(dummy);
    tav_temp.SetZona((Zona)zone);
    t.push_back(tav_temp);
  }

  // definisci le prenotazioni
  ifstream f2("prenotazioni.txt");
  Prenotazione pre_temp;

  while(!f2.eof()) {
    f2 >> dummy;
    pre_temp.SetGente(dummy);
    sprintf(pippo, "A%d", j);
    pre_temp.SetNome(pippo);
    j++;
    p.push_back(pre_temp);
  }
}


void ErasePrenotazione(Prenotazione p, vector<Prenotazione> *preno) {

  // elimina prenotazioni usate dalla lista
  vector<Prenotazione>::iterator it;
  for(it=preno->begin(); it != preno->end(); ) {
    if (it->GetNome() == p.GetNome())
      it = proeno->erase(it);
    else	
      it++;
  }
}

vector<Prenotazione*> SelezionaCombinazioni(vector<Prenotazione*> elements, int posti_vuoti) {
  
  vector<Prenotazione*> results;
  
  unsigned int nItems = 1;
  do {
    CombinationGenerator<Prenotazione*> CG(elements, nItems);
    //int nTries = 0;
    while (CG.NextCombination(results)) {
      
      unsigned int nSize = results.size();
      int somma = 0;
      for (unsigned int j=0; j<nSize; j++) {
	//cout << results[j].GetGente() << " ";
	somma += results[j]->GetGente();
      }
      //cout << endl;
      // nTries++;
      if (somma == posti_vuoti)
	return results;
    }
    nItems++;
  } while (nItems <= elements.size());
  //cout << "Number of combinations is " << nTries << endl;
  results.clear();
  return results;   
}

int main() {
  
  Mappa<Prenotazione> pre_map;
  Mappa<Tavolo> tav_map;
  
  LoadData(tav_map, pre_map);

  int offset = 0;
  int NumeroZone = 4;
  
  // inserisci prima tutti quelli che chiedono il tavolo
  for(unsigned int i=0; i<pre_map.data.size(); ++i) {
    int numeroTavolo = pre_map.data[i]->GetTavolo();
    if (numeroTavolo != -1) {
      if (numeroTavolo > 0 && numeroTavolo < tav_map.data.size()) {
	tav_map.data[numeroTavolo].AddPreno(&(pre_map.data[i]));
	// elimina prenotazione
	ErasePrenotazione(pre_map.data[i], &(pre_map.data));
      } else {
	cerr << "IL TAVOLO NON ESISTE" << endl;
      }
    }
  }

























  // poi inserisci i capotavola per zona
  for(unsigned int i=0; i<p.size(); ++i) {
    if (p[i]->GetCapotavola()) {
      if (p[i]->GetZona() != Nulla) {
	vector<Tavolo*> temp = tav_map[p[i]->GetZona()];
	vector<Tavolo*>::iterator it;
	for(it = temp.begin(); it != temp.end(); ++it) {
	  if ((*it)->GetCapotavola() < 2) {
	    (*it)->AddPreno(p[i]);
	    ErasePrenotazione(p[i], &p);
	    break;
	  }
	}
      }
    }
  }

  // gestire i capotavola senza zona preferenziale
  for(unsigned int i=0; i<p.size(); ++i) {
    if (p[i]->GetCapotavola()) {
      if (p[i]->GetZona() == Nulla) {
	vector<Tavolo*> temp = tav_map[Nulla];
	vector<Tavolo*>::iterator it;
	for(it = temp.begin(); it != temp.end(); ++it) {
	  if ((*it)->GetCapotavola() < 2) {
	    (*it)->AddPreno(p[i]);
	    ErasePrenotazione(p[i], &p);
	    break;
	  }
	}
      }
    }
  }

  // looppa sui tavoli prima per zona poi globalmente
  // se metti il Nulla alla fine degli enum dovrebbe gia` funzionare
  for(int z=0; z<NumeroZone; ++z) {

    vector<Tavolo*> t_zone = tav_map[(Zona)z];
    vector<Tavolo*>::iterator it, it2;
    
    vector<Prenotazione*> p_tot = pre_map[Nulla];
    vector<Prenotazione*> p_zone = pre_map[(Zona)z];

    // ordina i tavoli per posti vuoti
    for(unsigned int i=0; i<t_zone.size()-1; ++i) {
      for(unsigned int j=i+1; j<t_zone.size(); ++j) {
	if (t_zone[i]->GetRimasti() < t_zone[j]->GetRimasti()) {
	  Tavolo* tav_temp = t_zone[j];
	  t_zone[j] = t_zone[i];
	  t_zone[i] = tav_temp;
	}
      }
    }  
    
    do {
      
      bool aggiunta = false;
      for(it = t_zone.begin(); it != t_zone.end(); ++it) {
	
	// cerca tutte le combinazioni di prenotazioni anche qui per zona
	vector<Prenotazione*> result = SelezionaCombinazioni(p_zone, (*it)->GetRimasti()-offset);
	
	if (result.size() != 0) {
	  aggiunta = true;
	  // riempi il tavolo con le prenotazioni
	  for(unsigned int i=0; i<result.size(); i++) {
	    cout << result[i]->GetNome() << endl;	
	    (*it)->AddPreno(result[i]);
	    ErasePrenotazione(result[i], &p_tot);
	  }
	  
	  if (pre.size() == 0) {
	    // esci
	    break;
	  }
	}
      }
      cout << "2" << endl;
      
      // se i tavoli sono finiti ripeti il procedimento ammettendo di lasciare posti vuoti nei tavoli
      if (!aggiunta)
	offset++;
      cout << "3" << endl;
      // calcola il numero massimo di posti vuoti ammessi
      int maxOffset = 0;
      for(unsigned int i=0; i<temp.size(); i++) {
	//cout << tav[i].GetRimasti() << endl;
	if (temp[i]->GetRimasti() > maxOffset)
	  maxOffset = temp[i]->GetRimasti();
      }
      cout << "++++++++++++++" << endl;
      for(unsigned int i=0; i<pre.size(); i++)
	cout << pre[i].GetGente() << " ";
      cout << "-------------------" << endl;
      
      if (pre.size() == 0)
	break;
      
      // se raggiungi un certo offset esci con errore
      if (offset > maxOffset - 1) {
	// tira una eccezione ed esci
	cerr << "Problema !!!!" << endl;
	break;
      }
    } while(1);
  }
}
