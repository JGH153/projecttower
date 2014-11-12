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

	gridTileSize = ((float)gameEngine->getWindowSize().x / (float)GAMEMAPSIZEX);
	gridTileSize = 25;

	spawnDelayMS = 10;



	
	

		
		
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


	//for (int i = 0; i < 1; i++){

	//	//BasicUnit * testUnit = new BasicUnit(gameEngine, &mapGroundTile, 50 + (rand() % (gameEngine->getWindowSize().x - 100)), 50 + (rand() % (gameEngine->getWindowSize().y - 100)));
	//	BasicUnit * testUnit = new BasicUnit(gameEngine, &mapGroundTile, 50, (gameEngine->getWindowSize().y / 2)-25);
	//	//BasicUnit * testUnit = new BasicUnit(gameEngine, 200, 200);
	//	unitList.push_back(testUnit);
	//	//renderObjectsVector.push_back(testUnit);

	//}

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

	std::vector<BasicUnit *> preloadUnitList;
	preloadUnitList.push_back(new BasicUnit(gameEngine, &mapGroundTile, 50 + (rand() % (gameEngine->getWindowSize().x - 100)), 50 + (rand() % (gameEngine->getWindowSize().y - 100))));

	for (auto currentUnit : preloadUnitList) {
		delete currentUnit;
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
	gameEngine->towerProjectileMutex.lock();


	for (auto currentRenderVector : towerList) {

		auto tempVector = currentRenderVector->getRenderDrawable();

		renderList.insert(renderList.end(), tempVector.begin(), tempVector.end());

	}
	gameEngine->towerProjectileMutex.unlock();
	gameEngine->towerListMutex.unlock();
	gameEngine->unitListMutex.lock();

	for (auto currentRenderVector : unitList) {

		auto tempVector = currentRenderVector->getRenderDrawable();

		renderList.insert(renderList.end(), tempVector.begin(), tempVector.end());

	}

	gameEngine->unitListMutex.unlock();


	if (gameGuiController->building) {
		renderList.push_back(towerBuildSprite);
	}

	if (selectedTower != nullptr) {
		for (int i = 0; i < 4; i++) {
			renderList.push_back(selectionGizmo->selectionSprites[i]);
		}
	}

	renderSuperList.push_back(renderList);

	
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

	towerBuildSprite->setPosition(xpos * gridTileSize, (ypos * gridTileSize) - (towerBuildSprite->getTextureRect().height / 5));

	//prevent out of vector error
	if (xpos >= mapGroundTile.size() || ypos >= mapGroundTile[0].size()) {
		return;
	}

	if (mapGroundTile[xpos][ypos]->getTileTypeID() == TileTypes::grass && !unitOnTile(xpos, ypos)) {
		towerBuildSprite->setColor(ABLETOBUILD);
	}
	else {
		towerBuildSprite->setColor(UNABLETOBUILD);
	}
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




	if (unitSpawnTimer.getElapsedTime().asMilliseconds() >= spawnDelayMS) {


		BasicUnit * testUnit = new BasicUnit(gameEngine, &mapGroundTile, 50, (gameEngine->getWindowSize().y / 2) - 25);

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
	
	//if (gameEngine->eventMouseClickedLeft) {
	if (gameEngine->eventMousePressedLeft) {
		handlePlayerTowerAction();
	}
	
	gameEngine->renderObjectsListMutex.lock();
	for (auto * current : renderObjectsVector) {

		current->update();

	}
	gameEngine->renderObjectsListMutex.unlock();

	gameEngine->towerListMutex.lock();

	for (int i = 0; i < towerList.size(); i++) {

		towerList[i]->update();

	}

	/*for (auto * current : towerList) {
		current->update();
	}*/
	gameEngine->towerListMutex.unlock();

	gameEngine->unitListMutex.lock();
	for (Unit * current : unitList) {
		current->update();
	}

	for (int i = 0; i < unitList.size(); i++) {

		if (unitList[i]->isDead()) {
			delete unitList[i];
			unitList[i] = nullptr;
			unitList.erase(unitList.begin() + i);
			i--;
		}
	}
	

	//sorting units so the unit with the lowest base y is rendered first
	std::sort(unitList.begin(), unitList.end(), entitySortingStructDistanceDistance);
	std::sort(towerList.begin(), towerList.end(), entitySortingStructDistanceDistance);

	gameEngine->unitListMutex.unlock();


	for (auto currentController : childControllers) {
		currentController->update();
	}

	previousMousePos = mousePosWindow;
	
}

void GameController::handlePlayerTowerAction() {

	auto mousePosWindow = gameEngine->getMousePositionRelativeToWindow();
	auto mousePosView = gameEngine->getMousePositionRelativeToSetView();

	int xpos = mousePosView.x / gridTileSize;
	int ypos = mousePosView.y / gridTileSize;

	if (xpos < 0 || xpos > mapGroundTile.size() || ypos < 0 || ypos > mapGroundTile[0].size())
		return;
	

	//Not building, not deleting, and clicked on tower
	if (mapGroundTile[xpos][ypos]->getTileTypeID() == TileTypes::tower && !gameGuiController->building && !gameGuiController->deleting) {
		for (int i = 0; i < towerList.size(); i++) {
			sf::Vector2i towerGridPos(towerList[i]->posX / gridTileSize, towerList[i]->posY / gridTileSize);
			if (towerGridPos.x == xpos && towerGridPos.y == ypos) {
				selectedTower = towerList[i];
				selectionGizmo->selectionSprites[0]->setPosition(selectedTower->getTowerSprite()->getPosition()); //NW gizmo
				selectionGizmo->selectionSprites[1]->setPosition(selectedTower->getTowerSprite()->getPosition().x + selectedTower->width, selectedTower->getTowerSprite()->getPosition().y); //NE gizmo
				selectionGizmo->selectionSprites[2]->setPosition(selectedTower->getTowerSprite()->getPosition().x + selectedTower->width, selectedTower->getTowerSprite()->getPosition().y + selectedTower->height); //SE gizmo
				selectionGizmo->selectionSprites[3]->setPosition(selectedTower->getTowerSprite()->getPosition().x, selectedTower->getTowerSprite()->getPosition().y + selectedTower->height); //SW gizmo
				break;
			}
		}
		// TODO HERE: DISPLAY TOWER UPGRADE OPTIONS
	}
	//Not building, not deleting, and didnt click on tower - clear selection
	else if (mapGroundTile[xpos][ypos]->getTileTypeID() != TileTypes::tower && !gameGuiController->building && !gameGuiController->deleting) {
		selectedTower = nullptr;
	}
	//Building, and zone buildable
	else if (mapGroundTile[xpos][ypos]->getTileTypeID() == TileTypes::grass && gameGuiController->building && !gameGuiController->mouseOverSomeButton(gameView) && !unitOnTile(xpos, ypos)) {
		gameEngine->unitListMutex.lock();
		BasicTower * testTower = new BasicTower(gameEngine, &unitList, xpos * gridTileSize, ypos * gridTileSize, gridTileSize, sf::Vector2i(xpos, ypos));
		gameEngine->towerListMutex.lock();
		towerList.push_back(testTower);
		
		gameEngine->towerListMutex.unlock();
		gameEngine->unitListMutex.unlock();
		
		mapGroundTile[xpos][ypos]->changeTileType(TileTypes::tower);
		towerBuildSprite->setColor(UNABLETOBUILD);
	}
	//Clicked on tower and is deleting
	else if (gameGuiController->deleting && mapGroundTile[xpos][ypos]->getTileTypeID() == TileTypes::tower) {

		for (int i = 0; i < towerList.size(); i++) {

			sf::Vector2i mouseGridPos(mousePosView.x / gridTileSize, mousePosView.y / gridTileSize);

			if (towerList[i]->getMapGroundTileIndex().x == mouseGridPos.x
				&&	towerList[i]->getMapGroundTileIndex().y == mouseGridPos.y) {

				gameEngine->towerListMutex.lock();

				mapGroundTile[mouseGridPos.x][mouseGridPos.y]->changeTileType(TileTypes::grass);
				
				delete towerList[i];
				towerList[i] = nullptr;
				towerList.erase(towerList.begin() + i);
				i--;

				gameEngine->towerListMutex.unlock();

			}

			
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
	int viewChangeX = previousMousePos.x - mousePosWindow.x;
	int viewChangeY = previousMousePos.y - mousePosWindow.y;



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
			return false;
		}

		viewRelativeSizeX /= zoomRate;
		viewRelativeSizeY /= zoomRate;
		xdiff = (gameView.getCenter().x - mousePosView.x) * viewRelativeSizeX / 5.f;
		ydiff = (gameView.getCenter().y - mousePosView.y) * viewRelativeSizeX / 5.f;

	} else {
		if (viewRelativeSizeX >= 5.f) {
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