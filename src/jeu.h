#ifndef _JEU_H
#define _JEU_H


#include "perso.h"
#include "terrain.h"
#include "caisse.h"

typedef struct
{
	Terrain ter;
	Perso pers;
	int nb_caisses;
	int nb_actions;
	int niveau;
	Caisse * tab_caisses;
} Jeu;

void chargerFichierJeu(Jeu *, const char * filename);
void sauverFichierJeu(Jeu *);
void jeuInit(Jeu *);
void jeuLibere(Jeu *);
Terrain * jeuGetTerrainPtr(Jeu *);
Perso * jeuGetPersoPtr(Jeu *);
const Terrain * jeuGetConstTerrainPtr(const Jeu *);
const Perso * jeuGetConstPersoPtr(const Jeu *);
int testCaisseXY(Jeu *, int x, int y);
int estPositionValide(Jeu *, int x, int y);
void estPlaceCaisse(Jeu *, Caisse *, int x, int y);
int estJeuGagne(Jeu *);
void jeuTpPerso(Jeu *);
void jeuActionClavier(Jeu *, const char);

#endif
