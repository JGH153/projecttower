#include "Entity.h"


Entity::Entity(Vortex * gameEngine){

	this->gameEngine = gameEngine;

}


Entity::~Entity(){
}


sf::Vector2f Entity::getPos() {

	return sf::Vector2f(posX, posY);

}

sf::Vector2i Entity::getSize() {

	return sf::Vector2i(width, height);

}

void Entity::setPos(float posX, float posY) {

	this->posX = posX;
	this->posY = posY;

}

void Entity::setSize(int width, int height){

	this->width = width;
	this->height = height;

}