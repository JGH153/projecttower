#pragma once
#include "VortexSprite.h"
#include "Unit.h"
#include "Vortex.h"

class Tower
{
public:
	Tower(Vortex * gameEngine, sf::Vector2i pos, int dmg, double spd, double rng, VortexSprite spr);
	~Tower();
	sf::Vector2i position;
	int damage;
	double speed;
	double range;
	Unit *target;
	VortexSprite sprite;
	sf::Time timeSinceLastAttack;
	sf::Clock stopwatch;

	Vortex * gameEngine;

	bool canAttack();
	bool attack();
	void update();
};

