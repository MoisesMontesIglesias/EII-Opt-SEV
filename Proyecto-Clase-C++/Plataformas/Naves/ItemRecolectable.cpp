//Ampliacion-6
#include "ItemRecolectable.h"
ItemRecolectable::ItemRecolectable(float x, float y, Game* game)
	: Actor("res/recolectable.png", x, y, 40, 40, game) {
	actualizar = new Animation("res/recolectable.png", width, height,
		255, 45, 0, 8, true, game);
	animation = actualizar;
}

void ItemRecolectable::update() {
	// Actualizar la animación
	animation->update();
}

void ItemRecolectable::draw() {
	animation->draw(x,y);
}

