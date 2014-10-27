#include "MenuController.h"


MenuController::MenuController(Vortex * gameEngine) : SubController(gameEngine){
	nextControllerID = MENU_CONTROLLER_ID;
	int centerX = gameEngine->getWindowSize().x / 2;
	int centerY = gameEngine->getWindowSize().y / 2;
	int buttonWidth = 180;
	int buttonHeight = 60;

	std::vector<sf::Vector2f> vertices;
	vertices.push_back(sf::Vector2f(50, 50));
	vertices.push_back(sf::Vector2f(200, 50));
	vertices.push_back(sf::Vector2f(300, 100));
	vertices.push_back(sf::Vector2f(150, 275));
	vertices.push_back(sf::Vector2f(10, 210));
	vertices.push_back(sf::Vector2f(0, 85));

	guiObjects.push_back(new VortexButtonRectangle(centerX - (buttonWidth / 2), centerY - (buttonHeight / 2), buttonWidth, buttonHeight, "Graphics/button.png", "Menubutton", gameEngine));
	guiObjects.push_back(new VortexConvexButton(300, 300, vertices, "Graphics/button.png", "Poop", gameEngine));
}


MenuController::~MenuController()
{
}

void MenuController::update() {
	//std::cout << "In menu controller" << std::endl;
	for (auto *current : guiObjects) {
		current->update();
	}

	if (gameEngine->eventMouseClickedLeft) {
		nextControllerID = GAME_CONTROLLER_ID;
	}
}

std::vector<sf::Drawable *> MenuController::getDynamicRenderData() {
	std::vector<sf::Drawable *> returnList;
	/*
	//Add dynamic objects to be rendered into the return list
	guiMutex.lock();
	for (auto currentRenderVector : guiObjects) {
		for (auto currentRenderObj : currentRenderVector->getRenderData()) {
			returnList.push_back(currentRenderObj);
		}
	}
	guiMutex.unlock();
	*/
	return returnList;
}
std::vector<sf::Drawable *> MenuController::getStaticRenderData() {
	std::vector<sf::Drawable *> returnList;
	
	//Add static objects to be rendered into the return list
	guiMutex.lock();
	for (auto currentRenderVector : guiObjects) {
		for (auto currentRenderObj : currentRenderVector->getRenderDrawable()) {
			returnList.push_back(currentRenderObj);
		}
	}
	guiMutex.unlock();
	
	return returnList;
}