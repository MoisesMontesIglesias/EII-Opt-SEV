#pragma once

#include "Actor.h"
#include "Audio.h"
#include "Projectile.h" 

class Player : public Actor
{
public:
	Player(float x, float y, Game* game);
	Projectile* shoot();
	void update();
	void moveX(float axis);
	void moveY(float axis);
	int shootCadence = 30;
	int shootTime = 0;
	//Ampliacion-4
	int disparos = 3;
	bool naveDisparada = false;

	Audio* audioShoot;
	//Ampliación-3
	int numeroVidas = 3;
	void loseLife();
};
