#pragma once

#include <SFML\Window.hpp>
#include <SFML\Graphics.hpp>
#include <vector>
#include <iostream>
#include <string>
#include <sstream>

#include "Vortex.h"

#include "Tower.h"
#include "BasicUnit.h"
#include "SubController.h"
#include "VortexConvexButton.h"
#include "Renderer.h"

#include "GameGuiController.h"

class GameController : public SubController
{
public:
	GameController(Vortex * gameEngine, Renderer * renderer);
	~GameController();
	std::vector<Tower*> towers;
	std::vector<Unit*> units;

	GameGuiController * gameGuiController;
	Renderer * renderer;
	

	void update();
	void render();

	std::vector<RenderObject *> getRenderObjectList();
	
private:

	//void renderBG();
	//void renderTiles();

	VortexSprite bgSprite;

	std::vector<VortexSprite> mapTiles;


	std::vector <VortexConvexButton> buttonList;
	std::vector <VortexButton> rectButtonTest; //DEBUG: Delete if i forget

	std::vector <Unit *> unitList;

	std::vector<RenderObject *> renderObjectsVector;


};

