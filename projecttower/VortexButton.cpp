#include "VortexButton.h"

VortexButton::VortexButton(double x, double y, std::string imagePath, Vortex * gameEngine){
	this->gameEngine = gameEngine;
	image = VortexSprite(gameEngine->loadImageToSprite(imagePath));
	setPosition(x, y);

}


VortexButton::~VortexButton(){

}


sf::Vector2f VortexButton::getPosition(){

	return sf::Vector2f(posX, posY);

}

int VortexButton::getWidth(){
	return width;
}

int VortexButton::getHeight(){
	return height;
}

void VortexButton::setPosition(sf::Vector2f newPosition){
	posX = newPosition.x;
	posY = newPosition.y;
	image.setPosition(newPosition);
}

void VortexButton::setPosition(double x, double y){
	setPosition(sf::Vector2f(x, y));
}