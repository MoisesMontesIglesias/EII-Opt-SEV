//Ampliacion-6
#include "Monedas.h"

Monedas::Monedas(float x, float y, Game* game)
	: Actor("res/moneda.png", x, y, 45, 45, game) {

	vx = 1;
}

void Monedas::update() {
	vx = -1;
	x = x + vx;
}