#include "BasicTower.h"


BasicTower::BasicTower(Vortex * gameEngine, std::vector<Unit *> * enemyList, int posX, int posY) : Tower(gameEngine, enemyList) {

	damage = 2.f;
	range = 200;
	reloadTimeMS = 600;

	reloading = false;

	this->posX = posX;
	this->posY = posY;

	//towerSprite = new VortexSprite("Graphics/button.png", posX, posY);

	sf::Texture * texImageTile;
	texImageTile = gameEngine->loadImageToTexture("Graphics/Towers/NormalReducedCanvas.png");
	
	towerSprite = new VortexSprite(gameEngine, "Graphics/Towers/NormalReducedCanvas.png", posX, posY - texImageTile->getSize().y / 5, texImageTile->getSize().x / 2.1, texImageTile->getSize().y / 2.1);
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
			//target->damage(damage);
		}

	}

}