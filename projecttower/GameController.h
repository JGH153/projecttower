#pragma once

#include <SFML\Window.hpp>
#include <SFML\Graphics.hpp>
#include <vector>
#include <iostream>
#include <string>
#include <sstream>
#include <mutex> // std::mutex

#include "Vortex.h"

#include "Tower.h"
#include "BasicUnit.h"
#include "SubController.h"
#include "VortexConvexButton.h"
#include "VortexButtonRectangle.h"

#include "GameGuiController.h"
#include "GlobalDefines.h"

class GameController : public SubController
{
public:
	GameController(Vortex * gameEngine);
	~GameController();
	std::vector<Tower*> towers;
	std::vector<Unit*> units;

	GameGuiController * gameGuiController;
	//Renderer * renderer;
	

	void update();
	std::vector<sf::Drawable *> getDynamicRenderData();
	std::vector<sf::Drawable *> getStaticRenderData();

	//std::vector<RenderObject *> getRenderObjectList();
	
private:

	//void renderBG();
	//void renderTiles();

	VortexSprite bgSprite;

	std::vector<VortexSprite *> backgroundTextures;
	std::vector<VortexSprite *> mapTiles;


	std::vector <VortexConvexButton> buttonList;
	std::vector <VortexButton> rectButtonTest; //DEBUG: Delete if i forget
	std::vector <VortexButton *> someButtons; //DEBUG: Delete if i forget

	std::vector <Unit *> unitList;

	std::vector<RenderObject *> renderObjectsVector;

	std::mutex vectorMutex;



};

