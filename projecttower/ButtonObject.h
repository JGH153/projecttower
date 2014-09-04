#pragma once

#include "TexturedObject.h"

class ButtonObject : public TexturedObject {
public:
	ButtonObject();
	ButtonObject(Pos position, sf::Texture *tex, sf::Texture *mouseOver, sf::Texture *clicked);

	sf::Texture *mouseOverTexture;
	sf::Texture *clickedTexture;
};