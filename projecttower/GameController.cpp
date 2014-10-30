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
	//VortexSprite temp(gameEngine->loadImageToSprite("Graphics/tile_1.png"));
	bgSprite = temp;
	bgSprite.setPosition(0, 0);
	//bgSprite.setSize((sf::Vector2f)gameEngine->getWindowSize());

	//tileSize = 25;
	gridTileSize = ((float)gameEngine->getWindowSize().x / (float)GAMEMAPSIZEX);

	for (int x = 0; x < GAMEMAPSIZEX; x++){
		for (int y = 0; y < GAMEMAPSIZEY; y++){

			sf::Texture * texImageTile;
			

			if (x == (GAMEMAPSIZEX / 2)) {
				texImageTile = gameEngine->loadImageToTexture("Graphics/wall.png");
				buildable[x][y] = false;
			}
			else if ((x == (GAMEMAPSIZEX / 2) - 1 || x == (GAMEMAPSIZEX / 2) + 1) && (y == (GAMEMAPSIZEY / 2) - 1 || y == (GAMEMAPSIZEY / 2) + 1)) {
				texImageTile = gameEngine->loadImageToTexture("Graphics/wall.png");
				buildable[x][y] = false;
			}
			else if ((x == (GAMEMAPSIZEX / 2) - 1 || x == (GAMEMAPSIZEX / 2) + 1) && (y == (GAMEMAPSIZEY / 2) || y == (GAMEMAPSIZEY / 2))) {
				texImageTile = gameEngine->loadImageToTexture("Graphics/cave.png");
				buildable[x][y] = false;
			}
			else if ((x <= (GAMEMAPSIZEX / 10) - 1 || x >= (GAMEMAPSIZEX - (GAMEMAPSIZEX / 10)) || ((x == GAMEMAPSIZEX / 2 - 2) || (x == GAMEMAPSIZEX / 2 + 2) || (x <= GAMEMAPSIZEX / 10) || x >= (GAMEMAPSIZEX - (GAMEMAPSIZEX / 10) - 1)) && (y == GAMEMAPSIZEY / 2))) {
				texImageTile = gameEngine->loadImageToTexture("Graphics/dirt.png");
				buildable[x][y] = false;
			}
			else {
				texImageTile = gameEngine->loadImageToTexture("Graphics/grass_tile.png");
				buildable[x][y] = true;
			}

			if ((x == (GAMEMAPSIZEX / 10) - 1 || x == (GAMEMAPSIZEX - (GAMEMAPSIZEX / 10))) && y != GAMEMAPSIZEY / 2) {
				texImageTile = gameEngine->loadImageToTexture("Graphics/wall.png");
				buildable[x][y] = false;
			}

			if (y < (GAMEMAPSIZEY / 6) || y >= (GAMEMAPSIZEY) - (GAMEMAPSIZEY / 6)) {
				texImageTile = gameEngine->loadImageToTexture("Graphics/water.png");
				buildable[x][y] = false;
			}
			/*
			int num = rand() % 101;
			if (num < 25)
				texImageTile = gameEngine->loadImageToTexture("Graphics/dirt.png");
			else if (num < 50)
				
			else if (num < 75)
				texImageTile = gameEngine->loadImageToTexture("Graphics/wall.png");
			else
				texImageTile = gameEngine->loadImageToTexture("Graphics/water.png");

				*/
			VortexSprite * tempSprite = new VortexSprite(*texImageTile);
			tempSprite->setPosition(x * gridTileSize, y * gridTileSize);
			tempSprite->setSize(gridTileSize, gridTileSize);
			mapTiles.push_back(tempSprite);

		}

	}

	//Tower * testTower = new Tower(gameEngine);
	//unitList.push_back(testTower);

	for (int i = 0; i < 100; i++){

		BasicUnit * testUnit = new BasicUnit(gameEngine, 50 + (rand() % (gameEngine->getWindowSize().x - 100)), 50 + (rand() % (gameEngine->getWindowSize().y - 100)));
		//BasicUnit * testUnit = new BasicUnit(gameEngine, 200, 200);
		unitList.push_back(testUnit);
		//renderObjectsVector.push_back(testUnit);

	}
	/*
	for (int i = 0; i < 10; i++) {

		BasicTower * testTower = new BasicTower(gameEngine, 50 + (rand() % (gameEngine->getWindowSize().x - 100)), 50 + (rand() % (gameEngine->getWindowSize().y - 100)));
		//BasicUnit * testUnit = new BasicUnit(gameEngine, 200, 200);
		towerList.push_back(testTower);
		//renderObjectsVector.push_back(testUnit);

	}

	//Testing convex buttonz
	std::vector<sf::Vector2f> vertices;
	vertices.push_back(sf::Vector2f(50, 50));
	vertices.push_back(sf::Vector2f(200, 50));
	vertices.push_back(sf::Vector2f(300, 100));
	vertices.push_back(sf::Vector2f(150, 275));
	vertices.push_back(sf::Vector2f(10, 210));
	vertices.push_back(sf::Vector2f(0, 85));
	VortexConvexButton testButton(300, 300, vertices, "Graphics/button.png", "Poop", gameEngine);
	buttonList.push_back(testButton);
	//renderObjectsVector.push_back(new VortexConvexButton(300, 300, vertices, "Graphics/button.png", "Poop", gameEngine));
	/*renderer->mapTiles = mapTiles;
	renderer->unitList = unitList;
	renderer->bgSprite = bgSprite;

	renderer->renderObjectsVector = renderObjectsVector;*/

	//renderer->currentRenderSubController = this;


	//renderObjectsVector.push_back(new VortexButtonRectangle(10, 10, 150, 55, "Graphics/button.png", "Button", gameEngine));

	//set view size relative to org window size

	viewRelativeSizeX = 2.f;
	viewRelativeSizeY = 2.f;

	viewWidth = WINDOWSIZEX / viewRelativeSizeX; ///2
	viewHeight = WINDOWSIZEY / viewRelativeSizeY; ///2

	//set view to center
	sf::View view(sf::FloatRect(((WINDOWSIZEX / 2) - (viewWidth / 2)), ((WINDOWSIZEY / 2) - (viewHeight / 2)), viewWidth, viewHeight));
	//sf::View view(sf::FloatRect(((WINDOWSIZEX) - (viewWidth)), ((WINDOWSIZEY) - (viewHeight)), viewWidth, viewHeight));
	gameView = view;

	towerUnderMouse = false;

	
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

	vectorMutex.lock();

	for (VortexSprite * currentRenderObj : backgroundTextures) {

		auto tempVector = currentRenderObj->getRenderDrawable();

		renderList.insert(renderList.end(), tempVector.begin(), tempVector.end());

	}

	for (auto currentRenderObj : mapTiles) {

		auto tempVector = currentRenderObj->getRenderDrawable();

		renderList.insert(renderList.end(), tempVector.begin(), tempVector.end());

	}

	

	vectorMutex.unlock();

	renderSuperList.push_back(renderList);

	return renderSuperList;
}

std::vector<std::vector<sf::Drawable *>> GameController::getDynamicRenderData() {
	
	std::vector<std::vector<sf::Drawable *>> renderSuperList;

	std::vector<sf::Drawable *> renderList;

	vectorMutex.lock();



	for (auto currentRenderVector : renderObjectsVector) {

		auto tempVector = currentRenderVector->getRenderDrawable();

		renderList.insert(renderList.end(), tempVector.begin(), tempVector.end());

	}

	

	for (auto currentRenderVector : towerList) {

		auto tempVector = currentRenderVector->getRenderDrawable();

		renderList.insert(renderList.end(), tempVector.begin(), tempVector.end());

	}


	for (auto currentRenderVector : unitList) {

		auto tempVector = currentRenderVector->getRenderDrawable();

		renderList.insert(renderList.end(), tempVector.begin(), tempVector.end());

	}

	if (gameGuiController->building) {
		renderList.push_back(towerBuildSprite);
	}


	vectorMutex.unlock();

	renderSuperList.push_back(renderList);


	
	return renderSuperList;

}

GameController::~GameController(){
}


std::vector<SubController *> GameController::getChildControllers() {

	return childControllers;

}


void GameController::update() {

	gameEngine->getWindow()->setView(gameView);

	 //Should be true when player wants to build
	auto mousePos = gameEngine->getMousePosition();
	
	if (gameEngine->eventMouseMove && gameGuiController->building == true) {
		auto mousePos = gameEngine->getMousePositionLocal();

		int xpos = mousePos.x / gridTileSize;
		int ypos = mousePos.y / gridTileSize;

		towerBuildSprite->setPosition(xpos * gridTileSize, (ypos * gridTileSize) - (towerBuildSprite->getTextureRect().height / 5));

		if (buildable[xpos][ypos]) {
			towerBuildSprite->setColor(ABLETOBUILD);
		}
		else {
			towerBuildSprite->setColor(UNABLETOBUILD);
		}
	}


	if (gameEngine->eventMouseWheelScrollUp) {

		std::cout << "WHEEL +! " << viewRelativeSizeX << " " << viewRelativeSizeY << "\n";
		if (viewRelativeSizeX < 10.f) {
			viewRelativeSizeX *= 2.0f;
			viewRelativeSizeY *= 2.0f;

			viewWidth = WINDOWSIZEX / viewRelativeSizeX; ///2
			viewHeight = WINDOWSIZEY / viewRelativeSizeY; ///2

			gameView.reset(sf::FloatRect(gameView.getCenter().x - (viewWidth / 2), gameView.getCenter().y - (viewHeight / 2), viewWidth, viewHeight));
		}

		

	}

	if (gameEngine->eventMouseWheelScrollDown) {

		if (viewRelativeSizeX > 1.f) {
			std::cout << "WHEEL -!\n";
			viewRelativeSizeX /= 2.0f;
			viewRelativeSizeY /= 2.0f;

			viewWidth = WINDOWSIZEX / viewRelativeSizeX; ///2
			viewHeight = WINDOWSIZEY / viewRelativeSizeY; ///2

			gameView.reset(sf::FloatRect(gameView.getCenter().x - (viewWidth / 2), gameView.getCenter().y - (viewHeight / 2), viewWidth, viewHeight));
		}

		

	}

	
	if (gameEngine->eventMousePressedRight) {
		if (gameEngine->eventMouseMove) {
			//Move the viewport
			int viewChangeX = previousMousePos.x - mousePos.x;
			int viewChangeY = previousMousePos.y - mousePos.y;

			//If going out of bounds on the left side
			if (gameView.getCenter().x + viewChangeX < gameView.getSize().x / 2) {
				gameView.setCenter(sf::Vector2f(gameView.getSize().x / 2, gameView.getCenter().y));
				viewChangeX = 0;
			} 
			//If going out of bounds on the right side
			else if (gameView.getCenter().x + viewChangeX > gameView.getSize().x + gameView.getSize().x / 2) {
				gameView.setCenter(sf::Vector2f(gameView.getSize().x + gameView.getSize().x / 2, gameView.getCenter().y));
				viewChangeX = 0;
			}

			//If going out of bounds on top
			if (gameView.getCenter().y + viewChangeY < gameView.getSize().y / 2) {
				gameView.setCenter(sf::Vector2f(gameView.getCenter().x, gameView.getSize().y / 2));
				viewChangeY = 0;
			}
			//If going out of bounds on bottom
			else if (gameView.getCenter().y + viewChangeY > gameView.getSize().y + gameView.getSize().y / 2) {
				gameView.setCenter(sf::Vector2f(gameView.getCenter().x, gameView.getSize().y + gameView.getSize().y / 2));
				viewChangeY = 0;
			}

			gameView.move(viewChangeX, viewChangeY);
		}
		/*
		BasicUnit * testUnit = new BasicUnit(gameEngine, mousePos.x, mousePos.y);
		testUnit->posX = testUnit->posX - (testUnit->width / 2);
		testUnit->posY = testUnit->posY - (testUnit->height / 2);
		//BasicUnit * testUnit = new BasicUnit(gameEngine, 200, 200);

		//an vector is NOT thread safe (R/W)
		vectorMutex.lock();

		unitList.push_back(testUnit);
		//renderObjectsVector.push_back(testUnit);

		vectorMutex.unlock();
		*/
		
		
	}
	
	if (gameEngine->eventMouseClickedLeft) {
		
		auto mousePos = gameEngine->getMousePositionLocal();

		int xpos = mousePos.x / gridTileSize;
		int ypos = mousePos.y / gridTileSize;

		if (buildable[xpos][ypos] && gameGuiController->building) {
			BasicTower * testTower = new BasicTower(gameEngine, xpos * gridTileSize, ypos * gridTileSize);
			vectorMutex.lock();
			towerList.push_back(testTower);
			vectorMutex.unlock();
			buildable[xpos][ypos] = false;
			//gameGuiController->building = false;
		} else {
			// Play unable to build beep sound
		}
		

	}
	if (gameEngine->eventMousePressedLeft) {

		vectorMutex.lock();

		auto mousePos = gameEngine->getMousePositionLocal();
		/*
		for (int i = 0; i < unitList.size(); i++) {

			if (unitList[i]->posX < mousePos.x) {
				delete unitList[i];
				unitList.erase(unitList.begin()+i);
				i--;
			}

			if (unitList[i]->hitPoint(mousePos)) {
				delete unitList[i];
				unitList.erase(unitList.begin() + i);
			}

		}
		*/
		

		vectorMutex.unlock();

	}
	

	//for (Entity * current : entityList){

	for (auto * current : renderObjectsVector) {

		current->update();

	}
	
	for (Unit * current : unitList) {
		//std::cout << "Move me!" << std::endl;
		current->update();
//		std::cout << current->posX << "  " << current->posY << std::endl;
	}

	//sorting units so the unit with the lowest base y is renderd first
	std::sort(unitList.begin(), unitList.end(), entitySortingStructDistanceDistance);
	std::sort(towerList.begin(), towerList.end(), entitySortingStructDistanceDistance);
	
	//delete testing
	//if (rand() % 100 < 10 && unitList.size() > 0) {

	//	vectorMutex.lock();

	//	auto unit = unitList[unitList.size() - 1];
	//	delete unit;
	//	unitList.pop_back();

	//	vectorMutex.unlock();

	//}


	//Check if units are in proxmity to towers.
	//TODO use spatial index grid instead of matching the pos of every fucking entity?
	//for (uint i = 0; i < towers.size(); i++) {
	//	//If tower has a target, make sure it is still in range
	//	towers[i]->update();

	//	//If tower has no target find the closest unit within range
	//	double bestRange = 99999999999;
	//	if (!towers[i]->target) {
	//		for (uint j = 0; j < units.size(); j++) {
	//			//Get distance between objects
	//			double xdist = abs(towers[i]->position.x - units[j]->position.x);
	//			double ydist = abs(towers[i]->position.y - units[j]->position.y);

	//			//No point square rooting me thinks
	//			//katet^2 + katet^2 = hypotenus^2 eller noe sånt
	//			double totdist = (xdist + xdist) * (ydist + ydist);
	//			double totrange = (towers[i]->range * towers[i]->range);
	//			if (totdist <= totrange && totdist < bestRange) {
	//				towers[i]->target = units[j];
	//			}
	//		}
	//	}
	//	//If the tower has a target by now it should attack
	//	if (towers[i]->target) {
	//		//If unit was destroyed, remove it.
	//		if (towers[i]->attack()) {
	//			for (uint j = 0; j < units.size(); j++) {
	//				if (units[j] == towers[i]->target) {
	//					delete units[j];
	//					units.erase(units.begin() + j);
	//				}

	//			}
	//		}
	//	}
	//}





	for (auto currentController : childControllers) {
		currentController->update();
	}

	previousMousePos = mousePos;
	
}