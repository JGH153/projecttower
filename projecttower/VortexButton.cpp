#include "VortexButton.h"

VortexButton::VortexButton(double x, double y, Vortex * gameEngine){
	this->gameEngine = gameEngine;
	posX = x;
	posY = y;
}


VortexButton::~VortexButton(){

}


void VortexButton::setValueString(std::string value) {
	buttonStringValue = value;
}
std::string VortexButton::getValueString() {
	return buttonStringValue;
}

void VortexButton::setValueInt(int value) {
	buttonIntValue = value;
}
int VortexButton::getValueInt() {
	return buttonIntValue;
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
	if (gameEngine->eventMouseClickedLeft) {
		
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