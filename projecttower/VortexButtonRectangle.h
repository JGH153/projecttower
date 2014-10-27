#pragma once
#include "VortexButton.h"
class VortexButtonRectangle : public VortexButton
{
public:
	VortexButtonRectangle(double x, double y, int w, int h, std::string imagePath, Vortex * gameEngine);
	~VortexButtonRectangle();

	bool hitPoint(sf::Vector2f point);
	bool hitPoint(double x, double y);
	bool buttonClicked();

	void update();
	std::vector<sf::Drawable *> getRenderDrawable();

};

