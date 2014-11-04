#pragma once

#include "GlobalDefines.h"
#include "Entity.h"


class Unit : public Entity{
public:
	Unit(Vortex * gameEngine);
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
	


protected:

	
	float health;
	sf::Vector2i moveDirection;
	float speed;

};

