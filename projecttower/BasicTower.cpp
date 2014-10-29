#include "BasicTower.h"


BasicTower::BasicTower(Vortex * gameEngine, int posX, int posY) : Tower(gameEngine) {

	this->posX = posX;
	this->posY = posY;

	//towerSprite = new VortexSprite("Graphics/button.png", posX, posY);

	sf::Texture * texImageTile;
	texImageTile = gameEngine->loadImageToTexture("Graphics/Towers/Normal.png");
	towerSprite = new VortexSprite(*texImageTile);
	towerSprite->setPosition(posX, posY);
	towerSprite->setSize(50, 50);
	//towerSprite->rotate(180);
}


BasicTower::~BasicTower() {
}


std::vector<sf::Drawable *> BasicTower::getRenderDrawable() {
	return towerSprite->getRenderDrawable();
}



void BasicTower::update() {

}