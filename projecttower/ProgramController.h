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
#include "GlobalDefines.h"

class ProgramController : public SubController
{
public:
	ProgramController(Vortex * gameEngine);
	~ProgramController();

	void update();
	std::vector<std::vector<sf::Drawable *>> getDynamicRenderData();
	std::vector<std::vector<sf::Drawable *>> getStaticRenderData();
	sf::View getView();


private:
	Vortex * gameEngine;
	std::vector<SubController*> subControllers;
	int activeSubController;


};

