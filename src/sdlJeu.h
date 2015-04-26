#ifndef _SDLJEU_H
#define _SDLJEU_H

#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>
#include "jeu.h"

typedef struct
{
	Jeu jeu;
	TTF_Font * police;
	TTF_Font * police2;
	TTF_Font * police3;
	SDL_Color couleur;
	SDL_Color couleur2;
	SDL_Surface * surface_ecran;
	SDL_Surface * surface_perso;
	SDL_Surface * surface_mur;
	SDL_Surface * surface_tp_entree;
	SDL_Surface * surface_tp_sortie;
	SDL_Surface * surface_caisse;
	SDL_Surface * surface_sol;
	SDL_Surface * surface_trou;
    SDL_Surface * surface_caisse_place;
    SDL_Surface * surface_text_gagner;
    SDL_Surface * surface_gagner;
    SDL_Surface * surface_text_temps;
    SDL_Surface * surface_text_objectifs;
    SDL_Surface * surface_text_niveau;
    SDL_Surface * surface_text_menu;
    SDL_Surface * surface_text_reset;
    SDL_Surface * surface_text_actions;
    SDL_Surface * surface_menu_bas;
    SDL_Surface * surface_menu_haut;
    SDL_Surface * surface_text_next;
    SDL_Surface * surface_text_exit;
    SDL_Surface * surface_text_menu_continuer;
    SDL_Surface * surface_text_menu_quitter;
    SDL_Surface * surface_text_menu_sauver;
    SDL_Surface * surface_text_menu_options;
    SDL_Surface * surface_text_menu_titre;
    int jeu_pause;
} sdlJeu;

void sdljeuInit(sdlJeu *);
void sdljeuBoucle(sdlJeu *);
void sdljeuLibere(sdlJeu *);

#endif
