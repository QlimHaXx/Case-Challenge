#ifndef _TERRAIN_H
#define _TERRAIN_H

typedef struct
{
	int dimX;
	int dimY;
	char **tab;
} Terrain;

void terInit(Terrain *);
void terLibere(Terrain *);
const char terGetXY(const Terrain *, const int x, const int y);
void terSetXY(const Terrain *, const int x, const int y, const char);
const int getDimX(const Terrain *);
const int getDimY(const Terrain *);

#endif
