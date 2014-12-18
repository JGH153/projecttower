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

Projectile::Projectile(Vortex *gameEngine, int posX, int posY, VortexSprite *projectileSprite, Unit *target, float speed, float damage, int radius, std::vector<Unit *> * enemyList, std::vector<VortexParticleSystem *> * particleList, EffectsHandler* effectsHandler) : Entity(gameEngine, posX, posY) {
	this->gameEngine = gameEngine;
	this->speed = speed;
	this->target = target;
	this->projectileSprite = projectileSprite;
	projectileSprite->setScale(0.40f, 0.40f);
	this->damage = damage;
	destroyProjectile = false;
	hitParticleColor = sf::Color(222, 200, 150);

	this->radius = radius;
	this->enemyList = enemyList;
	this->particleList = particleList;
	this->effectsHandler = effectsHandler;
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
	float hitboxRadius = 25;

	float diffX = abs((target->posX + target->getSize().x / 2) - posX);
	float diffY = abs((target->posY + target->getSize().y / 2) - posY);

	if (diffX * diffX + diffY * diffY <= hitboxRadius * hitboxRadius) {
		// If the projectile is close enough to unit, damage it
		
		target->damage(damage);
		if (radius > 0) {
			// If projectile is explosive, damage others within radius as well
			effectsHandler->showExplosion(target->posX + target->width / 2, target->posY + target->height / 2);
			
			gameEngine->particleListMutex.lock();
			particleList->push_back(new VortexParticleSystem(1000, target->getPos().x + target->getSize().x / 2, target->getPos().y + target->getSize().y / 2, sf::Color::Green, sf::Points, 200, 120));
			gameEngine->particleListMutex.unlock();
			

			for (auto currentUnit : *enemyList) {
				if (currentUnit == target) {
					continue;
				}
				float xdist = abs(currentUnit->getPos().x - target->getPos().x);
				float ydist = abs(currentUnit->getPos().y - target->getPos().y);
				if (xdist * xdist + ydist * ydist <= radius * radius) {
					// If the unit is within the splash raidus, do damage relative to the distance from explosion
					float percentDistanceFromCenter = 1 - (xdist * xdist + ydist * ydist) / (radius * radius);
					currentUnit->damage(damage * percentDistanceFromCenter);
				}
			}
		}
		
		return true;
	}
	return false;
}

void Projectile::updatePos() {
	sf::Vector2f velocity(target->posX + target->getSize().x / 2 - posX, target->posY + target->getSize().y / 2 - posY);
	float cardVelocity = sqrtf((velocity.x * velocity.x) + (velocity.y * velocity.y));
	velocity.x /= cardVelocity;
	velocity.y /= cardVelocity;


	posX = posX + velocity.x * speed * gameEngine->deltaTime.asMilliseconds();
	posY = posY + velocity.y * speed * gameEngine->deltaTime.asMilliseconds();

	projectileSprite->setPosition(posX, posY);
	float angle = atan2(target->posY + target->getSize().y / 2 - posY, target->posX + target->getSize().x / 2 - posX);
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