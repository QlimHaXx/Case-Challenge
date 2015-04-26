#include <assert.h>
#include "sdlMenu.h"
#include "constantes.h"

SDL_Surface * SDL_load_image(const char * filename );
void SDL_apply_surface(SDL_Surface * source, SDL_Surface * destination, int x, int y );

void sdlmenuInit(sdlMenu * pSdlMenu)
{
	Menu * pMenu;
    SDL_Color couleurBlanc = {255, 255, 255};
    SDL_Color couleurJaune = {255, 255, 0};

	pSdlMenu -> police = NULL;
    pSdlMenu -> couleur = couleurBlanc;
    pSdlMenu -> couleur2 = couleurJaune;
    TTF_Init();

    pSdlMenu -> police = TTF_OpenFont("data/erasmd.ttf", 90);
    pSdlMenu -> police2 = TTF_OpenFont("data/erasmd.ttf", 50);

	pMenu = &(pSdlMenu -> menu);
	menuInit(pMenu);

	assert(SDL_Init(SDL_INIT_EVERYTHING) != -1);

	/* Chargement de l'icône AVANT SDL_SetVideoMode */
    SDL_WM_SetIcon(SDL_LoadBMP("data/caisse.bmp"), NULL);

	pSdlMenu -> surface_ecran = SDL_SetVideoMode(ECRAN_X, ECRAN_Y, 32, SDL_SWSURFACE | SDL_DOUBLEBUF | SDL_RESIZABLE); /* video avec double buffer */
	assert(pSdlMenu -> surface_ecran != NULL);

	SDL_WM_SetCaption("Case challenge", NULL); /* nom de la fenetre */

    /* ----------- Declaration des differentes surfaces ----- */

    pSdlMenu -> surface_text_jouer = TTF_RenderText_Blended(pSdlMenu -> police2, "Jouer", pSdlMenu -> couleur);
    pSdlMenu -> surface_text_editeur = TTF_RenderText_Blended(pSdlMenu -> police2, "Editeur", pSdlMenu -> couleur);
    pSdlMenu -> surface_text_options = TTF_RenderText_Blended(pSdlMenu -> police2, "Options", pSdlMenu -> couleur);
    pSdlMenu -> surface_text_quitter = TTF_RenderText_Blended(pSdlMenu -> police2, "Quitter", pSdlMenu -> couleur);

	pSdlMenu -> surface_fond = SDL_load_image("data/menu_bck.bmp");
	if(pSdlMenu -> surface_fond == NULL){
        pSdlMenu -> surface_fond = SDL_load_image("../data/menu_bck.bmp");
	}

    pSdlMenu -> surface_image1 = NULL;
    pSdlMenu -> surface_image2 = NULL;
    pSdlMenu -> surface_image3 = NULL;
    pSdlMenu -> surface_image4 = NULL;

}

void sdlmenuAff(sdlMenu * pSdlMenu)
{
	SDL_FillRect(pSdlMenu -> surface_ecran, &(pSdlMenu -> surface_ecran -> clip_rect), SDL_MapRGB(pSdlMenu -> surface_ecran -> format, 0x00, 0x00, 0x00));
	SDL_apply_surface(pSdlMenu -> surface_fond, pSdlMenu -> surface_ecran, 0, 0);

    SDL_apply_surface(pSdlMenu -> surface_text_jouer, pSdlMenu -> surface_ecran, ECRAN_X / 2 - 40, ECRAN_Y / 2 - 60);
    SDL_apply_surface(pSdlMenu -> surface_text_editeur, pSdlMenu -> surface_ecran, ECRAN_X / 2 - 40, ECRAN_Y / 2);
    SDL_apply_surface(pSdlMenu -> surface_text_options, pSdlMenu -> surface_ecran, ECRAN_X / 2 - 40, ECRAN_Y / 2 + 60);
    SDL_apply_surface(pSdlMenu -> surface_text_quitter, pSdlMenu -> surface_ecran, ECRAN_X / 2 - 40, ECRAN_Y / 2 + 120);

    SDL_apply_surface(pSdlMenu -> surface_image1, pSdlMenu -> surface_ecran, ECRAN_X / 2 - 80, ECRAN_Y / 2 - 45);
    SDL_apply_surface(pSdlMenu -> surface_image2, pSdlMenu -> surface_ecran, ECRAN_X / 2 - 80, ECRAN_Y / 2 + 15);
    SDL_apply_surface(pSdlMenu -> surface_image3, pSdlMenu -> surface_ecran, ECRAN_X / 2 - 80, ECRAN_Y / 2 + 75);
    SDL_apply_surface(pSdlMenu -> surface_image4, pSdlMenu -> surface_ecran, ECRAN_X / 2 - 80, ECRAN_Y / 2 + 135);
}

void sdlmenuBoucle(sdlMenu * pSdlMenu)
{
	SDL_Event event;
	int continue_boucle = 1;
	int rafraichissement = 0;

	sdlmenuAff(pSdlMenu);
	assert(SDL_Flip(pSdlMenu -> surface_ecran) != -1);

	while(continue_boucle == 1)
	{
		while(SDL_PollEvent(&event))
		{
			if(event.type == SDL_QUIT){
				continue_boucle = 0;
			}

			if(event.type == SDL_MOUSEBUTTONUP){
                if (event.button.button == SDL_BUTTON_LEFT){
                    if(event.button.x > ECRAN_X / 2 - 40 && event.button.x < ECRAN_X / 2 - 40 + pSdlMenu -> surface_text_jouer -> w && event.button.y > ECRAN_Y / 2 - 60 && event.button.y < ECRAN_Y / 2 - 60 + pSdlMenu -> surface_text_jouer -> h){ /* jouer */
                        pSdlMenu -> menu.choix = 1;
                        continue_boucle = 0;
                    }
                    if(event.button.x > ECRAN_X / 2 - 40 && event.button.x < ECRAN_X / 2 + 100 && event.button.y > ECRAN_Y / 2 && event.button.y < ECRAN_Y / 2 + 50){ /* editeur */
                        pSdlMenu -> menu.choix = 2;
                        continue_boucle = 0;
                    }
                    if(event.button.x > ECRAN_X / 2 - 40 && event.button.x < ECRAN_X / 2 + 135 && event.button.y > ECRAN_Y / 2 + 60 && event.button.y < ECRAN_Y / 2 + 120){ /* options */
                        pSdlMenu -> menu.choix = 3;
                        continue_boucle = 0;
                    }
                    if(event.button.x > ECRAN_X / 2 - 40 && event.button.x < ECRAN_X / 2 + 120 && event.button.y > ECRAN_Y / 2 + 120 && event.button.y < ECRAN_Y / 2 + 170){ /* quitter */
                        pSdlMenu -> menu.choix = 0;
                        continue_boucle = 0;
                    }
			    }
			}

			if(event.type == SDL_MOUSEMOTION){
                if(event.motion.x > ECRAN_X / 2 - 40 && event.motion.x < ECRAN_X / 2 - 40 + pSdlMenu -> surface_text_jouer -> w && event.motion.y > ECRAN_Y / 2 - 60 && event.motion.y < ECRAN_Y / 2 - 60 + pSdlMenu -> surface_text_jouer -> h){ /* jouer */
                    pSdlMenu -> surface_text_jouer = TTF_RenderText_Blended(pSdlMenu -> police2, "Jouer", pSdlMenu -> couleur2);
                    pSdlMenu -> surface_image1 = SDL_load_image("data/perso.bmp");
                    if(pSdlMenu -> surface_image1 == NULL){
                        pSdlMenu -> surface_image1 = SDL_load_image("../data/perso.bmp");
                    }
                    SDL_SetColorKey(pSdlMenu -> surface_image1, SDL_SRCCOLORKEY, SDL_MapRGB(pSdlMenu -> surface_image1 -> format, 0, 255, 0));
                    rafraichissement = 1;
                }
                else if(event.motion.x > ECRAN_X / 2 - 40 && event.motion.x < ECRAN_X / 2 - 40 + pSdlMenu -> surface_text_editeur -> w && event.motion.y > ECRAN_Y / 2 + 10 && event.motion.y < ECRAN_Y / 2 + 10 + pSdlMenu -> surface_text_editeur -> h){ /* jouer */
                    pSdlMenu -> surface_text_editeur = TTF_RenderText_Blended(pSdlMenu -> police2, "Editeur", pSdlMenu -> couleur2);
                    pSdlMenu -> surface_image2 = SDL_load_image("data/perso.bmp");
                    if(pSdlMenu -> surface_image2 == NULL){
                        pSdlMenu -> surface_image2 = SDL_load_image("../data/perso.bmp");
                    }
                    SDL_SetColorKey(pSdlMenu -> surface_image2, SDL_SRCCOLORKEY, SDL_MapRGB(pSdlMenu -> surface_image2 -> format, 0, 255, 0));
                    rafraichissement = 1;
                }
                else if(event.motion.x > ECRAN_X / 2 - 40 && event.motion.x < ECRAN_X / 2 - 40 + pSdlMenu -> surface_text_options -> w && event.motion.y > ECRAN_Y / 2 + 70 && event.motion.y < ECRAN_Y / 2 + 70 + pSdlMenu -> surface_text_options -> h){ /* jouer */
                    pSdlMenu -> surface_text_options = TTF_RenderText_Blended(pSdlMenu -> police2, "Options", pSdlMenu -> couleur2);
                    pSdlMenu -> surface_image3 = SDL_load_image("data/perso.bmp");
                    if(pSdlMenu -> surface_image3 == NULL){
                        pSdlMenu -> surface_image3 = SDL_load_image("../data/perso.bmp");
                    }
                    SDL_SetColorKey(pSdlMenu -> surface_image3, SDL_SRCCOLORKEY, SDL_MapRGB(pSdlMenu -> surface_image3 -> format, 0, 255, 0));
                    rafraichissement = 1;
                }
                else if(event.motion.x > ECRAN_X / 2 - 40 && event.motion.x < ECRAN_X / 2 - 40 + pSdlMenu -> surface_text_quitter -> w && event.motion.y > ECRAN_Y / 2 + 130 && event.motion.y < ECRAN_Y / 2 + 130 + pSdlMenu -> surface_text_quitter -> h){ /* quitter */
                    pSdlMenu -> surface_text_quitter = TTF_RenderText_Blended(pSdlMenu -> police2, "Quitter", pSdlMenu -> couleur2);
                    pSdlMenu -> surface_image4 = SDL_load_image("data/perso.bmp");
                    if(pSdlMenu -> surface_image4 == NULL){
                        pSdlMenu -> surface_image4 = SDL_load_image("../data/perso.bmp");
                    }
                    SDL_SetColorKey(pSdlMenu -> surface_image4, SDL_SRCCOLORKEY, SDL_MapRGB(pSdlMenu -> surface_image4 -> format, 0, 255, 0));
                    rafraichissement = 1;

                }
                else {
                    pSdlMenu -> surface_text_quitter = TTF_RenderText_Blended(pSdlMenu -> police2, "Quitter", pSdlMenu -> couleur);
                    pSdlMenu -> surface_text_jouer = TTF_RenderText_Blended(pSdlMenu -> police2, "Jouer", pSdlMenu -> couleur);
                    pSdlMenu -> surface_text_editeur = TTF_RenderText_Blended(pSdlMenu -> police2, "Editeur", pSdlMenu -> couleur);
                    pSdlMenu -> surface_text_options = TTF_RenderText_Blended(pSdlMenu -> police2, "Options", pSdlMenu -> couleur);
                    pSdlMenu -> surface_image1 = NULL;
                    pSdlMenu -> surface_image2 = NULL;
                    pSdlMenu -> surface_image3 = NULL;
                    pSdlMenu -> surface_image4 = NULL;
                    rafraichissement = 1;
                }
			}

			if(event.type == SDL_KEYDOWN)
			{
				switch(event.key.keysym.sym)
				{
				    case SDLK_1:
                        pSdlMenu -> menu.choix = 1;
                        continue_boucle = 0;
                        break;
                    case SDLK_2:
                        pSdlMenu -> menu.choix = 2;
                        continue_boucle = 0;
                        break;
                    case SDLK_3:
                        pSdlMenu -> menu.choix = 3;
                        continue_boucle = 0;
                        break;
                    case SDLK_ESCAPE:
                        continue_boucle = 0;
                        break;
                    default: break;
				}
			}
		}

		if (rafraichissement == 1)
        {
            /* on affiche le jeu sur le buffer caché */
            sdlmenuAff(pSdlMenu);

            /* on permute les deux buffers (cette fonction ne doit se faire qu'une seule fois dans la boucle) */
            SDL_Flip(pSdlMenu -> surface_ecran);
        }
	}
}

void sdlmenuLibere(sdlMenu * pSdlMenu)
{
	SDL_FreeSurface(pSdlMenu -> surface_text_quitter);
	SDL_FreeSurface(pSdlMenu -> surface_text_options);
	SDL_FreeSurface(pSdlMenu -> surface_text_jouer);
	SDL_FreeSurface(pSdlMenu -> surface_text_editeur);
	SDL_FreeSurface(pSdlMenu -> surface_image1);
	SDL_FreeSurface(pSdlMenu -> surface_image2);
	SDL_FreeSurface(pSdlMenu -> surface_image3);

	TTF_CloseFont(pSdlMenu -> police);
	TTF_CloseFont(pSdlMenu -> police2);

    TTF_Quit();

	SDL_Quit();
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
