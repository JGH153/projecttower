#pragma once

#include <SFML\Window.hpp>
#include <SFML\Graphics.hpp>
#include <vector>
#include <iostream>
#include <string>
#include <sstream>

#include "Vortex.h"
#include "Tower.h"

#include "GameGuiController.h"

class GameController
{
public:
	GameController(Vortex * gameEngine);
	~GameController();
	std::vector<Tower*> towers;
	std::vector<Unit*> units;

	GameGuiController * gameGuiController;

	

	void update();
	
private:

	void renderBG();
	void renderTiles();

	Vortex * gameEngine;

	VortexSprite bgSprite;

	std::vector<VortexSprite> mapTiles;

};

