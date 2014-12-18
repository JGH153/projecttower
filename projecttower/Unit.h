#pragma once

#include "GlobalDefines.h"
#include "Entity.h"

#include "aStar.h"


class Unit : public Entity{
public:
	Unit(Vortex * gameEngine, std::vector<std::vector<MapTile *>> * mapGroundTiles, int posX, int posY);
	~Unit();

	bool hitPoint(sf::Vector2f point);
	bool hitPoint(double x, double y);

	void damage(float damage);
	bool isDead();
	std::vector<sf::Drawable *> getHealthbarDrawable();

	void initUnit();
	sf::Color hitParticleColor;
	
	int killReward;
	bool reachedGoal;
	bool groundTilesChanged;
	bool towerRemoved;

protected:

	bool firstTimeRun = true;

	void updateMovement();
	void updateDirection();
	
	float currentHealth;
	float maxHealth;
	sf::Vector2i moveDirection;
	float speed;

	int endPosX;
	int endPosY;
	
	

	std::vector<std::vector<MapTile *>> * mapGroundTiles;

	bool atTileCentre();
	bool atTargetTile();
	
	sf::Vector2f mapGroundTilePosToWorldPos(int x, int y);
	sf::Vector2i WorldPosToMapGroundTilePos(double x, double y);

	VortexSprite *healthBarBG;
	VortexSprite *healthBarFG;
	VortexSprite *healthBarFrame;

	void moveHealthBar(sf::Vector2f offset);

	float offsetComponentsY;

	std::vector<VortexAnimation *> moveAnimations;
	int currentMoveAnimationIndex;
};

