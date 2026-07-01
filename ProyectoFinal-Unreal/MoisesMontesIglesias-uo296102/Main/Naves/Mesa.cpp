#include "Mesa.h"
#include "GameLayer.h"

Mesa::Mesa(string filename, float x, float y, Game* game, bool inicial)
    : Tile(filename, x, y, game) {
    item = new Item(Item::ItemType::Vacio, "", width, height, game);
    this->inicial = inicial;
}

bool Mesa::playerOnTile(Actor* actor) {
    return (actor->y + actor->height >= y &&
        actor->y + actor->height <= y + 2 && actor->x + actor->width / 2 >= x &&
        actor->x + actor->width / 2 <= x + width);
}

Item* Mesa::comprobarContenido()
{
    return getItem();
}

void Mesa::añadirItem(Item* item) {
    item = new Item(item->getItem(), "", width, height, game);
}

Item* Mesa::getItem() {
    return item;
}
string Mesa::getItemNombre() {
    if (item->getItem() == Item::ItemType::Cuerda) {
        return "Cuerda";
    }
    else if (item->getItem() == (Item::ItemType::Filo)) {
        return "Filo";
    }
    else if (item->getItem() == (Item::ItemType::Mango)) {
        return "Mango";
    }
    else {
        return "Vacio";
    }
}

void Mesa::removeItem() {
    item = new Item(Item::ItemType::Vacio, "", width, height, game);
}

void Mesa::meterFilo(float width, float height, Game* game) {
    item = new Item(Item::ItemType::Filo, "res/ItemFilo.png", width, height, game);
}

void Mesa::meterCuerda(float width, float height, Game* game) {
    item = new Item(Item::ItemType::Cuerda, "res/ItemCuerda.png", width, height, game);
}

void Mesa::meterMango(float width, float height, Game* game) {
    item = new Item(Item::ItemType::Mango, "res/ItemMango.png", width, height, game);
}
