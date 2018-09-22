#ifndef _PRENOTAZIONI_
#define _PRENOTAZIONI_

#include<string>
#include<vector>

using namespace std;

enum Zona {Nulla=-1, Alberi=0, Braciere=1, Riccio=2, Piazza=3};

class Prenotazione {
  
 public:

  Prenotazione();
  Prenotazione(string a, int b, int c=0):nome(a), tavolo(c), gente(b) 
    {}
  ~Prenotazione();
  
  void SetNome(string i) { nome = i; };
  void SetTavolo(int i) { tavolo = i; };
  void SetGente(int i) { gente = i; };
  void SetZona(Zona i) { zona = i; }; 
  void SetCapotavola(bool i) { capotavola = i; };
  
  string GetNome() { return nome; };
  int GetTavolo() { return tavolo; };
  int GetGente() { return gente; };
  bool GetCapotavola() { return capotavola; };
  Zona GetZona() { return zona; };
  
 private:
  string nome;
  int tavolo;
  int gente;
  Zona zona;
  bool capotavola;
};

class Tavolo {
  
 public:
  Tavolo();
  ~Tavolo();

  void SetNumero(int n) { numero = n; };
  void SetPosti(int n);
  void SetZona(Zona z) { zona = z; };
  
  void AddPreno(Prenotazione* p);
  //void DelPreno();

  int GetNumero() { return numero; };
  int GetRimasti() { return rimasti; };
  int GetPosti() { return posti; };
  vector<Prenotazione*> GetPreno() { return preno; };
  int GetCapotavola();
  Zona GetZona() { return zona; };

 private:
  vector<Prenotazione*> preno;
  int numero;
  int posti;
  int rimasti;
  Zona zona;
};

template<class T>
class Mappa {

 public:
  Mappa() {};
  ~Mappa() {};

  vector<T*> operator[](Zona zona){
    std::vector<T*> result;
    for(unsigned int i=0; i<.size(); ++i) {
      T* temp = &data[i];
      if ((temp->GetZona() == zona) || (zona == Nulla))
	result.push_back(temp);
    }
    
    return result;
  }
  
  vector<T> data;
};

#endif
