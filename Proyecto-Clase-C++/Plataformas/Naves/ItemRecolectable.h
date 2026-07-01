#pragma once
//Ampliacion-6
#include "Actor.h"
#include "Animation.h"

class ItemRecolectable : public Actor
{
public:
	ItemRecolectable(float x, float y, Game* game);
	void update();
	void draw();
	Animation* actualizar;
	Animation* animation; // Referencia a la animación mostrada

};
