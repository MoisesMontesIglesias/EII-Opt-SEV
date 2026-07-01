#pragma once

#include "Layer.h"
#include "Player.h"
#include "Enemy.h"
#include "Text.h"
#include "Audio.h" 
#include "Projectile.h"
//Ampliación-3
#include "Vidas.h"

//Ampliacion-4
#include "PowerUp.h"

//Ampliación-6
#include "Monedas.h"

//Ampliacion-10
#include "Bombas.h";

#include <list>

#include "Background.h"

class GameLayer : public Layer

{
public:
	GameLayer(Game* game);
	void init() override;
	void processControls() override;
	void update() override;
	void draw() override;

	//void keysToControls(SDL_Event event, Player* player);
	void keysToControls(SDL_Event event);

	int newEnemyTime = 0;
	Audio* audioBackground;
	Background* background;
	Actor* backgroundPoints;
	bool controlShoot = false;
	int controlMoveY = 0;
	int controlMoveX = 0;
	//Ampliacion-11
	int controlMoveXPlayer2 = 0;
	int controlMoveYPlayer2 = 0;
	bool controlShootPlayer2 = false;
	void playerColisionEnemy(Player* player, Enemy* enemy);
	void playerColisionMoneda(Player* player, Monedas* moneda, list<Monedas*> deleteMonedas);
	void monedaDeleted(Player* player, Monedas* moneda, list<Monedas*> deleteMonedas);
//	void bombaDeleted(Player* player, Bombas* bomba, list<Bombas*> deleteBombas);
//	void playerDisparos(Player* player);
//	void movimientoPlayer(Player* player, int controlMoveX, int controlMoveY);
//	void powerUpDeleted(Player* player, PowerUp* power, list<PowerUp*> deletePowerUps);

	Text* textPoints;
	int points;


	list<Enemy*> enemies;
	list<Projectile*> projectiles;
	//Ampliacion-3
	list<Vidas*> vidas;
	//void cargarVidas(Player* player);
	void cargarVidas();

	//Ampliacion-6
	list<Monedas*> monedas;
	int newMonedaTime = 0;

	//Àmpliacion-10
	list<Bombas*> bombas;
	int newBombaTime = 0;

	//Ampliacion-4
	list<PowerUp*> powerUps;
	int newPowerUpTime = 0;

	//Ampliacion-11
    //list<Player*> players;
	Player* player;
	Player* player2;
};