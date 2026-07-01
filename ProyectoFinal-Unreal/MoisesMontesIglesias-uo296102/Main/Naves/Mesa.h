#pragma once
#include "Tile.h"
#include "Item.h"

class Mesa : public Tile
{
public:
	Mesa(string filename, float x, float y, Game* game, bool inicial);

	bool playerOnTile(Actor* player);

	bool contieneItem;

	Item* comprobarContenido();
	Item* getItem();
	void removeItem();
	Item* item;
	void añadirItem(Item* item);
	void meterFilo(float x, float y, Game* game);
	void meterCuerda(float x, float y, Game* game);
	void meterMango(float x, float y, Game* game);
	string getItemNombre();
	bool inicial;
};