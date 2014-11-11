#include "BasicTower.h"


BasicTower::BasicTower(Vortex * gameEngine, std::vector<Unit *> * enemyList, int posX, int posY, double gridTileSize, sf::Vector2i mapGroundTileIndex) : Tower(gameEngine, enemyList, posX, posY, mapGroundTileIndex) {

	damage = 2.f;
	range = 200;
	reloadTimeMS = 1;
	projectileSpeed = 0.2f;

	reloading = false;

	this->gridTileSize = gridTileSize;

	/*this->posX = posX;
	this->posY = posY;*/

	//towerSprite = new VortexSprite("Graphics/button.png", posX, posY);

	sf::Texture * texImageTile;
	texImageTile = gameEngine->loadImageToTexture("Graphics/Towers/NormalReducedCanvas.png");
	
	towerSpriteOffsetX = 0.f;
	towerSpriteOffsetY = 23.f;


	/*spritePos.x = posX - towerSpriteOffsetX;
	spritePos.y = posY - towerSpriteOffsetY;*/
	width = gridTileSize;
	height = gridTileSize + towerSpriteOffsetY;
	towerSprite = new VortexSprite(gameEngine, "Graphics/Towers/NormalReducedCanvas.png", posX - towerSpriteOffsetX, posY - towerSpriteOffsetY, width, height);
	//projectileSprite = new 
	projectileSpritePath = "Graphics/Projectiles/Arrow.png";
}


BasicTower::~BasicTower() {
}


std::vector<sf::Drawable *> BasicTower::getRenderDrawable() {
	auto temp = towerSprite->getRenderDrawable();
	for (auto currentProjectile : projectiles) {
		towerProjectileMutex.lock();
		auto arrows = currentProjectile->getRenderDrawable();
		for (auto currentDrawable : arrows) {
			temp.push_back(currentDrawable);
		}
		towerProjectileMutex.unlock();
	}
	return temp;
}



void BasicTower::update() {
	for (int i = 0; i < projectiles.size(); i++) {
		if (projectiles[i]->destroyProjectile == true || projectiles[i]->posX < 0 || projectiles[i]->posX > WINDOWSIZEX || projectiles[i]->posY < 0 || projectiles[i]->posX > WINDOWSIZEY) {
			towerProjectileMutex.lock();
			delete projectiles[i];
			projectiles.erase(projectiles.begin() + i);
			towerProjectileMutex.unlock();
			i--;
		}
	}
	for (auto current : projectiles) {
		current->update();
	}
	if (reloadTimer.getElapsedTime().asMilliseconds() > reloadTimeMS) {
		reloading = false;
	}

	// If tower has a previous target, check if that target is still within range
	if (currentTarget != nullptr) {
		if (!targetWithinRange(currentTarget)) {
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
			towerProjectileMutex.lock();
			auto sprite =  new VortexSprite(gameEngine, projectileSpritePath, posX + width / 2, posY - towerSpriteOffsetY);
			auto projectile = new Projectile(gameEngine, posX + towerSprite->getSize().x / 2, posY, sprite, currentTarget, projectileSpeed, damage);
			//auto projectile = new Projectile(gameEngine, 100, 100, (new VortexSprite(gameEngine, "Graphics/Projectiles/Arrow.png", 100, 100, 10, 10)), nullptr, 1.f, 1.f);
			projectiles.push_back(projectile);
			towerProjectileMutex.unlock();
			reloading = true;
			reloadTimer.restart();
			
		}

	}

}