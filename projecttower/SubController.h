#pragma once

#include <vector>
#include <iostream>

#define MENU_CONTROLLER_ID 0
#define GAME_CONTROLLER_ID 1

#include "Vortex.h"
#include "RenderObject.h"
#include "GlobalDefines.h"



class SubController{
protected:
	Vortex * gameEngine;
	int nextControllerID;

	//std::vector<RenderObject *> renderObjects;

	SubController * currentRenderController = nullptr;

public:
	SubController(Vortex * gameEngine, int controllerID);
	~SubController();
	virtual void update();
	virtual std::vector<std::vector<sf::Drawable *>> getDynamicRenderData() = 0;
	virtual std::vector<std::vector<sf::Drawable *>> getStaticRenderData() = 0;
	//virtual std::vector<RenderObject *> getRenderObjectList() = 0;
	int getNextControllerID();
	void setNextControllerID(int ID);

	bool updateStaticRenderData;

	SubController * getCurrentRenderController();
};

