#pragma once
#include <iostream>
#include "VortexSprite.h"

class Unit {
public:
	Unit(sf::Vector2i pos, int hitpoints, double spd, VortexSprite spr);
	~Unit();
	sf::Vector2i position;
	int hp;
	double speed;
	VortexSprite sprite;

	bool takeDamageAndCheckIfDead(int damage);
};

