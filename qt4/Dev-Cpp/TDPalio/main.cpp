#include <iostream>
#include <stdlib.h>
#include "Gioco.h"
#include "Corsa.h"
#include "tdpalio.h"

using namespace std;

int main(int argc, char *argv[])
{
    Gioco* gioco = InizioGioco();
    Corsa* corsa = new Corsa();
    corsa->Batterie(gioco->GetCavalli());
    corsa->Assegnazione(gioco);
    corsa->SceltaFantini(gioco->GetFantini());
    
  
    system("PAUSE");	
    return 0;
}
