#pragma once
#include "VortexButtonRectangle.h"


VortexButtonRectangle::VortexButtonRectangle(double x, double y, int w, int h, std::string imagePath, std::string title, Vortex * gameEngine) : VortexButton(x, y, imagePath, title, gameEngine) {
	width = w;
	height = h;

	image.setSize(width, height);
	setPosition(posX, posY);
}

VortexButtonRectangle::~VortexButtonRectangle()
{
}

void VortexButtonRectangle::update(){

}


std::vector<sf::Drawable *> VortexButtonRectangle::getRenderDrawable() {
	std::vector<sf::Drawable *> drawData;
	drawData.push_back(&image);
	drawData.push_back(&text);
	return drawData;

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

void VortexButtonRectangle::setPosition(sf::Vector2f newPosition){
	posX = newPosition.x;
	posY = newPosition.y;
	text.setPosition(newPosition);
	image.setPosition(newPosition);
}

void VortexButtonRectangle::setPosition(double x, double y){
	setPosition(sf::Vector2f(x, y));
}