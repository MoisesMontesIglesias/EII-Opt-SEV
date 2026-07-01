#include "Projectile.h"
Projectile::Projectile(float x, float y, Game* game) :
	Actor("", x, y, 20, 20, game) {
	vx = 9;
	vy = -1; // La gravedad inicial es 1
	lifetime = 4;
	elapsedTime = 0;
	active = true;
}

void Projectile::update() {
	vy = vy - 1; // La gravedad suma 1 en cada actualización restamos para anularla 
	elapsedTime++; // deltaTime es el tiempo entre frames en ms

	// Verificar si el tiempo de vida ha expirado
	if (elapsedTime >= lifetime) {
		// Aquí puedes marcar el proyectil para ser eliminado
		active = false; // Por ejemplo, una bandera que indica si el proyectil está activo
	}
}
