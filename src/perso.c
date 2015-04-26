#include "perso.h"


void persoInit(Perso * pPers, int x, int y)
{
	pPers -> x = x;
	pPers -> y = y;
}

void persoGauche(Perso * pPers, const Terrain * pTer)
{
    pPers -> x--;
}

void persoDroite(Perso *pPers, const Terrain * pTer)
{
    pPers -> x++;
}

void persoHaut(Perso * pPers, const Terrain * pTer)
{
    pPers -> y--;
}

void persoBas(Perso * pPers, const Terrain * pTer)
{
    pPers -> y++;
}

void persoSetXY(Perso * pPers, int x, int y)
{
    pPers -> x = x;
    pPers -> y = y;
}

int persoGetX(const Perso * pPers)
{
	return pPers -> x;
}

int persoGetY(const Perso * pPers)
{
	return pPers -> y;
}
