#include "Projectile.h"


Projectile::Projectile(Vortex *gameEngine, int posX, int posY, VortexSprite *projectileSprite, Unit *target, float speed, float damage) : Entity(gameEngine, posX, posY) {
	this->gameEngine = gameEngine;
	this->speed = speed;
	this->target = target;
	this->projectileSprite = projectileSprite;
	projectileSprite->setScale(0.45f, 0.45f);
	this->damage = damage;
	destroyProjectile = false;
	hitParticleColor = sf::Color(222, 200, 150);

	radius = 0;

	updatePos();

	zIndex = zIndexlayer::projectile;
}

Projectile::Projectile(Vortex *gameEngine, int posX, int posY, VortexSprite *projectileSprite, Unit *target, float speed, float damage, int radius, std::vector<Unit *> * enemyList, std::vector<VortexParticleSystem *> * particleList) : Entity(gameEngine, posX, posY) {
	this->gameEngine = gameEngine;
	this->speed = speed;
	this->target = target;
	this->projectileSprite = projectileSprite;
	projectileSprite->setScale(0.45f, 0.45f);
	this->damage = damage;
	destroyProjectile = false;
	hitParticleColor = sf::Color(222, 200, 150);

	this->radius = radius;
	this->enemyList = enemyList;
	this->particleList = particleList;
	updatePos();

	zIndex = zIndexlayer::projectile;
}


Projectile::~Projectile() {

	delete projectileSprite;

}

std::vector<sf::Drawable*> Projectile::getRenderDrawable() {
	return projectileSprite->getRenderDrawable();
}


bool Projectile::checkIfHitTarget() {
	float radi = 25;

	float diffX = abs((target->posX + target->width / 2) - posX);
	float diffY = abs((target->posY + target->height / 2) - posY);

	if (diffX * diffX + diffY * diffY < radi * radi) {
		// If the projectile is close enough to unit, damage it
		
		target->damage(damage);
		if (radius > 0) {
			// If projectile is explosive, damage others within radius as well
			gameEngine->particleListMutex.lock();
			particleList->push_back(new VortexParticleSystem(160, target->getPos().x + target->getSize().x / 2, target->getPos().y + target->getSize().y / 2, sf::Color(100, 100, 100, 150), sf::Quads, 200, 150));
			gameEngine->particleListMutex.unlock();

			for (auto currentUnit : *enemyList) {
				if (abs(currentUnit->getPos().x - target->getPos().x) * abs(currentUnit->getPos().x - target->getPos().x) + abs(currentUnit->getPos().y - target->getPos().y) * abs(currentUnit->getPos().y - target->getPos().y) < radius * radius) {
					currentUnit->damage(damage);
				}
			}
		}
		
		return true;
	}
	return false;
}

void Projectile::updatePos() {

	sf::Vector2f velocity(target->posX - posX, target->posY + target->height / 2 - posY);
	float cardVelocity = sqrtf((velocity.x * velocity.x) + (velocity.y * velocity.y));
	velocity.x /= cardVelocity;
	velocity.y /= cardVelocity;


	posX = posX + velocity.x * speed * gameEngine->deltaTime.asMilliseconds();
	posY = posY + velocity.y * speed * gameEngine->deltaTime.asMilliseconds();

	projectileSprite->setPosition(posX, posY);
	float angle = atan2(target->posY + target->height / 2 - posY, target->posX - posX);
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
	

	if (posX < 0 || posX > WINDOWSIZEX || posY < 0 || posY > WINDOWSIZEY) {
		destroyProjectile = true;
	}
}


void Projectile::killYourself() {

	delete this;

}