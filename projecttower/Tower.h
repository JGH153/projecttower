#pragma once

#include "Unit.h"

#include "Entity.h"
#include "Projectile.h"

class Tower : public Entity {
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

	//sf::Vector2f spritePos;
	VortexSprite* getTowerSprite();

protected:

	sf::Clock reloadTimer;

	int reloadTimeMS;
	float projectileSpeed;
	float damage;
	int range;
	Unit *currentTarget;

	bool reloading;

	double gridTileSize;


	VortexSprite *towerSprite;
	std::vector<Unit *> * enemyList;
	std::vector<Projectile*> projectiles;
	std::mutex towerProjectileMutex;
};

