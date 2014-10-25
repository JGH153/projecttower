#pragma once

#include <SFML\Window.hpp>
#include <SFML\Graphics.hpp>
#include <vector>
#include <iostream>

//#include "Vortex.h"
#include "RenderObject.h"

class Vortex;

class VortexSprite : public sf::Sprite, public RenderObject{
public:
	VortexSprite();
	VortexSprite(const sf::Texture &texture);
	~VortexSprite();

	void setSize(double w, double h);
	void setSize(sf::Vector2f newSize);

	void update();
	void render();

	VortexSprite * getRenderSprite();


	sf::Vector2f getSize();
	
};

