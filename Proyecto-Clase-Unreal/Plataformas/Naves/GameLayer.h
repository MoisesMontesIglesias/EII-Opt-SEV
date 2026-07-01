#pragma once

#include "Background.h"
#include "Layer.h"
#include "Player.h"
#include "Enemy.h"
#include "Projectile.h"
#include "Text.h"
#include "Tile.h"
#include "Space.h" // importar
#include "Pad.h"

#include <fstream> // Leer ficheros
#include <sstream> // Leer líneas / String

//Ampliacion-6
#include "ItemRecolectable.h";
#include "Moneda.h";

//Ampliacion-9
#include "TileDestruibleJump.h"
#include "TileDestruibleShooting.h"

//Ampliacion-14
#include "PuntoGuardado.h"


#include <list>;


class GameLayer : public Layer

{
public:
	GameLayer(Game* game);
	void init() override;
	void processControls() override;
	void update() override;
	void draw() override;
	void keysToControls(SDL_Event event);
	void mouseToControls(SDL_Event event); // USO DE MOUSE
	void gamePadToControls(SDL_Event event); // USO DE GAMEPAD
	void loadMap(string name);
	void loadMapObject(char character, float x, float y);
	void calculateScroll();
	Actor* message;
	bool pause;

	// Elementos de interfaz
	SDL_GameController* gamePad;
	Actor* buttonJump;
	Actor* buttonShoot;
	Pad* pad;
	Tile* cup; // Elemento de final de nivel
	Space* space;
	float scrollX;

	int mapWidth;
	list<Tile*> tiles;

	Text* textPoints;
	int points;

	int newEnemyTime = 0;

	Player* player;
	Background* background; 
	Actor* backgroundPoints;
	bool controlContinue = false;
	bool controlShoot = false;
	int controlMoveY = 0;
	int controlMoveX = 0;

	list<Enemy*> enemies;

	list<Projectile*> projectiles;

	//Ampliacion-6
	list<Moneda*> monedas;
	ItemRecolectable* item;

	//Ampliacion-5
	float scrollY;

	//Ampliacion-14
	float savePointX;
	float savePointY;
	void setSavePoint(float x, float y);

	//Ampliacion-14
	list<PuntoGuardado*> puntosGuardado;
};




