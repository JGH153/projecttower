#pragma once

#include "Unit.h"

#include "Entity.h"
#include "Projectile.h"

class Tower : public Entity {
public:
	Tower(Vortex * gameEngine, std::vector<Unit *> * enemyList, int posX, int posY, sf::Vector2i mapGroundTileIndex, std::vector<VortexParticleSystem*> * particleList);
	~Tower();

	Unit * Tower::findTarget();
	bool newTargetCloser(Unit *previousBest, Unit *newPotential);
	bool targetWithinRange(Unit *testSubject);

	VortexSprite* getTowerSprite();

	sf::Vector2i getMapGroundTileIndex();
	std::vector<Projectile*> getProjectileList();

	std::vector<sf::Drawable *> getProjectilesRenderDrawable();

	void deleteProjectiles();
	int towerId;

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
	std::vector<VortexParticleSystem*> * particleList;
	std::vector<Projectile*> projectiles;
	EffectsHandler* effectsHandler;
	
};

