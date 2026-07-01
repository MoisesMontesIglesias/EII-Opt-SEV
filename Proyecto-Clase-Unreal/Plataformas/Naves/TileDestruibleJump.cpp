#include "TileDestruibleJump.h"

//Ampliacion-9

TileDestruibleJump::TileDestruibleJump(string filename, float x, float y, Game* game)
	: Tile(filename, x, y, game) {

    destructionTimer = 0;
    activeDestruction = false;
}

bool TileDestruibleJump::playerOnTile(Actor* actor) {
    return (actor->y + actor->height >= y &&
        actor->y + actor->height <= y + 2 && actor->x + actor->width / 2 >= x &&
            actor->x + actor->width / 2 <= x + width);
}

void TileDestruibleJump::activarDestruccion(int timeToDestroy) {
    destructionTimer = timeToDestroy;
    activeDestruction = true;
}

void TileDestruibleJump::updateDestructionTimer(int timeToDestroy) {
    if (activeDestruction && destructionTimer > 0) {
        destructionTimer -= timeToDestroy;
    }
}

bool TileDestruibleJump::shouldDestroy() {
    return activeDestruction && destructionTimer <= 0;
}
