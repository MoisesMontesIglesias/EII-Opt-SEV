//Ampliacion-10
#pragma once

#include "Actor.h";

class Bombas : public Actor
{
public: 
	Bombas(float x, float y, Game* game);
	virtual void update();
};
