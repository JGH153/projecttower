#include "MenuController.h"


MenuController::MenuController(Vortex * gameEngine) : SubController(gameEngine){
	nextControllerID = MENU_CONTROLLER_ID;
	int centerX = gameEngine->getWindowSize().x / 2;
	int centerY = gameEngine->getWindowSize().y / 2;
	int buttonWidth = 180;
	int buttonHeight = 60;

	guiObjects.push_back(new VortexButtonRectangle(centerX - (buttonWidth / 2), centerY - (buttonHeight / 2), buttonWidth, buttonHeight, "Graphics/button.png", gameEngine));
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

std::vector<RenderData> MenuController::getDynamicRenderData() {
	std::vector<RenderData> returnList;
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
std::vector<RenderData> MenuController::getStaticRenderData() {
	std::vector<RenderData> returnList;
	
	//Add static objects to be rendered into the return list
	guiMutex.lock();
	for (auto currentRenderVector : guiObjects) {
		for (auto currentRenderObj : currentRenderVector->getRenderData()) {
			returnList.push_back(currentRenderObj);
		}
	}
	guiMutex.unlock();
	
	return returnList;
}