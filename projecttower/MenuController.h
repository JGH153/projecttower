#pragma once

#include <SFML\Window.hpp>
#include <SFML\Graphics.hpp>
#include <vector>
#include <iostream>
#include <string>
#include <sstream>

#include "Vortex.h"

class MenuController{

public:
	MenuController(Vortex * gameEngine);
	~MenuController();

	void update();

	int programControllerNewActionID = 0; // 2 = game

private:
	Vortex * gameEngine;

	VortexSprite testSprite;

};

