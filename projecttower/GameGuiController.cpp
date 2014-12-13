#include "GameGuiController.h"


GameGuiController::GameGuiController(Vortex * gameEngine, int controllerID) : SubController(gameEngine, controllerID) {

	buildButton = new VortexButtonRectangle(0, 0, 200, 50, "Graphics/button.png", "Toggle Build", gameEngine);
	buildButton->setHoverImage("Graphics/dirt.png");

	deleteTowerButton = new VortexButtonRectangle(200, 0, 200, 50, "Graphics/button.png", "Toggle del", gameEngine);
	deleteTowerButton->setHoverImage("Graphics/dirt.png");

	building = true;
	deleting = false;

	playerResources = 50;

	resourceText = new VortexText("Resources: " + std::to_string(playerResources), *gameEngine->loadFont("Fonts/arial.ttf"), 34);
	resourceText->setColor(sf::Color::White);
	resourceText->setStyle(sf::Text::Bold);
	float textWidth = resourceText->getLocalBounds().width;
	resourceText->setPosition(WINDOWSIZEX - textWidth, 0);

	resourcePanel = new sf::RectangleShape(sf::Vector2f(resourceText->getLocalBounds().width, resourceText->getLocalBounds().height * 1.5));
	resourcePanel->setFillColor(sf::Color(25, 25, 25, 200));
	resourcePanel->setPosition(WINDOWSIZEX - textWidth, 0);
}

void GameGuiController::preloadAssets() {

}


GameGuiController::~GameGuiController() {
}

bool GameGuiController::mouseOverSomeButton(sf::View resetToView) {
	bool overSomeButton = false;

	gameEngine->setMousePosView(gameView);

	if (buildButton->mouseOver()) {
		overSomeButton = true;
	}

	gameEngine->setMousePosView(resetToView);

	return overSomeButton;

}

void GameGuiController::update() {

	gameEngine->setMousePosView(gameView);
	auto mousePosWindow = gameEngine->getMousePositionRelativeToWindow();
	auto mousePosView = gameEngine->getMousePositionRelativeToSetView();

	//gameEngine->getWindow()->setView(gameView);

	//std::cout << "In menu controller" << std::endl;
	for (auto *current : guiObjects) {
		current->update();
	}

	if (gameEngine->eventMouseClickedLeft) {
		nextControllerID = GAME_CONTROLLER_ID;
	}

	buildButton->update();
	deleteTowerButton->update();

	if (gameEngine->eventMouseReleasedLeft) {

		if (buildButton->mouseOver()) {

			if (building) {
				building = false;
				
			} else {
				building = true;
				deleting = false;
			}


		}

		if (deleteTowerButton->mouseOver()) {

			if (deleting) {
				deleting = false;
				
			} else {
				deleting = true;
				building = false;
			}


		}

	}

}

std::vector<std::vector<sf::Drawable *>> GameGuiController::getDynamicRenderData() {

	std::vector<std::vector<sf::Drawable *>> renderList;

	std::vector<sf::Drawable *> renderListSub;


	renderList.push_back(renderListSub);
	renderList.push_back(buildButton->getRenderDrawable());
	renderList.push_back(deleteTowerButton->getRenderDrawable());
	
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

	renderListSub.push_back(resourcePanel);
	for (auto currentRenderObj : resourceText->getRenderDrawable()) {
		renderListSub.push_back(currentRenderObj);
	}

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

void GameGuiController::setPlayerResources(int newValue) {
	playerResources = newValue;
	resourceText->setString("Resources: " + std::to_string(playerResources));
	float textWidth = resourceText->getLocalBounds().width;
	resourceText->setPosition(WINDOWSIZEX - textWidth, 0);

	resourcePanel->setPosition(WINDOWSIZEX - textWidth, 0);
	resourcePanel->setSize(sf::Vector2f(textWidth, resourceText->getLocalBounds().height * 1.5));
}

int GameGuiController::getPlayerResources() {
	return playerResources;
}