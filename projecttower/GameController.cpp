#include "GameController.h"


GameController::GameController(Vortex * gameEngine) : SubController(gameEngine){

	

	gameGuiController = new GameGuiController(gameEngine);

	sf::Texture * texImage = gameEngine->loadImageToTexture("Graphics/Textures/foresttile.png");
	texImage->setRepeated(true);
	texImage->getSize();
	VortexSprite temp(*texImage);
	//VortexSprite temp(gameEngine->loadImageToSprite("Graphics/tile_1.png"));
	bgSprite = temp;
	bgSprite.setPosition(0, 0);
	//bgSprite.setSize((sf::Vector2f)gameEngine->getWindowSize());

	int guiOffsetY = 50;
	int tileSize = 25;

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

			VortexSprite tempSprite(*texImageTile);
			tempSprite.setPosition(x * tileSize, guiOffsetY + (y * tileSize));
			tempSprite.setSize(tileSize, tileSize);
			mapTiles.push_back(tempSprite);

		}

	}

	//Tower * testTower = new Tower(gameEngine);
	//unitList.push_back(testTower);

	for (int i = 0; i < 1000; i++){

		BasicUnit * testUnit = new BasicUnit(gameEngine, 50 + (rand() % (gameEngine->getWindowSize().x - 100)), 50 + (rand() % (gameEngine->getWindowSize().y - 100)));
		//BasicUnit * testUnit = new BasicUnit(gameEngine, 200, 200);
		unitList.push_back(testUnit);

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

}


GameController::~GameController(){
}


void GameController::renderBG(){
	for (int x = 0; x < (gameEngine->getWindowSize().x / (int)bgSprite.getSize().x) + (int)bgSprite.getSize().x; x++){

		for (int y = 0; y < (gameEngine->getWindowSize().y / (int)bgSprite.getSize().y) + (int)bgSprite.getSize().y; y++){

			bgSprite.setPosition(x * (int)bgSprite.getSize().x, y * (int)bgSprite.getSize().y);
			gameEngine->getWindow()->draw(bgSprite);
		}
	}

}

void GameController::renderTiles(){

	for (uint i = 0; i < mapTiles.size(); i++){

		gameEngine->getWindow()->draw(mapTiles[i]);

	}

}

struct afsdgfghb{

	bool operator() (Unit * a, Unit * b) {

		return (a->posY + a->height < b->posY + b->height);

	}

} watever;

void GameController::update() {

	renderBG();

	renderTiles();

<<<<<<< HEAD
	

	for (Entity * current : entityList){
=======
	//sorting units so the unit with the lowest base y is renderd first
	std::sort(unitList.begin(), unitList.end(), watever);

	for (Unit * current : unitList) {
>>>>>>> c1cab4e80390af29b9c54ea5972f8a7f117ac331

		current->update();

	}

	
	


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
	//			//katet^2 + katet^2 = hypotenus^2 eller noe s�nt
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
	
	//BUG: Using an iterator fucks shit up for some reason..
	for (int i = 0; i < buttonList.size(); i++) {
		buttonList[i].update(0);
	}

}