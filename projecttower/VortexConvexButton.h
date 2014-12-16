#pragma once
#include <SFML\Window.hpp>
#include <SFML\Graphics.hpp>
#include <vector>
#include <iostream>

#include "Vortex.h"
#include "VortexButton.h"

class VortexConvexButton : public VortexButton
{
public:
	VortexConvexButton(int x, int y, std::vector<sf::Vector2f> vertices, std::string imageSource, std::string title, Vortex * gameEngine);
	~VortexConvexButton();

	void killYourself();


	void setPosition(sf::Vector2f newPosition);
	void setPosition(double x, double y);

	bool hitPoint(sf::Vector2f point);
	bool hitPoint(double x, double y);

	void update();
	std::vector<sf::Drawable *> getRenderDrawable();

	int isLeft(sf::Vector2f P0, sf::Vector2f P1, sf::Vector2f P2);
private:
	sf::ConvexShape shape;
	std::string title;
	VortexText text;
	sf::Font font;
	VortexSprite * image;


};
