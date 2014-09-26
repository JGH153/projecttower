#pragma once

#define MENU_CONTROLLER_ID 0
#define GAME_CONTROLLER_ID 1

#include "Vortex.h"
#include "Renderer.h"

class SubController{
protected:
	Vortex * gameEngine;
	int nextControllerID;
public:
	SubController(Vortex * gameEngine);
	~SubController();
	virtual void update();
	int getNextControllerID();
	void setNextControllerID(int ID);
};

