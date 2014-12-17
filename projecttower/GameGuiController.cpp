#include "GameGuiController.h"


GameGuiController::GameGuiController(Vortex * gameEngine, int controllerID) : SubController(gameEngine, controllerID) {
	int buttonSize = 64;
	int buttonSpread = 1;
	bottomToolbarPosY = WINDOWSIZEY - buttonSize;
	buildButton = new VortexButtonRectangle(WINDOWSIZEX / 2 - buttonSize, bottomToolbarPosY, buttonSize, buttonSize, "Graphics/GUI/build-arrowtower.png", "", gameEngine, 255, "Arrow tower\nCost 10");
	buildButton->setHoverImage("Graphics/GUI/build-arrowtower-hover.png");

	deleteTowerButton = new VortexButtonRectangle(buildButton->getPosition().x - buttonSize - buttonSpread, bottomToolbarPosY, buttonSize, buttonSize, "Graphics/GUI/delete-icon.png", "", gameEngine, 255, "Delete tower");
	deleteTowerButton->setHoverImage("Graphics/GUI/delete-hover-icon.png");

	sendUnit1Button = new VortexButtonRectangle(WINDOWSIZEX / 2 + buttonSpread, bottomToolbarPosY, buttonSize, buttonSize, "Graphics/GUI/ironman-button.png", "", gameEngine, 255, "Level 1 unit\nCost 10\n +1 Income");
	sendUnit1Button->setHoverImage("Graphics/GUI/ironman-hover-button.png");

	sendUnit2Button = new VortexButtonRectangle(sendUnit1Button->getPosition().x + sendUnit1Button->getWidth() + buttonSpread, bottomToolbarPosY, buttonSize, buttonSize, "Graphics/GUI/bahamut-button.png", "", gameEngine, 255, "Level 2 unit\nCost 19\n +2 Income");
	sendUnit2Button->setHoverImage("Graphics/GUI/bahamut-hover-button.png");
	
	upgradeToCannon = new VortexButtonRectangle(0, 0, buttonSize / 1.7f, buttonSize / 1.7f, "Graphics/GUI/UpgradeToCannon.png", "", gameEngine, 0, "Cannon tower\nCost 10");
	upgradeToCannon->setHoverImage("Graphics/GUI/UpgradeToCannon-hover.png");
	

	building = true;
	deleting = false;
	playerLost = false;
	addedLoserText = false;

	showingTowerUpgrades = false;
	buildTimer = 400; // Upgrade button cannot be clicked before 400 ms has passed since it first appeared

	playerResources = 50;
	playerIncome = 10;
	numLives = 15;
	msSinceLastIncome = 15000;
	msToNextLevel = 2000;

	resourceText = new VortexText("Resources: " + std::to_string(playerResources), *gameEngine->loadFont("Fonts/arial.ttf"), 34);
	resourceText->setColor(sf::Color::White);
	resourceText->setStyle(sf::Text::Bold);
	float resourceTextWidth = resourceText->getLocalBounds().width;
	resourceText->setPosition(WINDOWSIZEX - resourceTextWidth, 0);

	incomeText = new VortexText("Income: " + std::to_string(playerIncome), *gameEngine->loadFont("Fonts/arial.ttf"), 17);
	incomeText->setColor(sf::Color::White);
	incomeText->setStyle(sf::Text::Bold);
	float incomeTextWidth = incomeText->getLocalBounds().width;
	incomeText->setPosition(WINDOWSIZEX - incomeTextWidth, resourceText->getPosition().y + resourceText->getLocalBounds().height + 10);

	

	livesText = new VortexText("Lives remaining: " + std::to_string(numLives), *gameEngine->loadFont("Fonts/arial.ttf"), 17);
	livesText->setColor(sf::Color::White);
	livesText->setStyle(sf::Text::Bold);
	float livesTextWidth = livesText->getLocalBounds().width;
	livesText->setPosition(WINDOWSIZEX - livesTextWidth, incomeText->getPosition().y + incomeText->getLocalBounds().height + 5);


	timeText = new VortexText("Time till income: " + std::to_string(msSinceLastIncome / 1000), *gameEngine->loadFont("Fonts/arial.ttf"), 17);
	timeText->setColor(sf::Color::White);
	timeText->setStyle(sf::Text::Bold);
	float timeTextWidth = timeText->getLocalBounds().width;
	timeText->setPosition(WINDOWSIZEX - timeTextWidth, livesText->getPosition().y + livesText->getLocalBounds().height + 5);

	levelText = new VortexText("Level: " + std::to_string(currentLevel), *gameEngine->loadFont("Fonts/arial.ttf"), 23);
	levelText->setColor(sf::Color::White);
	levelText->setStyle(sf::Text::Bold);
	levelText->setPosition(0, 0);

	levelTimerText = new VortexText("Next level in: " + std::to_string(msToNextLevel / 1000), *gameEngine->loadFont("Fonts/arial.ttf"), 17);
	levelTimerText->setColor(sf::Color::White);
	levelTimerText->setStyle(sf::Text::Bold);
	levelTimerText->setPosition(0, levelText->getLocalBounds().height + 5);

	sf::Color panelColor(25, 25, 25, 200);

	resourcePanel = new sf::RectangleShape(sf::Vector2f(resourceText->getLocalBounds().width, timeText->getPosition().y + timeText->getLocalBounds().height + 10));
	resourcePanel->setFillColor(panelColor);
	resourcePanel->setPosition(WINDOWSIZEX - resourceTextWidth, 0);

	levelPanel = new sf::RectangleShape(sf::Vector2f(levelTimerText->getLocalBounds().width + 20, levelTimerText->getPosition().y + levelTimerText->getLocalBounds().height + 10));
	levelPanel->setFillColor(panelColor);
	levelPanel->setPosition(0, 0);

	sf::Color outlineColor(0, 0, 0, 200);

	resourcePanel->setOutlineThickness(3);
	resourcePanel->setOutlineColor(outlineColor);
	levelPanel->setOutlineThickness(3);
	levelPanel->setOutlineColor(outlineColor);

	guiObjects.push_back(buildButton);
	guiObjects.push_back(deleteTowerButton);
	guiObjects.push_back(sendUnit1Button);
	guiObjects.push_back(sendUnit2Button);
	
	guiObjects.push_back(resourceText);
	guiObjects.push_back(incomeText);
	guiObjects.push_back(timeText);
	guiObjects.push_back(livesText);

	guiObjects.push_back(levelText);
	guiObjects.push_back(levelTimerText);
	

	guiObjects.push_back(upgradeToCannon);

	lossText = new VortexText("YOU LOSE!", *gameEngine->loadFont("Fonts/arial.ttf"), 70);
	lossText->setColor(sf::Color::Transparent);
	lossText->setStyle(sf::Text::Bold);
	lossText->setPosition(WINDOWSIZEX / 2 - lossText->getLocalBounds().width / 2, WINDOWSIZEY / 2 - lossText->getLocalBounds().height / 2);
	guiObjects.push_back(lossText);
	
	currentLevel = 0;
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
	if (playerLost) {
		if (!addedLoserText) {
			addedLoserText = true;
			lossText->setColor(sf::Color::Red);
		}
		
		return;
	}

	if (buildTimer > 0) {
		buildTimer -= gameEngine->deltaTime.asMilliseconds();
	}
	
	gameEngine->setMousePosView(gameView);
	auto mousePosWindow = gameEngine->getMousePositionRelativeToWindow();
	auto mousePosView = gameEngine->getMousePositionRelativeToSetView();

	msSinceLastIncome -= gameEngine->deltaTime.asMilliseconds();
	if (msSinceLastIncome <= 0) {
		msSinceLastIncome += 15000;
		setPlayerResources(playerResources + playerIncome);
	}
	setTimer(msSinceLastIncome / 1000);

	msToNextLevel -= gameEngine->deltaTime.asMilliseconds();
	if (msToNextLevel <= 0) {
		msToNextLevel += 45000;
		currentLevel++;
		setCurrentLevel(currentLevel);
	}
	setNextLevelTime(msToNextLevel / 1000);

	if (gameEngine->eventMouseReleasedLeft) {
		
		if (buildButton->isPressed && buildButton->hovering) {
			if (building) {
				building = false;
			}
			else {
				building = true;
				deleting = false;
				hideTowerUpgrades();
			}
		}
		else if (deleteTowerButton->isPressed && deleteTowerButton->hovering) {
			if (deleting) {
				deleting = false;

			}
			else {
				deleting = true;
				building = false;
				hideTowerUpgrades();
			}
		}

		else if (sendUnit1Button->isPressed && sendUnit1Button->hovering) {
			if (playerResources >= 10) {
				setPlayerResources(playerResources - 10);
				setPlayerIncome(playerIncome + 1);
				unitsToSpawn.push_back(1);
				hideTowerUpgrades();
			}
		}

		else if (sendUnit2Button->isPressed && sendUnit2Button->hovering) {
			if (playerResources >= 19) {
				setPlayerResources(playerResources - 19);
				setPlayerIncome(playerIncome + 2);
				unitsToSpawn.push_back(2);
				hideTowerUpgrades();
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
	renderListSub.push_back(levelPanel);
	
	for (auto currentRenderVector : guiObjects) {
		for (auto currentRenderObj : currentRenderVector->getRenderDrawable()) {
			renderListSub.push_back(currentRenderObj);
		}
	}

	// Render all tooltips on top
	for (auto currentRenderObj : buildButton->getTooltipDrawable()) {
		renderListSub.push_back(currentRenderObj);
	}
	for (auto currentRenderObj : deleteTowerButton->getTooltipDrawable()) {
		renderListSub.push_back(currentRenderObj);
	}
	for (auto currentRenderObj : sendUnit1Button->getTooltipDrawable()) {
		renderListSub.push_back(currentRenderObj);
	}
	for (auto currentRenderObj : sendUnit2Button->getTooltipDrawable()) {
		renderListSub.push_back(currentRenderObj);
	}

	for (auto currentRenderObj : upgradeToCannon->getTooltipDrawable()) {
		renderListSub.push_back(currentRenderObj);
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
	if (playerLost) {
		return;
	}
	playerResources = newValue;
	resourceText->setString("Resources: " + std::to_string(playerResources));
	float textWidth = resourceText->getLocalBounds().width;
	resourceText->setPosition(WINDOWSIZEX - textWidth, 0);

	resourcePanel->setPosition(WINDOWSIZEX - textWidth, 0);
	resourcePanel->setSize(sf::Vector2f(resourceText->getLocalBounds().width, timeText->getPosition().y + timeText->getLocalBounds().height + 10));
}

void GameGuiController::setPlayerIncome(int newValue) {
	if (playerLost) {
		return;
	}
	playerIncome = newValue;
	incomeText->setString("Income: " + std::to_string(playerIncome));
	float textWidth = incomeText->getLocalBounds().width;
	incomeText->setPosition(WINDOWSIZEX - textWidth, resourceText->getPosition().y + resourceText->getLocalBounds().height + 10);
}

void GameGuiController::setTimer(int newValue) {
	if (playerLost) {
		return;
	}
	timeText->setString("Time till income: " + std::to_string(newValue));
	float textWidth = timeText->getLocalBounds().width;
	timeText->setPosition(WINDOWSIZEX - textWidth, livesText->getPosition().y + livesText->getLocalBounds().height + 5);
}

void GameGuiController::setPlayerLives(int newValue) {
	if (playerLost) {
		return;
	}
	numLives = newValue;
	livesText->setString("Lives remaining: " + std::to_string(newValue));
	float textWidth = timeText->getLocalBounds().width;
	livesText->setPosition(WINDOWSIZEX - textWidth, incomeText->getPosition().y + incomeText->getLocalBounds().height + 5);

	if (numLives <= 0) {
		playerLost = true;
	}
}

int GameGuiController::getPlayerResources() {
	return playerResources;
}

void GameGuiController::showTowerUpgrades(sf::Vector2i mousePosition) {
	buildTimer = 400;
	upgradeToCannon->setPosition(mousePosition.x, mousePosition.y);
	upgradeToCannon->setOpacity(255);
	showingTowerUpgrades = true;
}

void GameGuiController::hideTowerUpgrades() {
	showingTowerUpgrades = false;
	upgradeToCannon->setOpacity(0);
}

void GameGuiController::setCurrentLevel(int newLevel) {
	levelText->setString("Level: " + std::to_string(newLevel));
}

void GameGuiController::setNextLevelTime(int newValue) {
	levelTimerText->setString("Next level in: " + std::to_string(newValue));
	
}