#pragma once

#include <SFML\Window.hpp>
#include <SFML\Graphics.hpp>
#include <vector>
#include <iostream>
#include <string>

#include "Vortex.h"
#include "RenderObject.h"
#include "GlobalDefines.h"
#include "RemovableObject.h"

class Vortex;

class VortexSprite : public sf::Sprite, public RenderObject, public RemovableObject {
public:
	VortexSprite();
	VortexSprite(const sf::Texture &, sf::IntRect spriteRec, sf::IntRect texRec);
	VortexSprite(Vortex * gameEngine, std::string path, float posX, float posY, double width, double height);
	VortexSprite(Vortex * gameEngine, std::string path, float posX, float posY);
	VortexSprite(const sf::Texture &texture);
	VortexSprite(sf::Texture* texture, float posX, float posY, double width, double height);
	~VortexSprite();

	void setSize(double w, double h);
	void setSize(sf::Vector2f newSize);

	bool hitPoint(sf::Vector2f point);
	bool hitPoint(double x, double y);

	void update();

	std::vector<sf::Drawable *> getRenderDrawable();
	

	sf::Vector2f getSize();

	void killYourself();
	
};

