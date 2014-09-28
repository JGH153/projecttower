#pragma once

#define MENU_CONTROLLER_ID 0
#define GAME_CONTROLLER_ID 1

#include "Vortex.h"
#include "Renderer.h"
#include "RenderObject.h"


class SubController{
protected:
	Vortex * gameEngine;
	int nextControllerID;

	//std::vector<RenderObject *> renderObjects;

public:
	SubController(Vortex * gameEngine);
	~SubController();
	virtual void update();
	//virtual std::vector<RenderObject *> getRenderObjectList() = 0;
	int getNextControllerID();
	void setNextControllerID(int ID);
};

