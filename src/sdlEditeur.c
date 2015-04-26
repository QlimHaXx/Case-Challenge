#include <assert.h>
#include <time.h>
#include "sdlEditeur.h"
#include "constantes.h"

SDL_Surface * SDL_load_image(const char * filename );
void SDL_apply_surface(SDL_Surface * source, SDL_Surface * destination, int x, int y );

void sdlediteurInit(sdlEditeur * pSdlEdit){
    Jeu * pJeu;
    int x, y;
	SDL_Color couleurBlanc = {255, 255, 255};
	SDL_Color couleurBleu = {0, 200, 255};

	pSdlEdit -> police = NULL;
	pSdlEdit -> police2 = NULL;
    pSdlEdit -> couleur = couleurBlanc;
    pSdlEdit -> couleur2 = couleurBleu;

    pJeu = &(pSdlEdit -> jeu);
    pJeu -> nb_caisses = 0;
    pJeu -> tab_caisses = NULL;

    pJeu -> ter.dimX = 40;
    pJeu -> ter.dimY = 21;

    pJeu -> ter.tab = (char **)malloc(sizeof(char *)* pJeu -> ter.dimY);

	for(y = 0; y < pJeu -> ter.dimY; y++){
		pJeu -> ter.tab[y] = (char *)malloc(sizeof(char)* pJeu -> ter.dimX);
	}

	for(x = 0; x < pJeu -> ter.dimX; x++){
        for(y = 0; y < pJeu -> ter.dimY; y++){
            pJeu -> ter.tab[y][x] = '-';
        }
	}

	pSdlEdit -> estPersoPlace = 0;
	pSdlEdit -> estSortiePlace = 0;
	pSdlEdit -> estEntreePlace = 0;

    TTF_Init();
    pSdlEdit -> police = TTF_OpenFont("data/erasmd.ttf", 25);
    pSdlEdit -> police2 = TTF_OpenFont("data/erasmd.ttf", 50);

	assert(SDL_Init(SDL_INIT_EVERYTHING) != -1);

    SDL_WM_SetIcon(SDL_LoadBMP("data/caisse.bmp"), NULL);

	pSdlEdit -> surface_ecran = SDL_SetVideoMode(ECRAN_X, ECRAN_Y, 32, SDL_SWSURFACE | SDL_DOUBLEBUF);
	assert(pSdlEdit -> surface_ecran != NULL);

	SDL_WM_SetCaption("Case challenge", NULL);

    /* ----------- Declaration des differentes surfaces ----- */

    pSdlEdit -> surface_text_menu = TTF_RenderText_Blended(pSdlEdit -> police, "Menu", pSdlEdit -> couleur);
    pSdlEdit -> surface_text_sauver = TTF_RenderText_Blended(pSdlEdit -> police, "Sauver", pSdlEdit -> couleur);

    pSdlEdit -> surface_menu_haut = SDL_CreateRGBSurface(SDL_HWSURFACE, ECRAN_X, 32, 32, 0, 0, 0, 0);
    pSdlEdit -> surface_menu_bas = SDL_CreateRGBSurface(SDL_HWSURFACE, ECRAN_X, 64, 32, 0, 0, 0, 0);

    pSdlEdit -> surface_perso = SDL_load_image("data/perso.bmp");
	if(pSdlEdit -> surface_perso == NULL)
        pSdlEdit -> surface_perso = SDL_load_image("../data/perso.bmp");
    /* Rend la couleur de fond de l'image transparent */
	SDL_SetColorKey(pSdlEdit -> surface_perso, SDL_SRCCOLORKEY, SDL_MapRGB(pSdlEdit -> surface_perso -> format, 0, 255, 0));
	assert(pSdlEdit -> surface_perso != NULL);

	pSdlEdit -> surface_mur = SDL_load_image("data/mur.bmp");
	if(pSdlEdit -> surface_mur == NULL)
		pSdlEdit -> surface_mur = SDL_load_image("../data/mur.bmp");
	assert(pSdlEdit -> surface_mur != NULL);

	pSdlEdit -> surface_tp_entree = SDL_load_image("data/tp_entree.bmp");
	if(pSdlEdit -> surface_tp_entree == NULL)
		pSdlEdit -> surface_tp_entree = SDL_load_image("../data/tp_entree.bmp");
	assert(pSdlEdit -> surface_tp_entree != NULL);


    pSdlEdit -> surface_tp_sortie = SDL_load_image("data/tp_sortie.bmp");
	if(pSdlEdit -> surface_tp_sortie == NULL)
		pSdlEdit -> surface_tp_sortie = SDL_load_image("../data/tp_sortie.bmp");
	assert(pSdlEdit -> surface_tp_sortie != NULL);


	pSdlEdit -> surface_caisse = SDL_load_image("data/caisse.bmp");
	if(pSdlEdit -> surface_caisse == NULL)
		pSdlEdit -> surface_caisse = SDL_load_image("../data/caisse.bmp");
	assert(pSdlEdit -> surface_caisse != NULL);

	pSdlEdit -> surface_caisse_active = SDL_load_image("data/caisse_active.bmp");
	if(pSdlEdit -> surface_caisse_active == NULL)
		pSdlEdit -> surface_caisse_active = SDL_load_image("../data/caisse_active.bmp");
	assert(pSdlEdit -> surface_caisse_active != NULL);

	pSdlEdit -> surface_trou = SDL_load_image("data/trou.bmp");
	if(pSdlEdit -> surface_trou == NULL)
		pSdlEdit -> surface_trou = SDL_load_image("../data/trou.bmp");
	assert(pSdlEdit -> surface_trou != NULL);

	pSdlEdit -> surface_sol = SDL_load_image("data/sol.bmp");
	if(pSdlEdit -> surface_sol == NULL)
		pSdlEdit -> surface_sol = SDL_load_image("../data/sol.bmp");
	assert(pSdlEdit -> surface_sol != NULL);
}


void sdlediteurAff(sdlEditeur * pSdlEdit){
    int x, y;
    const Jeu * pJeu = &(pSdlEdit -> jeu);
	const Terrain * pTer = jeuGetConstTerrainPtr(pJeu);

	SDL_FillRect(pSdlEdit -> surface_ecran, &(pSdlEdit -> surface_ecran -> clip_rect), SDL_MapRGB(pSdlEdit -> surface_ecran -> format, 0x99, 0xBB, 0xCC));

    for (x = 0; x < getDimX(pTer); x++){
        for (y = 0; y < getDimY(pTer); y++){
            if(terGetXY(pTer, x, y) == '#'){
				SDL_apply_surface(pSdlEdit -> surface_mur, pSdlEdit -> surface_ecran, x * TAILLE_SPRITE, y * TAILLE_SPRITE);
            }
            else if(terGetXY(pTer, x, y) == '0'){
                SDL_apply_surface(pSdlEdit -> surface_trou, pSdlEdit -> surface_ecran, x * TAILLE_SPRITE, y * TAILLE_SPRITE);
            }
            else if(terGetXY(pTer, x, y) == '.'){
                SDL_apply_surface(pSdlEdit -> surface_sol, pSdlEdit -> surface_ecran, x * TAILLE_SPRITE, y * TAILLE_SPRITE);
            }
            else if(terGetXY(pTer, x, y) == 'E'){
                SDL_apply_surface(pSdlEdit -> surface_tp_entree, pSdlEdit -> surface_ecran, x * TAILLE_SPRITE, y * TAILLE_SPRITE);
                pSdlEdit -> estEntreePlace = 1;
            }
            else if(terGetXY(pTer, x, y) == 'S'){
                SDL_apply_surface(pSdlEdit -> surface_tp_sortie, pSdlEdit -> surface_ecran, x * TAILLE_SPRITE, y * TAILLE_SPRITE);
                pSdlEdit -> estSortiePlace = 1;
            }
            else if(terGetXY(pTer, x, y) == 'X'){
                SDL_apply_surface(pSdlEdit -> surface_caisse, pSdlEdit -> surface_ecran, x * TAILLE_SPRITE, y * TAILLE_SPRITE);
            }
            else if(terGetXY(pTer, x, y) == 'P'){
                SDL_apply_surface(pSdlEdit -> surface_sol, pSdlEdit -> surface_ecran, x * TAILLE_SPRITE, y * TAILLE_SPRITE);
                SDL_apply_surface(pSdlEdit -> surface_perso, pSdlEdit -> surface_ecran, x * TAILLE_SPRITE, y * TAILLE_SPRITE);
                pSdlEdit -> estPersoPlace = 1;
            }
            else if(terGetXY(pTer, x, y) == 'A'){
                SDL_apply_surface(pSdlEdit -> surface_trou, pSdlEdit -> surface_ecran, x * TAILLE_SPRITE, y * TAILLE_SPRITE);
                SDL_apply_surface(pSdlEdit -> surface_caisse_active, pSdlEdit -> surface_ecran, x * TAILLE_SPRITE, y * TAILLE_SPRITE);
            }
        }
	}

	SDL_FillRect(pSdlEdit -> surface_menu_haut, NULL, SDL_MapRGB(pSdlEdit -> surface_ecran -> format, 0x00, 0x33, 0x55));
    SDL_FillRect(pSdlEdit -> surface_menu_bas, NULL, SDL_MapRGB(pSdlEdit -> surface_ecran -> format, 0x00, 0x33, 0x55));

    SDL_apply_surface(pSdlEdit -> surface_menu_bas, pSdlEdit -> surface_ecran, 0, ECRAN_Y - 32);
    SDL_apply_surface(pSdlEdit -> surface_menu_haut, pSdlEdit -> surface_ecran, 0, 0);
    SDL_apply_surface(pSdlEdit -> surface_text_menu, pSdlEdit -> surface_ecran, ECRAN_X -  3 * 32, 2);
    SDL_apply_surface(pSdlEdit -> surface_text_sauver, pSdlEdit -> surface_ecran, 4, 1);
}

void sdlediteurBoucle(sdlEditeur * pSdlEdit){
    SDL_Event event;
    Jeu * pJeu = &(pSdlEdit -> jeu);
	int continue_boucle = 1;
    int rafraichissement;
    int selected = 0;
    int nb_trous = 0;

	sdlediteurAff(pSdlEdit);
	assert(SDL_Flip(pSdlEdit -> surface_ecran) != -1);

    /*SDL_EnableKeyRepeat(100, 150);*/

	while(continue_boucle == 1)
	{
	    rafraichissement = 0;

		while(SDL_PollEvent(&event))
		{
			if(event.type == SDL_QUIT){
				continue_boucle = 0;
			}

			if (event.type == SDL_MOUSEMOTION){
                /*if(event.motion.x > pSdlEdit -> surface_text_sauver -> clip_rect.x && event.motion.x < pSdlEdit -> surface_text_sauver -> w + 7 && event.motion.y > pSdlEdit -> surface_text_sauver -> clip_rect.y && event.motion.y < pSdlEdit -> surface_text_sauver -> h){
                    pSdlEdit -> surface_text_sauver = TTF_RenderText_Blended(pSdlEdit -> police, "Sauver", pSdlEdit -> couleur2);
                    rafraichissement = 1;
                }
                else */if(event.motion.x > ECRAN_X -  3 * 32 && event.motion.x < ECRAN_X - 32 && event.motion.y > 2 && event.motion.y < pSdlEdit -> surface_text_menu -> h){
                    pSdlEdit -> surface_text_menu = TTF_RenderText_Blended(pSdlEdit -> police, "Menu", pSdlEdit -> couleur2);
                    rafraichissement = 1;
                }
                else {
                    pSdlEdit -> surface_text_sauver = TTF_RenderText_Blended(pSdlEdit -> police, "Sauver", pSdlEdit -> couleur);
                    pSdlEdit -> surface_text_menu = TTF_RenderText_Blended(pSdlEdit -> police, "Menu", pSdlEdit -> couleur);
                    rafraichissement = 1;
                }
			}

            if (event.button.button == SDL_BUTTON_LEFT){
                if(event.button.y > 32 && event.button.x/32 < pJeu -> ter.dimX && event.button.y/32 < pJeu -> ter.dimY){
                    switch (selected)
                    {
                        case 0:
                            if(pJeu -> ter.tab[event.button.y/32][event.button.x/32] == 'X'){
                                pJeu -> nb_caisses --;
                            }
                            if(pJeu -> ter.tab[event.button.y/32][event.button.x/32] == '0'){
                                nb_trous --;
                            }
                            if(pJeu -> ter.tab[event.button.y/32][event.button.x/32] == 'E'){
                                pSdlEdit -> estEntreePlace = 0;
                            }
                            if(pJeu -> ter.tab[event.button.y/32][event.button.x/32] == 'S'){
                                pSdlEdit -> estSortiePlace = 0;
                            }
                            pJeu -> ter.tab[event.button.y/32][event.button.x/32] = '-';
                            rafraichissement = 1;
                            break;
                        case 1:
                            if(pJeu -> ter.tab[event.button.y/32][event.button.x/32] == 'X'){
                                pJeu -> nb_caisses --;
                            }
                            if(pJeu -> ter.tab[event.button.y/32][event.button.x/32] == '0'){
                                nb_trous --;
                            }
                            if(pJeu -> ter.tab[event.button.y/32][event.button.x/32] == 'E'){
                                pSdlEdit -> estEntreePlace = 0;
                            }
                            if(pJeu -> ter.tab[event.button.y/32][event.button.x/32] == 'S'){
                                pSdlEdit -> estSortiePlace = 0;
                            }
                            pJeu -> ter.tab[event.button.y/32][event.button.x/32] = '.';
                            rafraichissement = 1;
                            break;
                        case 2:
                            if(pJeu -> ter.tab[event.button.y/32][event.button.x/32] == 'X'){
                                pJeu -> nb_caisses --;
                            }
                            if(pJeu -> ter.tab[event.button.y/32][event.button.x/32] == '0'){
                                nb_trous --;
                            }
                            if(pJeu -> ter.tab[event.button.y/32][event.button.x/32] == 'E'){
                                pSdlEdit -> estEntreePlace = 0;
                            }
                            if(pJeu -> ter.tab[event.button.y/32][event.button.x/32] == 'S'){
                                pSdlEdit -> estSortiePlace = 0;
                            }
                            pJeu -> ter.tab[event.button.y/32][event.button.x/32] = '#';
                            rafraichissement = 1;
                            break;
                        case 3:
                            if(pJeu -> ter.tab[event.button.y/32][event.button.x/32] != 'X'){
                                pJeu -> nb_caisses ++;
                            }
                            if(pJeu -> ter.tab[event.button.y/32][event.button.x/32] == '0'){
                                nb_trous --;
                            }
                            if(pJeu -> ter.tab[event.button.y/32][event.button.x/32] == 'E'){
                                pSdlEdit -> estEntreePlace = 0;
                            }
                            if(pJeu -> ter.tab[event.button.y/32][event.button.x/32] == 'S'){
                                pSdlEdit -> estSortiePlace = 0;
                            }
                            pJeu -> ter.tab[event.button.y/32][event.button.x/32] = 'X';
                            rafraichissement = 1;
                            break;
                        case 4:
                            if(pJeu -> ter.tab[event.button.y/32][event.button.x/32] == 'X'){
                                pJeu -> nb_caisses --;
                            }
                            if(pJeu -> ter.tab[event.button.y/32][event.button.x/32] == '0'){
                                nb_trous ++;
                            }
                            if(pJeu -> ter.tab[event.button.y/32][event.button.x/32] == 'E'){
                                pSdlEdit -> estEntreePlace = 0;
                            }
                            if(pJeu -> ter.tab[event.button.y/32][event.button.x/32] == 'S'){
                                pSdlEdit -> estSortiePlace = 0;
                            }
                            pJeu -> ter.tab[event.button.y/32][event.button.x/32] = '0';
                            rafraichissement = 1;
                            break;
                        case 5:
                            if(pSdlEdit -> estEntreePlace == 0){
                                if(pJeu -> ter.tab[event.button.y/32][event.button.x/32] == 'X'){
                                    pJeu -> nb_caisses --;
                                }
                                if(pJeu -> ter.tab[event.button.y/32][event.button.x/32] == '0'){
                                    nb_trous --;
                                }
                                if(pJeu -> ter.tab[event.button.y/32][event.button.x/32] == 'S'){
                                    pSdlEdit -> estSortiePlace = 0;
                                }
                                pJeu -> ter.tab[event.button.y/32][event.button.x/32] = 'E';
                                rafraichissement = 1;
                            }
                            break;
                        case 6:
                            if(pSdlEdit -> estSortiePlace == 0){
                                if(pJeu -> ter.tab[event.button.y/32][event.button.x/32] == 'X'){
                                    pJeu -> nb_caisses --;
                                }
                                if(pJeu -> ter.tab[event.button.y/32][event.button.x/32] == '0'){
                                    nb_trous --;
                                }
                                if(pJeu -> ter.tab[event.button.y/32][event.button.x/32] == 'E'){
                                    pSdlEdit -> estEntreePlace = 0;
                                }
                                pJeu -> ter.tab[event.button.y/32][event.button.x/32] = 'S';
                                rafraichissement = 1;
                            }
                            break;
                        case 7:
                            if(pSdlEdit -> estPersoPlace == 0){
                                if(pJeu -> ter.tab[event.button.y/32][event.button.x/32] == 'X'){
                                    pJeu -> nb_caisses --;
                                }
                                if(pJeu -> ter.tab[event.button.y/32][event.button.x/32] == '0'){
                                    nb_trous --;
                                }
                                if(pJeu -> ter.tab[event.button.y/32][event.button.x/32] == 'E'){
                                    pSdlEdit -> estEntreePlace = 0;
                                }
                                if(pJeu -> ter.tab[event.button.y/32][event.button.x/32] == 'S'){
                                    pSdlEdit -> estSortiePlace = 0;
                                }
                                pJeu -> ter.tab[event.button.y/32][event.button.x/32] = 'P';
                                rafraichissement = 1;
                            }
                            break;
                        case 8:
                            if(pJeu -> ter.tab[event.button.y/32][event.button.x/32] == 'X'){
                                pJeu -> nb_caisses --;
                            }
                            if(pJeu -> ter.tab[event.button.y/32][event.button.x/32] == '0'){
                                nb_trous ++;
                            }
                            if(pJeu -> ter.tab[event.button.y/32][event.button.x/32] == 'E'){
                                pSdlEdit -> estEntreePlace = 0;
                            }
                            if(pJeu -> ter.tab[event.button.y/32][event.button.x/32] == 'S'){
                                pSdlEdit -> estSortiePlace = 0;
                            }
                            pJeu -> ter.tab[event.button.y/32][event.button.x/32] = 'A';
                            rafraichissement = 1;
                            break;
                        default: break;
                    }
                }
                if(event.button.x > pSdlEdit -> surface_text_sauver -> clip_rect.x && event.button.x < pSdlEdit -> surface_text_sauver -> w + 7 && event.button.y > pSdlEdit -> surface_text_sauver -> clip_rect.y && event.button.y < pSdlEdit -> surface_text_sauver -> h && pSdlEdit -> estPersoPlace){
                    sauverFichierJeu(&(pSdlEdit -> jeu));
                }
            }

			if(event.type == SDL_KEYUP)
			{
				switch(event.key.keysym.sym)
				{
				    case SDLK_1:
                        selected = 1;
                        break;
                    case SDLK_2:
                        selected = 2;
                        break;
                    case SDLK_3:
                        selected = 3;
                        break;
                    case SDLK_4:
                        selected = 4;
                        break;
                    case SDLK_5:
                        selected = 5;
                        break;
                    case SDLK_6:
                        selected = 6;
                        break;
                    case SDLK_7:
                        selected = 8;
                        break;
                    case SDLK_p:
                        selected = 7;
                        break;
                    case SDLK_SPACE:
                        selected = 0;
                        break;
                    case SDLK_ESCAPE:
                        continue_boucle = 0;
                        break;
                    default: break;
				}
			}
		}

        if(rafraichissement == 1)
        {
            pSdlEdit -> estPersoPlace = 0;
            sdlediteurAff(pSdlEdit);

            SDL_Flip(pSdlEdit -> surface_ecran);
        }
	}
}

void sdlediteurLibere(sdlEditeur * pSdlEdit){
    SDL_FreeSurface(pSdlEdit -> surface_perso);
	SDL_FreeSurface(pSdlEdit -> surface_mur);
	SDL_FreeSurface(pSdlEdit -> surface_caisse);
	SDL_FreeSurface(pSdlEdit -> surface_caisse_active);
	SDL_FreeSurface(pSdlEdit -> surface_trou);
	SDL_FreeSurface(pSdlEdit -> surface_sol);
	SDL_FreeSurface(pSdlEdit -> surface_tp_entree);
	SDL_FreeSurface(pSdlEdit -> surface_tp_sortie);
	SDL_FreeSurface(pSdlEdit -> surface_text_menu);
	SDL_FreeSurface(pSdlEdit -> surface_text_sauver);
	SDL_FreeSurface(pSdlEdit -> surface_menu_bas);
    SDL_FreeSurface(pSdlEdit -> surface_menu_haut);

    jeuLibere(&(pSdlEdit -> jeu));

	TTF_CloseFont(pSdlEdit -> police);
	TTF_CloseFont(pSdlEdit -> police2);

    TTF_Quit();

	SDL_Quit();
}
