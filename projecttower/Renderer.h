#pragma once

#include <SFML\Window.hpp>
#include <SFML\Graphics.hpp>
#include <iostream>

#include "Unit.h"
#include "SubController.h"
#include "GlobalDefines.h"

class SubController;

class Renderer
{
public:
	Renderer(int screenWidth, int screenHeight, float fps, std::string windowName, std::string iconPath, bool fullscreen);
	~Renderer();

	void drawClear();
	void drawDisplay();
	
//	SubController * currentSubCotroller = nullptr;


	void doRenderLoop();

	//TODO: Have an entity list containing all towers and units, and a list with GUI elements
	std::vector<RenderObject *> renderObjectsVector;

	std::vector<VortexSprite> mapTiles;
	std::vector <Unit *> unitList;
	VortexSprite bgSprite;
	
	sf::RenderWindow * getWindow();
	bool loaded;


	//SubController * currentRenderSubController = nullptr;
	SubController * topLevelRenderController = nullptr;

private:
	sf::RenderWindow * mainWindow;
	std::string windowName;
	float fps;

	std::vector<RenderData> renderList;
};

