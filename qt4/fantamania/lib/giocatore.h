#ifndef __GIOCATORE__
#define __GIOCATORE__

#include "prestazione.h"
#include "punteggi.h"

#include <QString>
#include <QTextStream>

#include <vector>

using namespace std;

enum Ruolo
{
    Portiere = 0,
    DifensoreLaterale = 21,
    DifensoreCentrale = 22,
    CentrocampistaCentrale = 31,
    CentrocampistaEsterno = 32,
    CentrocampistaTrequartista = 33,
    AttaccanteCentrale = 41,
    AttaccanteMovimento = 42,
    FuoriRosa = -1
};

class Giocatore {
 public:
  Giocatore();
  virtual ~Giocatore();

  friend QTextStream& operator<<(QTextStream& p, Giocatore x);
  friend QTextStream& operator>>(QTextStream& p, Giocatore& x);

  QString GetNome() { return nome; }
  QString GetCognome() { return cognome; }
  QString GetNomeCompleto() {
      if (nome == " ")
        return cognome;
      else
        return cognome+QString(" ")+nome.left(1)+QString(".");
  };
  float GetMedia(Punteggi* p);
  int GetAmmonizioni();
  int GetEspulsioni();
  QString GetPresenze();
  int GetGiocate();
  int GetRigori();
  int GetAutogoal();
  int GetGoal();

  int GetRuolo() { return ruolo; }
  QString GetSquadra() { return squadra; }
  int GetPrezzo() { return prezzo; }
  Prestazione& GetPartita(int);
  //int HaGiocato(int g) { return GetPartita(g).HaGiocato(); };

  void SetGiocatore(QString a, QString b, int c, QString e, int f);
  void SetNome(QString a) { nome = a; }
  void SetCognome(QString a) { cognome = a; }
  void SetRuolo(int a) { ruolo = a; }
  void SetPartita(int giornata, int b, int *c, float v);
  void SetSquadra(QString a) { squadra = a; }
  void SetPrezzo(int a) { prezzo = a; }
  float GetVoto(int i, Punteggi* p);

 private:
  QString nome;
  QString cognome;
  int ruolo;
  int prezzo;
  QString squadra;
  Prestazione prestazioni[50];
};
#endif
