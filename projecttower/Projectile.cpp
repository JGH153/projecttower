#include "Projectile.h"


Projectile::Projectile(Vortex *gameEngine, int posX, int posY, VortexSprite *projectileSprite, Unit *target, float speed, float damage) : Entity(gameEngine, posX, posY) {
	this->gameEngine = gameEngine;
	this->speed = speed;
	this->target = target;
	this->projectileSprite = projectileSprite;
	this->damage = damage;
	destroyProjectile = false;

	updatePos();
}


Projectile::~Projectile() {
}

std::vector<sf::Drawable*> Projectile::getRenderDrawable() {
	return projectileSprite->getRenderDrawable();
}


bool Projectile::checkIfHitTarget() {
	float radius = 50;

	float diffX = abs(target->posX - posX);
	float diffY = abs(target->posY- posY);

	if (diffX * diffX + diffY * diffY < radius * radius) {
		target->damage(damage);
		return true;
	}
	return false;
}

void Projectile::updatePos() {

	sf::Vector2f velocity(target->posX - posX, target->posY - posY);
	float cardVelocity = sqrtf((velocity.x * velocity.x) + (velocity.y * velocity.y));
	velocity.x /= cardVelocity;
	velocity.y /= cardVelocity;


	posX = posX + velocity.x * speed * gameEngine->deltaTime.asMilliseconds();
	posY = posY + velocity.y * speed * gameEngine->deltaTime.asMilliseconds();

	projectileSprite->setPosition(posX, posY);
	float angle = atan2(target->posY - posY, target->posX - posX);
	projectileSprite->setRotation(angle * 180 / 3.14159);

}

void Projectile::update() {
	if (destroyProjectile == true) {
		target = nullptr;
		return;
	}
	if (target == nullptr) {
		destroyProjectile = true;
		return;
	}
	if (target->isDead()) {
		target = nullptr;
		destroyProjectile = true;
		return;
	}

	updatePos();

	destroyProjectile = checkIfHitTarget();
}
