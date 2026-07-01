#include "Moneda.h"

Moneda::Moneda(float x, float y, Game* game)
	: Actor("res/moneda.png", x, y, 45, 45, game) {

	vx = 1;
	animation = new Animation("res/recolectable.png", width, height,
		320, 40, 6, 8, true, game);

}

void Moneda::update() {
	animation->update();
}