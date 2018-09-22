#include "fase.h"
#include "tdpalioserver.h"


FaseGioco::FaseGioco(TDPalioServer* s):_fase(eInizio), risposte(0), _continuato(false), server(s)
{}

FaseGioco::~FaseGioco() 
{}

bool FaseGioco::isCaricato() {

  bool result = _continuato;
  
  if (_continuato)
    _continuato = false;
  
  return result;
}

void FaseGioco::newAnswerNoSkip() {
  if (risposte > 0) 
    risposte--;
}

void FaseGioco::newAnswer() {
  std::cout << "Fase, risposte" << risposte << std::endl;
  risposte--;
  std::cout << "Fase, risposte" << risposte << std::endl;
  if (risposte == 0) {
     std::cout << "NUOVA FASE" << std::endl;
    int a = (int)_fase;
    a++;
    _fase = (Fase)a;
    std::cout << "FASE: " << _fase << std::endl;
    server->controller();
    return;
  }
}

void FaseGioco::newPhase(Fase f) {
  _fase = f;
  server->controller();
}

void FaseGioco::newPhase() {
  int a = (int)_fase;
  a++;
  _fase = (Fase)a;
  server->controller();
  return;
}
