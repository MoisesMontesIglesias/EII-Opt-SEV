#pragma once

#include "Actor.h"
#include "Animation.h" 

class Enemy : public Actor
{
public:
	Enemy(float x, float y, Game* game);
	void draw(float scrollX = 0, float scrollY = 0) override; // Va a sobrescribir
	void update();
	void impacted(); // Recibe impacto y pone animación de morir
	float vxIntelligence;
	int state;
	int orientation;
	bool isDeleted = false;

	Animation* aIdleUp;
	Animation* aIdleDown;

	Animation* aRunningRight;
	Animation* aRunningLeft;

	Animation* aDead;   
	Animation* aDying;     
	Animation* animation; 

	float timer;

	float const timeLookingDown = 250.0f;
	float const timeMoving = 60.0f;
	float const timeLookingUp = 80.0f;
};

