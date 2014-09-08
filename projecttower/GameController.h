#pragma once

#include <SFML\Window.hpp>
#include <SFML\Graphics.hpp>
#include <vector>
#include <iostream>
#include <string>
#include <sstream>

#include "Vortex.h"

class GameController
{
public:
	GameController(Vortex * gameEngine);
	~GameController();

	void update();

private:
	Vortex * gameEngine;
};

