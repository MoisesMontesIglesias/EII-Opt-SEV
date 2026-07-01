#pragma once
//Ampliacion-9

#include "Tile.h";



class TileDestruibleJump : public Tile
{
public:
	TileDestruibleJump(string filename, float x, float y, Game* game);

	bool playerOnTile(Actor* player);

	int destructionTimer;
	bool activeDestruction;

	void activarDestruccion(int timeToDestroy);
	void updateDestructionTimer(int timeToDestroy);

	bool shouldDestroy();
};


