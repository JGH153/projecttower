#pragma once

#include <SFML\Window.hpp>
#include <SFML\Graphics.hpp>
#include <vector>
#include <iostream>

class VortexSprite : public sf::Sprite {
public:
	VortexSprite();
	VortexSprite(const sf::Texture &texture);
	~VortexSprite();

	void setSize(double w, double h);
	
};

