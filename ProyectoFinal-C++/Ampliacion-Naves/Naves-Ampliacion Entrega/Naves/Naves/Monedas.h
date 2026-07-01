//Ampliacion-6
#pragma once

#include "Actor.h";

class Monedas : public Actor
{
public:
	Monedas(float x, float y, Game* game);
	virtual void update();
};
