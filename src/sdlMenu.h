#ifndef _SDLMENU_H
#define _SDLMENU_H

#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>
#include "menu.h"

typedef struct
{
	Menu menu;
	TTF_Font * police;
	TTF_Font * police2;
	SDL_Color couleur;
	SDL_Color couleur2;
	SDL_Surface * surface_ecran;
    SDL_Surface * surface_fond;
    SDL_Surface * surface_image1;
    SDL_Surface * surface_image2;
    SDL_Surface * surface_image3;
    SDL_Surface * surface_image4;
    SDL_Surface * surface_text_jouer;
    SDL_Surface * surface_text_editeur;
    SDL_Surface * surface_text_options;
    SDL_Surface * surface_text_quitter;
} sdlMenu;

void sdlmenuInit(sdlMenu *);
void sdlmenuBoucle(sdlMenu *);
void sdlmenuLibere(sdlMenu *);
SDL_Surface * SDL_load_image(const char * filename);
void SDL_apply_surface(SDL_Surface * source, SDL_Surface * destination, int x, int y);

#endif

