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


	float posX;
	float posY;

	int width;
	int height;


protected:

	

	sf::Vector2i moveDirection;
	float speed;

};

