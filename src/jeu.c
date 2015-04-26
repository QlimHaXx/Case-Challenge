#include "jeu.h"
#include <stdio.h>
#include <malloc.h>

void chargerFichierJeu(Jeu * pJeu, const char * filename){
    FILE * fichier = NULL;
    int x, y;
    int i_caisses = 0;

    fichier = fopen(filename, "r");

    if (fichier == NULL){
        EXIT_FAILURE;
    }
    else {
        fscanf(fichier, "dimx : %d\ndimy : %d\n", &(pJeu -> ter.dimX), &(pJeu -> ter.dimY));
        fscanf(fichier, "nb_caisses : %d", &(pJeu -> nb_caisses));
    }

    pJeu -> tab_caisses = malloc(sizeof(Caisse) * pJeu -> nb_caisses);
    pJeu -> ter.tab = (char **)malloc(sizeof(char *)* pJeu -> ter.dimY);

	for(y = 0; y < pJeu -> ter.dimY; y++){
		pJeu -> ter.tab[y] = (char *)malloc(sizeof(char)* pJeu -> ter.dimX);
	}

    for(y = 0; y < pJeu -> ter.dimY; y++){
        for(x = 0; x < pJeu -> ter.dimX; x++){
            pJeu -> ter.tab[y][x] = fgetc(fichier);
            if(pJeu -> ter.tab[y][x] == 'X'){
                caisseInit(&(pJeu -> tab_caisses[i_caisses]), x, y);
                i_caisses++;
                pJeu -> ter.tab[y][x] = '.';
            }
            if(pJeu -> ter.tab[y][x] == 'P'){
                persoInit(&(pJeu -> pers), x, y);
                pJeu -> ter.tab[y][x] = '.';
            }
            if(pJeu -> ter.tab[y][x] == 'A'){
                caisseInit(&(pJeu -> tab_caisses[i_caisses]), x, y);
                pJeu -> tab_caisses[i_caisses].estPlace = 1;
                i_caisses++;
                pJeu -> ter.tab[y][x] = '0';
            }
        }
    }

    fclose(fichier);
}

void sauverFichierJeu(Jeu * pJeu){
    FILE * fichier = NULL;
    int x, y;

    fichier = fopen("data/Niveaux/Niveau3.txt", "w");

    if (fichier == NULL){
        EXIT_FAILURE;
    }
    else {
        fprintf(fichier, "dimx : %d\ndimy : %d\n", pJeu -> ter.dimX + 1, pJeu -> ter.dimY);
        fprintf(fichier, "nb_caisses : %d\n", pJeu -> nb_caisses);
    }

    for(y = 0; y < pJeu -> ter.dimY; y++){
        for(x = 0; x < pJeu -> ter.dimX; x++){
            fputc(pJeu -> ter.tab[y][x], fichier);
        }
        fputc('\n', fichier);
    }

    fclose(fichier);
}

void jeuInit(Jeu * pJeu)
{
    persoInit(&(pJeu -> pers), 0, 0);
    terInit(&(pJeu -> ter));
    pJeu -> nb_actions = 0;
    pJeu -> niveau = 1;
}

void jeuLibere(Jeu * pJeu)
{
	terLibere(&(pJeu -> ter));
	free(pJeu -> tab_caisses);
}

Terrain * jeuGetTerrainPtr(Jeu * pJeu)
{
	return &(pJeu -> ter);
}

Perso * jeuGetPersoPtr(Jeu * pJeu)
{
	return &(pJeu -> pers);
}

const Terrain * jeuGetConstTerrainPtr(const Jeu * pJeu)
{
	return &(pJeu -> ter);
}

const Perso * jeuGetConstPersoPtr(const Jeu * pJeu)
{
	return &(pJeu -> pers);
}

int testCaisseXY(Jeu * pJeu, int x, int y){
    int i;
    int res = -1;
    for(i = 0; i < pJeu -> nb_caisses; i++){
        if(pJeu -> tab_caisses[i].x == x && pJeu -> tab_caisses[i].y == y){
            res = i; /* index de la caisse trouvée */
        }
    }
    return res;
}

int estPositionValide(Jeu * pJeu, int x, int y){
    int res;
    char terXY = terGetXY(&(pJeu -> ter), x, y);
    int is_caisse = testCaisseXY(pJeu, x, y);
    if(is_caisse != -1){
        res = 2; /* caisse aux coordonnees XY */
    }
    else if(terXY == 'E'){
        res = 3; /* tp au coordonnées XY */
    }
    else if(terXY == '#'){
        res = 1; /* mur au coordonnées XY */
    }
    else {
        res = 0; /* rien aux coordonnées XY */
    }
    return res;
}

void estPlaceCaisse(Jeu * pJeu, Caisse * pCaiss,int x, int y){
    char terXY = terGetXY(&(pJeu -> ter), x, y);
    if(terXY == '0' && pCaiss -> x == x && pCaiss -> y == y){
        pCaiss -> estPlace = 1;
    }
    else {
        pCaiss -> estPlace = 0;
    }
}

int estJeuGagne(Jeu * pJeu){
    int i;
    int res = 0;
    for(i = 0; i < pJeu -> nb_caisses; i++){
        if(pJeu -> tab_caisses[i].estPlace == 1){
            res++;
        }
    }
    if(res == pJeu -> nb_caisses){
        return 1;
    }
    else {
        return 0;
    }
}

void jeuTpPerso(Jeu * pJeu){
    int i, j;
    for(i = 0; i < pJeu -> ter.dimX; i++){
        for(j = 0; j < pJeu -> ter.dimY; j++){
            if(terGetXY(&(pJeu -> ter), i, j) == 'S'){
                persoSetXY(&(pJeu -> pers), i, j);
            }
        }
    }
}

void jeuActionClavier(Jeu * pJeu, const char touche)
{
    int persoX = persoGetX(&(pJeu -> pers));
    int persoY = persoGetY(&(pJeu -> pers));
    int i_caisse_next = 0;
	switch(touche)
	{
		case 'g' :
		    if(estPositionValide(pJeu, persoX - 1, persoY) == 2){ /* ya une caisse a gauche du perso */
                i_caisse_next = testCaisseXY(pJeu, persoX - 1, persoY); /* on stock cette caisse */
                if(estPositionValide(pJeu, persoX - 2, persoY) == 0){ /* ya rien a coté de la caisse */
                    caisseGauche(&(pJeu -> tab_caisses[i_caisse_next])); /* on pousse la caisse */
                    estPlaceCaisse(pJeu, &(pJeu -> tab_caisses[i_caisse_next]), persoX - 2, persoY);/* si la caisse est sur un trou */
                    persoGauche(&(pJeu -> pers), &(pJeu -> ter));
                    pJeu -> nb_actions++;
                }
		    }
		    else if(estPositionValide(pJeu, persoX - 1, persoY) == 3){/* ya un tp a gauche du perso */
                jeuTpPerso(pJeu);
		    }
		    else if(estPositionValide(pJeu, persoX - 1, persoY) == 0){ /* ya rien a gauche du perso */
                persoGauche(&(pJeu -> pers), &(pJeu -> ter)); /* on deplace le perso a gauche */
		    }
			break;
		case 'd' :
            if(estPositionValide(pJeu, persoX + 1, persoY) == 2){
                i_caisse_next = testCaisseXY(pJeu, persoX + 1, persoY);
                if(estPositionValide(pJeu, persoX + 2, persoY) == 0){
                    caisseDroite(&(pJeu -> tab_caisses[i_caisse_next]));
                    estPlaceCaisse(pJeu, &(pJeu -> tab_caisses[i_caisse_next]), persoX + 2, persoY);
                    persoDroite(&(pJeu -> pers), &(pJeu -> ter));
                    pJeu -> nb_actions++;
                }
		    }
		    else if(estPositionValide(pJeu, persoX + 1, persoY) == 3){/* ya un tp a gauche du perso */
                jeuTpPerso(pJeu);
		    }
		    else if(estPositionValide(pJeu, persoX + 1, persoY) == 0){
                persoDroite(&(pJeu -> pers), &(pJeu -> ter));
		    }
			break;
		case 'h' :
            if(estPositionValide(pJeu, persoX, persoY - 1) == 2){
                i_caisse_next = testCaisseXY(pJeu, persoX, persoY - 1);
                if(estPositionValide(pJeu, persoX, persoY - 2) == 0){
                    caisseHaut(&(pJeu -> tab_caisses[i_caisse_next]));
                    estPlaceCaisse(pJeu, &(pJeu -> tab_caisses[i_caisse_next]), persoX, persoY - 2);
                    persoHaut(&(pJeu -> pers), &(pJeu -> ter));
                    pJeu -> nb_actions++;
                }
		    }
		    else if(estPositionValide(pJeu, persoX, persoY - 1) == 3){/* ya un tp a gauche du perso */
                jeuTpPerso(pJeu);
		    }
		    else if(estPositionValide(pJeu, persoX, persoY - 1) == 0){
                persoHaut(&(pJeu -> pers), &(pJeu -> ter));
		    }
			break;
		case 'b' :
            if(estPositionValide(pJeu, persoX, persoY + 1) == 2){
                i_caisse_next = testCaisseXY(pJeu, persoX, persoY + 1);
                if(estPositionValide(pJeu, persoX, persoY + 2) == 0){
                    caisseBas(&(pJeu -> tab_caisses[i_caisse_next]));
                    estPlaceCaisse(pJeu, &(pJeu -> tab_caisses[i_caisse_next]), persoX, persoY + 2);
                    persoBas(&(pJeu -> pers), &(pJeu -> ter));
                    pJeu -> nb_actions++;
                }
		    }
		    else if(estPositionValide(pJeu, persoX, persoY + 1) == 3){/* ya un tp a gauche du perso */
                jeuTpPerso(pJeu);
		    }
		    else if(estPositionValide(pJeu, persoX, persoY + 1) == 0){
                persoBas(&(pJeu -> pers), &(pJeu -> ter));
		    }
			break;
	}
}
