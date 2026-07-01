#pragma once

#include "Layer.h"
#include "Player.h"
#include "Enemy.h"
#include "Projectile.h"
#include "Text.h"
#include "Tile.h"
#include "Space.h" // importar

#include <fstream> // Leer ficheros
#include <sstream> // Leer líneas / String

#include "Silla.h"
#include "Mesa.h"
#include "Vidas.h"
#include "Item.h"
#include "Audio.h" 
#include "CharcoAgua.h"
#include <random>


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
	void loadMap(string name);
	void loadMapObject(char character, float x, float y);
	void calculateScroll();
	Actor* message;
	bool pause;


	Tile* cup; // Elemento de final de nivel
	Space* space;
	float scrollX;
	Actor* button;
	int mapWidth;
	list<Tile*> tiles;

	Text* textItems;
	Text* textAccion;
	Text* textProfesor;
	Text* textSaqueo;
	Text* textExtra;

	int delay = 0;
	bool aplicarDelay();
	bool esperandoAccion = false;
	int mensaje = 0;
	void manejarInteraccionMesa(Mesa* mesa);
	bool manejarInteraccionProfesor(bool mensajeProfe);

	int points;

	int newEnemyTime = 0;

	Player* player; 
	bool controlContinue = false;
	bool controlShoot = false;
	int controlMoveY = 0;
	int controlMoveX = 0;

	list<Enemy*> enemies;

	list<Projectile*> projectiles;

	float scrollY;


	list<Mesa*> mesasClase;
	void cargarVidas();
	list<Vidas*> vidas;
	bool checkInteraction = false;
	void generarItemsMesas();
	Audio* audioBackground;
};




