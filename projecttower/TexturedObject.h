#pragma once
#include "GameObject.h"

class TexturedObject : public GameObject {
public:
	TexturedObject();
	TexturedObject(sf::Texture *tex);
	TexturedObject(Pos position, sf::Texture *tex);
	sf::Texture *texture;
};