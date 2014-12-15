#include "MenuController.h"


MenuController::MenuController(Vortex * gameEngine, int controllerID) : SubController(gameEngine, controllerID) {
	nextControllerID = MENU_CONTROLLER_ID;

	sf::Texture * texBackgroundImage = gameEngine->loadImageToTexture("Graphics/menuBackground.jpg");
	backgroundImage = new VortexSprite(*texBackgroundImage);
	backgroundImage->setPosition(0, 0);
	backgroundImage->setSize(WINDOWSIZEX, WINDOWSIZEY);


	int centerX = gameEngine->getWindowSize().x / 2;
	int centerY = gameEngine->getWindowSize().y / 2;
	int buttonWidth = 180;
	int buttonHeight = 60;


	quitGameButton = new VortexButtonRectangle((buttonWidth / 2), WINDOWSIZEY - buttonHeight* 2, buttonWidth, buttonHeight, "Graphics/blackbutton.png", "Quit", gameEngine, 175);
	startGameButton = new VortexButtonRectangle((buttonWidth / 2), quitGameButton->getPosition().y - buttonHeight * 1.2, buttonWidth, buttonHeight, "Graphics/blackbutton.png", "New Game", gameEngine, 175);
	
	networkClientButton = new VortexButtonRectangle(WINDOWSIZEX - (buttonWidth * 1.5), WINDOWSIZEY - buttonHeight * 2, buttonWidth, buttonHeight, "Graphics/blackbutton.png", "Client", gameEngine, 175);
	networkServerButton = new VortexButtonRectangle(WINDOWSIZEX - (buttonWidth * 1.5), quitGameButton->getPosition().y - buttonHeight * 1.2, buttonWidth, buttonHeight, "Graphics/blackbutton.png", "Server", gameEngine, 175);

	quitGameButton->setHoverImage("Graphics/graybutton.png");
	startGameButton->setHoverImage("Graphics/graybutton.png");
	
	networkClientButton->setHoverImage("Graphics/graybutton.png");
	networkServerButton->setHoverImage("Graphics/graybutton.png");

	guiObjects.push_back(startGameButton);
	guiObjects.push_back(quitGameButton);
	guiObjects.push_back(networkClientButton);
	guiObjects.push_back(networkServerButton);
}


MenuController::~MenuController()
{
}

void MenuController::preloadAssets() {

}

void MenuController::update() {

	if (startGameButton->buttonClicked()) {
		nextControllerID = GAME_CONTROLLER_ID;
	}
	else if (quitGameButton->buttonClicked()) {
		gameEngine->closeApplication();
	}
	else if (networkClientButton->buttonClicked()) {
		nextControllerID = NETWORK_GAME_CLIENT_ID;
	}
	else if (networkServerButton->buttonClicked()) {
		nextControllerID = NETWORK_GAME_SERVER_ID;
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