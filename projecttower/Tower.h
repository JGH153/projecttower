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
	bool newTargetCloser(Unit *previousBest, Unit *newPotential);
	bool targetWithinRange(Unit *testSubject);

	sf::Vector2f spritePos;

protected:

	sf::Clock reloadTimer;

	int reloadTimeMS;
	float damage;
	int range;
	Unit *currentTarget;

	bool reloading;
	bool selected;

	double gridTileSize;

	

	

	std::vector<Unit *> * enemyList;

};

