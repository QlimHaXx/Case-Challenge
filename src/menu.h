#ifndef _MENU_H
#define _MENU_H

typedef struct
{
	int choix;
} Menu;

void menuInit(Menu *);
void menuChoix(Menu *, int choix);

#endif
