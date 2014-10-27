#pragma once

#include <SFML\Window.hpp>
#include <SFML\Graphics.hpp>
#include <vector>
#include <iostream>


#include "RenderObject.h"
#include "GlobalDefines.h"

class Vortex;

class VortexSprite : public sf::Sprite, public RenderObject{
public:
	VortexSprite();
	VortexSprite(const sf::Texture &texture);
	~VortexSprite();

	void setSize(double w, double h);
	void setSize(sf::Vector2f newSize);

	void update();

	std::vector<RenderData> getRenderData();


	sf::Vector2f getSize();
	
};

