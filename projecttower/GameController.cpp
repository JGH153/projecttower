#include "GameController.h"


GameController::GameController(Vortex * gameEngine) : SubController(gameEngine){

	gameGuiController = new GameGuiController(gameEngine);

	int tileSize = 50;

	for (int x = 0; x < (gameEngine->getWindowSize().x / tileSize); x++) {
		for (int y = 0; y < (gameEngine->getWindowSize().y / tileSize); y++) {

			sf::Texture * texImageTile;
			texImageTile = gameEngine->loadImageToTexture("Graphics/Textures/foresttile.png");
			VortexSprite * tempSprite = new VortexSprite(*texImageTile);
			tempSprite->setPosition(x * tileSize, y * tileSize);
			tempSprite->setSize(tileSize, tileSize);
			backgroundTextures.push_back(tempSprite);


		}
	}




	sf::Texture * texImage = gameEngine->loadImageToTexture("Graphics/Textures/foresttile.png");
	texImage->setRepeated(true);
	texImage->getSize();
	VortexSprite temp(*texImage);
	//VortexSprite temp(gameEngine->loadImageToSprite("Graphics/tile_1.png"));
	bgSprite = temp;
	bgSprite.setPosition(0, 0);
	//bgSprite.setSize((sf::Vector2f)gameEngine->getWindowSize());

	int guiOffsetY = 50;
	tileSize = 25;

	for (int x = 0; x < (gameEngine->getWindowSize().x / tileSize); x++){
		for (int y = 0; y < ((gameEngine->getWindowSize().y / tileSize) - ((guiOffsetY * 2) / tileSize)); y++){

			sf::Texture * texImageTile;

			int num = rand() % 101;
			if (num < 25)
				texImageTile = gameEngine->loadImageToTexture("Graphics/dirt.png");
			else if (num < 50)
				texImageTile = gameEngine->loadImageToTexture("Graphics/grass.png");
			else if (num < 75)
				texImageTile = gameEngine->loadImageToTexture("Graphics/wall.png");
			else
				texImageTile = gameEngine->loadImageToTexture("Graphics/water.png");

			VortexSprite * tempSprite = new VortexSprite(*texImageTile);
			tempSprite->setPosition(x * tileSize, guiOffsetY + (y * tileSize));
			tempSprite->setSize(tileSize, tileSize);
			mapTiles.push_back(tempSprite);

		}

	}

	//Tower * testTower = new Tower(gameEngine);
	//unitList.push_back(testTower);

	for (int i = 0; i < 1000; i++){

		BasicUnit * testUnit = new BasicUnit(gameEngine, 50 + (rand() % (gameEngine->getWindowSize().x - 100)), 50 + (rand() % (gameEngine->getWindowSize().y - 100)));
		//BasicUnit * testUnit = new BasicUnit(gameEngine, 200, 200);
		unitList.push_back(testUnit);
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
	VortexConvexButton testButton(vertices, "Graphics/button.png", "", "Poop", gameEngine);
	buttonList.push_back(testButton);

	/*renderer->mapTiles = mapTiles;
	renderer->unitList = unitList;
	renderer->bgSprite = bgSprite;

	renderer->renderObjectsVector = renderObjectsVector;*/

	//renderer->currentRenderSubController = this;



	
}

struct sortinStructDistance {

	bool operator() (Unit * a, Unit * b) {

		if (a->posY + a->height < b->posY + b->height) {

			//if (a->posX + a->width < b->posX + b->height) {
				return true;
			//} else {
			//	return false;
			//}


		} else {
			return false;
		}

	}

} sortingInstanceDistance;


std::vector<VortexSprite *> GameController::getRenderSprites() {
	
	std::vector<VortexSprite *> spriteList;

	vectorMutex.lock();

	for (VortexSprite * currentRenderObj : backgroundTextures) {

		spriteList.push_back(currentRenderObj);
		//gameEngine->getWindow()->draw(*currentRenderObj.getRenderSprite());

	}


	for (uint i = 0; i < mapTiles.size(); i++) {

		spriteList.push_back(mapTiles[i]);
		//gameEngine->getWindow()->draw(*mapTiles[i].getRenderSprite());

	}

	for (auto currentRenderObj : renderObjectsVector) {

		spriteList.push_back(currentRenderObj->getRenderSprite());
		//gameEngine->getWindow()->draw(*currentRenderObj->getRenderSprite());

	}

	for (auto currentRenderObj : unitList) {

		spriteList.push_back(currentRenderObj->getRenderSprite());
		//gameEngine->getWindow()->draw(*currentRenderObj->getRenderSprite());

	}


	vectorMutex.unlock();


	
	return spriteList;

}

GameController::~GameController(){
}



void GameController::update() {

	//renderBG();

	//renderTiles();


	if (gameEngine->eventMousePressedLeft) {
		
		auto mousePos = gameEngine->getMousePositionLocal();

		BasicUnit * testUnit = new BasicUnit(gameEngine, mousePos.x, mousePos.y);
		testUnit->posX = testUnit->posX - (testUnit->width / 2);
		testUnit->posY = testUnit->posY - (testUnit->height / 2);
		//BasicUnit * testUnit = new BasicUnit(gameEngine, 200, 200);

		//an vector is NOT thread safe (R/W)
		vectorMutex.lock();

		unitList.push_back(testUnit);
		//renderObjectsVector.push_back(testUnit);

		vectorMutex.unlock();

	}
	

	//for (Entity * current : entityList){
	
	for (Unit * current : unitList) {
		//std::cout << "Move me!" << std::endl;
		current->update();
//		std::cout << current->posX << "  " << current->posY << std::endl;
	}

	//sorting units so the unit with the lowest base y is renderd first
	std::sort(unitList.begin(), unitList.end(), sortingInstanceDistance);
	


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







	gameGuiController->update();
	
	
}