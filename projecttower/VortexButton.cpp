#include "VortexButton.h"

VortexButton::VortexButton(double x, double y, Vortex * gameEngine){
	this->gameEngine = gameEngine;
	posX = x;
	posY = y;
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



bool VortexButton::buttonClicked(){
	if (gameEngine->eventMouseReleasedLeft) {
		
	//if (gameEngine->eventMouseReleasedLeft){
		//sf::Vector2f mouse = gameEngine->getMousePositionRelativeToSetView();
		sf::Vector2i mouse = gameEngine->getMousePosition();
		
		return hitPoint(mouse.x, mouse.y);
	}
	return false;
}

bool VortexButton::mouseOver(){	
	//sf::Vector2f mouse = gameEngine->getMousePositionRelativeToSetView();
	sf::Vector2i mouse = gameEngine->getMousePosition();
	return hitPoint(mouse.x, mouse.y);
}