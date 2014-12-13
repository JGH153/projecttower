#pragma once

#include "GlobalDefines.h"
#include "Entity.h"

#include "aStar.h"


class Unit : public Entity{
public:
	Unit(Vortex * gameEngine, std::vector<std::vector<MapTile *>> * mapGroundTiles, int posX, int posY);
	~Unit();
	//sf::Vector2i position;
	//int hp;
	//double speed;
	//VortexSprite sprite;


	//bool takeDamageAndCheckIfDead(int damage);
	//void update();

	bool hitPoint(sf::Vector2f point);
	bool hitPoint(double x, double y);

	//is damaged
	void damage(float damage);
	bool isDead();

	void initUnit();
	sf::Color hitParticleColor;
	
	int killReward;


protected:

	deque<sf::Vector2i> pathToTarget;

	bool atWaypointTarget;
	sf::Vector2i currentWaypointTarget;

	
	float currentHealth;
	float maxHealth;
	sf::Vector2i moveDirection;
	float speed;

	std::vector<std::vector<MapTile *>> * mapGroundTiles;

	bool atCurrentWaypointTarget();
	bool atCurrentWaypointTargetX();
	bool atCurrentWaypointTargetY();

	sf::Vector2f mapGroundTilePosToWorldPos(int x, int y);
	sf::Vector2i WorldPosToMapGroundTilePos(double x, double y);

	VortexSprite *healthBarBG;
	VortexSprite *healthBarFG;
	VortexSprite *healthBarFrame;

	void moveHealthBar(sf::Vector2f offset);

	float offsetComponentsY;
};

