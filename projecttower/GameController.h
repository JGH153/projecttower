#pragma once

#include <SFML\Window.hpp>
#include <SFML\Graphics.hpp>
#include <vector>
#include <iostream>
#include <string>
#include <sstream>
#include <mutex> // std::mutex

#include "Vortex.h"

#include "BasicTower.h"
#include "BasicUnit.h"
#include "SubController.h"
#include "VortexConvexButton.h"
#include "VortexButtonRectangle.h"

#include "GameGuiController.h"
#include "GlobalDefines.h"

#define TILE_TYPE_GRASS 0
#define TILE_TYPE_DIRT 1
#define TILE_TYPE_WATER 2
#define TILE_TYPE_WALL 3
#define TILE_TYPE_CAVE 4
#define TILE_TYPE_TOWER 5

class GameController : public SubController
{
public:
	GameController(Vortex * gameEngine, int controllerID);
	~GameController();
	std::vector<Tower*> towers;
	std::vector<Unit*> units;

	GameGuiController * gameGuiController;
	//Renderer * renderer;
	

	void update();
	std::vector<std::vector<sf::Drawable *>> getDynamicRenderData();
	std::vector<std::vector<sf::Drawable *>> getStaticRenderData();
	sf::View getView();
	std::vector<SubController *> getChildControllers();

	//std::vector<RenderObject *> getRenderObjectList();
	
private:

	//void renderBG();
	//void renderTiles();

	VortexSprite bgSprite;
	float gridTileSize;
	int tileType[GAMEMAPSIZEX][GAMEMAPSIZEY];
	std::vector<VortexSprite *> backgroundTextures;
	std::vector<VortexSprite *> mapTiles;
	
	sf::Vector2i previousMousePos;

	float zoomRate;
	float viewRelativeSizeX;
	float viewRelativeSizeY;

	int viewWidth;
	int viewHeight;

	bool building;
	bool towerUnderMouse;
	VortexSprite * towerBuildSprite;

	void updateGhostBuildingSprite(sf::Vector2f mousePosView);
	void lerpZoom(float t); //Linear interpolation
	float lerpTime;
	bool zooming;
	sf::FloatRect zoomEndPoint;

	std::vector <VortexButton> buttonList;
	std::vector <VortexButton> rectButtonTest; //DEBUG: Delete if i forget
	std::vector <VortexButton *> someButtons; //DEBUG: Delete if i forget

	std::vector <Unit *> unitList;
	std::vector <Tower *> towerList;
	

	std::vector<RenderObject *> renderObjectsVector;

	std::mutex vectorMutex;

	

};

