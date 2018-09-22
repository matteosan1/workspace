#ifndef FASE_H
#define FASE_H

enum Fase {eInizio, eEstrazione, eTratta, eSceltaFantino, eProve, eSegnatura, ePalio, eFinePalio};

class TDPalioServer;

class FaseGioco {
 public:
  FaseGioco(TDPalioServer*);
  ~FaseGioco();
  
  Fase currentPhase() { return _fase; };
  void newPhase();
  void newPhase(Fase);
  void setPhase(Fase f) { _fase = f; };
  void setWaiting(int i) { risposte = i; };
  void setCaricato() { _continuato = true; };

  void newAnswer();
  void newAnswerNoSkip();
  void waiting() { risposte++; };
  int answers() { return risposte; };
  bool isCaricato();

 private:
  Fase _fase;
  int risposte;
  bool _continuato;
  TDPalioServer* server;
};

#endif
