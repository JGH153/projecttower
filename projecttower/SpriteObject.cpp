#include "SpriteObject.h"

SpriteObject::SpriteObject() {
	sprite = NULL;
}

SpriteObject::SpriteObject(sf::Sprite *spr) {
	sprite = spr;
}

SpriteObject::SpriteObject(Pos position, sf::Sprite *spr) {
	pos = position;
	sprite = spr;
}