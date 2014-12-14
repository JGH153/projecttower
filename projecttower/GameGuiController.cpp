#include "GameGuiController.h"


GameGuiController::GameGuiController(Vortex * gameEngine, int controllerID) : SubController(gameEngine, controllerID) {
	int buttonSize = 64;
	int buttonSpread = 1;
	bottomToolbarPosY = WINDOWSIZEY - buttonSize;
	buildButton = new VortexButtonRectangle(WINDOWSIZEX / 2 - buttonSize, bottomToolbarPosY, buttonSize, buttonSize, "Graphics/GUI/diy-hammer-icon.png", "", gameEngine);
	buildButton->setHoverImage("Graphics/GUI/diy-hammer-hover-icon.png");

	deleteTowerButton = new VortexButtonRectangle(buildButton->getPosition().x - buttonSize - buttonSpread, bottomToolbarPosY, buttonSize, buttonSize, "Graphics/GUI/delete-icon.png", "", gameEngine);
	deleteTowerButton->setHoverImage("Graphics/GUI/delete-hover-icon.png");

	sendUnit1Button = new VortexButtonRectangle(WINDOWSIZEX / 2 + buttonSpread, bottomToolbarPosY, buttonSize, buttonSize, "Graphics/GUI/ironman-button.png", "", gameEngine);
	sendUnit1Button->setHoverImage("Graphics/GUI/ironman-hover-button.png");

	building = true;
	deleting = false;

	playerResources = 50;
	playerIncome = 10;
	msSinceLastIncome = 30000;

	resourceText = new VortexText("Resources: " + std::to_string(playerResources), *gameEngine->loadFont("Fonts/arial.ttf"), 34);
	resourceText->setColor(sf::Color::White);
	resourceText->setStyle(sf::Text::Bold);
	float resourceTextWidth = resourceText->getLocalBounds().width;
	resourceText->setPosition(WINDOWSIZEX - resourceTextWidth, 0);

	incomeText = new VortexText("Income: " + std::to_string(playerIncome), *gameEngine->loadFont("Fonts/arial.ttf"), 17);
	incomeText->setColor(sf::Color::White);
	incomeText->setStyle(sf::Text::Bold);
	float incomeTextWidth = incomeText->getLocalBounds().width;
	incomeText->setPosition(WINDOWSIZEX - incomeTextWidth, resourceText->getLocalBounds().height + incomeText->getLocalBounds().height);

	timeText = new VortexText("Time till income: " + std::to_string(msSinceLastIncome / 1000), *gameEngine->loadFont("Fonts/arial.ttf"), 17);
	timeText->setColor(sf::Color::White);
	timeText->setStyle(sf::Text::Bold);
	float timeTextWidth = timeText->getLocalBounds().width;
	timeText->setPosition(WINDOWSIZEX - timeTextWidth, resourceText->getLocalBounds().height + incomeText->getLocalBounds().height + timeText->getLocalBounds().height);

	resourcePanel = new sf::RectangleShape(sf::Vector2f(resourceText->getLocalBounds().width, timeText->getPosition().y + timeText->getLocalBounds().height + 10));
	resourcePanel->setFillColor(sf::Color(25, 25, 25, 200));
	resourcePanel->setPosition(WINDOWSIZEX - resourceTextWidth, 0);

	guiObjects.push_back(buildButton);
	guiObjects.push_back(deleteTowerButton);
	guiObjects.push_back(sendUnit1Button);
	guiObjects.push_back(resourceText);
	guiObjects.push_back(incomeText);
	guiObjects.push_back(timeText);

	
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

	msSinceLastIncome -= gameEngine->deltaTime.asMilliseconds();
	if (msSinceLastIncome <= 0) {
		msSinceLastIncome += 30000;
		setPlayerResources(playerResources + playerIncome);
	}
	setTimer(msSinceLastIncome / 1000);

	if (gameEngine->eventMouseReleasedLeft) {

		if (buildButton->isPressed && buildButton->hovering) {
			if (building) {
				building = false;

			}
			else {
				building = true;
				deleting = false;
			}
		}
		else if (deleteTowerButton->isPressed && deleteTowerButton->hovering) {
			if (deleting) {
				deleting = false;

			}
			else {
				deleting = true;
				building = false;
			}
		}

		else if (sendUnit1Button->isPressed && sendUnit1Button->hovering) {
			if (playerResources >= 10) {
				setPlayerResources(playerResources - 10);
				setPlayerIncome(playerIncome + 1);
				unitsToSpawn.push_back(1);
			}
		}
	}



	for (auto *current : guiObjects) {
		current->update();
	}
}

std::vector<std::vector<sf::Drawable *>> GameGuiController::getDynamicRenderData() {

	std::vector<std::vector<sf::Drawable *>> renderList;

	//std::vector<sf::Drawable *> renderListSub;


	
	return renderList;
}

std::vector<std::vector<sf::Drawable *>> GameGuiController::getStaticRenderData() {

	std::vector<std::vector<sf::Drawable *>> renderList;

	std::vector<sf::Drawable *> renderListSub;

	//Add static objects to be rendered into the return list
	guiMutex.lock();

	renderListSub.push_back(resourcePanel);
	
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
	resourcePanel->setSize(sf::Vector2f(resourceText->getLocalBounds().width, timeText->getPosition().y + timeText->getLocalBounds().height + 10));
}

void GameGuiController::setPlayerIncome(int newValue) {
	playerIncome = newValue;
	incomeText->setString("Income: " + std::to_string(playerIncome));
	float textWidth = incomeText->getLocalBounds().width;
	incomeText->setPosition(WINDOWSIZEX - textWidth, resourceText->getLocalBounds().height + incomeText->getLocalBounds().height);
}

void GameGuiController::setTimer(int newValue) {
	timeText->setString("Time till income: " + std::to_string(newValue));
	float textWidth = timeText->getLocalBounds().width;
	timeText->setPosition(WINDOWSIZEX - textWidth, resourceText->getLocalBounds().height + incomeText->getLocalBounds().height + timeText->getLocalBounds().height);
}

int GameGuiController::getPlayerResources() {
	return playerResources;
}