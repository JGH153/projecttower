#pragma once

#include <vector>
#include <iostream>

#define LOADING_CONTROLLER_ID 1
#define MENU_CONTROLLER_ID 2
#define GAME_CONTROLLER_ID 3
#define SERVERBROWSER_CONTROLLER_ID 4

#include "Vortex.h"
#include "RenderObject.h"
#include "GlobalDefines.h"



class SubController{
protected:
	Vortex * gameEngine;
	int nextControllerID;
	int myControllerID;

	sf::View gameView;

	//std::vector<RenderObject *> renderObjects;

	SubController * currentRenderController = nullptr;

	//sub controllers of current that are goint to be updated/renderd too (afther the main)
	std::vector<SubController *> childControllers;

public:
	SubController(Vortex * gameEngine, int controllerID);
	~SubController();
	virtual void update();
	virtual std::vector<std::vector<sf::Drawable *>> getDynamicRenderData() = 0;
	virtual std::vector<std::vector<sf::Drawable *>> getStaticRenderData() = 0;
	virtual sf::View getView() = 0;
	virtual std::vector<SubController *> getChildControllers() = 0;
	//virtual std::vector<RenderObject *> getRenderObjectList() = 0;
	int getNextControllerID();
	void setNextControllerID(int ID);
	int getMyControllerID();

	

	bool updateStaticRenderData;
	bool requestingUpdateStaticRenderData();

	bool controllerInitialized;
	bool controllerAssetsLoaded;
	//void startController();
	//both of these functions needs to be called before the first call to update(), and they need tto be called in order:
	virtual void initController() = 0;
	virtual void loadAssets() = 0;
	
	//controller is replaced by another (but NOT detroyed), "looses focus"
	virtual void onStop() = 0;
	//controller gets focus, called each time before first update
	virtual void onStart() = 0;

	SubController * getCurrentRenderController();
};

