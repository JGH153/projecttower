#pragma once

#include <SFML\Window.hpp>
#include <SFML\Graphics.hpp>
#include <vector>
#include <iostream>
#include <string>
#include <sstream>

#include "Vortex.h"
#include "VortexSprite.h"

class VortexButton : public RenderObject
{
public:
	VortexButton(double x, double y, int w, int h, std::string imagePath, std::string title, Vortex * gameEngine);
	~VortexButton();

	void setPosition(double x, double y);
	sf::Vector2f getPosition();

	void update();
	std::vector<VortexSprite *> getRenderSprites();

	bool hitPoint(sf::Vector2f point);
	bool hitPoint(double x, double y);

	bool mouseOver();

	bool buttonClicked(); //return if mouse button was realeased this frame and over the button

private:

	double posX;
	double posY;
	int width;
	int height;

	std::string title;
	sf::Font font;
	sf::Text text;

	VortexSprite image;

	Vortex * gameEngine;

	bool mouseOverButton = false;

};

