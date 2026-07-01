//Ampliacion-4

#include "PowerUp.h"

PowerUp::PowerUp(float x, float y, Game* game)
	: Actor("res/planeta_2.png", x, y, 45, 45, game) {

	vx = 1;
}

void PowerUp::update() {
	vx = -1;
	x = x + vx;
}