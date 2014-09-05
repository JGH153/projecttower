#pragma once

#include <SFML\Window.hpp>
#include <SFML\Graphics.hpp>
#include <vector>
#include <iostream>
#include <string>
#include <sstream>

#include "VortexLoader.h"
#include "Vortex.h"
#include "VortexSprite.h"

class VortexButton
{
public:
	VortexButton(int x, int y, int w, int h, std::string imagePath, std::string title, Vortex * gameEngine);
	~VortexButton();

	void update(float delta);

	bool hitPoint(sf::Vector2f point);
	bool hitPoint(int x, int y);

	bool VortexButton::mouseOver();

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

