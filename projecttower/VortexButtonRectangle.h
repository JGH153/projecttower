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
	VortexButtonRectangle(double x, double y, int w, int h, std::string imagePath, std::string title, Vortex * gameEngine, int opacity);
	VortexButtonRectangle(double x, double y, int w, int h, std::string imagePath, std::string title, Vortex * gameEngine, int opacity, std::string tooltipText);
	~VortexButtonRectangle();

	
	void setIdleImage(sf::Texture * newImage);
	void setHoverImage(sf::Texture * newImage);
	void setPressedImage(sf::Texture * newImage);

	void setIdleImage(std::string imagePath);
	void setHoverImage(std::string imagePath);
	void setPressedImage(std::string imagePath);


	void setPosition(sf::Vector2f newPosition);
	void setPosition(double x, double y);

	bool hitPoint(sf::Vector2f point);
	bool hitPoint(double x, double y);

	void update();
	std::vector<sf::Drawable *> getRenderDrawable();
	std::vector<sf::Drawable *> getTooltipDrawable();
	bool isPressed;
	bool hovering;

private:
	
	

	std::string title;
	VortexText text;
	sf::Font font;
	
	sf::Texture * idleImage;
	sf::Texture * hoverImage;
	sf::Texture * pressedImage;

};

