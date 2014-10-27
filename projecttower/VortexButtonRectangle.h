#pragma once
#include <SFML\Window.hpp>
#include <SFML\Graphics.hpp>
#include <vector>
#include <iostream>

#include "Vortex.h"
#include "VortexButton.h"

class VortexButtonRectangle : public VortexButton
{
public:
	VortexButtonRectangle(double x, double y, int w, int h, std::string imagePath, std::string title, Vortex * gameEngine);
	~VortexButtonRectangle();

	void setPosition(sf::Vector2f newPosition);
	void setPosition(double x, double y);

	bool hitPoint(sf::Vector2f point);
	bool hitPoint(double x, double y);

	void update();
	std::vector<sf::Drawable *> getRenderDrawable();


};

