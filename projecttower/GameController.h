#pragma once

#include <SFML\Window.hpp>
#include <SFML\Graphics.hpp>
#include <vector>
#include <iostream>
#include <string>
#include <sstream>
#include <mutex> // std::mutex

#include "Vortex.h"

#include "ArrowTower.h"
#include "CannonTower.h"
#include "IronmanUnit.h"
#include "BahamutUnit.h"
#include "SubController.h"
#include "VortexConvexButton.h"
#include "VortexButtonRectangle.h"
#include "MapTile.h"
#include "SelectionGizmo.h"

#include "GameGuiController.h"
#include "GlobalDefines.h"

class GameController : public SubController
{
public:
	GameController(Vortex * gameEngine, int controllerID);
	~GameController();
	//std::vector<Tower*> towers;
	//std::vector<Unit*> units;

	GameGuiController * gameGuiController;
	//Renderer * renderer;
	

	void update();
	std::vector<std::vector<sf::Drawable *>> getDynamicRenderData();
	std::vector<std::vector<sf::Drawable *>> getStaticRenderData();
	sf::View getView();
	std::vector<SubController *> getChildControllers();
	bool unitOnTile(int x, int y);
	void handlePlayerTowerAction();
	void moveViewport();
	bool calculateZoom(bool zoomOut);

	//std::vector<RenderObject *> getRenderObjectList();

	void preloadAssets();
	std::vector<std::vector<int>> makeNavigationMapFromTileMap(std::vector<std::vector<MapTile *>> map);
	sf::Vector2i worldCoordinateToMapTileCoordinate(sf::Vector2i coord);
private:

	sf::Clock unitSpawnTimer;
	int spawnDelayMS;

	//void renderBG();
	//void renderTiles();

	VortexSprite bgSprite;
	float gridTileSize;
	//int tileType[GAMEMAPSIZEX][GAMEMAPSIZEY];
	std::vector<VortexSprite *> backgroundTextures;
	//std::vector<VortexSprite *> mapTiles;


	std::vector<std::vector<MapTile *>> mapGroundTile;

	
	sf::Vector2i previousMousePos;

	float zoomRate;
	float viewRelativeSizeX;
	float viewRelativeSizeY;

	int viewWidth;
	int viewHeight;

	sf::Vector2i playerUnitSpawnPos;
	sf::Vector2i playerUnitTargetPos;

	sf::Vector2i enemyPlayerUnitSpawnPos;
	sf::Vector2i enemyPlayerUnitTargetPos;

	bool playerLost;
	bool groundTilesChanged;
	bool towerRemoved;
	bool building;
	bool towerUnderMouse;
	
	VortexSprite * towerBuildSprite;
	Tower* selectedTower;
	SelectionGizmo* selectionGizmo;

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
	//std::vector <Projectile*> projectileList;
	std::vector <VortexParticleSystem*> particleList;
	

	std::vector<RenderObject *> renderObjectsVector;

	
	void doGameControllerStatup();
	void readNetworkPackets();

	bool gameControllerFistRunDone;

	bool multiplayerMode;
	int playerID; // 0 = left/server, 1 = right/client

	void spawnNewUnit(int ID, bool toOponent);
	void sendSpawnUnitPacket(int unitID);

	void spawnNewTower(int towerID, int gridX, int gridY);// 0 = arrowTow
	void sendSpawnNewTowerPacket(int towerID, int gridX, int gridY); // 0 = arrowTow

	bool onMyMapSide(int gridX, int gridY);

};

