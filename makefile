# Aissatou Diallo et Christian Jimenez

all: bin/main

#Creation de l'Executable du main
bin/main: obj/main.o
	gcc obj/main.o obj/sdlMenu.o obj/sdlJeu.o obj/menu.o obj/jeu.o obj/perso.o obj/terrain.o obj/caisse.o -lSDL -lSDL_ttf -o bin/main

#Creation de l'objet main
obj/main.o : src/main.c
	gcc -Wall -pedantic -c src/main.c -lSDL -lSDL_ttf -o $@

#Creation de l'objet sdlMenu
obj/sdlMenu.o : src/sdlMenu.c
	gcc  -Wall -pedantic -c src/sdlMenu.c -lSDL -lSDL_ttf -o $@
	
#Creation de l'objet sdlJeu
obj/sdlJeu.o : src/sdlJeu.c
	gcc  -Wall -pedantic -c src/sdlJeu.c -lSDL -lSDL_ttf -o $@

#Creation de l'objet menu
obj/menu.o : src/sdlJeu.c
	gcc  -Wall -pedantic -c src/menu.c -lSDL -lSDL_ttf -o $@
	
#Creation de l'objet Jeu
obj/jeu.o : src/jeu.c
	gcc  -Wall -pedantic -c src/jeu.c -lSDL -lSDL_ttf -o $@

#Creation de l'objet Perso
obj/perso.o : src/perso.c
	gcc  -Wall -pedantic -c src/perso.c -lSDL -lSDL_ttf -o $@

#Creation de l'objet Terrain
obj/terrain.o : src/terrain.c
	gcc  -Wall -pedantic -c src/terrain.c -lSDL -lSDL_ttf -o $@
	
#Creation de l'objet Caisse
obj/caisse.o : src/caisse.c
	gcc  -Wall -pedantic -c src/caisse.c -lSDL -lSDL_ttf -o $@


clean:
	rm obj/*.o *~ bin/main
