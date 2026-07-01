#include "GameLayer.h"

GameLayer::GameLayer(Game* game) : Layer(game) {
	//llama al constructor del padre : Layer(renderer)
	init();
}

void GameLayer::init() {
	audioBackground = Audio::createAudio("res/musica_ambiente.mp3", true);
	audioBackground->play();

	points = 0;
	textPoints = new Text("hola", WIDTH * 0.92, HEIGHT * 0.04, game);
	textPoints->content = to_string(points);

	player = new Player(50, 50, game);
	player2 = new Player(50, 200, game);

	background = new Background("res/fondo.png", WIDTH * 0.5, HEIGHT * 0.5, -1, game);
	backgroundPoints = new Actor("res/icono_puntos.png",
		WIDTH * 0.85, HEIGHT * 0.05, 24, 24, game);
	
	//Ampliacion-3
	cargarVidas();

	projectiles.clear(); // Vaciar por si reiniciamos el juego
	
	enemies.clear(); // Vaciar por si reiniciamos el juego
	enemies.push_back(new Enemy(300, 50, game));
	enemies.push_back(new Enemy(300, 200, game));

	//Ampliacion-6
	monedas.clear();
	monedas.push_back(new Monedas(300, 125, game));

	//Ampliacion-4
	powerUps.clear();
	powerUps.push_back(new PowerUp(500, 125, game));
}

void GameLayer::processControls() {
	// obtener controles
	SDL_Event event;
	while (SDL_PollEvent(&event)) {
		keysToControls(event);
	}
	//procesar controles
	// Disparar
	if (controlShoot) {
		Projectile* newProjectile = player->shoot();
		//Ampliacion-4
		if (newProjectile != NULL && player->disparos != 0) {
			projectiles.push_back(newProjectile);
			player->disparos--;
			player->naveDisparada = true;
		}

	}

	// Eje X
	if (controlMoveX > 0) {
		player->moveX(1);
	}
	else if (controlMoveX < 0) {
		player->moveX(-1);
	}
	else {
		player->moveX(0);
	}

	// Eje Y
	if (controlMoveY > 0) {
		player->moveY(1);
	}
	else if (controlMoveY < 0) {
		player->moveY(-1);
	}
	else {
		player->moveY(0);
	}

	//Ampliacion-11
	if (controlShootPlayer2) {
		Projectile* newProjectile = player2->shoot();
		//Ampliacion-4
		if (newProjectile != NULL && player2->disparos != 0) {
			projectiles.push_back(newProjectile);
			player2->disparos--;
			player2->naveDisparada = true;
		}

	}

	// Eje X
	if (controlMoveXPlayer2 > 0) {
		player2->moveX(1);
	}
	else if (controlMoveXPlayer2 < 0) {
		player2->moveX(-1);
	}
	else {
		player2->moveX(0);
	}

	// Eje Y
	if (controlMoveYPlayer2 > 0) {
		player2->moveY(1);
	}
	else if (controlMoveYPlayer2 < 0) {
		player2->moveY(-1);
	}
	else {
		player2->moveY(0);
	}

}

void GameLayer::keysToControls(SDL_Event event) {

	if (event.type == SDL_KEYDOWN) {
		int code = event.key.keysym.sym;
		// Pulsada
		switch (code) {
		case SDLK_ESCAPE:
			game->loopActive = false;
			break;
		case SDLK_1:
			game->scale();
			break;
		case SDLK_d: // derecha
			controlMoveX = 1;
			break;
		case SDLK_a: // izquierda
			controlMoveX = -1;
			break;
		case SDLK_w: // arriba
			controlMoveY = -1;
			break;
		case SDLK_s: // abajo
			controlMoveY = 1;
			break;
		case SDLK_SPACE: // dispara
			controlShoot = true;
			break;
		case SDLK_RIGHT: // derecha
			controlMoveXPlayer2 = 1;
			break;
		case SDLK_LEFT: // izquierda
			controlMoveXPlayer2 = -1;
			break;
		case SDLK_UP: // arriba
			controlMoveYPlayer2 = -1;
			break;
		case SDLK_DOWN: // abajo
			controlMoveYPlayer2 = 1;
			break;
		case SDLK_RCTRL: // dispara
			controlShootPlayer2 = true;
			break;
		}

	}
	if (event.type == SDL_KEYUP) {
		int code = event.key.keysym.sym;
		// Levantada
		switch (code) {
		case SDLK_d: // derecha
			if (controlMoveX == 1) {
				controlMoveX = 0;
			}
			break;
		case SDLK_a: // izquierda
			if (controlMoveX == -1) {
				controlMoveX = 0;
			}
			break;
		case SDLK_w: // arriba
			if (controlMoveY == -1) {
				controlMoveY = 0;
			}
			break;
		case SDLK_s: // abajo
			if (controlMoveY == 1) {
				controlMoveY = 0;
			}
			break;
		case SDLK_SPACE: // dispara
			controlShoot = false;
			break;

		case SDLK_RIGHT: // derecha
			if (controlMoveXPlayer2 == 1) {
				controlMoveXPlayer2 = 0;
			}
			break;
		case SDLK_LEFT: // izquierda
			if (controlMoveXPlayer2 == -1) {
				controlMoveXPlayer2 = 0;
			}
			break;
		case SDLK_UP: // arriba
			if (controlMoveYPlayer2 == -1) {
				controlMoveYPlayer2 = 0;
			}
			break;
		case SDLK_DOWN: // abajo
			if (controlMoveYPlayer2 == 1) {
				controlMoveYPlayer2 = 0;
			}
			break;
		case SDLK_RCTRL: // dispara
			controlShootPlayer2 = false;
			break;
		}
	}
}

void GameLayer::update() {
	background->update();
	// Generar enemigos
	newEnemyTime--;
	if (newEnemyTime <= 0) {
		int rX = (rand() % (600 - 500)) + 1 + 500;
		int rY = (rand() % (300 - 60)) + 1 + 60;
		enemies.push_back(new Enemy(rX, rY, game));
		newEnemyTime = 110;
	}

	//Ampliación-6
	//Generar monedas
	newMonedaTime--;
	if (newMonedaTime <= 0) {
		int rX = (rand() % (600 - 500)) + 1 + 500;
		int rY = (rand() % (300 - 60)) + 1 + 60;
		monedas.push_back(new Monedas(rX, rY, game));
		newMonedaTime = 620;
	}

	//Ampliación-10
	//Generar bombas
	newBombaTime--;
	if (newBombaTime <= 0) {
		int rX = (rand() % (600 - 500)) + 1 + 500;
		int rY = (rand() % (300 - 60)) + 1 + 60;
		bombas.push_back(new Bombas(rX, rY, game));
		newBombaTime = 2000;
	}

	//Ampliación-4
	//Generar bombas
	newPowerUpTime--;
	if (newPowerUpTime <= 0) {
		int rX = (rand() % (600 - 500)) + 1 + 500;
		int rY = (rand() % (300 - 60)) + 1 + 60;
		powerUps.push_back(new PowerUp(rX, rY, game));
		newPowerUpTime = 4000;
	}

	player->update();
	//Ampliacion-11
	player2->update();

	for (auto const& enemy : enemies) {
		enemy->update();
	}
	for (auto const& projectile : projectiles) {
		projectile->update();
	}

	//Ampliacion-6
	for (auto const& moneda : monedas) {
		moneda->update();
	}

	//Ampliacion-10
	for (auto const& bomba : bombas) {
		bomba->update();
	}

	//Ampliacion-4
	for (auto const& power : powerUps) {
		power->update();
	}
	list<Enemy*> deleteEnemies;

	// Colisiones
	for (auto const& enemy : enemies) {
		if (player->isOverlap(enemy)) {
			//Ampliacion-3
			player->loseLife();
			bool eInList = std::find(deleteEnemies.begin(),
				deleteEnemies.end(),
				enemy) != deleteEnemies.end();

			if (!eInList) {
				deleteEnemies.push_back(enemy);
			}
			if (player->numeroVidas <= 0) {
				init();
				return;
			}
			else {
				cargarVidas();
			}
		}
		//Ampliacion-11
		if (player2->isOverlap(enemy)) {
			//Ampliacion-3
			player2->loseLife();
			bool eInList = std::find(deleteEnemies.begin(),
				deleteEnemies.end(),
				enemy) != deleteEnemies.end();

			if (!eInList) {
				deleteEnemies.push_back(enemy);
			}
			if (player2->numeroVidas <= 0) {
				init();
				return;
			}
			else {
				cargarVidas();
			}
		}
	}


	//Ampliacion-4
	list<PowerUp*> deletePowerUps;
	//Colisiones con powerUps
	for (auto const& power : powerUps) {
		if (player->isOverlap(power)) {
			player->disparos += 10;
		}
		//Ampliacion-11
		if (player2->isOverlap(power)) {
			player2->disparos += 10;
		}
	}

	for (auto const& power : powerUps) {
		if (power->isOverlap(player)) {
			bool mInList = std::find(deletePowerUps.begin(),
				deletePowerUps.end(),
				power) != deletePowerUps.end();

			if (!mInList) {
				deletePowerUps.push_back(power);
			}

			deletePowerUps.push_back(power);
		}
		//Ampliacion-11
		if (power->isOverlap(player2)) {
			bool mInList = std::find(deletePowerUps.begin(),
				deletePowerUps.end(),
				power) != deletePowerUps.end();

			if (!mInList) {
				deletePowerUps.push_back(power);
			}

			deletePowerUps.push_back(power);
		}
	}
	//Ampliacion-4
	for (auto const& power : deletePowerUps) {
		powerUps.remove(power);
	}
	deletePowerUps.clear();

	//Ampliacion-10
	list<Bombas*> deleteBombas;
	//Colisiones con bombas
	for (auto const& bomba : bombas) {
		if (player->isOverlap(bomba)) {
			enemies.clear();
		}
		//Ampliacion-11
		if (player2->isOverlap(bomba)) {
			enemies.clear();
		}
	}
	for (auto const& bomba : bombas) {
		if (bomba->isOverlap(player)) {
			bool mInList = std::find(deleteBombas.begin(),
				deleteBombas.end(),
				bomba) != deleteBombas.end();

			if (!mInList) {
				deleteBombas.push_back(bomba);
			}

			deleteBombas.push_back(bomba);
		}
		//Ampliacion-11
		if (bomba->isOverlap(player2)) {
			bool mInList = std::find(deleteBombas.begin(),
				deleteBombas.end(),
				bomba) != deleteBombas.end();

			if (!mInList) {
				deleteBombas.push_back(bomba);
			}

			deleteBombas.push_back(bomba);
		}
	}
	//Ampliacion-10
	for (auto const& bomba : deleteBombas) {
		bombas.remove(bomba);
	}
	deleteBombas.clear();




	list<Monedas*> deleteMonedas;

	//Ampliacion-6
	//Colisiones con monedas
	for (auto const& moneda : monedas) {
		if (player->isOverlap(moneda)) {
			if (player->numeroVidas < 3) {
				player->numeroVidas++;
				cargarVidas();
			}
			else {
				points++;
				textPoints->content = to_string(points);
			}
		}
		//Ampliacion-11
		if (player2->isOverlap(moneda)) {
			if (player2->numeroVidas < 3) {
				player2->numeroVidas++;
				cargarVidas();
			}
			else {
				points++;
				textPoints->content = to_string(points);
			}
		}
	}

	for (auto const& moneda : monedas) {
		if (moneda->isOverlap(player)) {
			bool mInList = std::find(deleteMonedas.begin(),
				deleteMonedas.end(),
				moneda) != deleteMonedas.end();

			if (!mInList) {
				deleteMonedas.push_back(moneda);
			}

			deleteMonedas.push_back(moneda);
		}
		//Ampliacion-11
		if (moneda->isOverlap(player2)) {
			bool mInList = std::find(deleteMonedas.begin(),
				deleteMonedas.end(),
				moneda) != deleteMonedas.end();

			if (!mInList) {
				deleteMonedas.push_back(moneda);
			}

			deleteMonedas.push_back(moneda);
		}
	}
	//Ampliacion-6
	for (auto const& delMoneda : deleteMonedas) {
		monedas.remove(delMoneda);
	}
	deleteMonedas.clear();


	// Colisiones , Enemy - Projectile
	list<Projectile*> deleteProjectiles;

	for (auto const& projectile : projectiles) {
		if (projectile->isInRender() == false) {

			bool pInList = std::find(deleteProjectiles.begin(),
				deleteProjectiles.end(),
				projectile) != deleteProjectiles.end();

			if (!pInList) {
				deleteProjectiles.push_back(projectile);
			}
		}
	}

	for (auto const& enemy : enemies) {
		for (auto const& projectile : projectiles) {
			if (enemy->isOverlap(projectile)) {
				//Ampliacion-4
				if(player->naveDisparada == true && player2->naveDisparada == true){
					player->disparos++;
					player2->disparos++;
				}
				else if(player->naveDisparada == true){
					player->disparos++;
				}
				else {
					player2->disparos++;
				}
				bool pInList = std::find(deleteProjectiles.begin(),
					deleteProjectiles.end(),
					projectile) != deleteProjectiles.end();

				if (!pInList) {
					deleteProjectiles.push_back(projectile);
				}

				bool eInList = std::find(deleteEnemies.begin(),
					deleteEnemies.end(),
					enemy) != deleteEnemies.end();

				if (!eInList) {
					deleteEnemies.push_back(enemy);
				}
				points++;
				textPoints->content = to_string(points);
			}
		}
	}




	for (auto const& delEnemy : deleteEnemies) {
		enemies.remove(delEnemy);
	}
	deleteEnemies.clear();

	for (auto const& delProjectile : deleteProjectiles) {
		projectiles.remove(delProjectile);
	}
	deleteProjectiles.clear();


	cout << "update GameLayer" << endl;
}

void GameLayer::draw() {
	background->draw();
	for (auto const& vida : vidas) {
		vida->draw();
	}
	player->draw();
	//Ampliacion-11
	player2->draw();
	for (auto const& enemy : enemies) {
		enemy->draw();
	}
	backgroundPoints->draw();
	//Ampliacion-6
	for (auto const& moneda : monedas) {
		moneda->draw();
	}
	//Ampliacion-4
	if (player->disparos != 0) {
		for (auto const& projectile : projectiles) {
			projectile->draw();
		}
	}
	for (auto const& power : powerUps) {
		power->draw();
	}
	
	//Ampliacion-10
	for (auto const& bomba : bombas) {
		bomba->draw();
	}
	textPoints->draw();
	backgroundPoints->draw();

	SDL_RenderPresent(game->renderer); // Renderiza
}

//Ampliacion-11
void GameLayer::cargarVidas() {
	vidas.clear();
	int distancia = 0;
	for (int i = 0; i < player->numeroVidas; i++)
	{
		vidas.push_back(new Vidas(25 + distancia, background->fileHeight - 20, game));
		distancia += 50;
	}
	distancia = 0;
	for (int i = 0; i < player2->numeroVidas; i++)
	{
		vidas.push_back(new Vidas(background->fileWidth - 25 - distancia, background->fileHeight - 20, game));
		distancia += 50;
	}
}

void GameLayer::playerColisionEnemy(Player* player, Enemy* enemy) {
	if (player->isOverlap(enemy)) {
		//Ampliacion-3
		player->loseLife();
		if (player->numeroVidas <= 0) {
			init();
			return;
		}
		else {
			cargarVidas();
		}
	}
}

void GameLayer::playerColisionMoneda(Player* player, Monedas* moneda, list<Monedas*> deleteMonedas) {
	if (player->isOverlap(moneda)) {
		bool mInList = std::find(deleteMonedas.begin(),
			deleteMonedas.end(),
			moneda) != deleteMonedas.end();

		if (!mInList) {
			deleteMonedas.push_back(moneda);
		}

		deleteMonedas.push_back(moneda);
	}
}

void GameLayer::monedaDeleted(Player* player, Monedas* moneda, list<Monedas*> deleteMonedas) {
	if (player->isOverlap(moneda)) {
		bool mInList = std::find(deleteMonedas.begin(),
			deleteMonedas.end(),
			moneda) != deleteMonedas.end();

		if (!mInList) {
			deleteMonedas.push_back(moneda);
		}

		deleteMonedas.push_back(moneda);
	}
}

