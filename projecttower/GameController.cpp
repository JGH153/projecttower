#include "GameController.h"


GameController::GameController(Vortex * gameEngine){

	this->gameEngine = gameEngine;

	gameGuiController = new GameGuiController(gameEngine);

	sf::Texture * texImage = gameEngine->loadImageToTexture("Graphics/Textures/foresttile.png");
	texImage->setRepeated(true);
	texImage->getSize();
	VortexSprite temp(*texImage);
	//VortexSprite temp(gameEngine->loadImageToSprite("Graphics/tile_1.png"));
	bgSprite = temp;
	bgSprite.setPosition(0, 0);
	//bgSprite.setSize((sf::Vector2f)gameEngine->getWindowSize());

}


GameController::~GameController(){
}


void GameController::renderBG(){
	for (int x = 0; x < (gameEngine->getWindowSize().x % (int)bgSprite.getSize().x); x++){

		for (int y = 0; y < (gameEngine->getWindowSize().x % (int)bgSprite.getSize().x); y++){

			bgSprite.setPosition(x * (int)bgSprite.getSize().x, y * (int)bgSprite.getSize().y);
			gameEngine->getWindow()->draw(bgSprite);
		}
	}

}

void GameController::update() {

	renderBG();

	//Check if units are in proxmity to towers.
	//TODO use spatial index grid instead of matching the pos of every fucking entity?
	for (uint i = 0; i < towers.size(); i++) {
		//If tower has a target, make sure it is still in range
		towers[i]->update();

		//If tower has no target find the closest unit within range
		double bestRange = 99999999999;
		if (!towers[i]->target) {
			for (uint j = 0; j < units.size(); j++) {
				//Get distance between objects
				double xdist = abs(towers[i]->position.x - units[j]->position.x);
				double ydist = abs(towers[i]->position.y - units[j]->position.y);

				//No point square rooting me thinks
				//katet^2 + katet^2 = hypotenus^2 eller noe sånt
				double totdist = xdist * xdist + ydist * ydist;
				if (totdist <= towers[i]->range && totdist < bestRange) {
					towers[i]->target = units[j];
				}
			}
		}
		//If the tower has a target by now it should attack
		if (towers[i]->target) {
			//If unit was destroyed, remove it.
			if (towers[i]->attack()) {
				for (uint j = 0; j < units.size(); j++) {
					if (units[j] == towers[i]->target) {
						delete units[j];
						units.erase(units.begin() + j);
					}

				}
			}
		}
	}







	gameGuiController->update();


}