#include "CannonTower.h"


CannonTower::CannonTower(Vortex * gameEngine, std::vector<Unit *> * enemyList, int posX, int posY, double gridTileSize, sf::Vector2i mapGroundTileIndex, std::vector<VortexParticleSystem *> * particleList) : Tower(gameEngine, enemyList, posX, posY, mapGroundTileIndex, particleList) {
	damage = 5.f;
	range = 150;
	reloadTimeMS = 1000;
	projectileSpeed = 0.15f;
	splashRadius = 50;
	reloading = false;

	this->gridTileSize = gridTileSize;

	sf::Texture * texImageTile;
	texImageTile = gameEngine->loadImageToTexture("Graphics/Towers/CannonReducedCanvas.png");

	towerSpriteOffsetX = 8.f;
	towerSpriteOffsetY = 23.f;

	width = gridTileSize + towerSpriteOffsetX;
	height = gridTileSize + towerSpriteOffsetY;
	towerSprite = new VortexSprite(gameEngine, "Graphics/Towers/CannonReducedCanvas.png", posX - towerSpriteOffsetX / 2, posY - towerSpriteOffsetY, width, height);
	projectileSpritePath = "Graphics/Projectiles/cannonball.png";

	towerId = 2;
}


CannonTower::~CannonTower() {

}



std::vector<sf::Drawable *> CannonTower::getRenderDrawable() {

	auto returnList = towerSprite->getRenderDrawable();

	return returnList;

}



void CannonTower::update() {

	//gameEngine->towerProjectileMutex.lock();

	for (int i = 0; i < projectiles.size(); i++) {
		if (projectiles[i]->destroyProjectile == true) {
			gameEngine->addRemovableObjectToList(projectiles[i]);
			projectiles[i] = nullptr;
			projectiles.erase(projectiles.begin() + i);
			i--;
		}
	}


	for (auto current : projectiles) {
		current->update();
	}

	//gameEngine->towerProjectileMutex.unlock();

	if (reloadTimer.getElapsedTime().asMilliseconds() > reloadTimeMS) {
		reloading = false;
	}

	// If tower has a previous target, check if that target is still within range
	if (currentTarget != nullptr) {
		if (!targetWithinRange(currentTarget) || currentTarget->isDead()) {
			currentTarget = nullptr;
		}
	}


	if (!reloading) {
		// If tower has no target, find one

		if (currentTarget == nullptr) {
			currentTarget = findTarget();
		}
		// If it has a viable target by now, attack it
		if (currentTarget != nullptr) {

			auto sprite = new VortexSprite(gameEngine, projectileSpritePath, posX + width / 2, posY - towerSpriteOffsetY);
			auto projectile = new Projectile(gameEngine, posX + towerSprite->getSize().x / 2, posY, sprite, currentTarget, projectileSpeed, damage, splashRadius, enemyList, particleList);

			projectiles.push_back(projectile);
			reloading = true;
			reloadTimer.restart();
		}
	}
}

void CannonTower::killYourself() {

	delete this;

}