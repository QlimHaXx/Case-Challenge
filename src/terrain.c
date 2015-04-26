#include "terrain.h"
#include <stdio.h>
#include <malloc.h>
#include <assert.h>

void terInit(Terrain * pTer)
{
	pTer -> dimX = 0;
	pTer -> dimY = 0;

	pTer -> tab = NULL;

}

void terLibere(Terrain * pTer)
{
	int y;

	for (y = 0; y < pTer -> dimY; y++)
		free(pTer -> tab[y]);
	free(pTer -> tab);

	pTer -> dimX = 0;
	pTer -> dimY = 0;
	pTer -> tab = NULL;
}

const char terGetXY(const Terrain * pTer, const int x, const int y)
{
	assert(x >= 0);
	assert(y >= 0);
	assert(x < pTer -> dimX);
	assert(y < pTer -> dimY);
	return pTer -> tab[y][x];
}

void terSetXY(const Terrain * pTer, const int x, const int y, const char val)
{
	assert(x >= 0);
	assert(y >= 0);
	assert(x < pTer -> dimX);
	assert(y < pTer -> dimY);
	pTer -> tab[y][x] = val;
}

const int getDimX(const Terrain * pTer)
{
	return pTer -> dimX;
}

const int getDimY(const Terrain * pTer)
{
	return pTer -> dimY;
}
