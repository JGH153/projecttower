#include "BasicTower.h"


BasicTower::BasicTower(Vortex * gameEngine, std::vector<Unit *> * enemyList, int posX, int posY, double gridTileSize) : Tower(gameEngine, enemyList, posX, posY) {

	damage = 2.f;
	range = 200;
	reloadTimeMS = 500;

	reloading = false;

	this->gridTileSize = gridTileSize;

	/*this->posX = posX;
	this->posY = posY;*/

	//towerSprite = new VortexSprite("Graphics/button.png", posX, posY);

	sf::Texture * texImageTile;
	texImageTile = gameEngine->loadImageToTexture("Graphics/Towers/NormalReducedCanvas.png");
	
	float towerSpriteOffsetX = 0.f;
	float towerSpriteOffsetY = 23.f;


	spritePos.x = posX - towerSpriteOffsetX;
	spritePos.y = posY - towerSpriteOffsetY;
	width = gridTileSize;
	height = gridTileSize + towerSpriteOffsetY;
	towerSprite = new VortexSprite(gameEngine, "Graphics/Towers/NormalReducedCanvas.png", spritePos.x, spritePos.y, width, height);
}


BasicTower::~BasicTower() {
}


std::vector<sf::Drawable *> BasicTower::getRenderDrawable() {
	return towerSprite->getRenderDrawable();
}



void BasicTower::update() {
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
			//fire!
			//std::cout << "im firing my lazer" << std::endl;
			reloading = true;
			reloadTimer.restart();
			currentTarget->damage(damage);
		}

	}

}