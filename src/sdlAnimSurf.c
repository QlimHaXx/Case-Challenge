#include <assert.h>
#include <time.h>
#include "sdlAnimSurf.h"

void animSurfSet(Anim_Surface * pASurf, int x, int y, const char * filename){
    char filename2[100];
    sprintf(filename2, ".../%s", filename);
    pASurf -> surface = SDL_load_image(filename);
	if(pASurf -> surface == NULL){
		pASurf -> surface = SDL_load_image(filename2);
	}
	assert(pASurf -> surface != NULL);
    pASurf -> x = x;
    pASurf -> y = y;
    pASurf -> w = pASurf -> surface -> w;
    pASurf -> h = pASurf -> surface -> h;
}

void animTexteSet(Anim_Texte * pATexte, int x, int y, const char * texte, TTF_Font * police, SDL_Color color){
    pATexte -> surface = TTF_RenderText_Blended(police, texte, color);
    pATexte -> x = x;
    pATexte -> y = y;
    pATexte -> w = pATexte -> surface -> w;
    pATexte -> h = pATexte -> surface -> h;
}

void animSurfLibere(Anim_Surface * pASurf){
    SDL_FreeSurface(pASurf -> surface);
    pASurf -> x = 0;
    pASurf -> y = 0;
    pASurf -> w = 0;
    pASurf -> h = 0;
}

void animTexteLibere(Anim_Texte * pATexte){
    SDL_FreeSurface(pATexte -> surface);
    pATexte -> x = 0;
    pATexte -> y = 0;
    pATexte -> w = 0;
    pATexte -> h = 0;
}

SDL_Surface * SDL_load_image(const char * filename)
{
	/* Temporary storage for the image that's loaded */
	SDL_Surface * loadedImage = NULL;

	/* The optimized image that will be used */
	SDL_Surface * optimizedImage = NULL;

	/* Load the image */
	loadedImage = SDL_LoadBMP(filename);

	/* If nothing went wrong in loading the image */
	if (loadedImage != NULL)
	{
		/* Create an optimized image */
		optimizedImage = SDL_DisplayFormat(loadedImage);

		/* Free the old image */
		SDL_FreeSurface(loadedImage);
	}

	/* Return the optimized image */
	return optimizedImage;
}


void SDL_apply_surface(SDL_Surface * source, SDL_Surface * destination, int x, int y)
{
	/* Make a temporary rectangle to hold the offsets */
	SDL_Rect offset;

	/* Give the offsets to the rectangle */
	offset.x = x;
	offset.y = y;

	/* Blit the surface */
	SDL_BlitSurface(source, NULL, destination, &offset);
}
