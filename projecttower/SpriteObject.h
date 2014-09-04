#pragma once
#include "GameObject.h"

class SpriteObject : public GameObject {
public:
	SpriteObject();
	SpriteObject(sf::Sprite *spr);
	SpriteObject(Pos position, sf::Sprite *spr);
	sf::Sprite *sprite;
};