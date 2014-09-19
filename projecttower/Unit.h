#pragma once

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

protected:

	int posX;
	int posY;

};

