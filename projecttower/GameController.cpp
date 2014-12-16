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

	//gridTileSize = ((float)gameEngine->getWindowSize().x / (float)GAMEMAPSIZEX);
	gridTileSize = 25;

	spawnDelayMS = 2000;

	/*
	playerUnitSpawnPos = sf::Vector2i(0, 13 * gridTileSize);
	playerUnitTargetPos = sf::Vector2i(23 * gridTileSize, 13 * gridTileSize);
	*/
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
}


void GameController::preloadAssets() {

	std::vector<IronmanUnit *> preloadUnitList;
	gameEngine->groundTileListMutex.lock();
	preloadUnitList.push_back(new IronmanUnit(gameEngine, &mapGroundTile, playerUnitSpawnPos.x, playerUnitSpawnPos.y, playerUnitTargetPos.x, playerUnitTargetPos.y));
	gameEngine->groundTileListMutex.unlock();

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



	gameEngine->gameControllerProjectileMutex.lock();
	//for (auto currentRenderVector : projectileList) {
	//	auto tempVector = currentRenderVector->getRenderDrawable();
	//	renderList.insert(renderList.end(), tempVector.begin(), tempVector.end());
	//}
	gameEngine->gameControllerProjectileMutex.unlock();




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

	if (mapGroundTile[xpos][ypos]->getTileTypeID() == TileTypes::grass && !unitOnTile(xpos, ypos) && (gameGuiController->getPlayerResources() >= 10)) {
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

void GameController::update() {

	gameEngine->setMousePosView(gameView);
	auto mousePosWindow = gameEngine->getMousePositionRelativeToWindow();
	auto mousePosView = gameEngine->getMousePositionRelativeToSetView();

	if (zooming) {
		lerpTime += 1.0f * ((float)gameEngine->deltaTime.asMilliseconds() / 200);
		lerpZoom(lerpTime);
		updateGhostBuildingSprite(mousePosView);
	}

	// Upgrade tower
	if (gameGuiController->showingTowerUpgrades && selectedTower != nullptr) {
		if (gameGuiController->upgradeToCannon->isPressed && gameGuiController->upgradeToCannon->hovering && gameGuiController->timer <= 0) {
			if (gameGuiController->playerResources >= 10) {
				gameGuiController->setPlayerResources(gameGuiController->playerResources - 10);
				gameGuiController->hideTowerUpgrades();
				gameGuiController->upgradeToCannon->tooltipBackground->setFillColor(sf::Color::Transparent);
				gameGuiController->upgradeToCannon->tooltipText->setColor(sf::Color::Transparent);


				gameEngine->towerListMutex.lock();
				for (int i = 0; i < towerList.size(); i++) {
					if (towerList[i] == selectedTower) {
						int xpos = selectedTower->getPos().x;
						int ypos = selectedTower->getPos().y;

						gameEngine->addRemovableObjectToList(towerList[i]);
						towerList.erase(towerList.begin() + i);
						
						gameEngine->unitListMutex.lock();
						CannonTower* newTower = new CannonTower(gameEngine, &unitList, xpos, ypos, gridTileSize, sf::Vector2i(xpos / gridTileSize, ypos / gridTileSize), &particleList);
						selectedTower = newTower;
						gameEngine->selectionSpriteMutex.lock();
						selectionGizmo->selectionSprites[0]->setPosition(selectedTower->getTowerSprite()->getPosition()); //NW gizmo
						selectionGizmo->selectionSprites[1]->setPosition(selectedTower->getTowerSprite()->getPosition().x + selectedTower->width, selectedTower->getTowerSprite()->getPosition().y); //NE gizmo
						selectionGizmo->selectionSprites[2]->setPosition(selectedTower->getTowerSprite()->getPosition().x + selectedTower->width, selectedTower->getTowerSprite()->getPosition().y + selectedTower->height); //SE gizmo
						selectionGizmo->selectionSprites[3]->setPosition(selectedTower->getTowerSprite()->getPosition().x, selectedTower->getTowerSprite()->getPosition().y + selectedTower->height); //SW gizmo
						gameEngine->selectionSpriteMutex.unlock();


						gameEngine->unitListMutex.unlock();

						towerList.push_back(newTower);

						break;
					}
				}
				gameEngine->towerListMutex.unlock();

			}
		}
	}


	if (unitSpawnTimer.getElapsedTime().asMilliseconds() >= spawnDelayMS && unitList.size() < 20000) {

		gameEngine->groundTileListMutex.lock();
		
		//IronmanUnit * testUnit = new IronmanUnit(gameEngine, &mapGroundTile, -100, (gameEngine->getWindowSize().y / 2));
		IronmanUnit * testUnit = new IronmanUnit(gameEngine, &mapGroundTile, playerUnitSpawnPos.x, playerUnitSpawnPos.y, playerUnitTargetPos.x, playerUnitTargetPos.y);
		gameEngine->groundTileListMutex.unlock();

		gameEngine->unitListMutex.lock();

		unitSpawnTimer.restart();

		unitList.push_back(testUnit);

		gameEngine->unitListMutex.unlock();

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


	gameEngine->unitListMutex.lock();
	for (int i = 0; i < unitList.size(); i++) {
		if (groundTilesChanged) {
			unitList[i]->groundTilesChanged = true;
		}
		if (towerRemoved) {
			unitList[i]->towerRemoved = true;
		}
		unitList[i]->update();
		if (unitList[i]->isDead()) {
			gameGuiController->setPlayerResources(gameGuiController->getPlayerResources() + unitList[i]->killReward);

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
			gameGuiController->setPlayerLives(gameGuiController->numLives - 1);
			if (gameGuiController->numLives == 0) {
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
		if (gameGuiController->unitsToSpawn.back() == 1) {
			// Spawn level 1 unit
			gameEngine->groundTileListMutex.lock();
			IronmanUnit* spawnedUnit = new IronmanUnit(gameEngine, &mapGroundTile, playerUnitSpawnPos.x, playerUnitSpawnPos.y, playerUnitTargetPos.x, playerUnitTargetPos.y);
			gameEngine->groundTileListMutex.unlock();

			gameEngine->unitListMutex.lock();
			unitList.push_back(spawnedUnit);
			gameEngine->unitListMutex.unlock();
		}
		else {
			printf("Error spawning unit\n");
		}

		gameGuiController->unitsToSpawn.pop_back();
	}

	previousMousePos = mousePosWindow;
	
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
	else if (mapGroundTile[xpos][ypos]->getTileTypeID() == TileTypes::grass && gameGuiController->building && !gameGuiController->mouseOverSomeButton(gameView) && !unitOnTile(xpos, ypos)) {
		// Check if player has resources to build
		if (gameGuiController->getPlayerResources() >= 10) {
			gameEngine->unitListMutex.lock();
			ArrowTower * testTower = new ArrowTower(gameEngine, &unitList, xpos * gridTileSize, ypos * gridTileSize, gridTileSize, sf::Vector2i(xpos, ypos), &particleList);
			gameEngine->unitListMutex.unlock();

			gameEngine->towerListMutex.lock();
			towerList.push_back(testTower);
			gameEngine->towerListMutex.unlock();

			mapGroundTile[xpos][ypos]->changeTileType(TileTypes::tower);
			towerBuildSprite->setColor(UNABLETOBUILD);

			// Subtract building cost from resource
			gameGuiController->setPlayerResources(gameGuiController->getPlayerResources() - 10);

			// Notify units to calculate new route if this tile was in their path
			groundTilesChanged = true;
		}
		
	}
	//Clicked on tower and is deleting
	else if (gameGuiController->deleting && mapGroundTile[xpos][ypos]->getTileTypeID() == TileTypes::tower) {
		
		for (int i = 0; i < towerList.size(); i++) {

			sf::Vector2i mouseGridPos(mousePosView.x / gridTileSize, mousePosView.y / gridTileSize);

			gameEngine->towerListMutex.lock();
			
			if (towerList[i]->getMapGroundTileIndex().x == mouseGridPos.x
				&&	towerList[i]->getMapGroundTileIndex().y == mouseGridPos.y) {

				mapGroundTile[mouseGridPos.x][mouseGridPos.y]->changeTileType(TileTypes::grass);
				
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
			}
			
			gameEngine->towerListMutex.unlock();
			
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