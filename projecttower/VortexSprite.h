#pragma once

#include <SFML\Window.hpp>
#include <SFML\Graphics.hpp>
#include <vector>
#include <iostream>
#include <string>

#include "Vortex.h"
#include "RenderObject.h"
#include "GlobalDefines.h"

class Vortex;

class VortexSprite : public sf::Sprite, public RenderObject{
public:
	VortexSprite();
	VortexSprite(Vortex * gameEngine, std::string path, float posX, float posY, double width, double height);
	VortexSprite(const sf::Texture &texture);
	~VortexSprite();

	void setSize(double w, double h);
	void setSize(sf::Vector2f newSize);

	bool hitPoint(sf::Vector2f point);
	bool hitPoint(double x, double y);

	void update();

	std::vector<sf::Drawable *> getRenderDrawable();
	

	sf::Vector2f getSize();
	
};

