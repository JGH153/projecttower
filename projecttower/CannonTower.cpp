#include "CannonTower.h"


CannonTower::CannonTower(Vortex * gameEngine, std::vector<Unit *> * enemyList, int posX, int posY, double gridTileSize, sf::Vector2i mapGroundTileIndex, std::vector<VortexParticleSystem *> * particleList, EffectsHandler* effectsHandler) : Tower(gameEngine, enemyList, posX, posY, mapGroundTileIndex, particleList) {
	damage = 2.5f;
	range = 150;
	reloadTimeMS = 1100;
	projectileSpeed = 0.15f;
	splashRadius = 33;
	reloading = false;

	this->effectsHandler = effectsHandler;
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


	if (reloadTimer.getElapsedTime().asMilliseconds() > reloadTimeMS) {
		reloading = false;
	}

	

	// If it is time to attack
	if (!reloading) {
		// If tower has a previous target, check if that target is still within range
		if (currentTarget != nullptr) {
			if (!targetWithinRange(currentTarget) || currentTarget->isDead()) {
				currentTarget = nullptr;
			}
		}

		// If tower has no target, find one
		if (currentTarget == nullptr) {
			currentTarget = findTarget();
		}
		// If it has a viable target by now, attack it
		if (currentTarget != nullptr) {

			auto sprite = new VortexSprite(gameEngine, projectileSpritePath, posX + width / 2, posY - towerSpriteOffsetY);
			auto projectile = new Projectile(gameEngine, posX + towerSprite->getSize().x / 2, posY, sprite, currentTarget, projectileSpeed, damage, splashRadius, enemyList, particleList, effectsHandler);

			projectiles.push_back(projectile);
			reloading = true;
			reloadTimer.restart();
		}
	}
}

void CannonTower::killYourself() {

	delete this;

}