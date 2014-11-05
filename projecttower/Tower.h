#pragma once

#include "Unit.h"

#include "Entity.h"

class Tower : public Entity{
public:
	Tower(Vortex * gameEngine, std::vector<Unit *> * enemyList, int posX, int posY);
	~Tower();
	//sf::Vector2i position;
	//int damage;
	//double speed;
	//double range;
	//Unit *target;
	//VortexSprite sprite;
	//sf::Time timeSinceLastAttack;
	//sf::Clock stopwatch;

	//bool canAttack();
	//bool attack();
	//virtual void update();

	Unit * Tower::findTarget();

protected:

	sf::Clock reloadTimer;

	int reloadTimeMS;
	float damage;
	int range;

	bool reloading;

	

	std::vector<Unit *> * enemyList;

};

