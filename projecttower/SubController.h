#pragma once

#include "Vortex.h"
class SubController
{
protected:
	Vortex * gameEngine;
	int nextControllerID;
public:
	SubController();
	~SubController();
	virtual void update();
	int getNextControllerID();
	void setNextControllerID(int ID);
};

