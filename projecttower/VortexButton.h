#pragma once

#include <SFML\Window.hpp>
#include <SFML\Graphics.hpp>
#include <vector>
#include <iostream>
#include <string>
#include <sstream>

#include "Vortex.h"
#include "VortexSprite.h"
#include "GlobalDefines.h"

class VortexButton : public RenderObject
{
public:
	VortexButton(double x, double y, std::string imagePath, Vortex * gameEngine);
	~VortexButton();

	void setPosition(sf::Vector2f newPosition);
	void setPosition(double x, double y);
	sf::Vector2f getPosition();
	int getWidth();
	int getHeight();

	virtual bool hitPoint(sf::Vector2f point) = 0;
	virtual bool hitPoint(double x, double y) = 0;

	virtual bool buttonClicked() = 0;
protected:

	double posX;
	double posY;
	int width;
	int height;

	VortexSprite image;
	Vortex * gameEngine;
};

