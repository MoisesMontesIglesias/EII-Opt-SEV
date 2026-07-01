#pragma once

#include "Actor.h";
#include "Animation.h"

class Moneda : public Actor
{
public:
	Moneda(float x, float y, Game* game);
	virtual void update();
	int state;
	Animation* animation;
};