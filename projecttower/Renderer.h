#pragma once

#include <SFML\Window.hpp>
#include <SFML\Graphics.hpp>
#include <iostream>

#include "Unit.h"
#include "GlobalDefines.h"


class Renderer
{
public:
	Renderer(int screenWidth, int screenHeight, float fps, std::string windowName, std::string iconPath, bool fullscreen);
	~Renderer();

	void drawClear();
	void drawDisplay();
	

	void renderBG();
	void renderTiles();
	void renderEntities();

	//TODO: Have an entity list containing all towers and units, and a list with GUI elements
	std::vector<VortexSprite> mapTiles;
	std::vector <Unit *> unitList;
	VortexSprite bgSprite;
	
	sf::RenderWindow * getWindow();
	bool loaded;

private:
	sf::RenderWindow * mainWindow;
	std::string windowName;
	float fps;
};

