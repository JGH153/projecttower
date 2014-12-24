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
#include "ServerbrowserController.h"
#include "LoadingController.h"

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

	void initController();
	void loadAssets();


private:
	
	std::vector<SubController*> subControllers;
	int activeSubController;

	int getIndexOfController(int controllerID);
	void setNewActiveController(int controllerID);


};

