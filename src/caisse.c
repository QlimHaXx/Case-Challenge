#include <stdlib.h>
#include "caisse.h"


void caisseInit(Caisse * pCaiss, int x, int y){
    pCaiss -> x = x;
    pCaiss -> y = y;
    pCaiss -> estPlace = 0;
}

void caisseGauche(Caisse * pCaiss)
{
    pCaiss -> x--;
}

void caisseDroite(Caisse * pCaiss)
{
    pCaiss -> x++;
}

void caisseHaut(Caisse * pCaiss)
{
    pCaiss -> y--;
}

void caisseBas(Caisse * pCaiss)
{
    pCaiss -> y++;
}

int caisseGetX(const Caisse * pCaiss){
    return pCaiss -> x;
}

int caisseGetY(const Caisse * pCaiss){
    return pCaiss -> y;
}
