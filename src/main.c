#include <stdio.h>
#include "sdlMenu.h"
#include "sdlJeu.h"
#include "sdlEditeur.h"

int main (int argc, char** argv){

	sdlMenu sm;
	sdlJeu sj;
	sdlEditeur se;
	sdlmenuInit(&sm);
	sdlmenuBoucle(&sm);
	if(sm.menu.choix == 1){
        sdljeuInit(&sj);
        sdljeuBoucle(&sj);
        sdljeuLibere(&sj);
	}
	else if(sm.menu.choix == 2){
        sdlediteurInit(&se);
        sdlediteurBoucle(&se);
        sdlediteurLibere(&se);
	}
	sdlmenuLibere(&sm);

	printf("Fin\n");
	return 0;
}
