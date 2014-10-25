#pragma once

#include <vector>
#include <iostream>

#define MENU_CONTROLLER_ID 0
#define GAME_CONTROLLER_ID 1

#include "Vortex.h"
#include "RenderObject.h"



class SubController{
protected:
	Vortex * gameEngine;
	int nextControllerID;

	//std::vector<RenderObject *> renderObjects;

	SubController * currentRenderController = nullptr;

public:
	SubController(Vortex * gameEngine);
	~SubController();
	virtual void update();
	virtual std::vector<VortexSprite *> getRenderSprites() = 0;
	//virtual std::vector<RenderObject *> getRenderObjectList() = 0;
	int getNextControllerID();
	void setNextControllerID(int ID);

	SubController * getCurrentRenderController();
};

