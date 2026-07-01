//Ampliacion-10
#include "Bombas.h"

Bombas::Bombas(float x, float y, Game* game)
	: Actor("res/planeta_1.png", x, y, 45, 45, game) {

	vx = 1;
}

void Bombas::update() {
	vx = -1;
	x = x + vx;
}