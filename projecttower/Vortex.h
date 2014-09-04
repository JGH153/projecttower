#pragma once

#include "SpriteObject.h"
#include "TexturedObject.h"
#include "VortexParticleSystem.h"
#include <SFML\Window.hpp>
#include <vector>
#include <iostream>


//The game engine, uning SFML
class Vortex {
public:
	Vortex();
	~Vortex();

	void initVortex(int screenWidth, int screenHeight, std::string windowName, std::string iconPath, std::string defaultFontPath);

	void drawClear();
	void drawToScreen(sf::Sprite sprite);
	void drawToScreen(sf::Sprite * sprite);
	void drawToScreen(sf::CircleShape);
	void drawToScreen(VortexParticleSystem particles);
	void drawToScreen(sf::Text text);
	void drawDisplay();

	sf::Vector2i getMousePosition();
	sf::Vector2f getMapPixelToCoords(sf::Vector2i point);

	sf::Sprite loadImageToSprite(std::string path);
	sf::Texture loadImageToTexture(std::string path);
	sf::Font loadFont(std::string path); //returns fornt ID

	sf::Font getDefaultFont();

	void setSpriteSize(sf::Sprite * sprite, double x, double y);

	void regEvents();
	std::vector<sf::Event> getWindowEvents();

	void closeApplication();
	sf::Texture checkForBackupImage(std::string path);

	bool running;

private:

	std::vector<sf::Event> eventList;

	std::string windowName;
	sf::RenderWindow * mainWindow;

	sf::Font defaultFont;

	

};

