#pragma once

#include "SpriteObject.h"

class TowerObject : SpriteObject {
public:
	TowerObject();
	TowerObject(Pos position, sf::Sprite *spr, std::string nam, int cst, float dmg, float rng, float spd);

	std::string name;
	int cost;
	float damage;
	float range;
	float speed;
	//And other tower specific stuffs
};