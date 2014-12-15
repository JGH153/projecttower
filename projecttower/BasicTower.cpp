#include "BasicTower.h"


BasicTower::BasicTower(Vortex * gameEngine, std::vector<Unit *> * enemyList, int posX, int posY, double gridTileSize, sf::Vector2i mapGroundTileIndex, std::vector<VortexParticleSystem *> * particleList) : Tower(gameEngine, enemyList, posX, posY, mapGroundTileIndex, particleList) {

	damage = 2.f;
	range = 150;
	reloadTimeMS = 700;
	projectileSpeed = 0.2f;

	reloading = false;

	this->gridTileSize = gridTileSize;

	sf::Texture * texImageTile;
	texImageTile = gameEngine->loadImageToTexture("Graphics/Towers/NormalReducedCanvas.png");
	
	towerSpriteOffsetX = 0.f;
	towerSpriteOffsetY = 23.f;

	width = gridTileSize;
	height = gridTileSize + towerSpriteOffsetY;
	towerSprite = new VortexSprite(gameEngine, "Graphics/Towers/NormalReducedCanvas.png", posX - towerSpriteOffsetX, posY - towerSpriteOffsetY, width, height);
	projectileSpritePath = "Graphics/Projectiles/Arrow.png";
}


BasicTower::~BasicTower() {
}


std::vector<sf::Drawable *> BasicTower::getRenderDrawable() {

	//auto temp = towerSprite->getRenderDrawable();

	/*for (auto currentProjectile : projectiles) {
		auto arrows = currentProjectile->getRenderDrawable();

		temp.insert(temp.end(), arrows.begin(), arrows.end());
	}*/
	auto returnList =  towerSprite->getRenderDrawable();

	return returnList;

}



void BasicTower::update() {

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

			auto sprite =  new VortexSprite(gameEngine, projectileSpritePath, posX + width / 2, posY - towerSpriteOffsetY);
			auto projectile = new Projectile(gameEngine, posX + towerSprite->getSize().x / 2, posY, sprite, currentTarget, projectileSpeed, damage);
			
			//gameEngine->towerProjectileMutex.lock();
			projectiles.push_back(projectile);
			//gameEngine->towerProjectileMutex.unlock();
			reloading = true;
			reloadTimer.restart();
		}
	}
}

void BasicTower::killYourself() {

	delete this;

}