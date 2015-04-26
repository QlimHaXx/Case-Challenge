#include <assert.h>
#include <time.h>
#include "sdlJeu.h"
#include "constantes.h"

SDL_Surface * SDL_load_image(const char * filename );
void SDL_apply_surface(SDL_Surface * source, SDL_Surface * destination, int x, int y );

void sdljeuInit(sdlJeu * pSdlJeu)
{
	Jeu * pJeu;
	char niveau[40] = "";
	int nb_niveau;
	SDL_Color couleurBlanc = {255, 255, 255};
	SDL_Color couleurBleu = {0, 200, 255};

    pSdlJeu -> jeu_pause = 0;

	pSdlJeu -> police = NULL;
    pSdlJeu -> couleur = couleurBlanc;
    pSdlJeu -> couleur2 = couleurBleu;

    TTF_Init();
    pSdlJeu -> police = TTF_OpenFont("data/erasmd.ttf", 80);
    pSdlJeu -> police2 = TTF_OpenFont("data/erasmd.ttf", 25);
    pSdlJeu -> police3 = TTF_OpenFont("data/erasmd.ttf", 50);

	pJeu = &(pSdlJeu -> jeu);
	jeuInit(pJeu);

	nb_niveau = pJeu -> niveau;
	sprintf(niveau, "data/Niveaux/Niveau%d.txt", nb_niveau);
	chargerFichierJeu(pJeu, niveau); /* initialise les valeurs de pJeu avec celles du niveau */

	assert(SDL_Init(SDL_INIT_EVERYTHING) != -1);

	/* Chargement de l'icône AVANT SDL_SetVideoMode */
    SDL_WM_SetIcon(SDL_LoadBMP("data/caisse.bmp"), NULL);

	pSdlJeu -> surface_ecran = SDL_SetVideoMode(ECRAN_X, ECRAN_Y, 32, SDL_SWSURFACE | SDL_DOUBLEBUF | SDL_RESIZABLE); /* video avec double buffer */
	assert(pSdlJeu -> surface_ecran != NULL);

	SDL_WM_SetCaption("Case challenge", NULL); /* nom de la fenetre */

    /* ----------- Declaration des differentes surfaces ----- */

    pSdlJeu -> surface_text_gagner = TTF_RenderText_Blended(pSdlJeu -> police, "Vous avez gagné", pSdlJeu -> couleur);
    pSdlJeu -> surface_text_temps = TTF_RenderText_Blended(pSdlJeu -> police2, "Temps écoulé : 0:0:0", pSdlJeu -> couleur);
    pSdlJeu -> surface_text_objectifs = TTF_RenderText_Blended(pSdlJeu -> police2, "Caisses placées : ", pSdlJeu -> couleur);
    pSdlJeu -> surface_text_reset = TTF_RenderText_Blended(pSdlJeu -> police2, "Recommencer", pSdlJeu -> couleur);
    pSdlJeu -> surface_text_menu = TTF_RenderText_Blended(pSdlJeu -> police2, "Menu", pSdlJeu -> couleur);
    pSdlJeu -> surface_text_niveau = TTF_RenderText_Blended(pSdlJeu -> police2, "Niveau : 1", pSdlJeu -> couleur);
    pSdlJeu -> surface_text_next = TTF_RenderText_Blended(pSdlJeu -> police3, "Suivant", pSdlJeu -> couleur);
    pSdlJeu -> surface_text_exit = TTF_RenderText_Blended(pSdlJeu -> police3, "Quitter", pSdlJeu -> couleur);
    pSdlJeu -> surface_text_actions = TTF_RenderText_Blended(pSdlJeu -> police2, "Actions : 0", pSdlJeu -> couleur);
    pSdlJeu -> surface_text_menu_titre = TTF_RenderText_Blended(pSdlJeu -> police, "Case Challenge", pSdlJeu -> couleur);
    pSdlJeu -> surface_text_menu_continuer = TTF_RenderText_Blended(pSdlJeu -> police3, "Continuer", pSdlJeu -> couleur);
    pSdlJeu -> surface_text_menu_quitter = TTF_RenderText_Blended(pSdlJeu -> police3, "Quitter", pSdlJeu -> couleur);
    pSdlJeu -> surface_text_menu_options = TTF_RenderText_Blended(pSdlJeu -> police3, "Options", pSdlJeu -> couleur);
    pSdlJeu -> surface_text_menu_sauver = TTF_RenderText_Blended(pSdlJeu -> police3, "Sauver", pSdlJeu -> couleur);

    pSdlJeu -> surface_gagner = SDL_CreateRGBSurface(SDL_HWSURFACE, ECRAN_X, ECRAN_Y - 64, 32, 0, 0, 0, 0);
    pSdlJeu -> surface_menu_bas = SDL_CreateRGBSurface(SDL_HWSURFACE, ECRAN_X, 32, 32, 0, 0, 0, 0);
    pSdlJeu -> surface_menu_haut = SDL_CreateRGBSurface(SDL_HWSURFACE, ECRAN_X, 32, 32, 0, 0, 0, 0);

    pSdlJeu -> surface_perso = SDL_load_image("data/perso.bmp");
	if(pSdlJeu -> surface_perso == NULL)
        pSdlJeu -> surface_perso = SDL_load_image("../data/perso.bmp");
    /* Rend la couleur de fond de l'image transparent */
	SDL_SetColorKey(pSdlJeu -> surface_perso, SDL_SRCCOLORKEY, SDL_MapRGB(pSdlJeu -> surface_perso -> format, 0, 255, 0));
	assert(pSdlJeu -> surface_perso != NULL);

	pSdlJeu -> surface_mur = SDL_load_image("data/mur.bmp");
	if(pSdlJeu -> surface_mur == NULL)
		pSdlJeu -> surface_mur = SDL_load_image("../data/mur.bmp");
	assert(pSdlJeu -> surface_mur != NULL);

	pSdlJeu -> surface_tp_entree = SDL_load_image("data/tp_entree.bmp");
	if(pSdlJeu -> surface_tp_entree == NULL)
		pSdlJeu -> surface_tp_entree = SDL_load_image("../data/tp_entree.bmp");
	assert(pSdlJeu -> surface_tp_entree != NULL);


    pSdlJeu -> surface_tp_sortie = SDL_load_image("data/tp_sortie.bmp");
	if(pSdlJeu -> surface_tp_sortie == NULL)
		pSdlJeu -> surface_tp_sortie = SDL_load_image("../data/tp_sortie.bmp");
	assert(pSdlJeu -> surface_tp_sortie != NULL);


	pSdlJeu -> surface_caisse = SDL_load_image("data/caisse.bmp");
	if(pSdlJeu -> surface_caisse == NULL)
		pSdlJeu -> surface_caisse = SDL_load_image("../data/caisse.bmp");
	assert(pSdlJeu -> surface_caisse != NULL);

	pSdlJeu -> surface_caisse_place = SDL_load_image("data/caisse_active.bmp");
	if(pSdlJeu -> surface_caisse_place == NULL)
		pSdlJeu -> surface_caisse_place = SDL_load_image("../data/caisse_active.bmp");
	assert(pSdlJeu -> surface_caisse_place != NULL);

	pSdlJeu -> surface_trou = SDL_load_image("data/trou.bmp");
	if(pSdlJeu -> surface_trou == NULL)
		pSdlJeu -> surface_trou = SDL_load_image("../data/trou.bmp");
	assert(pSdlJeu -> surface_trou != NULL);

	pSdlJeu -> surface_sol = SDL_load_image("data/sol.bmp");
	if(pSdlJeu -> surface_sol == NULL)
		pSdlJeu -> surface_sol = SDL_load_image("../data/sol.bmp");
	assert(pSdlJeu -> surface_sol != NULL);
}

void sdljeuAff(sdlJeu * pSdlJeu)
{
	int x, y, i;
	int nb_caisses_place = 0;
	char nb_Cplace[20] = "";
	char actions[40] = "";
    const Jeu * pJeu = &(pSdlJeu -> jeu);
	const Terrain * pTer = jeuGetConstTerrainPtr(pJeu);
	const Perso * pPers = jeuGetConstPersoPtr(pJeu);

	/* Remplir l'écran de blanc */
	SDL_FillRect(pSdlJeu -> surface_ecran, &(pSdlJeu -> surface_ecran -> clip_rect), SDL_MapRGB(pSdlJeu -> surface_ecran -> format, 0x99, 0xBB, 0xCC));
	SDL_FillRect(pSdlJeu -> surface_gagner, NULL, SDL_MapRGB(pSdlJeu -> surface_ecran -> format, 0x00, 0x00, 0x00));
	SDL_SetAlpha(pSdlJeu -> surface_gagner, SDL_SRCALPHA, 200);
    SDL_FillRect(pSdlJeu -> surface_menu_haut, NULL, SDL_MapRGB(pSdlJeu -> surface_ecran -> format, 0x00, 0x33, 0x55));
    SDL_FillRect(pSdlJeu -> surface_menu_bas, NULL, SDL_MapRGB(pSdlJeu -> surface_ecran -> format, 0x00, 0x33, 0x55));

	for (x = 0; x < getDimX(pTer); x++){
        for (y = 0; y < getDimY(pTer); y++){
            if(terGetXY(pTer, x, y) == '#'){
				SDL_apply_surface(pSdlJeu -> surface_mur, pSdlJeu -> surface_ecran, x * TAILLE_SPRITE, y * TAILLE_SPRITE);
            }
            else if(terGetXY(pTer, x, y) == '0'){
                SDL_apply_surface(pSdlJeu -> surface_trou, pSdlJeu -> surface_ecran, x * TAILLE_SPRITE, y * TAILLE_SPRITE);
            }
            else if(terGetXY(pTer, x, y) == '.'){
                SDL_apply_surface(pSdlJeu -> surface_sol, pSdlJeu -> surface_ecran, x * TAILLE_SPRITE, y * TAILLE_SPRITE);
            }
            else if(terGetXY(pTer, x, y) == 'E'){
                SDL_apply_surface(pSdlJeu -> surface_tp_entree, pSdlJeu -> surface_ecran, x * TAILLE_SPRITE, y * TAILLE_SPRITE);
            }
            else if(terGetXY(pTer, x, y) == 'S'){
                SDL_apply_surface(pSdlJeu -> surface_tp_sortie, pSdlJeu -> surface_ecran, x * TAILLE_SPRITE, y * TAILLE_SPRITE);
            }
        }
	}

	SDL_apply_surface(pSdlJeu -> surface_perso, pSdlJeu -> surface_ecran, persoGetX(pPers) * TAILLE_SPRITE, persoGetY(pPers) * TAILLE_SPRITE);

    sprintf(nb_Cplace, "Caisses placées : %d/%d", nb_caisses_place, pJeu -> nb_caisses);
    pSdlJeu -> surface_text_objectifs = TTF_RenderText_Blended(pSdlJeu -> police2, nb_Cplace, pSdlJeu -> couleur);

	for(i = 0; i < pJeu -> nb_caisses; i++){
        if(pJeu -> tab_caisses[i].estPlace == 0){
            SDL_apply_surface(pSdlJeu -> surface_caisse, pSdlJeu -> surface_ecran, (pJeu -> tab_caisses[i].x)*TAILLE_SPRITE, (pJeu -> tab_caisses[i].y)*TAILLE_SPRITE);
        }
        else {
            SDL_apply_surface(pSdlJeu -> surface_caisse_place, pSdlJeu -> surface_ecran, (pJeu -> tab_caisses[i].x)*TAILLE_SPRITE, (pJeu -> tab_caisses[i].y)*TAILLE_SPRITE);

            nb_caisses_place ++;
            sprintf(nb_Cplace, "Caisses placées : %d/%d", nb_caisses_place, pJeu -> nb_caisses);
            pSdlJeu -> surface_text_objectifs = TTF_RenderText_Blended(pSdlJeu -> police2, nb_Cplace, pSdlJeu -> couleur);
        }
	}

    SDL_apply_surface(pSdlJeu -> surface_menu_bas, pSdlJeu -> surface_ecran, 0, ECRAN_Y - 32);
	SDL_apply_surface(pSdlJeu -> surface_menu_haut, pSdlJeu -> surface_ecran, 0, 0);
    SDL_apply_surface(pSdlJeu -> surface_text_niveau, pSdlJeu -> surface_ecran, 5, 3);
    SDL_apply_surface(pSdlJeu -> surface_text_temps, pSdlJeu -> surface_ecran, 5, ECRAN_Y - 32 + 3);
    SDL_apply_surface(pSdlJeu -> surface_text_objectifs, pSdlJeu -> surface_ecran, ECRAN_X - 7 * 32, ECRAN_Y - 32 + 3);
    SDL_apply_surface(pSdlJeu -> surface_text_reset, pSdlJeu -> surface_ecran, ECRAN_X - 8 * 32, 3);
    SDL_apply_surface(pSdlJeu -> surface_text_menu, pSdlJeu -> surface_ecran, ECRAN_X - 2 * 35, 3);
    SDL_apply_surface(pSdlJeu -> surface_text_actions, pSdlJeu -> surface_ecran, ECRAN_X / 2 - 32, ECRAN_Y - 32 + 3);

    if(pSdlJeu -> jeu_pause){
        SDL_apply_surface(pSdlJeu -> surface_gagner, pSdlJeu -> surface_ecran, 0, 32);
        SDL_apply_surface(pSdlJeu -> surface_text_menu_titre, pSdlJeu -> surface_ecran, ECRAN_X / 2 - pSdlJeu -> surface_text_menu_titre -> w / 2, 4 * 32);
        SDL_apply_surface(pSdlJeu -> surface_text_menu_continuer, pSdlJeu -> surface_ecran, ECRAN_X / 2 - pSdlJeu -> surface_text_menu_continuer -> w / 2, 9 * 32);
        SDL_apply_surface(pSdlJeu -> surface_text_menu_sauver, pSdlJeu -> surface_ecran, ECRAN_X / 2 - pSdlJeu -> surface_text_menu_sauver -> w / 2, 11 * 32);
        SDL_apply_surface(pSdlJeu -> surface_text_menu_options, pSdlJeu -> surface_ecran, ECRAN_X / 2 - pSdlJeu -> surface_text_menu_options -> w / 2, 13 * 32);
        SDL_apply_surface(pSdlJeu -> surface_text_menu_quitter, pSdlJeu -> surface_ecran, ECRAN_X / 2 - pSdlJeu -> surface_text_menu_quitter -> w / 2, 15 * 32);
    }

	if(estJeuGagne(&(pSdlJeu -> jeu))){
        SDL_apply_surface(pSdlJeu -> surface_gagner, pSdlJeu -> surface_ecran, 0, 32);
        SDL_apply_surface(pSdlJeu -> surface_text_gagner, pSdlJeu -> surface_ecran, ECRAN_X / 4, ECRAN_Y / 3 - 32);
        SDL_apply_surface(pSdlJeu -> surface_text_next, pSdlJeu -> surface_ecran, ECRAN_X - 7 * 32, ECRAN_Y - 5 * 32);
        SDL_apply_surface(pSdlJeu -> surface_text_exit, pSdlJeu -> surface_ecran, 2 * 32, ECRAN_Y - 5 * 32);
    }

    sprintf(actions, "Actions : %d", pJeu -> nb_actions);
    pSdlJeu -> surface_text_actions = TTF_RenderText_Blended(pSdlJeu -> police2, actions, pSdlJeu -> couleur);
}

void sdljeuPause(sdlJeu * psdlJeu){

}

void sdljeuBoucle(sdlJeu * pSdlJeu)
{
	SDL_Event event;
	SDL_Event event2;
	Jeu * pJeu;
	int continue_boucle = 1;
	int quitter = 0;
    int rafraichissement;
    int reset;
    int tempsPrecedent = 0, tempsActuel = 0;
    int min = 0;
    int sec = 0;
    int ms = 0;
    char temps[40] = "";
    char niveau[40] = "";
	int nb_niveau;
    int niveau_suivant;

    pJeu = &(pSdlJeu -> jeu);
    tempsActuel = SDL_GetTicks();

    sprintf(temps, "Temps écoulé : %d:%d:%d", min, sec, ms); /* écrit "compteur" dans la chaine de caracteres (converti l'int en char) */
    pSdlJeu -> surface_text_temps = TTF_RenderText_Blended(pSdlJeu -> police2, temps, pSdlJeu -> couleur);

    nb_niveau = pJeu -> niveau;
    sprintf(niveau, "Niveau : %d", nb_niveau); /* écrit "compteur" dans la chaine de caracteres (converti l'int en char) */
    pSdlJeu -> surface_text_niveau = TTF_RenderText_Blended(pSdlJeu -> police2, niveau, pSdlJeu -> couleur);
	sprintf(niveau, "data/Niveaux/Niveau%d.txt", nb_niveau);
	chargerFichierJeu(pJeu, niveau); /* initialise les valeurs de pJeu avec celles du niveau */

	sdljeuAff(pSdlJeu);
	assert(SDL_Flip(pSdlJeu -> surface_ecran) != -1);

    SDL_EnableKeyRepeat(100, 150); /* active la répétition des touches en ms */

    while(!quitter){

        continue_boucle = 1;

        while(continue_boucle == 1 && !estJeuGagne(&(pSdlJeu -> jeu))) /* boucle evenement avant d'avoir gagner */
        {
            reset = 0;
            tempsActuel = SDL_GetTicks();
            rafraichissement = 0;

            /* tant qu'il y a des evenements à traiter : cette boucle n'est pas bloquante */
            while(SDL_PollEvent(&event))
            {
                /* Si l'utilisateur a cliqué sur la croix de fermeture */
                if(event.type == SDL_QUIT){
                    continue_boucle = 0;
                    quitter = 1;
                }

                if(event.type == SDL_VIDEORESIZE){
                    pSdlJeu -> surface_ecran = SDL_SetVideoMode(event.resize.w, event.resize.h, 32, SDL_HWSURFACE | SDL_RESIZABLE);
                }

                if(event.type == SDL_MOUSEBUTTONUP){
                    if (event.button.button == SDL_BUTTON_LEFT){
                        if(event.button.x > ECRAN_X - 8 * 32 && event.button.x < ECRAN_X - 3 * 32 && event.button.y > 0 && event.button.y < 32){ /* reset */
                            reset = 1;
                            pJeu -> nb_actions = 0;
                            pSdlJeu -> jeu_pause = 0;
                            continue_boucle = 0;
                            quitter = 1; /* comme reset rapel sdlboucle il faut sortir de tout les while d'abord */
                        }
                        if(event.button.x > ECRAN_X - 2 * 35 && event.button.x < ECRAN_X && event.button.y > 3 && event.button.y < 32){ /* menu */
                            if(pSdlJeu -> jeu_pause){
                               pSdlJeu -> jeu_pause = 0;
                            }
                            else {
                               pSdlJeu -> jeu_pause = 1;
                            }
                            rafraichissement = 1;
                            continue_boucle = 0;
                        }
                    }
                }

                if(event.type == SDL_MOUSEMOTION){
                    if(event.motion.x > ECRAN_X - 8 * 32 && event.motion.x < ECRAN_X - 3 * 32 && event.motion.y > 0 && event.motion.y < 32){ /* reset */
                        pSdlJeu -> surface_text_reset = TTF_RenderText_Blended(pSdlJeu -> police2, "Recommencer", pSdlJeu -> couleur2);
                        rafraichissement = 1;
                    }
                    else if(event.motion.x > ECRAN_X - 2 * 32 && event.motion.x < ECRAN_X && event.motion.y > 0 && event.motion.y < 32){ /* menu */
                        pSdlJeu -> surface_text_menu = TTF_RenderText_Blended(pSdlJeu -> police2, "Menu", pSdlJeu -> couleur2);
                        rafraichissement = 1;
                    }
                    else {
                        pSdlJeu -> surface_text_reset = TTF_RenderText_Blended(pSdlJeu -> police2, "Recommencer", pSdlJeu -> couleur);
                        pSdlJeu -> surface_text_menu = TTF_RenderText_Blended(pSdlJeu -> police2, "Menu", pSdlJeu -> couleur);
                        rafraichissement = 1;
                    }
                }

                /* Si l'utilisateur a appuyé sur une touche */
                if(event.type == SDL_KEYDOWN)
                {
                    switch(event.key.keysym.sym)
                    {
                        case SDLK_UP:
                            jeuActionClavier(&(pSdlJeu -> jeu), 'h');
                            rafraichissement = 1;
                            pSdlJeu -> surface_perso = SDL_load_image("data/perso_up.bmp");
                            if(pSdlJeu -> surface_perso == NULL)
                                pSdlJeu -> surface_perso = SDL_load_image("../data/perso_up.bmp");
                            SDL_SetColorKey(pSdlJeu -> surface_perso, SDL_SRCCOLORKEY, SDL_MapRGB(pSdlJeu -> surface_perso -> format, 0, 255, 0));
                            break;
                        case SDLK_DOWN:
                            jeuActionClavier(&(pSdlJeu -> jeu), 'b');
                            rafraichissement = 1;
                            pSdlJeu -> surface_perso = SDL_load_image("data/perso_down.bmp");
                            if(pSdlJeu -> surface_perso == NULL)
                                pSdlJeu -> surface_perso = SDL_load_image("../data/perso_down.bmp");
                            SDL_SetColorKey(pSdlJeu -> surface_perso, SDL_SRCCOLORKEY, SDL_MapRGB(pSdlJeu -> surface_perso -> format, 0, 255, 0));
                            break;
                        case SDLK_LEFT:
                            jeuActionClavier(&(pSdlJeu -> jeu), 'g');
                            rafraichissement = 1;
                            pSdlJeu -> surface_perso = SDL_load_image("data/perso_left.bmp");
                            if(pSdlJeu -> surface_perso == NULL)
                                pSdlJeu -> surface_perso = SDL_load_image("../data/perso_left.bmp");
                            SDL_SetColorKey(pSdlJeu -> surface_perso, SDL_SRCCOLORKEY, SDL_MapRGB(pSdlJeu -> surface_perso -> format, 0, 255, 0));
                            break;
                        case SDLK_RIGHT:
                            jeuActionClavier(&(pSdlJeu -> jeu), 'd');
                            rafraichissement = 1;
                            pSdlJeu -> surface_perso = SDL_load_image("data/perso_right.bmp");
                            if(pSdlJeu -> surface_perso == NULL)
                                pSdlJeu -> surface_perso = SDL_load_image("../data/perso_right.bmp");
                            SDL_SetColorKey(pSdlJeu -> surface_perso, SDL_SRCCOLORKEY, SDL_MapRGB(pSdlJeu -> surface_perso -> format, 0, 255, 0));
                            break;
                        case SDLK_ESCAPE:
                            if(pSdlJeu -> jeu_pause){
                               pSdlJeu -> jeu_pause = 0;
                            }
                            else {
                               pSdlJeu -> jeu_pause = 1;
                            }
                            rafraichissement = 1;
                            continue_boucle = 0;
                            break;
                        default: break;
                    }
                }
            }

            if(tempsActuel - tempsPrecedent > 9 && !pSdlJeu -> jeu_pause) /* Si 10 ms se sont écoulées depuis le dernier tour de boucle */
            {
                ms ++;
                if(ms > 99){
                    sec ++;
                    ms = 0;
                }
                if(sec > 59){
                    min ++;
                    sec = 0;
                }
                sprintf(temps, "Temps écoulé : %d:%d:%d", min, sec, ms); /* On écrit dans la chaîne "temps" le nouveau temps */
                SDL_FreeSurface(pSdlJeu -> surface_text_temps); /* On supprime la surface précédente */
                pSdlJeu -> surface_text_temps = TTF_RenderText_Blended(pSdlJeu -> police2, temps, pSdlJeu -> couleur); /* On écrit la chaîne temps dans la SDL_Surface */
                tempsPrecedent = tempsActuel; /* On met à jour le tempsPrecedent */
                rafraichissement = 1;
            }

            if(reset == 1){
                sdljeuBoucle(pSdlJeu);
            }

            if(rafraichissement == 1)
            {
                /* on affiche le jeu sur le buffer caché */
                sdljeuAff(pSdlJeu);

                /* on permute les deux buffers (cette fonction ne doit se faire qu'une seule fois dans la boucle) */
                SDL_Flip(pSdlJeu -> surface_ecran);
            }
        }

        while(pSdlJeu -> jeu_pause) /* boucle evenement jeu en pause */
        {

            rafraichissement = 0;
            reset = 0;

            while(SDL_PollEvent(&event))
            {
                if(event.type == SDL_QUIT){
                    quitter = 1;
                    pSdlJeu -> jeu_pause = 0;
                }

                if(event.type == SDL_KEYDOWN)
                {
                    switch(event.key.keysym.sym)
                    {
                        case SDLK_ESCAPE:
                            pSdlJeu -> jeu_pause = 0;
                            continue_boucle = 1;
                            break;
                        default: break;
                    }
                }

                if(event.type == SDL_MOUSEBUTTONUP){
                    if (event.button.button == SDL_BUTTON_LEFT){
                        if(event.button.x > ECRAN_X - 8 * 32 && event.button.x < ECRAN_X - 3 * 32 && event.button.y > 0 && event.button.y < 32){ /* reset */
                            reset = 1;
                            pSdlJeu -> jeu_pause = 0;
                            continue_boucle = 1;
                            pJeu -> nb_actions = 0;
                            quitter = 1;
                        }
                        if(event.button.x > ECRAN_X - 2 * 35 && event.button.x < ECRAN_X && event.button.y > 3 && event.button.y < 32){ /* menu */
                            pSdlJeu -> jeu_pause = 0;
                            continue_boucle = 1;
                        }
                    }
                }

                if(event.type == SDL_MOUSEMOTION){
                    if(event.motion.x > ECRAN_X - 8 * 32 && event.motion.x < ECRAN_X - 3 * 32 && event.motion.y > 0 && event.motion.y < 32){ /* reset */
                        pSdlJeu -> surface_text_reset = TTF_RenderText_Blended(pSdlJeu -> police2, "Recommencer", pSdlJeu -> couleur2);
                        rafraichissement = 1;
                    }
                    else if(event.motion.x > ECRAN_X - 2 * 32 && event.motion.x < ECRAN_X && event.motion.y > 0 && event.motion.y < 32){ /* menu */
                        pSdlJeu -> surface_text_menu = TTF_RenderText_Blended(pSdlJeu -> police2, "Menu", pSdlJeu -> couleur2);
                        rafraichissement = 1;
                    }
                    else {
                        pSdlJeu -> surface_text_reset = TTF_RenderText_Blended(pSdlJeu -> police2, "Recommencer", pSdlJeu -> couleur);
                        pSdlJeu -> surface_text_menu = TTF_RenderText_Blended(pSdlJeu -> police2, "Menu", pSdlJeu -> couleur);
                        rafraichissement = 1;
                    }
                }

            }

            if(reset == 1){
                sdljeuBoucle(pSdlJeu);
            }

        }

        while(continue_boucle == 1 && estJeuGagne(&(pSdlJeu -> jeu))) /* boucle evenement apres avoir gagner */
        {
            reset = 0;
            niveau_suivant = 0;

            while(SDL_PollEvent(&event))
            {
                if(event.type == SDL_QUIT){
                    continue_boucle = 0;
                    quitter = 1;
                }

                if(event.type == SDL_MOUSEBUTTONUP){
                    if (event.button.button == SDL_BUTTON_LEFT){
                        if(event.button.x > 2 * 32 && event.button.x < 7 * 32 && event.button.y > ECRAN_Y - 5 * 32 && event.button.y < ECRAN_Y - 3 * 32){ /* quitter */
                            continue_boucle = 0;
                            reset = 0;
                            niveau_suivant = 0;
                        }
                        else if(event.button.x > ECRAN_X - 7 * 32 && event.button.x < ECRAN_X - 2 * 30 && event.button.y > ECRAN_Y - 5 * 32 && event.button.y < ECRAN_Y - 3 * 32){ /* suivant */
                            pJeu -> niveau++;
                            pJeu -> nb_actions = 0;
                            niveau_suivant = 1;
                            continue_boucle = 0;
                        }
                        else if(event.button.x > ECRAN_X - 8 * 32 && event.button.x < ECRAN_X - 3 * 32 && event.button.y > 0 && event.button.y < 32){ /* reset */
                            reset = 1;
                            pJeu -> nb_actions = 0;
                            continue_boucle = 0;
                        }
                    }
                }

                if(event.type == SDL_MOUSEMOTION){
                    if(event.motion.x > 2 * 32 && event.motion.x < 7 * 32 && event.motion.y > ECRAN_Y - 5 * 32 && event.motion.y < ECRAN_Y - 3 * 32){ /* quitter */
                        pSdlJeu -> surface_text_exit = TTF_RenderText_Blended(pSdlJeu -> police3, "Quitter", pSdlJeu -> couleur2);
                        rafraichissement = 1;
                    }
                    else if(event.motion.x > ECRAN_X - 7 * 32 && event.motion.x < ECRAN_X - 2 * 30 && event.motion.y > ECRAN_Y - 5 * 32 && event.motion.y < ECRAN_Y - 3 * 32){ /* suivant */
                        pSdlJeu -> surface_text_next = TTF_RenderText_Blended(pSdlJeu -> police3, "Suivant", pSdlJeu -> couleur2);
                        rafraichissement = 1;
                    }
                    else if(event.motion.x > ECRAN_X - 8 * 32 && event.motion.x < ECRAN_X - 3 * 32 && event.motion.y > 0 && event.motion.y < 32){ /* reset */
                        pSdlJeu -> surface_text_reset = TTF_RenderText_Blended(pSdlJeu -> police2, "Recommencer", pSdlJeu -> couleur2);
                        rafraichissement = 1;
                    }
                    else if(event.motion.x > ECRAN_X - 2 * 32 && event.motion.x < ECRAN_X && event.motion.y > 0 && event.motion.y < 32){ /* menu+ */
                        pSdlJeu -> surface_text_menu = TTF_RenderText_Blended(pSdlJeu -> police2, "Menu", pSdlJeu -> couleur2);
                        rafraichissement = 1;
                    }
                    else {
                        pSdlJeu -> surface_text_reset = TTF_RenderText_Blended(pSdlJeu -> police2, "Recommencer", pSdlJeu -> couleur);
                        pSdlJeu -> surface_text_menu = TTF_RenderText_Blended(pSdlJeu -> police2, "Menu", pSdlJeu -> couleur);
                        pSdlJeu -> surface_text_exit = TTF_RenderText_Blended(pSdlJeu -> police3, "Quitter", pSdlJeu -> couleur);
                        pSdlJeu -> surface_text_next = TTF_RenderText_Blended(pSdlJeu -> police3, "Suivant", pSdlJeu -> couleur);
                        rafraichissement = 1;
                    }
                }

            }

            if(reset == 1){
                sdljeuBoucle(pSdlJeu);
            }

            if(niveau_suivant == 1){
                sdljeuBoucle(pSdlJeu);
            }

            if (rafraichissement == 1)
            {
                /* on affiche le jeu sur le buffer caché */
                sdljeuAff(pSdlJeu);

                /* on permute les deux buffers (cette fonction ne doit se faire qu'une seule fois dans la boucle) */
                SDL_Flip(pSdlJeu -> surface_ecran);
            }

        }
    }
}

void sdljeuLibere(sdlJeu * pSdlJeu)
{
	SDL_FreeSurface(pSdlJeu -> surface_perso);
	SDL_FreeSurface(pSdlJeu -> surface_mur);
	SDL_FreeSurface(pSdlJeu -> surface_caisse);
	SDL_FreeSurface(pSdlJeu -> surface_caisse_place);
	SDL_FreeSurface(pSdlJeu -> surface_trou);
	SDL_FreeSurface(pSdlJeu -> surface_sol);
	SDL_FreeSurface(pSdlJeu -> surface_tp_entree);
	SDL_FreeSurface(pSdlJeu -> surface_tp_sortie);
	SDL_FreeSurface(pSdlJeu -> surface_text_gagner);
	SDL_FreeSurface(pSdlJeu -> surface_gagner);
	SDL_FreeSurface(pSdlJeu -> surface_text_objectifs);
	SDL_FreeSurface(pSdlJeu -> surface_text_temps);
	SDL_FreeSurface(pSdlJeu -> surface_text_niveau);
	SDL_FreeSurface(pSdlJeu -> surface_text_menu);
	SDL_FreeSurface(pSdlJeu -> surface_text_reset);
	SDL_FreeSurface(pSdlJeu -> surface_menu_bas);
    SDL_FreeSurface(pSdlJeu -> surface_menu_haut);
    SDL_FreeSurface(pSdlJeu -> surface_text_exit);
    SDL_FreeSurface(pSdlJeu -> surface_text_next);
    SDL_FreeSurface(pSdlJeu -> surface_text_menu_continuer);
    SDL_FreeSurface(pSdlJeu -> surface_text_menu_quitter);
    SDL_FreeSurface(pSdlJeu -> surface_text_menu_sauver);
    SDL_FreeSurface(pSdlJeu -> surface_text_menu_options);
    SDL_FreeSurface(pSdlJeu -> surface_text_menu_titre);

	jeuLibere(&(pSdlJeu -> jeu));

	TTF_CloseFont(pSdlJeu -> police);
	TTF_CloseFont(pSdlJeu -> police2);

    TTF_Quit();

	SDL_Quit();
}
