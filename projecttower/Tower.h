#pragma once

#include "Unit.h"

#include "Entity.h"
#include "Projectile.h"

class Tower : public Entity {
public:
	Tower(Vortex * gameEngine, std::vector<Unit *> * enemyList, int posX, int posY, sf::Vector2i mapGroundTileIndex);
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

	sf::Vector2i getMapGroundTileIndex();
	std::vector<Projectile*> getProjectileList();

	std::vector<sf::Drawable *> getProjectilesRenderDrawable();

	void deleteProjectiles();

protected:

	sf::Clock reloadTimer;

	int reloadTimeMS;
	float projectileSpeed;
	float damage;
	int range;
	Unit *currentTarget;

	bool reloading;

	double gridTileSize;

	std::string projectileSpritePath;

	float towerSpriteOffsetX;
	float towerSpriteOffsetY;

	sf::Vector2i mapGroundTileIndex;


	VortexSprite *towerSprite;
	std::vector<Unit *> * enemyList;
	std::vector<Projectile*> projectiles;
	
};

