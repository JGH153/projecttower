#include "Projectile.h"


Projectile::Projectile(Vortex *gameEngine, int posX, int posY, VortexSprite *projectileSprite, Unit *target, float speed, float damage) : Entity(gameEngine, posX, posY) {
	this->gameEngine = gameEngine;
	this->speed = speed;
	this->target = target;
	this->projectileSprite = projectileSprite;
	this->damage = damage;
}


Projectile::~Projectile() {
}

std::vector<sf::Drawable*> Projectile::getRenderDrawable() {
	//i dont understand how to use this shit function system, so im just getting the projectile sprite itself atm in BasicTower::getRenderDrawable()
	return projectileSprite->getRenderDrawable();
}


bool Projectile::hasHitTarget() {
	if (target == nullptr) {
		return true;
	}

	float radius = 50;

	float diffX = abs(target->posX - posX);
	float diffY = abs(target->posY- posY);

	if (diffX * diffX + diffY * diffY < radius * radius) {
		target->damage(damage);
		return true;
	}
	return false;
}

void Projectile::update() {
	if (hasHitTarget() || target == nullptr) {
		return;
	}
	

	sf::Vector2f velocity(target->posX - posX, target->posY - posY);
	float cardVelocity = sqrtf((velocity.x * velocity.x) + (velocity.y * velocity.y));
	velocity.x /= cardVelocity;
	velocity.y /= cardVelocity;

	//std::cout << "Rad: " << angle << " Deg: " << angle * 180 / 3.14159 << std::endl;

	// new position is +velocity
	posX = posX + velocity.x * speed * gameEngine->deltaTime.asMilliseconds();
	posY = posY + velocity.y * speed * gameEngine->deltaTime.asMilliseconds();

	//The following code affects every single arrow which uses the same sprite. Temp test until shit works, fix the getRenderDrawable function.
	projectileSprite->setPosition(posX, posY); 
	float angle = atan2(target->posY - posY, target->posX - posX);
	projectileSprite->setRotation(angle * 180 / 3.14159);
}
