#include "BasicTower.h"


BasicTower::BasicTower(Vortex * gameEngine, int posX, int posY) : Tower(gameEngine) {

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

}