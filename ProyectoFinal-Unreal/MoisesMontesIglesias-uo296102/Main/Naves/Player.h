#pragma once

#include "Actor.h"
#include "Projectile.h" 
#include "Animation.h" // incluir animacion 
#include "Item.h"
#include "Audio.h"
#include <list>

class Player : public Actor
{
public:
	Player(float x, float y, Game* game);
	Projectile* shoot();
	void update();
	void jump();
	void moveX(float axis);
	void moveY(float axis);
	void draw(float scrollX = 0, float scrollY = 0) override; // Va a sobrescribir

	int invulnerableTime = 0;

	bool onAir;
	int orientation;
	int state;
	Animation* aIdleRight;
	Animation* aIdleLeft;
	Animation* aIdleUp;
	Animation* aIdleDown;

	Animation* aRunningRight;
	Animation* aRunningLeft;
	Animation* aRunningUp;
	Animation* aRunningDown;

	Animation* aShootingUp;
	Animation* aShootingDown;
	Animation* aShootingRight;
	Animation* aShootingLeft;

	Animation* aSentado;

	Animation* animation; // Referencia a la animación mostrada
	int shootCadence = 30;
	int shootTime = 0;

	int timeOnTile = 0;

	bool sentado;
	float tiempoSentado;
	bool recienLevantado;
	void delaySentado();
	int numeroVidas = 3;
	void loseLife();
	list<Item*> items;
	void addItemToInventory(Item* item);
	list<Item*> getItemsInInventory();
	float loseLifeCooldown;
	void crearItem(float x, float y, Game* game);
	Item* cuchillo;
	Audio* audioShoot;
	void reiniciarLista();
};