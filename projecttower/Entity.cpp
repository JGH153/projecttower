#include "Entity.h"


Entity::Entity(Vortex * gameEngine, int posX, int posY){

	this->gameEngine = gameEngine;
	setPos(posX, posY);
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

void Entity::setPos(sf::Vector2f pos) {

	this->posX = pos.x;
	this->posY = pos.y;

}



void Entity::setSize(int width, int height){

	this->width = width;
	this->height = height;

}