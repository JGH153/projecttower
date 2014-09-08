#pragma once

#include <SFML\Window.hpp>
#include <SFML\Graphics.hpp>
#include <vector>
#include <iostream>
#include <string>
#include <sstream>

#include "Vortex.h"
#include "MenuController.h"
#include "GameController.h"

class ProgramController
{
public:
	ProgramController(Vortex * gameEngine);
	~ProgramController();

	void update();

private:
	Vortex * gameEngine;

	MenuController * menuController; // activeSubControllerID = 1
	GameController * gameController; // = 2

	int activeSubControllerID = 0;

};

