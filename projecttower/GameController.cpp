#include "GameController.h"


GameController::GameController(Vortex * gameEngine, int controllerID) : SubController(gameEngine, controllerID) {

	gameGuiController = new GameGuiController(gameEngine, 1);
	childControllers.push_back(gameGuiController);

	float forestTileSize = 50;

	for (int x = 0; x < (gameEngine->getWindowSize().x / forestTileSize); x++) {
		for (int y = 0; y < (gameEngine->getWindowSize().y / forestTileSize); y++) {

			sf::Texture * texImageTile;
			texImageTile = gameEngine->loadImageToTexture("Graphics/Textures/foresttile.png");
			VortexSprite * tempSprite = new VortexSprite(*texImageTile);
			tempSprite->setPosition(x * forestTileSize, y * forestTileSize);
			tempSprite->setSize(forestTileSize, forestTileSize);
			backgroundTextures.push_back(tempSprite);


		}
	}
	sf::Texture * tempBuildTexture = gameEngine->loadImageToTexture("Graphics/Towers/NormalReducedCanvas.png");
	towerBuildSprite = new VortexSprite(gameEngine, "Graphics/Towers/NormalReducedCanvas.png", 0, 0, tempBuildTexture->getSize().x / 2.1, tempBuildTexture->getSize().y / 2.1);
	towerBuildSprite->setColor(UNABLETOBUILD); //A bit red and transparent = cannot build here

	sf::Texture * texImage = gameEngine->loadImageToTexture("Graphics/Textures/foresttile.png");
	texImage->setRepeated(true);
	texImage->getSize();
	VortexSprite temp(*texImage);
	bgSprite = temp;
	bgSprite.setPosition(0, 0);

	gridTileSize = 25;

	spawnDelayMS = 2000;

	playerUnitSpawnPos = sf::Vector2i(23 * gridTileSize, 13 * gridTileSize);
	playerUnitTargetPos = sf::Vector2i(0, 13 * gridTileSize);
	
	groundTilesChanged = false;
	playerLost = false;
	towerRemoved = false;
		
		
	for (int x = 0; x < GAMEMAPSIZEX; x++) {

		std::vector<MapTile *> tempVec;

		for (int y = 0; y < GAMEMAPSIZEY; y++) {

			int ID = 0;

			if (x == (GAMEMAPSIZEX / 2)) {
				ID = TileTypes::wall;
			}
			else if ((x == (GAMEMAPSIZEX / 2) - 1 || x == (GAMEMAPSIZEX / 2) + 1) && (y == (GAMEMAPSIZEY / 2) - 1 || y == (GAMEMAPSIZEY / 2) + 1)) {
				ID = TileTypes::wall;
			}
			else if ((x == (GAMEMAPSIZEX / 2) - 1 || x == (GAMEMAPSIZEX / 2) + 1) && (y == (GAMEMAPSIZEY / 2) || y == (GAMEMAPSIZEY / 2))) {
				ID = TileTypes::cave;
			}
			else if ((x <= (GAMEMAPSIZEX / 10) - 1 || x >= (GAMEMAPSIZEX - (GAMEMAPSIZEX / 10)) || ((x == GAMEMAPSIZEX / 2 - 2) || (x == GAMEMAPSIZEX / 2 + 2) || (x <= GAMEMAPSIZEX / 10) || x >= (GAMEMAPSIZEX - (GAMEMAPSIZEX / 10) - 1)) && (y == GAMEMAPSIZEY / 2))) {
				ID = TileTypes::dirt;
			}else {
				ID = TileTypes::grass;
			}
			if ((x == (GAMEMAPSIZEX / 10) - 1 || x == (GAMEMAPSIZEX - (GAMEMAPSIZEX / 10))) && y != GAMEMAPSIZEY / 2) {
				ID = TileTypes::wall;
			}
			if (y < (GAMEMAPSIZEY / 6) || y >= (GAMEMAPSIZEY) - (GAMEMAPSIZEY / 6)) {
				ID = TileTypes::water;
			}

			tempVec.push_back(new MapTile(gameEngine, ID, x * gridTileSize, y * gridTileSize, gridTileSize, gridTileSize));

		}

		mapGroundTile.push_back(tempVec);

	}

	std::cout << mapGroundTile.size() << " " << mapGroundTile[0].size() << std::endl;



	preloadAssets();

//	std::vector<std::vector<int>> navigationMap;
//	navigationMap = makeNavigationMapFromTileMap(mapGroundTile);
//	sf::Vector2i targetInMapCoord = worldCoordinateToMapTileCoordinate(playerUnitTargetPos);
//	gameEngine->pathFinder->breadthFirstDirectionMap = gameEngine->pathFinder->makeBreadthFirstDirectionMap(navigationMap, targetInMapCoord, DIR_WEST);


	//set view size relative to org window size
	viewRelativeSizeX = 1.0f;
	viewRelativeSizeY = 1.0f;
	zoomRate = 1.15f;

	viewWidth = WINDOWSIZEX / viewRelativeSizeX; ///2
	viewHeight = WINDOWSIZEY / viewRelativeSizeY; ///2

	//set view to center
	sf::View view(sf::FloatRect(((WINDOWSIZEX / 2) - (viewWidth / 2)), ((WINDOWSIZEY / 2) - (viewHeight / 2)), viewWidth, viewHeight));
	gameView = view;

	towerUnderMouse = false;
	zoomEndPoint = sf::FloatRect(0.f, 0.f, 0.f, 0.f);
	selectionGizmo = new SelectionGizmo(gameEngine, 0, 0);


	gameControllerFistRunDone = false;
	multiplayerMode = false;
	playerID = 0;
	
	effectsHandler = new EffectsHandler(gameEngine);






	sideTextMe = new VortexText("Your Side", *gameEngine->loadFont("Fonts/arial.ttf"), 30);
	sideTextMe->setColor(sf::Color::Blue);
	sideTextMe->setStyle(sf::Text::Bold);

	sideTextOponent = new VortexText("Opponent Side", *gameEngine->loadFont("Fonts/arial.ttf"), 30);
	sideTextOponent->setColor(sf::Color::Red);
	sideTextOponent->setStyle(sf::Text::Bold);



	//sideTextMe->setPosition((float)WINDOWSIZEX / 4 - sideTextMe->getLocalBounds().width / 2, 50);
	//guiObjects.push_back(sideTextMe);




	
}


void GameController::preloadAssets() {

	std::vector<IronmanUnit *> preloadUnitList;
	gameEngine->groundTileListMutex.lock();
	preloadUnitList.push_back(new IronmanUnit(gameEngine, &mapGroundTile, playerUnitSpawnPos.x, playerUnitSpawnPos.y, playerUnitTargetPos.x, playerUnitTargetPos.y));
	gameEngine->groundTileListMutex.unlock();

	VortexAnimation* explosionEffect = new VortexAnimation(0, 0, 93, 100, 14, gameEngine);
	explosionEffect->asembleSpritesheetAnimation("Graphics/explosion_sheet.png", 93, 100, 10, 4);

	gameEngine->addRemovableObjectToList(explosionEffect);

	for (auto currentUnit : preloadUnitList) {
		gameEngine->addRemovableObjectToList(currentUnit);
	}
	preloadUnitList.clear();

}




sf::View GameController::getView() {
	return gameView;
}

struct EntitySortingStructDistance {

	bool operator() (Entity * a, Entity * b) {

		if (a->getPos().y + a->getSize().y < b->getPos().y + b->getSize().y) {
			return true;
		}
		else {
			return false;
		}

	}

} entitySortingStructDistanceDistance;

struct zIndexSort {

	bool operator() (RenderObject * a, RenderObject * b) {

		return(a->getZIndex() < b->getZIndex());
		
	}

} zIndexSortInstance;

std::vector<std::vector<sf::Drawable *>> GameController::getStaticRenderData() {
	
	std::vector<std::vector<sf::Drawable *>> renderSuperList;
	std::vector<sf::Drawable *> renderList;


	gameEngine->backgroundListMutex.lock();

	for (VortexSprite * currentRenderObj : backgroundTextures) {

		auto tempVector = currentRenderObj->getRenderDrawable();

		renderList.insert(renderList.end(), tempVector.begin(), tempVector.end());

	}

	gameEngine->backgroundListMutex.unlock();

	gameEngine->groundTileListMutex.lock();

	for (auto currentRenderList : mapGroundTile) {

		for (auto currentRenderObj : currentRenderList) {

			auto tempVector = currentRenderObj->getRenderDrawable();

			renderList.insert(renderList.end(), tempVector.begin(), tempVector.end());

		}

	}

	gameEngine->groundTileListMutex.unlock();




	for (auto currentRenderVector : guiObjects) {
		for (auto currentRenderObj : currentRenderVector->getRenderDrawable()) {
			renderList.push_back(currentRenderObj);
		}
	}



	renderSuperList.push_back(renderList);



	return renderSuperList;
}

std::vector<std::vector<sf::Drawable *>> GameController::getDynamicRenderData() {
	
	std::vector<std::vector<sf::Drawable *>> renderSuperList;

	std::vector<sf::Drawable *> renderList;

	

	gameEngine->renderObjectsListMutex.lock();

	for (auto currentRenderVector : renderObjectsVector) {

		auto tempVector = currentRenderVector->getRenderDrawable();

		renderList.insert(renderList.end(), tempVector.begin(), tempVector.end());

	}

	gameEngine->renderObjectsListMutex.unlock();

	gameEngine->towerListMutex.lock();

	std::vector<sf::Drawable *> renderProjectileList;

	//gameEngine->towerProjectileMutex.lock();
	for (auto currentRenderVector : towerList) {

		auto tempVector = currentRenderVector->getRenderDrawable();
		auto tempVectorProject = currentRenderVector->getProjectilesRenderDrawable();

		renderList.insert(renderList.end(), tempVector.begin(), tempVector.end());
		renderProjectileList.insert(renderProjectileList.end(), tempVectorProject.begin(), tempVectorProject.end());

	}

	renderList.insert(renderList.end(), renderProjectileList.begin(), renderProjectileList.end());

	//gameEngine->towerProjectileMutex.unlock();
	gameEngine->towerListMutex.unlock();


	gameEngine->unitListMutex.lock();
	for (auto currentRenderVector : unitList) {

		auto tempVector = currentRenderVector->getRenderDrawable();

		renderList.insert(renderList.end(), tempVector.begin(), tempVector.end());

	}
	gameEngine->unitListMutex.unlock();

	gameEngine->particleListMutex.lock();
	for (sf::Drawable* current : particleList) {
		renderList.push_back(current);
	}
	gameEngine->particleListMutex.unlock();


	gameEngine->effectsMutex.lock();
	for (auto currentDrawable : effectsHandler->getRenderDrawable()) {
		renderList.push_back(currentDrawable);
	}
	gameEngine->effectsMutex.unlock();


	gameEngine->builderSpriteMutex.lock();
	if (gameGuiController->building) {
		renderList.push_back(towerBuildSprite);
	}
	gameEngine->builderSpriteMutex.unlock();

	gameEngine->selectionSpriteMutex.lock();
	if (selectedTower != nullptr) {
		for (int i = 0; i < 4; i++) {
			renderList.push_back(selectionGizmo->selectionSprites[i]);
		}
	}
	gameEngine->selectionSpriteMutex.unlock();

	renderSuperList.push_back(renderList);


	//std::sort(renderSuperList.begin(), renderSuperList.end(), zIndexSortInstance);

	
	return renderSuperList;

}

GameController::~GameController(){
}


std::vector<SubController *> GameController::getChildControllers() {

	return childControllers;

}

bool GameController::unitOnTile(int x, int y) {
	int unitposX;
	int unitposY;

	std::lock_guard<std::mutex> unitLock(gameEngine->unitListMutex);

	for (auto *current : unitList) {
		unitposX = (current->getPos().x + (current->width / 2)) / gridTileSize;
		unitposY = (current->getPos().y + current->height) / gridTileSize;
		if (unitposX == x && unitposY == y) {
			return true;
		}
	}
	return false;
}

void GameController::updateGhostBuildingSprite(sf::Vector2f mousePosView) {
	int xpos = mousePosView.x / gridTileSize;
	int ypos = mousePosView.y / gridTileSize;

	//gameEngine->builderSpriteMutex.lock();
	towerBuildSprite->setPosition(xpos * gridTileSize, (ypos * gridTileSize) - (towerBuildSprite->getTextureRect().height / 5));

	//prevent out of vector error
	if (xpos >= mapGroundTile.size() || ypos >= mapGroundTile[0].size()) {
		return;
	}

	if (onMyMapSide(xpos, ypos) && mapGroundTile[xpos][ypos]->getTileTypeID() == TileTypes::grass && !unitOnTile(xpos, ypos) && (gameGuiController->getPlayerResources() >= 10)) {
		towerBuildSprite->setColor(ABLETOBUILD);
	}
	else {
		towerBuildSprite->setColor(UNABLETOBUILD);
	}
	//gameEngine->builderSpriteMutex.unlock();
}

void GameController::lerpZoom(float t) {
	if (t > 1.0f) {
		t = 1;
	}
	//If t = 1, then we are at the end point
	sf::FloatRect currentViewport;
	currentViewport.width = gameView.getSize().x;
	currentViewport.height = gameView.getSize().y;
	currentViewport.top = gameView.getCenter().y - gameView.getSize().y / 2;
	currentViewport.left = gameView.getCenter().x - gameView.getSize().x / 2;

	currentViewport.width = (1 - t) * currentViewport.width + t * zoomEndPoint.width;
	currentViewport.height = (1 - t) * currentViewport.height + t * zoomEndPoint.height;
	currentViewport.top = (1 - t) * currentViewport.top + t * zoomEndPoint.top;
	currentViewport.left = (1 - t) * currentViewport.left + t * zoomEndPoint.left;

	gameView.reset(currentViewport);
	
	if (t >= 1.0f) {
		zoomEndPoint.height = 0;
		zoomEndPoint.width = 0;
		zoomEndPoint.top = 0;
		zoomEndPoint.left = 0;
		zooming = false;
	}
}

void GameController::doGameControllerStatup() {

	//is multiplayer
	//std::cout << "1";
	if (gameEngine->networkHandler->connectedByTCP) {

		multiplayerMode = true;

		if (gameEngine->networkHandler->iAmTheServer) {

			playerID = 0;
			playerUnitSpawnPos = sf::Vector2i(23 * gridTileSize, 13 * gridTileSize);
			playerUnitTargetPos = sf::Vector2i(0 * gridTileSize, 13 * gridTileSize);

			enemyPlayerUnitSpawnPos = sf::Vector2i(27 * gridTileSize, 13 * gridTileSize);
			enemyPlayerUnitTargetPos = sf::Vector2i(47 * gridTileSize, 13 * gridTileSize);

		} else {

			playerID = 1;
			playerUnitSpawnPos = sf::Vector2i(27 * gridTileSize, 13 * gridTileSize);
			playerUnitTargetPos = sf::Vector2i(47 * gridTileSize, 13 * gridTileSize);

			enemyPlayerUnitSpawnPos = sf::Vector2i(23 * gridTileSize, 13 * gridTileSize);
			enemyPlayerUnitTargetPos = sf::Vector2i(0 * gridTileSize, 13 * gridTileSize);

		}


	}else{
		//is singelplayer


	}
	
	
	addPlayersSideTexts();
	recalculateNavigationMaps();

}

void GameController::addPlayersSideTexts() {


	if (gameEngine->networkHandler->connectedByTCP) {




		if (gameEngine->networkHandler->iAmTheServer) {


			sideTextMe->setPosition((float)WINDOWSIZEX / 4 - sideTextMe->getLocalBounds().width / 2, 50);
			sideTextOponent->setPosition((float)WINDOWSIZEX / 1.5f - sideTextMe->getLocalBounds().width / 2, 50);



		} else {

			sideTextOponent->setPosition((float)WINDOWSIZEX / 4 - sideTextMe->getLocalBounds().width / 2, 50);
			sideTextMe->setPosition((float)WINDOWSIZEX / 1.5f - sideTextMe->getLocalBounds().width / 2, 50);

		}

		guiObjects.push_back(sideTextMe);
		guiObjects.push_back(sideTextOponent);




	} else {

		sideTextMe->setPosition(WINDOWSIZEX / 4 - sideTextMe->getLocalBounds().width / 2, 50);
		guiObjects.push_back(sideTextMe);


	}


	updateStaticRenderData = true;


}


void GameController::readNetworkPackets() {

	

	if (gameEngine->networkHandler->newPacketsReady) {

		auto packets = gameEngine->networkHandler->getTcpPackets();

		for each (auto packet in packets) {

			sf::Int32 typeID;

			packet >> typeID;

			if (typeID == VortexNetwork::packetId_MainGameSpawnUnit) {

				sf::Int32 unitID;
				sf::Int32 sendToOponent;
				packet >> unitID >> sendToOponent;

				//std::cout << "PACKET RECIVED FOR UNIT: unitID:(" << unitID << ") Side: (" << sendToOponent << ")!!\n";

				if ((bool)sendToOponent == true)
					spawnNewUnit(unitID, true);
				else
					spawnNewUnit(unitID, false);



			} else if (typeID == VortexNetwork::packetId_MainGameSpawnTower) {

				sf::Int32 towerID;
				

				sf::Int32 gridX;
				sf::Int32 gridY;

				packet >> towerID >> gridX >> gridY;

				//std::cout << "PACKET RECIVED FOR towerID:(" << towerID << ")!!\n";

				spawnNewTower(towerID, gridX, gridY, true);



			} else if (typeID == VortexNetwork::packetId_MainGameLoss) {
				//Other player losses, i win!
				gameGuiController->playerWon = true;



			} else if (typeID == VortexNetwork::packetId_MainGameDeleteTower) {


				sf::Int32 gridX;
				sf::Int32 gridY;

				packet >> gridX >> gridY;

				//std::cout << "PACKET RECIVED FOR towerID:(" << towerID << ")!!\n";

				deleteTower(gridX, gridY);


			} else if (typeID == VortexNetwork::packetId_MainGameUpgradeTower) {

				sf::Int32 towerID;

				sf::Int32 gridX;
				sf::Int32 gridY;

				packet >> towerID >> gridX >> gridY;

				//std::cout << "PACKET RECIVED FOR towerID:(" << towerID << ")!!\n";

				upgradeTower(towerID, gridX, gridY);



			}


		}

	}


	

}


void GameController::spawnNewUnit(int ID, bool toOponent) {

	sf::Vector2i unitSpawnPosTemp;
	sf::Vector2i unitTargetPosTemp;

	if (toOponent) {

		//std::cout << "SPAWNER HOST FIENDE\n";
		unitSpawnPosTemp = enemyPlayerUnitSpawnPos;
		unitTargetPosTemp = enemyPlayerUnitTargetPos;

	} else {

		//std::cout << "SPAWNER HOST MEG <3\n";
		unitSpawnPosTemp = playerUnitSpawnPos;
		unitTargetPosTemp = playerUnitTargetPos;

	}


	Unit* testUnit;

	gameEngine->groundTileListMutex.lock();
	switch (ID) {
	case 0:
		testUnit = new IronmanUnit(gameEngine, &mapGroundTile, unitSpawnPosTemp.x, unitSpawnPosTemp.y, unitTargetPosTemp.x, unitTargetPosTemp.y);
		break;
	case 1:
		testUnit = new BahamutUnit(gameEngine, &mapGroundTile, unitSpawnPosTemp.x, unitSpawnPosTemp.y, unitTargetPosTemp.x, unitTargetPosTemp.y);
		break;
	case 2:
		testUnit = new RussianGirlUnit(gameEngine, &mapGroundTile, unitSpawnPosTemp.x, unitSpawnPosTemp.y, unitTargetPosTemp.x, unitTargetPosTemp.y);
		break;
	case 3:
		testUnit = new SadakoUnit(gameEngine, &mapGroundTile, unitSpawnPosTemp.x, unitSpawnPosTemp.y, unitTargetPosTemp.x, unitTargetPosTemp.y);
		break;
	case 4:
		testUnit = new IndianaJonesUnit(gameEngine, &mapGroundTile, unitSpawnPosTemp.x, unitSpawnPosTemp.y, unitTargetPosTemp.x, unitTargetPosTemp.y);
		break;
	default:
		testUnit = new IndianaJonesUnit(gameEngine, &mapGroundTile, unitSpawnPosTemp.x, unitSpawnPosTemp.y, unitTargetPosTemp.x, unitTargetPosTemp.y);
		break;
	}

	gameEngine->groundTileListMutex.unlock();

	gameEngine->unitListMutex.lock();

	unitList.push_back(testUnit);

	gameEngine->unitListMutex.unlock();

}


void GameController::spawnNewTower(int towerID, int gridX, int gridY, bool buildCommandFromOtherPlayer) {

	gameEngine->unitListMutex.lock();
	ArrowTower * testTower = new ArrowTower(gameEngine, &unitList, gridX * gridTileSize, gridY * gridTileSize, gridTileSize, sf::Vector2i(gridX, gridY), &particleList);
	gameEngine->unitListMutex.unlock();

	gameEngine->towerListMutex.lock();
	towerList.push_back(testTower);
	gameEngine->towerListMutex.unlock();

	mapGroundTile[gridX][gridY]->changeTileType(TileTypes::tower);
	towerBuildSprite->setColor(UNABLETOBUILD);

	if (!buildCommandFromOtherPlayer) {
		// Subtract building cost from resource
		gameGuiController->setPlayerResources(gameGuiController->getPlayerResources() - 10);
	}

	// Notify units to calculate new route if this tile was in their path
	groundTilesChanged = true;


}


void GameController::sendSpawnUnitPacket(int unitID, bool toOponent) {

	if (multiplayerMode && gameEngine->networkHandler->connectedByTCP) {

		//your oponent != opponent to himself
		toOponent = !toOponent;

		sf::Packet sendPacket;
		sf::Int32 typeID = VortexNetwork::packetId_MainGameSpawnUnit;
		sf::Int32 sendUnitID = unitID;
		sf::Int32 sendToOponent = toOponent;

		sendPacket << typeID << sendUnitID << sendToOponent;

		gameEngine->networkHandler->sendTcpPacket(sendPacket);

		//std::cout << "New unit Pakke sendt!?!\n";

	} else {
		//std::cout << "NOPE\n";
	}

}


void GameController::sendSpawnNewTowerPacket(int towerID, int gridX, int gridY) {
	

	if (multiplayerMode && gameEngine->networkHandler->connectedByTCP) {

		sf::Packet sendPacket;
		sf::Int32 typeID = VortexNetwork::packetId_MainGameSpawnTower;
		sf::Int32 spawnTowerID = towerID;
		sf::Int32 spawnTowerGridX = gridX;
		sf::Int32 spawnTowerGridY = gridY;

		sendPacket << typeID << spawnTowerID << spawnTowerGridX << spawnTowerGridY;

		gameEngine->networkHandler->sendTcpPacket(sendPacket);

		//std::cout << "New tower Pakke sendt\n";

	}


}


void GameController::sendDeleteTowerPacket(int gridX, int gridY) {


	if (multiplayerMode && gameEngine->networkHandler->connectedByTCP) {

		sf::Packet sendPacket;
		sf::Int32 typeID = VortexNetwork::packetId_MainGameDeleteTower;
		sf::Int32 delTowerGridX = gridX;
		sf::Int32 delTowerGridY = gridY;

		sendPacket << typeID << delTowerGridX << delTowerGridY;

		gameEngine->networkHandler->sendTcpPacket(sendPacket);

		std::cout << "del tower Pakke sendt\n";

	}


}


void GameController::sendUpgradeTowerPacket(int towerID, int gridX, int gridY) {


	if (multiplayerMode && gameEngine->networkHandler->connectedByTCP) {

		sf::Packet sendPacket;
		sf::Int32 typeID = VortexNetwork::packetId_MainGameUpgradeTower;
		sf::Int32 upgradeTowerID = towerID;
		sf::Int32 upgradeTowerGridX = gridX;
		sf::Int32 upgradeTowerGridY = gridY;

		sendPacket << typeID << upgradeTowerID << upgradeTowerGridX << upgradeTowerGridY;

		gameEngine->networkHandler->sendTcpPacket(sendPacket);

		std::cout << "tower upgrade Pakke sendt\n";

	}


}


bool GameController::unitOnMyPlayfield(int unitListIndex) {

	//meh, all is mine in SP
	if (!multiplayerMode) {
		return true;
	} else {

		if (gameEngine->networkHandler->iAmTheServer) {
			//server on left side
			if (unitList[unitListIndex]->getPos().x < WINDOWSIZEX / 2) {
				return true;
			}

		} else {

			if (unitList[unitListIndex]->getPos().x > WINDOWSIZEX / 2) {
				return true;
			}

		}


	}

	return false;


}


void GameController::update() {

	gameEngine->setMousePosView(gameView);
	auto mousePosWindow = gameEngine->getMousePositionRelativeToWindow();
	auto mousePosView = gameEngine->getMousePositionRelativeToSetView();


	if (!gameControllerFistRunDone) {

		gameControllerFistRunDone = true;
		//run on first call to update
		doGameControllerStatup();

	}

	if (gameEngine->networkHandler->connectedByTCP) {
		readNetworkPackets();
	}

	effectsHandler->update();


	if (zooming) {
		lerpTime += 1.0f * ((float)gameEngine->deltaTime.asMilliseconds() / 200);
		lerpZoom(lerpTime);
		updateGhostBuildingSprite(mousePosView);
	}

	// Upgrade tower
	if (gameGuiController->showingTowerUpgrades && selectedTower != nullptr) {
		if (gameGuiController->upgradeToCannon->isPressed && gameGuiController->upgradeToCannon->hovering && gameGuiController->buildTimer <= 0) {
			if (gameGuiController->playerResources >= 10) {
				gameGuiController->setPlayerResources(gameGuiController->playerResources - 10);
				gameGuiController->hideTowerUpgrades();
				gameGuiController->upgradeToCannon->tooltipBackground->setFillColor(sf::Color::Transparent);
				gameGuiController->upgradeToCannon->tooltipText->setColor(sf::Color::Transparent);


				//gameEngine->towerListMutex.lock();
				for (int i = 0; i < towerList.size(); i++) {
					if (towerList[i] == selectedTower) {
						int xpos = selectedTower->getPos().x;
						int ypos = selectedTower->getPos().y;

						upgradeTower(1, towerList[i]->getMapGroundTileIndex().x, towerList[i]->getMapGroundTileIndex().y);
						sendUpgradeTowerPacket(1, towerList[i]->getMapGroundTileIndex().x, towerList[i]->getMapGroundTileIndex().y);
/*
						gameEngine->addRemovableObjectToList(towerList[i]);
						towerList.erase(towerList.begin() + i);
						
						gameEngine->unitListMutex.lock();
						CannonTower* newTower = new CannonTower(gameEngine, &unitList, xpos, ypos, gridTileSize, sf::Vector2i(xpos / gridTileSize, ypos / gridTileSize), &particleList, effectsHandler);*/
						selectedTower = towerList[i];
						gameEngine->selectionSpriteMutex.lock();
						selectionGizmo->selectionSprites[0]->setPosition(selectedTower->getTowerSprite()->getPosition()); //NW gizmo
						selectionGizmo->selectionSprites[1]->setPosition(selectedTower->getTowerSprite()->getPosition().x + selectedTower->width, selectedTower->getTowerSprite()->getPosition().y); //NE gizmo
						selectionGizmo->selectionSprites[2]->setPosition(selectedTower->getTowerSprite()->getPosition().x + selectedTower->width, selectedTower->getTowerSprite()->getPosition().y + selectedTower->height); //SE gizmo
						selectionGizmo->selectionSprites[3]->setPosition(selectedTower->getTowerSprite()->getPosition().x, selectedTower->getTowerSprite()->getPosition().y + selectedTower->height); //SW gizmo
						gameEngine->selectionSpriteMutex.unlock();


						//gameEngine->unitListMutex.unlock();

						

						break;
					}
				}
				//gameEngine->towerListMutex.unlock();

			}
		}
	}

	//REMOVE FALSE TO ACTIVATE
	if (unitSpawnTimer.getElapsedTime().asMilliseconds() >= spawnDelayMS && unitList.size() < 20000 && gameGuiController->currentLevel != 0) {

		//std::cout << "spawning at fixed rate\n";

		spawnNewUnit(gameGuiController->currentLevel - 1, false);

		if (multiplayerMode && gameEngine->networkHandler->connectedByTCP) {

			//send spawn on our side (on enemy game)
			sendSpawnUnitPacket(gameGuiController->currentLevel - 1, false);

		}

		unitSpawnTimer.restart();


	}


	if (gameEngine->eventMouseMove || gameGuiController->building == true) {
		updateGhostBuildingSprite(mousePosView);
	}

	if (gameEngine->eventMouseWheelScrollUp) {
		zooming = calculateZoom(false);
	}
	else if (gameEngine->eventMouseWheelScrollDown) {
		zooming = calculateZoom(true);
	}

	
	if (gameEngine->eventMousePressedRight) {
		if (gameEngine->eventMouseMove) {
			moveViewport();
		}
	}
	
	if (gameEngine->eventMouseClickedLeft) {
	//if (gameEngine->eventMousePressedLeft) {
		handlePlayerTowerAction();
	}
	
	gameEngine->renderObjectsListMutex.lock();
	for (auto * current : renderObjectsVector) {

		current->update();

	}
	gameEngine->renderObjectsListMutex.unlock();

	if (groundTilesChanged){
		recalculateNavigationMaps();
	}

	gameEngine->unitListMutex.lock();
	for (int i = 0; i < unitList.size(); i++) {
		if (towerRemoved) {
			unitList[i]->towerRemoved = true;
		}
		unitList[i]->update();
		if (unitList[i]->isDead()) {

			if (unitOnMyPlayfield(i)) {
				gameGuiController->setPlayerResources(gameGuiController->getPlayerResources() + unitList[i]->killReward);
			}

			gameEngine->addRemovableObjectToList(unitList[i]);
			gameEngine->particleListMutex.lock();
			particleList.push_back(new VortexParticleSystem(35, unitList[i]->getPos().x + unitList[i]->getSize().x / 2, unitList[i]->getPos().y + unitList[i]->getSize().y / 2, unitList[i]->hitParticleColor, sf::Quads, 200, 30));
			gameEngine->particleListMutex.unlock();
			unitList[i] = nullptr;
			unitList.erase(unitList.begin() + i);
			i--;
		}

		else if (unitList[i]->reachedGoal) {
			// Remove life
			particleList.push_back(new VortexParticleSystem(35, unitList[i]->getPos().x + unitList[i]->getSize().x / 2, unitList[i]->getPos().y + unitList[i]->getSize().y / 2, sf::Color(100, 100, 100, 255), sf::Quads, 200, 30));

			if (unitOnMyPlayfield(i)){
				gameGuiController->setPlayerLives(gameGuiController->numLives - 1);
			}
			if (gameGuiController->numLives == 0 ) {
				playerLost = true;
			}


			gameEngine->addRemovableObjectToList(unitList[i]);
			unitList[i] = nullptr;
			unitList.erase(unitList.begin() + i);
			i--;
		}
	}
	groundTilesChanged = false;
	towerRemoved = false;

	//sorting units so the unit with the lowest base y is rendered first
	std::sort(unitList.begin(), unitList.end(), entitySortingStructDistanceDistance);

	gameEngine->unitListMutex.unlock();


	gameEngine->towerListMutex.lock();
	for (auto * current : towerList) {
		current->update();
	}

	std::sort(towerList.begin(), towerList.end(), entitySortingStructDistanceDistance);

	gameEngine->towerListMutex.unlock();


	gameEngine->particleListMutex.lock();
	for (int i = 0; i < particleList.size(); i++) {
		particleList[i]->update(gameEngine->deltaTime);
		if (particleList[i]->stopEmitting == true) {
			gameEngine->addRemovableObjectToList(particleList[i]);
			particleList[i] == nullptr;
			particleList.erase(particleList.begin() + i);
		}
	}
	gameEngine->particleListMutex.unlock();


	for (auto currentController : childControllers) {
		currentController->update();
	}

	while (!gameGuiController->unitsToSpawn.empty()) {

		//std::cout << "spawning at userWill rate\n";

		

		if (multiplayerMode && gameEngine->networkHandler->connectedByTCP) {

			int unitToSpawnID = gameGuiController->unitsToSpawn.back() - 1;

			spawnNewUnit(unitToSpawnID, true);
			gameGuiController->unitsToSpawn.pop_back();

			//send spawn on ther side in their game
			sendSpawnUnitPacket(unitToSpawnID, true);

		} else {

			int unitToSpawnID = gameGuiController->unitsToSpawn.back() - 1;

			spawnNewUnit(unitToSpawnID, false);
			gameGuiController->unitsToSpawn.pop_back();

		}

		//Unit* spawnedUnit;

		//gameEngine->groundTileListMutex.lock();
		//switch (gameGuiController->unitsToSpawn.back()) {
		//case 1:
		//	spawnedUnit = new IronmanUnit(gameEngine, &mapGroundTile, playerUnitSpawnPos.x, playerUnitSpawnPos.y, playerUnitTargetPos.x, playerUnitTargetPos.y);
		//	break;

		//case 2:
		//	spawnedUnit = new BahamutUnit(gameEngine, &mapGroundTile, playerUnitSpawnPos.x, playerUnitSpawnPos.y, playerUnitTargetPos.x, playerUnitTargetPos.y);
		//	break;

		//default:
		//	spawnedUnit = new IronmanUnit(gameEngine, &mapGroundTile, playerUnitSpawnPos.x, playerUnitSpawnPos.y, playerUnitTargetPos.x, playerUnitTargetPos.y);
		//	printf("Error spawning unit!!!!!\n");
		//}
		//gameEngine->groundTileListMutex.unlock();
		//gameGuiController->unitsToSpawn.pop_back();

		//gameEngine->unitListMutex.lock();
		//unitList.push_back(spawnedUnit);
		//gameEngine->unitListMutex.unlock();

		
	}

	previousMousePos = mousePosWindow;
	
}



bool GameController::onMyMapSide(int gridX, int gridY) {

	if (playerID == 0) { //only left side:


		if (gridX <= (playerUnitSpawnPos.x/gridTileSize)) {
			//std::cout << "spiller 0 rett side: " << gridX << " / " << (playerUnitSpawnPos.x / gridTileSize) << " \n";
			return true;
		}

	} else if (playerID == 1) { //only right side:

		if (gridX >= (playerUnitSpawnPos.x / gridTileSize)) {
			return true;
		}

	}

	return false;


}


void GameController::deleteTower(int gridX, int gridY) {

	gameEngine->towerListMutex.lock();

	for (int i = 0; i < towerList.size(); i++) {

		if (towerList[i]->getMapGroundTileIndex().x == gridX
			&&	towerList[i]->getMapGroundTileIndex().y == gridY){

			mapGroundTile[gridX][gridY]->changeTileType(TileTypes::grass);

			towerList[i]->deleteProjectiles();
			gameEngine->addRemovableObjectToList(towerList[i]);

			if (towerList[i] == selectedTower) {
				selectedTower = nullptr;
				if (gameGuiController->showingTowerUpgrades) {
					gameGuiController->showingTowerUpgrades = false;
					gameGuiController->hideTowerUpgrades();
				}
			}
			towerList[i] = nullptr;
			towerList.erase(towerList.begin() + i);
			i--;

			towerRemoved = true;
			groundTilesChanged = true;

		}

	}

	gameEngine->towerListMutex.unlock();



}

void GameController::upgradeTower(int newTowerID, int gridX, int gridY) {


	gameEngine->towerListMutex.lock();

	for (int i = 0; i < towerList.size(); i++) {

		if (towerList[i]->getMapGroundTileIndex().x == gridX
			&&	towerList[i]->getMapGroundTileIndex().y == gridY) {

			gameEngine->unitListMutex.lock();

			gameEngine->addRemovableObjectToList(towerList[i]);
			towerList.erase(towerList.begin() + i);

			CannonTower* newTower = new CannonTower(gameEngine, &unitList, gridX*gridTileSize, gridY*gridTileSize, gridTileSize, sf::Vector2i((gridX*gridTileSize) / gridTileSize, (gridY*gridTileSize) / gridTileSize), &particleList, effectsHandler);

			towerList.push_back(newTower);

			gameEngine->unitListMutex.unlock();

		}

	}

	gameEngine->towerListMutex.unlock();


}


void GameController::handlePlayerTowerAction() {
	if (playerLost) {
		return;
	}

	auto mousePosWindow = gameEngine->getMousePositionRelativeToWindow();
	auto mousePosView = gameEngine->getMousePositionRelativeToSetView();

	int xpos = mousePosView.x / gridTileSize;
	int ypos = mousePosView.y / gridTileSize;

	if (mousePosWindow.y >= gameGuiController->bottomToolbarPosY) {
		return;
	}

	if (xpos < 0 || xpos > mapGroundTile.size() || ypos < 0 || ypos > mapGroundTile[0].size())
		return;
	

	//Not building, not deleting, and clicked on tower
	if (mapGroundTile[xpos][ypos]->getTileTypeID() == TileTypes::tower && !gameGuiController->building && !gameGuiController->deleting) {
		if (gameGuiController->showingTowerUpgrades && gameGuiController->upgradeToCannon->hovering) {
			// Nomnomcookie
		}
		else {
			for (int i = 0; i < towerList.size(); i++) {
				sf::Vector2i towerGridPos(towerList[i]->posX / gridTileSize, towerList[i]->posY / gridTileSize);
				if (towerGridPos.x == xpos && towerGridPos.y == ypos) {
					if (selectedTower == towerList[i] && gameGuiController->showingTowerUpgrades) {
						break;
					}

					selectedTower = towerList[i];
					gameEngine->selectionSpriteMutex.lock();
					selectionGizmo->selectionSprites[0]->setPosition(selectedTower->getTowerSprite()->getPosition()); //NW gizmo
					selectionGizmo->selectionSprites[1]->setPosition(selectedTower->getTowerSprite()->getPosition().x + selectedTower->width, selectedTower->getTowerSprite()->getPosition().y); //NE gizmo
					selectionGizmo->selectionSprites[2]->setPosition(selectedTower->getTowerSprite()->getPosition().x + selectedTower->width, selectedTower->getTowerSprite()->getPosition().y + selectedTower->height); //SE gizmo
					selectionGizmo->selectionSprites[3]->setPosition(selectedTower->getTowerSprite()->getPosition().x, selectedTower->getTowerSprite()->getPosition().y + selectedTower->height); //SW gizmo
					gameEngine->selectionSpriteMutex.unlock();

					// If selected tower is a basic tower show upgrade options
					if (selectedTower->towerId == 1) {
						gameGuiController->showingTowerUpgrades = true;
						gameGuiController->showTowerUpgrades(mousePosWindow);
					}
					
					
					break;
				}
			}
		}
		
		
		

	}
	//Not building, not deleting, and didnt click on tower - clear selection
	else if (mapGroundTile[xpos][ypos]->getTileTypeID() != TileTypes::tower && !gameGuiController->building && !gameGuiController->deleting) {
		// If upgrade tab is open
		if (gameGuiController->showingTowerUpgrades) {
			// If mouse is not over an upgrade button
			if (!gameGuiController->upgradeToCannon->isPressed && !gameGuiController->upgradeToCannon->hovering) {
				selectedTower = nullptr;
				if (gameGuiController->showingTowerUpgrades) {
					gameGuiController->showingTowerUpgrades = false;
					gameGuiController->hideTowerUpgrades();
				}
			}
		}
		else {
			selectedTower = nullptr;
			if (gameGuiController->showingTowerUpgrades) {
				gameGuiController->showingTowerUpgrades = false;
				gameGuiController->hideTowerUpgrades();
			}
		}
		
		
	}
	//Building, and zone buildable
	else if (onMyMapSide(xpos, ypos) && mapGroundTile[xpos][ypos]->getTileTypeID() == TileTypes::grass && gameGuiController->building && !gameGuiController->mouseOverSomeButton(gameView) && !unitOnTile(xpos, ypos)) {
		// Check if player has resources to build
		if (gameGuiController->getPlayerResources() >= 10) {

			spawnNewTower(0, xpos, ypos, false);
			sendSpawnNewTowerPacket(0, xpos, ypos);

			
			//gameEngine->unitListMutex.lock();
			//ArrowTower * testTower = new ArrowTower(gameEngine, &unitList, xpos * gridTileSize, ypos * gridTileSize, gridTileSize, sf::Vector2i(xpos, ypos), &particleList);
			//gameEngine->unitListMutex.unlock();

			//gameEngine->towerListMutex.lock();
			//towerList.push_back(testTower);
			//gameEngine->towerListMutex.unlock();

			//mapGroundTile[xpos][ypos]->changeTileType(TileTypes::tower);
			//towerBuildSprite->setColor(UNABLETOBUILD);

			//// Subtract building cost from resource
			//gameGuiController->setPlayerResources(gameGuiController->getPlayerResources() - 10);

			//// Notify units to calculate new route if this tile was in their path
			//groundTilesChanged = true;
		}
		
	}
	//Clicked on tower and is deleting
	else if (gameGuiController->deleting && mapGroundTile[xpos][ypos]->getTileTypeID() == TileTypes::tower) {
		
		for (int i = 0; i < towerList.size(); i++) {

			sf::Vector2i mouseGridPos(mousePosView.x / gridTileSize, mousePosView.y / gridTileSize);

			//gameEngine->towerListMutex.lock();
			
			if (towerList[i]->getMapGroundTileIndex().x == mouseGridPos.x
				&&	towerList[i]->getMapGroundTileIndex().y == mouseGridPos.y) {

				deleteTower(mouseGridPos.x, mouseGridPos.y);
				sendDeleteTowerPacket(mouseGridPos.x, mouseGridPos.y);


				/*mapGroundTile[mouseGridPos.x][mouseGridPos.y]->changeTileType(TileTypes::grass);
				
				towerList[i]->deleteProjectiles();
				gameEngine->addRemovableObjectToList(towerList[i]);
				
				if (towerList[i] == selectedTower) {
					selectedTower = nullptr;
					if (gameGuiController->showingTowerUpgrades) {
						gameGuiController->showingTowerUpgrades = false;
						gameGuiController->hideTowerUpgrades();
					}
				}
				towerList[i] = nullptr;
				towerList.erase(towerList.begin() + i);
				i--;

				towerRemoved = true;
				groundTilesChanged = true;*/
			}
			
			//gameEngine->towerListMutex.unlock();
			
		}

	}
	else {
		// Play unable to do action beep sound
	}
}

void GameController::moveViewport() {

	auto mousePosWindow = gameEngine->getMousePositionRelativeToWindow();
	auto mousePosView = gameEngine->getMousePositionRelativeToSetView();

	//Move the viewport
	float viewChangeX = ((float)previousMousePos.x - (float)mousePosWindow.x) / (viewRelativeSizeX);
	float viewChangeY = ((float)previousMousePos.y - (float)mousePosWindow.y) / (viewRelativeSizeY);



	//If going out of bounds on the left side
	if (gameView.getCenter().x + viewChangeX < viewWidth / 2) {
		gameView.setCenter(sf::Vector2f(viewWidth / 2, gameView.getCenter().y));
		viewChangeX = 0;
	}

	//If going out of bounds on the right side
	else if (gameView.getCenter().x + viewChangeX > WINDOWSIZEX - viewWidth / 2) {
		gameView.setCenter(sf::Vector2f(WINDOWSIZEX - viewWidth / 2, gameView.getCenter().y));
		viewChangeX = 0;
	}
	//If going out of bounds on top
	if (gameView.getCenter().y + viewChangeY < viewHeight / 2) {
		gameView.setCenter(sf::Vector2f(gameView.getCenter().x, viewHeight / 2));
		viewChangeY = 0;
	}
	//If going out of bounds on bottom
	else if (gameView.getCenter().y + viewChangeY > WINDOWSIZEY - viewHeight / 2) {
		gameView.setCenter(sf::Vector2f(gameView.getCenter().x, WINDOWSIZEY - viewHeight / 2));
		viewChangeY = 0;
	}

	gameView.move(viewChangeX, viewChangeY);
}

bool GameController::calculateZoom(bool zoomOut) {

	auto mousePosWindow = gameEngine->getMousePositionRelativeToWindow();
	auto mousePosView = gameEngine->getMousePositionRelativeToSetView();

	float xdiff;
	float ydiff;
	if (zoomOut) {
		if (viewRelativeSizeX <= 1.f) {
			if (zooming) {
				return true;
			}
			return false;
		}

		viewRelativeSizeX /= zoomRate;
		viewRelativeSizeY /= zoomRate;

		xdiff = 0;
		ydiff = 0;
		// Zoom out relative by mouse pos, but me no likey
		/*
		xdiff = (gameView.getCenter().x - mousePosView.x) * viewRelativeSizeX / 5.f;
		ydiff = (gameView.getCenter().y - mousePosView.y) * viewRelativeSizeX / 5.f;
		*/
		

	} else {
		if (viewRelativeSizeX >= 5.f) {
			if (zooming) {
				return true;
			}
			return false;
		}

		viewRelativeSizeX *= zoomRate;
		viewRelativeSizeY *= zoomRate;
		xdiff = (mousePosView.x - gameView.getCenter().x) * viewRelativeSizeX / 5.f;
		ydiff = (mousePosView.y - gameView.getCenter().y) * viewRelativeSizeX / 5.f;
	}

	viewWidth = WINDOWSIZEX / viewRelativeSizeX;
	viewHeight = WINDOWSIZEY / viewRelativeSizeY;

	sf::View tempView = gameView;
	

	//Zooming out so that view comes out of bounds on left side fix
	if (tempView.getCenter().x - viewWidth / 2 + xdiff < 0) {
		tempView.setCenter(sf::Vector2f(viewWidth / 2, tempView.getCenter().y));
	}
	//Zooming out so that view comes out of bounds on right side fix
	else if (tempView.getCenter().x + viewWidth / 2 + xdiff > WINDOWSIZEX) {
		tempView.setCenter(sf::Vector2f(WINDOWSIZEX - viewWidth / 2, tempView.getCenter().y));
	}

	//Zooming out so that view comes out of bounds on top fix
	if (tempView.getCenter().y - viewHeight / 2 + ydiff < 0) {
		tempView.setCenter(sf::Vector2f(tempView.getCenter().x, viewHeight / 2));
	}
	//Zooming out so that view comes out of bounds on bottom fix
	else if (tempView.getCenter().y + viewHeight / 2 + ydiff > WINDOWSIZEY) {
		tempView.setCenter(sf::Vector2f(tempView.getCenter().x, WINDOWSIZEY - viewHeight / 2));
	}

	//At max zoom out level, center view to screen
	if (viewWidth > WINDOWSIZEX) {
		viewWidth = WINDOWSIZEX;
		viewHeight = WINDOWSIZEY;
		tempView.setCenter(sf::Vector2f(WINDOWSIZEX / 2, WINDOWSIZEY / 2));
	}

	sf::FloatRect newZoom(tempView.getCenter().x - (viewWidth / 2), tempView.getCenter().y - (viewHeight / 2), viewWidth, viewHeight);

	//If center has not changed
	if (tempView.getCenter().x == gameView.getCenter().x) {
		newZoom.left += xdiff;
	}

	if (tempView.getCenter().y == gameView.getCenter().y) {
		newZoom.top += ydiff;
	}

	zoomEndPoint.width = newZoom.width;
	zoomEndPoint.height = newZoom.height;
	zoomEndPoint.top = newZoom.top;
	zoomEndPoint.left = newZoom.left;

	lerpTime = 0.0f;
	return true;
}

std::vector<std::vector<int>> GameController::makeNavigationMapFromTileMap(std::vector<std::vector<MapTile *>> map) {
	std::vector<std::vector<int>> resultMap;
	int width, height;
	width = map.size();
	height = map[0].size();

	for (int x = 0; x < width; x++) {
		std::vector<int> column;
		for (int y = 0; y < height; y++) {
			column.push_back(map[x][y]->getTileTypeID());
		}
		resultMap.push_back(column);
	}
	return resultMap;
}

sf::Vector2i GameController::worldCoordinateToMapTileCoordinate(sf::Vector2i coord) {
	int tileSize = (int)gridTileSize;
	return coord / tileSize;
}

void GameController::recalculateNavigationMaps(){
	std::vector<std::vector<int>> navigationMap;
	navigationMap = makeNavigationMapFromTileMap(mapGroundTile);
	sf::Vector2i playerTargetInMapCoord = worldCoordinateToMapTileCoordinate(playerUnitTargetPos);
	sf::Vector2i enemyTargetInMapCoord = worldCoordinateToMapTileCoordinate(enemyPlayerUnitTargetPos);
	gameEngine->pathFinder->navigationMap = gameEngine->pathFinder->makeBreadthFirstDirectionMap(navigationMap, playerTargetInMapCoord, enemyTargetInMapCoord);
}