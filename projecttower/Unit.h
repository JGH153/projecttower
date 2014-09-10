#pragma once
#include <iostream>
#include "VortexSprite.h"
#include "Vortex.h"

class Unit {
public:
	Unit(Vortex * gameEngine, sf::Vector2i pos, int hitpoints, double spd, VortexSprite spr);
	~Unit();
	sf::Vector2i position;
	int hp;
	double speed;
	VortexSprite sprite;

	Vortex * gameEngine;

	bool takeDamageAndCheckIfDead(int damage);
};

