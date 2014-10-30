#include "GameGuiController.h"


GameGuiController::GameGuiController(Vortex * gameEngine, int controllerID) : SubController(gameEngine, controllerID) {

	buildButton = new VortexButtonRectangle(0, 0, 200, 50, "Graphics/button.png", "Toggle Build", gameEngine);
	buildButton->setHoverImage("Graphics/dirt.png");

	building = true;

}


GameGuiController::~GameGuiController() {
}

void GameGuiController::update() {

	//gameEngine->getWindow()->setView(gameView);

	//std::cout << "In menu controller" << std::endl;
	for (auto *current : guiObjects) {
		current->update();
	}

	if (gameEngine->eventMouseClickedLeft) {
		nextControllerID = GAME_CONTROLLER_ID;
	}

	buildButton->update();

	if (gameEngine->eventMouseReleasedLeft) {

		if (buildButton->mouseOver()) {

			building = !building;

		}
	}

}

std::vector<std::vector<sf::Drawable *>> GameGuiController::getDynamicRenderData() {

	std::vector<std::vector<sf::Drawable *>> renderList;

	std::vector<sf::Drawable *> renderListSub;


	renderList.push_back(renderListSub);
	renderList.push_back(buildButton->getRenderDrawable());
	return renderList;

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
	return renderList;
}
std::vector<std::vector<sf::Drawable *>> GameGuiController::getStaticRenderData() {

	std::vector<std::vector<sf::Drawable *>> renderList;

	std::vector<sf::Drawable *> renderListSub;


	//Add static objects to be rendered into the return list
	guiMutex.lock();
	for (auto currentRenderVector : guiObjects) {
		for (auto currentRenderObj : currentRenderVector->getRenderDrawable()) {
			renderListSub.push_back(currentRenderObj);
		}
	}
	guiMutex.unlock();

	renderList.push_back(renderListSub);

	return renderList;
}

sf::View GameGuiController::getView() {
	return sf::View(sf::FloatRect(0, 0, WINDOWSIZEX, WINDOWSIZEY));
}

std::vector<SubController *> GameGuiController::getChildControllers() {

	return childControllers;

}