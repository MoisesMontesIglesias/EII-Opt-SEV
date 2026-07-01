#include "Enemy.h"

Enemy::Enemy(float x, float y, Game* game)
	: Actor("ProfesorEstaticoAbajo", x, y, 32, 40, game) {
	vx = 1;
	vxIntelligence = -1;
	vx = vxIntelligence;

	state = game->stateMoving;

	aIdleUp = new Animation("res/ProfesorEstaticoAbajo.png", width, height,
        32, 40, 6, 1, true, game);
	aIdleDown = new Animation("res/ProfesorEstaticoArriba.png", width, height,
        32, 40, 6, 1, true, game);
	aRunningRight = new Animation("res/ProfesorMovimientoIzquierda.png", width, height,
        128, 40, 6, 4, true, game);
	aRunningLeft = new Animation("res/ProfesorMovimientoDerecha.png", width, height,
		128, 40, 6, 4, true, game);

	aDying = new Animation("res/ProfesorAnimacionMuerte.png", width, height,
        96, 40, 6, 3, false, game);

	aDead = new Animation("res/ProfesorEstaticoMuerte.png", width, height,
        32, 40, 6, 1, true, game);
	animation = aIdleDown;
    orientation = game->orientationDown;

    timer = 0;

}

void Enemy::update() {
    timer ++;
    bool endAnimation = animation->update();
    if (endAnimation) {
        if (state == game->stateDying) {
            state = game->stateDead;
            animation = aDead;
        }
    }

    if (state == game->stateDying) {
        animation = aDying;
    }
    else if (state == game->stateMoving) {
        if (orientation == game->orientationDown) {
            if (timer >= timeLookingDown) {
                vxIntelligence *= -1;
                vx = vxIntelligence;
                timer = 0;
                orientation = game->orientationLeft;
                animation = aRunningLeft;
            }
        }
        else if (orientation == game->orientationLeft) {
            if (timer >= timeMoving) {
                vx = 0;
                timer = 0;
                orientation = game->orientationUp;
                animation = aIdleUp;
            }
        }
        else if (orientation == game->orientationUp) {
            if (timer >= timeLookingUp) {
                vxIntelligence *= -1;
                vx = vxIntelligence;
                timer = 0;
                orientation = game->orientationRight;
                animation = aRunningRight;
            }
        }
        else if (orientation == game->orientationRight) {
            if (timer >= timeMoving) {
                vx = 0;
                timer = 0;
                orientation = game->orientationDown;
                animation = aIdleDown;
            }
        }

        if (orientation == game->orientationRight) {
            x += vx;  // Mover hacia la izquierda
        }
        else if (orientation == game->orientationLeft) {
            x += vx;  // Mover hacia la derecha
        }
    }
}

void Enemy::draw(float scrollX, float scrollY) {
	animation->draw(x - scrollX, y - scrollY);
}

void Enemy::impacted() {
	if (state != game->stateDying) {
		state = game->stateDying;
	}
}

