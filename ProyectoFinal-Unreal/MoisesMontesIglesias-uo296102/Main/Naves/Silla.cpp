#include "Silla.h"

Silla::Silla(string filename, float x, float y, Game* game, bool inicio, bool sentable)
	: Tile(filename, x, y, game) {
    this->sillaInicial = inicio;
    this->poderSentarse = sentable;
}

bool Silla::playerOnTile(Actor* actor) {
    return (actor->y + actor->height >= y &&
        actor->y + actor->height <= y + 2 && actor->x + actor->width / 2 >= x &&
            actor->x + actor->width / 2 <= x + width);
}
