#include "MenuController.h"


MenuController::MenuController(Vortex * gameEngine, int controllerID) : SubController(gameEngine, controllerID) {
	nextControllerID = MENU_CONTROLLER_ID;

	doMultiplayer = false;

	


}


MenuController::~MenuController()
{
}

void MenuController::initController() {

}

void MenuController::loadAssets() {


	sf::Texture * texBackgroundImage = gameEngine->loadImageToTexture("Graphics/menuBackground.jpg");
	backgroundImage = new VortexSprite(*texBackgroundImage);
	backgroundImage->setPosition(0, 0);
	backgroundImage->setSize(WINDOWSIZEX, WINDOWSIZEY);


	int centerX = gameEngine->getWindowSize().x / 2;
	int centerY = gameEngine->getWindowSize().y / 2;
	int buttonWidth = 180;
	int buttonHeight = 60;


	quitGameButton = new VortexButtonRectangle((buttonWidth / 2), WINDOWSIZEY - buttonHeight * 3, buttonWidth, buttonHeight, "Graphics/blackbutton.png", "Quit", gameEngine, 175);
	startMultiplayerGameButton = new VortexButtonRectangle((buttonWidth / 2), quitGameButton->getPosition().y - buttonHeight * 1.2, buttonWidth, buttonHeight, "Graphics/blackbutton.png", "Multiplayer", gameEngine, 175);
	startSingelplayerGameButton = new VortexButtonRectangle((buttonWidth / 2), startMultiplayerGameButton->getPosition().y - buttonHeight * 1.2, buttonWidth, buttonHeight, "Graphics/blackbutton.png", "Singleplayer", gameEngine, 175);


	quitGameButton->setHoverImage("Graphics/graybutton.png");
	startSingelplayerGameButton->setHoverImage("Graphics/graybutton.png");
	startMultiplayerGameButton->setHoverImage("Graphics/graybutton.png");

	guiObjects.push_back(startSingelplayerGameButton);
	guiObjects.push_back(quitGameButton);
	guiObjects.push_back(startMultiplayerGameButton);


}

void MenuController::update() {
	if (startSingelplayerGameButton->isPressed && startSingelplayerGameButton->hovering) {
		nextControllerID = GAME_CONTROLLER_ID;
	}
	else if (quitGameButton->isPressed && quitGameButton->hovering) {
		gameEngine->closeApplication();
	}
	else if (startMultiplayerGameButton->isPressed && startMultiplayerGameButton->hovering) {
		nextControllerID = SERVERBROWSER_CONTROLLER_ID;
	}


	for (auto *current : guiObjects) {
		current->update();
	}
	
	

}

std::vector<std::vector<sf::Drawable *>> MenuController::getDynamicRenderData() {
	
	std::vector<std::vector<sf::Drawable *>> renderList;
	std::vector<sf::Drawable *> renderListSub;


	
	renderList.push_back(renderListSub);
	return renderList;
	
}
std::vector<std::vector<sf::Drawable *>> MenuController::getStaticRenderData() {
	
	std::vector<std::vector<sf::Drawable *>> renderList;

	std::vector<sf::Drawable *> renderListSub;
	
	
	//Add static objects to be rendered into the return list
	guiMutex.lock();
	renderListSub.push_back(backgroundImage);

	for (auto currentRenderVector : guiObjects) {
		for (auto currentRenderObj : currentRenderVector->getRenderDrawable()) {
			renderListSub.push_back(currentRenderObj);
		}
	}
	guiMutex.unlock();

	renderList.push_back(renderListSub);
	
	return renderList;
}

sf::View MenuController::getView() {
	return sf::View(sf::FloatRect(0, 0, WINDOWSIZEX, WINDOWSIZEY));
}

std::vector<SubController *> MenuController::getChildControllers() {

	return childControllers;

}