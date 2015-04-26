#ifndef _PERSO_H
#define _PERSO_H

#include "terrain.h"

typedef struct
{
	int x,y;
} Perso;

void persoInit(Perso *, int x, int y);
void persoGauche(Perso *, const Terrain *);
void persoDroite(Perso *, const Terrain *);
void persoHaut(Perso *, const Terrain *);
void persoBas(Perso *, const Terrain *);
void persoSetXY(Perso *, int x, int y);
int persoGetX(const Perso *);
int persoGetY(const Perso *);

#endif
