//Ampliacion-4
#pragma once

#include "Actor.h";

class PowerUp : public Actor
{
public:
	PowerUp(float x, float y, Game* game);
	virtual void update();
};