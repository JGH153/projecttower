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

	towerSprite = new VortexSprite(gameEngine, "Graphics/Towers/NormalReducedCanvas.png", posX - towerSpriteOffsetX, posY - towerSpriteOffsetY, gridTileSize, gridTileSize + towerSpriteOffsetY);
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

	if (!reloading) {

		Unit * target = findTarget();
		if (target != nullptr) {
			//fire!
			//std::cout << "im firing my lazer" << std::endl;
			reloading = true;
			reloadTimer.restart();
			target->damage(damage);
		}

	}

}