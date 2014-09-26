#include "MenuController.h"


MenuController::MenuController(Vortex * gameEngine) : SubController(gameEngine){
	nextControllerID = GAME_CONTROLLER_ID;

	sf::Texture * texImage = gameEngine->loadImageToTexture("Graphics/tile_1.png");
	VortexSprite temp(*texImage);
	//VortexSprite temp(gameEngine->loadImageToSprite("Graphics/tile_1.png"));
	testSprite = temp;
	testSprite.setPosition(200, 200);

}


MenuController::~MenuController()
{
}

void MenuController::update(){

	//gameEngine->getWindow()->draw(testSprite); //Use the renderer to draw

}
