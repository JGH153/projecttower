#pragma once
#include "VortexButtonRectangle.h"


VortexButtonRectangle::VortexButtonRectangle(double x, double y, int w, int h, std::string imagePath, Vortex * gameEngine) : VortexButton(x, y, imagePath, gameEngine) {
	width = w;
	height = h;

	image.setSize(width, height);
}

VortexButtonRectangle::~VortexButtonRectangle()
{
}

void VortexButtonRectangle::update(){

}


std::vector<sf::Drawable *> VortexButtonRectangle::getRenderDrawable() {

	return image.getRenderDrawable();

}


bool VortexButtonRectangle::hitPoint(sf::Vector2f point){
	return hitPoint(point.x, point.y);
}

bool VortexButtonRectangle::hitPoint(double x, double y){

	if (x >= this->posX && x <= this->posX + this->width
		&& y >= this->posY && y <= this->posY + this->height){
		return true;
	}

	return false;
}

bool VortexButtonRectangle::buttonClicked() {
	if (gameEngine->eventMousePressedLeft){
		sf::Vector2i mouse = gameEngine->getMousePosition();
		return hitPoint(gameEngine->getMapPixelToCoords(mouse));
	}
	return false;
}