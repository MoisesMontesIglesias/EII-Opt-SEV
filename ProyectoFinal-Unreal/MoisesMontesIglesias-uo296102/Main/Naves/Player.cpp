#include "Player.h"

Player::Player(float x, float y, Game* game)
	: Actor("", x, y, 35, 35, game) {
	onAir = false;
	orientation = game->orientationRight;
	state = game->stateMoving;

	aShootingRight = new Animation("res/PlayerAtaqueDerecha.png",
		width, height, 160, 40, 6, 1, false, game);
	aShootingLeft = new Animation("res/PlayerAtaqueIzquierda.png",
		width, height, 160, 40, 6, 1, false, game);
	aShootingDown = new Animation("res/PlayerAtaqueAbajo.png",
		width, height, 160, 40, 6, 1, false, game);
	aShootingUp = new Animation("res/PlayerEstaticoArriba.png",
		width, height, 160, 40, 6, 1, false, game);

	aIdleRight = new Animation("res/PlayerEstaticoDerecha.png", width, height,
		128, 40, 6, 1, true, game);
	aIdleLeft = new Animation("res/PlayerEstaticoIzquierda.png", width, height,
		128, 40, 6, 1, true, game);
	aIdleUp = new Animation("res/PlayerEstaticoAbajo.png", width, height,
		128, 40, 6, 1, true, game);
	aIdleDown = new Animation("res/PlayerEstaticoArriba.png", width, height,
		128, 40, 6, 1, true, game);

	aRunningRight = new Animation("res/PlayerMovimientoDerecha.png", width, height,
		128, 40, 6, 4, true, game);
	aRunningLeft = new Animation("res/PlayerMovimientoIzquierda.png", width, height,
		128, 40, 6, 4, true, game);
	aRunningUp = new Animation("res/PlayerMovimientoAbajo.png", width, height,
		128, 40, 6, 4, true, game);
	aRunningDown = new Animation("res/PlayerMovimientoArriba.png", width, height,
		128, 40, 6, 4, true, game);

	aSentado = new Animation("res/PlayerSentado.png", width, height,
		128, 40, 6, 1, true, game);

	animation = aSentado;
	sentado = true;
	recienLevantado = false;
	tiempoSentado = -1;
	loseLifeCooldown = 0;
	audioShoot = Audio::createAudio("res/SonidoCuchillada.wav", false);
}

void Player::jump() {
	if (!onAir) {
		vy = -16;
		onAir = true;
	}

}

void Player::update() {
	if (loseLifeCooldown > 0) {
		loseLifeCooldown--;
	}
	if (!sentado) {
		tiempoSentado = -1;
	}
	else {
		tiempoSentado++;
	}

	if (invulnerableTime > 0) {
		invulnerableTime--;
	}

	bool endAnimation = animation->update();

	if (endAnimation) {
		if (state == game->stateShooting) {
			state = game->stateMoving;
		}
	}
	if (state == game->stateSentado) {
		animation = aSentado;
	}
	if (vx > 0) {
		orientation = game->orientationRight;
	}
	if (vx < 0) {
		orientation = game->orientationLeft;
	}
	if (vy > 0) {
		orientation = game->orientationUp;
	}
	if (vy < 0) {
		orientation = game->orientationDown;
	}
	if (state == game->stateShooting) {
		if (orientation == game->orientationRight) {
			animation = aShootingRight;
		}
		if (orientation == game->orientationLeft) {
			animation = aShootingLeft;
		}
		if (orientation == game->orientationUp) {
			animation = aShootingUp;
		}
		if (orientation == game->orientationDown) {
			animation = aShootingDown;
		}
	}
	if (state == game->stateMoving) {
		if (vx != 0) {
			if (orientation == game->orientationRight) {
				animation = aRunningRight;
			}
			if (orientation == game->orientationLeft) {
				animation = aRunningLeft;
			}
		}
		if (vx == 0) {
			if (orientation == game->orientationRight) {
				animation = aIdleRight;
			}
			if (orientation == game->orientationLeft) {
				animation = aIdleLeft;
			}
		}
		if (vy != 0) {
			if (orientation == game->orientationUp) {
				animation = aRunningUp;
			}
			if (orientation == game->orientationDown) {
				animation = aRunningDown;
			}
		}
		if (vy == 0) {
			if (orientation == game->orientationUp) {
				animation = aIdleUp;
			}
			if (orientation == game->orientationDown) {
				animation = aIdleDown;
			}
		}
	}


	if (shootTime > 0) {
		shootTime--;
	}
}

void Player::moveX(float axis) {
	vx = axis * 3;
}

void Player::moveY(float axis) {
	vy = axis * 3;
}

Projectile* Player::shoot() {
	bool cuchillo = false;
	if (items.size() == 1) {
		for (auto const& item : items) {
			if (item->getItem() == Item::ItemType::Cuchillo) {
				cuchillo = true;
			}
		}
	}
	if (shootTime == 0 && cuchillo) {
		audioShoot->play();
		state = game->stateShooting;
		shootTime = shootCadence;
		aShootingUp->currentFrame = 0;
		aShootingDown->currentFrame = 0;
		aShootingLeft->currentFrame = 0;
		aShootingRight->currentFrame = 0;
		Projectile* projectile = new Projectile(x, y, game);
		if (orientation == game->orientationLeft) {
			projectile->vx = projectile->vx * -1;
		}
		if (orientation == game->orientationLeft) {
			projectile->vx = projectile->vx * 1;
		}
		if (orientation == game->orientationDown) {
			projectile->vy = projectile->vy * 1;
		}
		if (orientation == game->orientationUp) {
			projectile->vy = projectile->vy * -1;
		}
		return projectile;
	}
	else {
		return NULL;
	}
}

void Player::draw(float scrollX, float scrollY) {
	if (invulnerableTime == 0) {
		animation->draw(x - scrollX, y - scrollY);
	}
	else {
		if (invulnerableTime % 10 >= 0 && invulnerableTime % 10 <= 5) {
			animation->draw(x - scrollX, y - scrollY);
		}
	}

}

void Player::loseLife() {
	if (numeroVidas > 0) {
		loseLifeCooldown = 200;
		numeroVidas--;
	}
}

list<Item*> Player::getItemsInInventory() {
	return items;
}

void Player::reiniciarLista() {
	items.clear();
}

void Player::addItemToInventory(Item* item) {
	items.push_back(item);
}

void Player::crearItem(float x, float y, Game* game) {
	cuchillo = new Item(Item::ItemType::Cuchillo, "res/ItemCuchillo.png", x, y, game);
	items.push_back(cuchillo);
}
