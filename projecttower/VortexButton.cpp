#include "VortexButton.h"

VortexButton::VortexButton(double x, double y, Vortex * gameEngine){
	this->gameEngine = gameEngine;
	posX = x;
	posY = y;
}


VortexButton::~VortexButton(){

}


void VortexButton::setValue(std::string value) {
	buttonValue = value;
}
std::string VortexButton::getValue() {
	return buttonValue;
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
	if (gameEngine->eventMousePressedLeft) {
		
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

void VortexButton::setOpacity(int value) {
	if (image != NULL) {
		sf::Color imageColor = image->getColor();
		imageColor.a = value;
		image->setColor(imageColor);

		if (value <= 0) {
			hidden = true;
		}
		else {
			hidden = false;
		}
	}
}