#ifndef _CAISSE_H
#define _CAISSE_H

#include "terrain.h"

typedef struct
{
	int x, y;
	int estPlace; /* placé sur un trou = 1 */
} Caisse;

void caisseInit(Caisse *, int x, int y);
void caisseGauche(Caisse *);
void caisseDroite(Caisse *);
void caisseHaut(Caisse *);
void caisseBas(Caisse *);
int caisseGetX(const Caisse *);
int caisseGetY(const Caisse *);

#endif
