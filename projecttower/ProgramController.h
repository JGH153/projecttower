#pragma once

#include <SFML\Window.hpp>
#include <SFML\Graphics.hpp>
#include <vector>
#include <queue>
#include <iostream>
#include <string>
#include <sstream>

#include "Vortex.h"
#include "MenuController.h"
#include "GameController.h"
#include "SubController.h"

class ProgramController
{
public:
	ProgramController(Vortex * gameEngine, Renderer * renderer);
	~ProgramController();

	void update();

private:
	Vortex * gameEngine;
	std::vector<SubController*> subControllers;
	int activeSubController;
};

