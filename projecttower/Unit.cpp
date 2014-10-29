#include "Unit.h"


Unit::Unit(Vortex * gameEngine) : Entity(gameEngine){

	this->gameEngine = gameEngine;
}


Unit::~Unit()
{
}


bool Unit::hitPoint(sf::Vector2f point) {
	return hitPoint(point.x, point.y);
}

bool Unit::hitPoint(double x, double y) {

	if (x >= this->posX && x <= this->posX + this->width
		&& y >= this->posY && y <= this->posY + this->height) {
		return true;
	}

	return false;
}

//bool Unit::takeDamageAndCheckIfDead(int damage) {
//	hp -= damage;
//	if (hp <= 0) {
//		return true;	//Returns true if unit is dead. Delete unit and remove it from vector in GameController.
//	}
//	
//	std::cout << "My hp: " << hp << std::endl; //DEBUG
//	return false;	//Unit still alive. Dont do shit.
//}

//void Unit::update() {
//
//	std::cout << "UNIT" << std::endl;
//
//}