#pragma once

#include <SFML\Window.hpp>
#include <SFML\Graphics.hpp>
#include <vector>
#include <iostream>
#include <string>
#include <sstream>

#include "Vortex.h"
#include "VortexText.h"
#include "SubController.h"
#include "IronmanUnit.h"
#include "VortexButtonRectangle.h"
#include "VortexConvexButton.h"

class LoadingController : public SubController {

public:
	LoadingController(Vortex * gameEngine, int controllerID);
	~LoadingController();

	void update();
	std::vector<std::vector<sf::Drawable *>> getDynamicRenderData();
	std::vector<std::vector<sf::Drawable *>> getStaticRenderData();
	sf::View getView();
	std::vector<SubController *> getChildControllers();


	void initController();
	void loadAssets();

	void setTotalToLoad(int total);
	void setNewProgress(int numDone);

private:
	std::mutex guiMutex;
	std::vector<RenderObject *> guiObjects;
	
	VortexSprite * backgroundImage;

	VortexText * loadingText;

	int totalLoading;
	int numLoadingDone;

	



};



