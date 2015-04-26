#ifndef _SDLEDITEUR_H
#define _SDLEDITEUR_H

#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>
#include "jeu.h"

typedef struct
{
    Jeu jeu;
	TTF_Font * police;
	TTF_Font * police2;
	SDL_Color couleur;
	SDL_Color couleur2;
	SDL_Surface * surface_ecran;
	SDL_Surface * surface_perso;
	SDL_Surface * surface_mur;
	SDL_Surface * surface_tp_entree;
	SDL_Surface * surface_tp_sortie;
	SDL_Surface * surface_caisse;
	SDL_Surface * surface_caisse_active;
	SDL_Surface * surface_sol;
	SDL_Surface * surface_trou;
	SDL_Surface * surface_text_sauver;
    SDL_Surface * surface_text_menu;
    SDL_Surface * surface_menu_bas;
    SDL_Surface * surface_menu_haut;
    int estPersoPlace;
    int estSortiePlace;
    int estEntreePlace;
} sdlEditeur;

void sdlediteurInit(sdlEditeur *);
void sdlediteurBoucle(sdlEditeur *);
void sdlediteurLibere(sdlEditeur *);

#endif
