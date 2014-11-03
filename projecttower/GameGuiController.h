#pragma once


#include <SFML\Window.hpp>
#include <SFML\Graphics.hpp>
#include <SFML\Audio.hpp>
#include <vector>
#include <iostream>

#include "Vortex.h"
#include "SubController.h"
#include "VortexButtonRectangle.h"
#include "VortexConvexButton.h"

class GameGuiController : public SubController{
public:
	GameGuiController(Vortex * gameEngine, int controllerID);
	~GameGuiController();

	void update();
	std::vector<std::vector<sf::Drawable *>> getDynamicRenderData();
	std::vector<std::vector<sf::Drawable *>> getStaticRenderData();
	sf::View getView();
	std::vector<SubController *> getChildControllers();

	bool building;

	//std::vector<RenderObject *> getRenderObjectList();

	bool mouseOverSomeButton(sf::View resetToView);
	

private:
	std::mutex guiMutex;
	std::vector<RenderObject *> guiObjects;
	VortexButtonRectangle * buildButton;
};

