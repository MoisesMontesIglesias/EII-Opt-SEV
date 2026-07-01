#pragma once

#include "Tile.h";

class Silla : public Tile
{
public:
	Silla(string filename, float x, float y, Game* game, bool inicio, bool sentable);

	bool playerOnTile(Actor* player);
	bool sillaInicial;
	bool poderSentarse;
	bool tieneItem;
};