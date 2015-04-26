#include "menu.h"

void menuInit(Menu * pMenu)
{
	pMenu -> choix = 0;
}

void menuChoix(Menu * pMenu, int choix){
    switch (choix) {
        case 1 :
            pMenu -> choix = 1; /* jouer */
            break;

        case 2 :
            pMenu -> choix = 2; /* editeur */
            break;

        case 3 :
            pMenu -> choix = 3; /* options */
            break;

        default:
            pMenu -> choix = 0; /* quitter */
    }
}
