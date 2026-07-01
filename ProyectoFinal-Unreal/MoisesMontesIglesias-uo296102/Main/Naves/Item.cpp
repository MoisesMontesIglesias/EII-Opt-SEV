#include "Item.h"
Item::Item(ItemType itemTipo, string filename, float x, float y, Game* game) : 
	Actor(filename, x, y, 32, 40, game) {
	this->item = itemTipo;
}

Item::ItemType Item::getItem() {
	return item;
}