#pragma once

#include <SFML\Window.hpp>
#include <SFML\Graphics.hpp>
#include <vector>
#include <iostream>
#include <string>
#include <sstream>

#include "Vortex.h"
#include "SubController.h"
#include "IronmanUnit.h"
#include "VortexButtonRectangle.h"
#include "VortexConvexButton.h"

class MenuController : public SubController {

public:
	MenuController(Vortex * gameEngine, int controllerID);
	~MenuController();

	void update();
	std::vector<std::vector<sf::Drawable *>> getDynamicRenderData();
	std::vector<std::vector<sf::Drawable *>> getStaticRenderData();
	sf::View getView();
	std::vector<SubController *> getChildControllers();

	//std::vector<RenderObject *> getRenderObjectList();

	void preloadAssets();

private:
	std::mutex guiMutex;
	std::vector<RenderObject *> guiObjects;
	VortexButtonRectangle * startSingelplayerGameButton;
	VortexButtonRectangle * startMultiplayerGameButton;
	VortexButtonRectangle * quitGameButton;
	VortexSprite * backgroundImage;

	bool doMultiplayer;

};

