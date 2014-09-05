#include "TowerObject.h"

TowerObject::TowerObject() {

}

TowerObject::TowerObject(Pos position, sf::Sprite *spr, std::string nam, int cst, float dmg, float rng, float spd) {
	name = nam;
	topLeft = position;
	sprite = spr;
	cost = cst;
	damage = dmg;
	range = rng;
	speed = spd;
}