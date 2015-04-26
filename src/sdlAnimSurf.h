#ifndef _SDLANIMSURF_H
#define _SDLANIMSURF_H

#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>

typedef struct
{
    int x, y; /* coordonées */
    int w, h; /* w: largeur h : hauteur */
    SDL_Surface * surface;
}Anim_Surface;

typedef struct
{
    int x, y; /* coordonées */
    int w, h; /* w: largeur h : hauteur */
    SDL_Surface * surface;
}Anim_Texte;

void animSurfSet(Anim_Surface * pASurf, int x, int y, const char * filename);
void animTexteSet(Anim_Texte * pATexte, int x, int y, const char * texte, TTF_Font * police, SDL_Color color);
void animSurfLibere(Anim_Surface *);
void animTexteLibere(Anim_Texte *);
SDL_Surface * SDL_load_image(const char * filename);
void SDL_apply_surface(SDL_Surface * source, SDL_Surface * destination, int x, int y);

#endif
