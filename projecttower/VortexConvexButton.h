#pragma once
#include <SFML\Window.hpp>
#include <SFML\Graphics.hpp>
#include <vector>
#include <iostream>

#include "Vortex.h"

class VortexConvexButton
{
public:
	VortexConvexButton(std::vector<sf::Vector2f> vertices, std::string idleImage, std::string hoverImage, std::string title, Vortex * gameEngine);
	~VortexConvexButton();

	void setPosition(double x, double y);
	sf::Vector2f getPosition();

	void update(float delta);

	bool hitPoint(sf::Vector2f point);
	bool hitPoint(float x, float y);
	int isLeft(sf::Vector2f P0, sf::Vector2f P1, sf::Vector2f P2);

	bool mouseOver();

	void executeButton();

private:

	std::string title;
	std::string tooltip;
	sf::Font font;
	sf::Text text;
	sf::ConvexShape shape;
	sf::Texture *idleImage;
	sf::Texture *hoverImage;

	Vortex * gameEngine;

	bool mouseOverButton;
	bool buttonPressed;
};

