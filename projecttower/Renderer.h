#pragma once

#include <SFML\Window.hpp>
#include <SFML\Graphics.hpp>
#include <iostream>

#include "Unit.h"
#include "SubController.h"
#include "GlobalDefines.h"
#include "VortexText.h"

class SubController;

class Renderer
{
public:
	Renderer::Renderer(Vortex * gameEngine, int screenWidth, int screenHeight, float fps, std::string windowName, std::string iconPath, bool fullscreen);
	~Renderer();

	void drawClear();
	void drawDisplay();
	
//	SubController * currentSubCotroller = nullptr;


	void renderMainLoop();

	void doRenderLoop();

	//TODO: Have an entity list containing all towers and units, and a list with GUI elements
	std::vector<RenderObject *> renderObjectsVector;

	//std::vector<VortexSprite> mapTiles;
	//std::vector <Unit *> unitList;
	VortexSprite bgSprite;
	
	void handleStaticBackground();
	sf::RenderWindow * getWindow();
	bool loaded;

	bool renderThreadOnline;


	//SubController * currentRenderSubController = nullptr;
	SubController * topLevelRenderController = nullptr;

private:

	Vortex * gameEngine;

	sf::RenderWindow * mainWindow;
	std::string windowName;
	float fps;

	//[each subController (stating from main at 0][draw layer][layer Drawable list]
	std::vector<std::vector<std::vector<sf::Drawable *>>> staticRenderList;

	//temp values:

	int screenWidth, screenHeight;
	std::string iconPath;
	bool fullscreen;

};

