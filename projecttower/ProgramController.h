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
#include "NetworkGameClient.h"
#include "NetworkGameServer.h"
#include "SubController.h"
#include "GlobalDefines.h"

class ProgramController : public SubController
{
public:
	ProgramController(Vortex * gameEngine, int controllerID);
	~ProgramController();

	void update();
	std::vector<std::vector<sf::Drawable *>> getDynamicRenderData();
	std::vector<std::vector<sf::Drawable *>> getStaticRenderData();
	sf::View getView();
	std::vector<SubController *> getChildControllers();

	void preloadAssets();


private:
	Vortex * gameEngine;
	std::vector<SubController*> subControllers;
	int activeSubController;


};

