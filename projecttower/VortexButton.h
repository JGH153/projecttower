#pragma once

#include <SFML\Window.hpp>
#include <SFML\Graphics.hpp>
#include <vector>
#include <iostream>
#include <string>
#include <sstream>

#include "Vortex.h"
#include "VortexSprite.h"

class VortexButton
{
public:
	VortexButton(int x, int y, int w, int h, std::string imagePath, std::string title, Vortex * gameEngine);
	~VortexButton();

	void setPosition(double x, double y);
	sf::Vector2f getPosition();

	void update(float delta);

	bool hitPoint(sf::Vector2f point);
	bool hitPoint(int x, int y);

	bool mouseOver();

	bool buttonCliced(); //return if mouse button was realeased this frame and over the button

private:

	int posX;
	int posY;
	int width;
	int height;

	std::string title;
	sf::Font font;
	sf::Text text;

	VortexSprite image;

	Vortex * gameEngine;

	bool mouseOverButton = false;

};

