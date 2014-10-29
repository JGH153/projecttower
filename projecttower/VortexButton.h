#pragma once

#include <SFML\Window.hpp>
#include <SFML\Graphics.hpp>
#include <vector>
#include <iostream>
#include <string>
#include <sstream>
#include <mutex>

#include "Vortex.h"
#include "VortexSprite.h"
#include "GlobalDefines.h"
#include "VortexText.h"

class VortexButton : public RenderObject
{
public:
	VortexButton(double x, double y, Vortex * gameEngine);
	~VortexButton();

	virtual void setPosition(sf::Vector2f newPosition) = 0;
	virtual void setPosition(double x, double y) = 0;
	sf::Vector2f getPosition();

	int getWidth();
	int getHeight();

	virtual bool hitPoint(sf::Vector2f point) = 0;
	virtual bool hitPoint(double x, double y) = 0;

	bool buttonClicked();
	bool mouseOver();

protected:	
	

	double posX;
	double posY;
	int width;
	int height;

	Vortex * gameEngine;
};

