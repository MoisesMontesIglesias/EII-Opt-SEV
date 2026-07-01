#include "GameLayer.h"

GameLayer::GameLayer(Game* game) : Layer(game) {
	pause = true;
	message = new Actor("res/ComoJugar.png", WIDTH * 0.5, HEIGHT * 0.5,
		WIDTH, HEIGHT, game);
	button = new Actor("", WIDTH * 0.52, HEIGHT * 0.7, 232, 72, game);
	//Hago init() 3 veces, porque al generar numeros random para que los items se guarden en mesas aleatorias,
	//con solo un init(), la primera vez que inicializas la app, no se generar de manera random
	init();
	init();
	init();
}

void GameLayer::init() {
	audioBackground = Audio::createAudio("res/MusicaInicial.mp3", true);
	audioBackground->play();
	cup = nullptr;

	space = new Space();
	scrollX = 0;
	scrollY = 0;

	tiles.clear();

	textItems = new Text("Mis items: ", WIDTH - 50, HEIGHT - 45, game);
	textAccion = new Text(" ", WIDTH - 240, HEIGHT - 45, game);
	textProfesor = new Text(" ", WIDTH - 240, 20, game);
	textSaqueo = new Text(" ", WIDTH - 240, HEIGHT - 75, game);
	textExtra = new Text(" ", WIDTH - 200, HEIGHT - 15, game);

	projectiles.clear();
	enemies.clear();
	mesasClase.clear();
	loadMap("res/" + to_string(game->currentLevel) + ".txt");
	generarItemsMesas();
}


void GameLayer::calculateScroll() {
	//limite alto
	if (player->y > HEIGHT * 0.3) {
		if (player->y - scrollY < HEIGHT * 0.3) {
			scrollY = player->y - HEIGHT * 0.3;
		}
	}
	// limite bajo
	if (player->y < mapWidth - HEIGHT * 0.3) {
		if (player->y - scrollY > HEIGHT * 0.7) {
			scrollY = player->y - HEIGHT * 0.7;
		}
	}
	// limite izquierda
	if (player->x > WIDTH * 0.3) {
		if (player->x - scrollX < WIDTH * 0.3) {
			scrollX = player->x - WIDTH * 0.3;
		}

	}
	// limite derecha
	if (player->x < mapWidth - WIDTH * 0.3) {
		if (player->x - scrollX > WIDTH * 0.7) {
			scrollX = player->x - WIDTH * 0.7;
		}
	}
}


void GameLayer::loadMap(string name) {
	char character;
	string line;
	ifstream streamFile(name.c_str());
	if (!streamFile.is_open()) {
		return;
	}
	else {
		// Por línea
		for (int i = 0; getline(streamFile, line); i++) {
			istringstream streamLine(line);
			mapWidth = line.length() * 40; // Ancho del mapa en pixels
			// Por carácter (en cada línea)
			for (int j = 0; !streamLine.eof(); j++) {
				streamLine >> character; // Leer character 
				float x = 40 / 2 + j * 40; // x central
				float y = 32 + i * 32; // y suelo
				loadMapObject(character, x, y);
			}

		}
	}
	streamFile.close();
}

void GameLayer::loadMapObject(char character, float x, float y)
{
	switch (character) {
	case '.': {
		Tile* tile = new Tile("res/SueloMadera.png", x, y, game);
		tile->y = tile->y - tile->height / 2;
		tiles.push_back(tile);
		break;
	}

	case 'E': {
		loadMapObject('.', x, y);

		Enemy* enemy = new Enemy(x, y, game);
		enemy->y = enemy->y - enemy->height / 2;
		space->addDynamicActor(enemy);
		space->addStaticActor(enemy);
		enemies.push_back(enemy);
		break;
	}
	case 'C': {
		loadMapObject('.', x, y);
		CharcoAgua* cAgua = new CharcoAgua("res/CharcoAgua.png", x, y, game);
		cAgua->y = cAgua->y - cAgua->height / 2;
		tiles.push_back(cAgua);
		break;
	}
	case '1': {
		loadMapObject('.', x, y);

		player = new Player(x, y, game);
		player->y = player->y - player->height / 2;
		space->addDynamicActor(player);
		cargarVidas();
		break;
	}
	case '-': {
		Tile* tile = new Tile("res/Bloque_negro.png", x, y, game);
		tile->y = tile->y - tile->height / 2;
		tiles.push_back(tile);
		space->addStaticActor(tile);
		break;
	}case 'M': {
		loadMapObject('.', x, y);
		Mesa* mesa = new Mesa("res/Mesas_Clase.png", x, y, game, false);
		mesa->y = mesa->y - mesa->height / 2;
		tiles.push_back(mesa);
		space->addStaticActor(mesa);
		mesasClase.push_back(mesa);
		break;
	}
	case 'K': {
		loadMapObject('.', x, y);
		Tile* cono = new Tile("res/Cono.png", x, y, game);
		cono->y = cono->y - cono->height / 2;
		tiles.push_back(cono);
		space->addStaticActor(cono);
		break;
	}
	case 'H': {
		loadMapObject('.', x, y);
		Tile* mochila = new Tile("res/Mochila.png", x, y, game);
		mochila->y = mochila->y - mochila->height / 2;
		tiles.push_back(mochila);
		space->addStaticActor(mochila);
		break;
	}case 'L': {
		loadMapObject('.', x, y);
		Tile* libros = new Tile("res/Libros.png", x, y, game);
		libros->y = libros->y - libros->height / 2;
		tiles.push_back(libros);
		space->addStaticActor(libros);
		break;
	}
	case 'W': {
		loadMapObject('.', x, y);
		Mesa* mesa = new Mesa("res/Mesas_Clase.png", x, y, game, true);
		mesa->y = mesa->y - mesa->height / 2;
		tiles.push_back(mesa);
		space->addStaticActor(mesa);
		mesasClase.push_back(mesa);
		break;
	}
	case 'I': {
		loadMapObject('.', x, y);
		Mesa* mesa = new Mesa("res/MesaProfesorIzquierda.png", x, y-3, game, false);
		mesa->y = mesa->y - mesa->height / 2;
		tiles.push_back(mesa);
		space->addStaticActor(mesa);
		break;
	}
	case 'D': {
		loadMapObject('.', x, y);
		Mesa* mesa = new Mesa("res/MesaProfesorDerecha.png", x, y-3, game, false);
		mesa->y = mesa->y - mesa->height / 2;
		tiles.push_back(mesa);
		space->addStaticActor(mesa);
		break;
	}
	case 'S': {
		loadMapObject('.', x, y);
		Silla* tile = new Silla("res/Silla_Vacia.png", x, y, game, false, true);
		tile->y = tile->y - tile->height / 2;
		tiles.push_back(tile);
		space->addStaticActor(tile);
		break;
	}
	case '5': {
		loadMapObject('.', x, y);
		Silla* tile = new Silla("res/Silla_Vacia.png", x, y, game, true, true);
		tile->y = tile->y - tile->height / 2;
		tiles.push_back(tile);
		space->addStaticActor(tile);
		break;
	}
	case 'N': {
		loadMapObject('.', x, y);
		Silla* silla = new Silla("res/Nino_Sentado.png", x, y, game, false, false);
		silla->y = silla->y - silla->height / 2;
		tiles.push_back(silla);
		space->addStaticActor(silla);
	}
	}
}


void GameLayer::processControls() {
	// obtener controles
	SDL_Event event;
	while (SDL_PollEvent(&event)) {
		if (event.type == SDL_KEYDOWN) {
			game->input = game->inputKeyboard;
		}
		if (event.type == SDL_MOUSEBUTTONDOWN) {
			game->input = game->inputMouse;
		}

		// Procesar teclas
		if (game->input == game->inputKeyboard) {
			keysToControls(event);
		}
		if (game->input == game->inputMouse) {
			mouseToControls(event);
		}

	}

	if (player->sentado) {
		controlMoveX = 0;
		controlMoveY = 0;
	}

	//procesar controles
	if (controlContinue) {
		pause = false;
		controlContinue = false;
	}

	// Disparar
	if (controlShoot) {
		Projectile* newProjectile = player->shoot();
		if (newProjectile != NULL) {
			space->addDynamicActor(newProjectile);
			projectiles.push_back(newProjectile);
		}

	}	

	bool sobreAgua = false;
	for (auto const& tile : tiles) {
		CharcoAgua* cAgua = dynamic_cast<CharcoAgua*>(tile);
		if (cAgua) {
			if (player->isOverlap(cAgua)) {
				sobreAgua = true;
			}
		}
	}

	if (sobreAgua && !player->recienLevantado) {
		if (controlMoveX > 0) {
			player->moveX(0.5);
		}
		else if (controlMoveX < 0) {
			player->moveX(-0.5);
		}
		else {
			player->moveX(0);
		}
		if (controlMoveY > 0) {
			player->moveY(0.5);
		}
		else if (controlMoveY < 0) {
			player->moveY(-0.5);
		}
		else {
			player->moveY(0);
		}
	}
	else {
		if (controlMoveX > 0) {
			player->moveX(1);
		}
		else if (controlMoveX < 0) {
			player->moveX(-1);
		}
		else {
			player->moveX(0);
		}
		if (controlMoveY > 0) {
			player->moveY(1);
		}
		else if (controlMoveY < 0) {
			player->moveY(-1);
		}
		else {
			player->moveY(0);
		}
	}
	player->recienLevantado = false;
}

void GameLayer::keysToControls(SDL_Event event) {
	if (event.type == SDL_KEYDOWN) {
		int code = event.key.keysym.sym;
		if (player->sentado) {
			if(player->tiempoSentado > 20)
				switch (code) {
				case SDLK_d: 
					player->x += player->width;
					player->sentado = false;
					player->animation = player->aIdleRight;
					controlMoveX = 1;
					player->recienLevantado = true;
					break;
				case SDLK_a:
					player->x -= player->width;
					player->sentado = false;
					player->animation = player->aIdleLeft;
					controlMoveX = -1;
					player->recienLevantado = true;
					break;
				case SDLK_s:
					player->y += player->height;
					player->sentado = false;
					player->animation = player->aIdleDown;
					controlMoveY = 1;
					player->recienLevantado = true;
					break;
				}
		}
		else {
			// Movimiento normal cuando no está sentado
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
			case SDLK_e: // interactua
				checkInteraction = true;
				break;
			}
		}
	}

	if (event.type == SDL_KEYUP) {
		int code = event.key.keysym.sym;
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
		}
		
	}

	if (event.type == SDL_QUIT) {
		game->loopActive = false;
	}
}
void GameLayer::update() {

	for (auto const& enemy : enemies) {
		if (enemy->state == game->stateDead) {
			mensaje = 4;
			textExtra->content = "¿Y PORQUE NO MATAR A TODOS?";
			for (auto const& tile : tiles) {
				Silla* silla = dynamic_cast<Silla*>(tile);
				if (silla && !silla->poderSentarse && controlShoot && player->isOverlap(silla)) {
					string nombreFichero = "res/Nino_Sentado_Muerto.png";
					silla->texture = SDL_CreateTextureFromSurface(game->renderer, IMG_Load(nombreFichero.c_str()));
				}
			}

		}
		else {
			if (aplicarDelay()) {
				for (auto* actor : space->staticActors) { 
					Mesa* mesa = dynamic_cast<Mesa*>(actor);
					if (mesa) { 
						if (player->isOverlap(mesa)) {
							manejarInteraccionMesa(mesa);
						}
					}
				}
				if (cup == nullptr) {
					checkInteraction = false;
				}
			}
		}
	}

	space->update();

	player->update();

	for (auto const& enemy : enemies) {
		enemy->update();
	}

	for (auto const& projectile : projectiles) {
		projectile->update();
	}

	float contador = 0;
	for (auto const& tile : tiles) {
		Silla* silla = dynamic_cast<Silla*>(tile);
		if (silla && player->isOverlap(silla) && silla->poderSentarse == true) {
			contador = 1;
			player->sentado = true;
			player->x = silla->x;
			player->y = silla->y;
			player->state = game->stateSentado;
			break;
		}
	}
	if (contador == 0) {
		player->state = game->stateMoving;
	}

	bool mensajeProfe = manejarInteraccionProfesor(false);

	int mensaje = 0;
	for (auto const& tile : tiles) {
		Mesa* mesa = dynamic_cast<Mesa*>(tile);
		if (mesa && player->isOverlap(mesa) && !player->sentado && !esperandoAccion) {
			if (mesa->inicial && player->getItemsInInventory().size() == 3) {
				mensaje = 2;
			}
			else {
				mensaje = 1;
			}
		}
	}

	list<Item*> listaProvisional = player->getItemsInInventory();
	for (auto it = listaProvisional.begin(); it != listaProvisional.end(); ++it)
	{
		Item* item = *it;
		if (item->getItem() == Item::ItemType::Cuchillo) {
			mensaje = 3;
		}
	}

	if (!mensajeProfe) {
		textProfesor->content = " ";
	}

	list<Projectile*> deleteProjectiles;

	for (auto const& projectile : projectiles) {
		if (projectile->isInRender(scrollX, scrollY) == false ||
			projectile->vx == 0 || !projectile->active) {

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
				bool pInList = std::find(deleteProjectiles.begin(),
					deleteProjectiles.end(),
					projectile) != deleteProjectiles.end();

				if (!pInList) {
					deleteProjectiles.push_back(projectile);
				}
				enemy->impacted();
				space->removeDynamicActor(enemy);
			}
		}
	}

	if (cup == nullptr) {
		for (auto const& enemy : enemies) {
			if (enemy->state == game->stateDead) {
				cup = new Tile("res/copa.png", enemy->x, enemy->y, game);
				space->addStaticActor(cup);
				audioBackground = Audio::createAudio("res/MusicaFinal.mp3", true);
				audioBackground->play();
			}
		}
	} else{
		if (player->isOverlap(cup)) {
			if (checkInteraction) {
				message = new Actor("res/FondoVictoria.png", WIDTH * 0.5, HEIGHT * 0.5,
					WIDTH, HEIGHT, game);
				button = new Actor("res/boton_jugar.png", WIDTH * 0.52, HEIGHT * 0.7, 232, 72, game);
				pause = true;
				init();
			}
			else {
				mensaje = 5;
			}
		}
		else {
			mensaje = 4;
		}
	}

	if (!esperandoAccion) {
		if (mensaje == 5) {
			textAccion->content = "Pre510nA 'E' pARa r0Bar 1aS 11avE5 E 1rTe";
		}
		else if (mensaje == 4) {
			textAccion->content = "M444T44444RRRRR!!!";;
		}
		else if (mensaje == 3) {
			textAccion->content = "PrESi0na 'sPaCE' p4R4 ... M4t4r!?!?!?";
		}
		else if (mensaje == 2) {
			textAccion->content = "Presiona 'E' para juntar tus cosas";
		}
		else if (mensaje == 1) {
			textAccion->content = "Presiona 'E' para interactuar";
		}
		else {
			textAccion->content = " ";
		}
	}

	if (textSaqueo->lifetime == 0) {
		textSaqueo->content = " ";
	}

	for (auto const& delProjectile : deleteProjectiles) {
		projectiles.remove(delProjectile);
		space->removeDynamicActor(delProjectile);
		delete delProjectile;
	}
	deleteProjectiles.clear();
}

void GameLayer::draw() {
	if (!player->sentado) {
		calculateScroll();
	}
	for (auto const& tile : tiles) {
		tile->draw(scrollX, scrollY);
	}

	for (auto const& vida : vidas) {
		vida->draw();
	}

	for (auto const& item : player->getItemsInInventory()) {
		item->draw();
	}

	for (auto const& projectile : projectiles) {
		projectile->draw(scrollX, scrollY);
	}

	player->draw(scrollX, scrollY);

	for (auto const& enemy : enemies) {
		enemy->draw(scrollX, scrollY);
	}

	textItems->draw();
	if (textAccion->content != " ") {
		textAccion->draw();
	}
	if (textProfesor->content != " ") {
		textProfesor->draw();
	}
	if (textSaqueo->lifetime > 0) {
		textSaqueo->lifetime--;
		textSaqueo->draw();
	}

	if (textExtra->content != " ") {
		textExtra->draw();
	}
	if (pause) {
		message->draw();
		button->draw();
	}
	SDL_RenderPresent(game->renderer); 

}

void GameLayer::mouseToControls(SDL_Event event) {
	if (event.type == SDL_MOUSEBUTTONDOWN) {
		controlContinue = true;
	}
}

bool GameLayer::aplicarDelay() {
	bool jugadorEnMesa = false;

	for (auto* actor : space->staticActors) { 
		Mesa* mesa = dynamic_cast<Mesa*>(actor);
		if (mesa) { 
			if (player->isOverlap(mesa) && checkInteraction) { 
				jugadorEnMesa = true;
				delay++;
				esperandoAccion = true;

				if (delay == 30) {
					delay = 0;
					esperandoAccion = false;
					return true;
				}
				else {
					textAccion->content = "Buscando...";
					return false;
				}
			}
		}
	}
	if (!jugadorEnMesa) {
		delay = 0;
		esperandoAccion = false;
		checkInteraction = false;
		textAccion->content = " ";
	}

	return false;
}

void GameLayer::manejarInteraccionMesa(Mesa* mesa) {
	textSaqueo->lifetime = 80.0f;
	if (mesa->getItemNombre() != "Vacio") {
		list<Item*> listaItems = player->getItemsInInventory();
		if (listaItems.empty()) {
			if (mesa->getItemNombre() == "Cuerda") {
				textSaqueo->content = "Al fin, la cuerda, con esto podré forzar otras mesas";
				audioBackground = Audio::createAudio("res/MusicaPrimerItem.mp3", true);
				audioBackground->play();
				player->addItemToInventory(mesa->getItem());
				mesa->removeItem();
			}
			else if (mesa->getItemNombre() == "Mango") {
				textSaqueo->content = "Mmmm, voy a necesitar una cuerda para forzar esta mesa";
			}
			else if (mesa->getItemNombre() == "Filo") {
				textSaqueo->content = "Aquí hay algo punzante, necesito algo para cogerlo";
			}
		}
		else {
			if (mesa->getItemNombre() == "Mango") {
				if (player->getItemsInInventory().size() == 1) {
					textSaqueo->content = "He encontrado el mango, ahora necesito algo cortante";
					audioBackground = Audio::createAudio("res/MusicaSegundoItem.mp3", true);
					audioBackground->play();
					player->addItemToInventory(mesa->getItem()); 
					mesa->removeItem();
				}
			}
			else if (mesa->getItemNombre() == "Filo") {
				textSaqueo->content = "Aquí hay algo punzante, necesito algo para cogerlo";
				if (player->getItemsInInventory().size() == 2) {
					textSaqueo->content = "El filo SI,debo volver a mi asiento";
					audioBackground = Audio::createAudio("res/MusicaTercerItem.mp3", true);
					audioBackground->play();
					player->addItemToInventory(mesa->getItem());
					mesa->removeItem();
				}
			}
		}
	}
	else {
		if (mesa->inicial) {
			if (player->getItemsInInventory().size() == 3) {
				player->reiniciarLista();
				player->crearItem(WIDTH - 25, HEIGHT - 20, game);
				audioBackground = Audio::createAudio("res/MusicaCuchillo.mp3", true);
				audioBackground->play();
				textSaqueo->content = "Con esto, podre cumplir mi objetivo... EL PROFESOR";
			}
			else {
				textSaqueo->content = "Debo encontrar algo con lo que acabar con el";
			}
		}
		else {
			textSaqueo->content = "Mierda, aquí no hay nada";
		}
	}
}

bool GameLayer::manejarInteraccionProfesor(bool mensajeProfe) {
	for (auto const& enemy : enemies) {
		if (enemy->orientation == game->orientationUp) {
			mensajeProfe = true;
			if (!player->sentado) {
				textProfesor->content = "Te pille granuja, no debiste pasarte de listo";
				textProfesor->draw();
				message = new Actor("res/FondoDerrota.png", WIDTH * 0.5, HEIGHT * 0.5,
					WIDTH, HEIGHT, game);
				button = new Actor("res/boton_jugar.png", WIDTH * 0.52, HEIGHT * 0.7, 232, 72, game); 
				pause = true;
				init();
				return mensajeProfe;
			}
			else if (player->sentado) {
				for (auto const& tile : tiles) {
					Silla* silla = dynamic_cast<Silla*>(tile);
					if (silla != nullptr) {
						if (player->x == silla->x && player->y == silla->y) {
							if (!silla->sillaInicial) {
								if (player->loseLifeCooldown <= 0) {
									if (player->numeroVidas <= 0) {
										message = new Actor("res/FondoDerrota.png", WIDTH * 0.5, HEIGHT * 0.5,
											WIDTH, HEIGHT, game);
										button = new Actor("res/boton_jugar.png", WIDTH * 0.52, HEIGHT * 0.7, 232, 72, game);
										pause = true;
										init();
										return mensajeProfe;
									}
									else {
										textProfesor->content = "Mmmm, hay algo que no me cuadra en esta clase...";
										player->loseLife();
										vidas.pop_back();
									}
								}
							}
							else {
								textProfesor->content = "Demasiado tranquilo está todo esto, algo me huele mal";
							}
						}
					}
				}
			}
		}
	}
	return mensajeProfe;
}

void GameLayer::generarItemsMesas() {
	int contador = 0;
	unsigned int randomCuerda = std::rand() % mesasClase.size();
	unsigned int randomMango = std::rand() % mesasClase.size();
	while (randomMango == randomCuerda) {
		randomMango = std::rand() % mesasClase.size();
	}
	unsigned int randomFilo = std::rand() % mesasClase.size();
	while (randomFilo == randomMango || randomFilo == randomCuerda) {
		randomFilo = std::rand() % mesasClase.size();
	}
	for (auto it = mesasClase.begin(); it != mesasClase.end(); ++it)
	{
		Mesa* mesa = *it;
		if (contador == randomCuerda) {
			mesa->meterCuerda(WIDTH - 25, HEIGHT - 20, game);
		}
		else if (contador == randomFilo) {
			mesa->meterFilo(WIDTH - 125, HEIGHT - 20, game);
		}
		else if (contador == randomMango) {
			mesa->meterMango(WIDTH - 75, HEIGHT - 20, game);
		}
		contador++;
	}
}

void GameLayer::cargarVidas() {
	vidas.clear();
	int distancia = 0;
	for (int i = 0; i < player->numeroVidas; i++)
	{
		vidas.push_back(new Vidas(25 + distancia, HEIGHT - 20, game));
		distancia += 50;
	}
}

