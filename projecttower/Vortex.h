#pragma once

#include <SFML\Window.hpp>
#include <SFML\Graphics.hpp>
#include <vector>
#include <iostream>


//The game engine, uning SFML
class Vortex {
public:
	Vortex();
	~Vortex();

	void initVortex(int screenWidth, int screenHeight, std::string windowName);

	void drawClear();
	void drawToScreen(sf::Sprite sprite);
	void drawToScreen(sf::Sprite * sprite);
	void drawToScreen(sf::CircleShape);
	void drawDisplay();

	sf::Sprite loadImageToSprite(std::string path);
	sf::Texture loadImageToTexture(std::string path);

	void setSpriteSize(sf::Sprite * sprite, double x, double y);

	void regEvents();
	std::vector<sf::Event> getWindowEvents();

	void closeApplication();

	bool running;

private:

	std::vector<sf::Event> eventList;

	std::string windowName;
	sf::RenderWindow * mainWindow;

	

};

