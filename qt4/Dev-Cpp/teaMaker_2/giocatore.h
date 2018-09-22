#ifndef _GIOCATORE_
#define _GIOCATORE_

#include <fstream>
#include <string>

using namespace std;

class Giocatore
{
    public:
        Giocatore();
        virtual ~Giocatore();
        
        friend istream& operator>>(istream& p, Giocatore& x);
        
        void SetNome(string);
        void SetBravura(float);
        void SetGoal(float);
        void SetResistenza(float);
        void SetParate(float);
        void SetGiocate(int);
        void SetMedia(float);
        void SetMediaGoal(float);
        
        string GetNome() { return nome; };
        float GetBravura() { return bravura; };
        float GetGoal() { return goal; };
        float GetResistenza() { return resistenza; };
        float GetParate() { return parate; };
        float GetMediaGoal() { return media_goal; };
        float GetMedia() { return media; };
        int GetGiocate() { return giocate; };
        
    private:
        string nome;
        int giocate;
        float media_goal;
        float media;
        float bravura;
        float goal;
        float resistenza;
        float parate;
};
#endif
