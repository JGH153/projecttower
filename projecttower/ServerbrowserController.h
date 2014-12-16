#pragma once

#include <SFML\Window.hpp>
#include <SFML\Graphics.hpp>
#include <vector>
#include <iostream>
#include <string>
#include <sstream>

#include "Vortex.h"
#include "SubController.h"
#include "BasicUnit.h"
#include "VortexButtonRectangle.h"
#include "VortexConvexButton.h"
#include "VortexText.h"
#include "VortexNetwork.h"

class ServerbrowserController : public SubController {

public:
	ServerbrowserController(Vortex * gameEngine, int controllerID);
	~ServerbrowserController();

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
	VortexButtonRectangle * startSearchButton;
	VortexButtonRectangle * quitGameButton;
	VortexSprite * backgroundImage;

	VortexText * serverbrowserTittle;

	bool startedBroadcastSearch;

	bool doMultiplayer;

};

