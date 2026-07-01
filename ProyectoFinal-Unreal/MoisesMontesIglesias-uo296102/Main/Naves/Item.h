#pragma once

#include "Actor.h"

class Item : public Actor
{
public: 
    enum class ItemType {
        Filo,
        Cuerda,
        Mango,
        Vacio, 
        Cuchillo
    };

    Item(ItemType type, string filename, float x, float y, Game* game);
    ItemType getItem();
    ItemType item;
};

