#include "Unit.h"


Unit::Unit(sf::Vector2i pos, int hitpoints, double spd, VortexSprite spr)
{
	position = pos;
	hp = hitpoints;
	speed = spd;
	sprite = spr;
}


Unit::~Unit()
{
	std::cout << "I am dead, goodbye" << std::endl;
}

bool Unit::takeDamageAndCheckIfDead(int damage) {
	hp -= damage;
	if (hp <= 0) {
		return true;	//Returns true if unit is dead. Delete unit and remove it from vector in GameController.
	}
	
	std::cout << "My hp: " << hp << std::endl; //DEBUG
	return false;	//Unit still alive. Dont do shit.
}