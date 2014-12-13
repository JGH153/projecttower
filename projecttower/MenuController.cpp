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
	
	quitGameButton->setHoverImage("Graphics/graybutton.png");
	startGameButton->setHoverImage("Graphics/graybutton.png");
	
	guiObjects.push_back(startGameButton);
	guiObjects.push_back(quitGameButton);
}


MenuController::~MenuController()
{
}

void MenuController::preloadAssets() {

}

void MenuController::update() {
	//std::cout << "In menu controller" << std::endl;
	for (auto *current : guiObjects) {
		current->update();
	}

	if (gameEngine->eventMouseReleasedLeft) {
		if (startGameButton->buttonClicked()) {
			nextControllerID = GAME_CONTROLLER_ID;
		}
		else if (quitGameButton->buttonClicked()) {
			gameEngine->closeApplication();
		}
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