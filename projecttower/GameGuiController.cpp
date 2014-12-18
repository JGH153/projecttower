#include "GameGuiController.h"


GameGuiController::GameGuiController(Vortex * gameEngine, int controllerID) : SubController(gameEngine, controllerID) {
	int buttonSize = 50;
	int buttonSpread = 1;
	int numToolbarButtons = 14;
	int toolbarPanelWidth = numToolbarButtons * (buttonSize + buttonSpread);
	int toolbarPanelPosX = WINDOWSIZEX / 2 - toolbarPanelWidth / 2;
	bottomToolbarPosY = WINDOWSIZEY - buttonSize;

	deleteTowerButton = new VortexButtonRectangle(toolbarPanelPosX + buttonSpread, bottomToolbarPosY, buttonSize, buttonSize, "Graphics/GUI/delete-icon.png", "", gameEngine, 255, "Delete tower");
	deleteTowerButton->setHoverImage("Graphics/GUI/delete-hover-icon.png");


	buildButton = new VortexButtonRectangle(deleteTowerButton->getPosition().x + deleteTowerButton->getWidth() + buttonSpread, bottomToolbarPosY, buttonSize, buttonSize, "Graphics/GUI/build-arrowtower.png", "", gameEngine, 255, "Arrow tower\nCost 10");
	buildButton->setHoverImage("Graphics/GUI/build-arrowtower-hover.png");

	
	sendUnit1Button = new VortexButtonRectangle(buildButton->getPosition().x + buildButton->getWidth() + buttonSpread, bottomToolbarPosY, buttonSize, buttonSize, "Graphics/GUI/ironman-button.png", "", gameEngine, 255, "Level 1 unit\nCost 10\n +1 Income");
	sendUnit1Button->setHoverImage("Graphics/GUI/ironman-hover-button.png");

	sendUnit2Button = new VortexButtonRectangle(sendUnit1Button->getPosition().x + sendUnit1Button->getWidth() + buttonSpread, bottomToolbarPosY, buttonSize, buttonSize, "Graphics/GUI/bahamut-button.png", "", gameEngine, 255, "Level 2 unit\nCost 19\n +2 Income");
	sendUnit2Button->setHoverImage("Graphics/GUI/bahamut-hover-button.png");

	sendUnit3Button = new VortexButtonRectangle(sendUnit2Button->getPosition().x + sendUnit2Button->getWidth() + buttonSpread, bottomToolbarPosY, buttonSize, buttonSize, "Graphics/GUI/russiangirl-button.png", "", gameEngine, 255, "Level 3 unit\nCost 28\n +3 Income");
	sendUnit3Button->setHoverImage("Graphics/GUI/russiangirl-hover-button.png");

	sendUnit4Button = new VortexButtonRectangle(sendUnit3Button->getPosition().x + sendUnit3Button->getWidth() + buttonSpread, bottomToolbarPosY, buttonSize, buttonSize, "Graphics/GUI/sadako-button.png", "", gameEngine, 255, "Level 4 unit\nCost 37\n +4 Income");
	sendUnit4Button->setHoverImage("Graphics/GUI/sadako-hover-button.png");

	sendUnit5Button = new VortexButtonRectangle(sendUnit4Button->getPosition().x + sendUnit4Button->getWidth() + buttonSpread, bottomToolbarPosY, buttonSize, buttonSize, "Graphics/GUI/indiana-button.png", "", gameEngine, 255, "Level 5 unit\nCost 46\n +5 Income");
	sendUnit5Button->setHoverImage("Graphics/GUI/indiana-hover-button.png");

	sendUnit6Button = new VortexButtonRectangle(sendUnit5Button->getPosition().x + sendUnit5Button->getWidth() + buttonSpread, bottomToolbarPosY, buttonSize, buttonSize, "Graphics/GUI/chinese-button.png", "", gameEngine, 255, "Level 6 unit\nCost 55\n +6 Income");
	sendUnit6Button->setHoverImage("Graphics/GUI/chinese-hover-button.png");

	sendUnit7Button = new VortexButtonRectangle(sendUnit6Button->getPosition().x + sendUnit6Button->getWidth() + buttonSpread, bottomToolbarPosY, buttonSize, buttonSize, "Graphics/GUI/kavi-button.png", "", gameEngine, 255, "Level 7 unit\nCost 64\n +7 Income");
	sendUnit7Button->setHoverImage("Graphics/GUI/kavi-hover-button.png");

	sendUnit8Button = new VortexButtonRectangle(sendUnit7Button->getPosition().x + sendUnit7Button->getWidth() + buttonSpread, bottomToolbarPosY, buttonSize, buttonSize, "Graphics/GUI/starlord-button.png", "", gameEngine, 255, "Level 8 unit\nCost 73\n +8 Income");
	sendUnit8Button->setHoverImage("Graphics/GUI/starlord-hover-button.png");

	sendUnit9Button = new VortexButtonRectangle(sendUnit8Button->getPosition().x + sendUnit8Button->getWidth() + buttonSpread, bottomToolbarPosY, buttonSize, buttonSize, "Graphics/GUI/drax-button.png", "", gameEngine, 255, "Level 9 unit\nCost 82\n +9 Income");
	sendUnit9Button->setHoverImage("Graphics/GUI/drax-hover-button.png");

	sendUnit10Button = new VortexButtonRectangle(sendUnit9Button->getPosition().x + sendUnit9Button->getWidth() + buttonSpread, bottomToolbarPosY, buttonSize, buttonSize, "Graphics/GUI/ifrit-button.png", "", gameEngine, 255, "Level 10 unit\nCost 91\n +10 Income");
	sendUnit10Button->setHoverImage("Graphics/GUI/ifrit-hover-button.png");

	sendUnit11Button = new VortexButtonRectangle(sendUnit10Button->getPosition().x + sendUnit10Button->getWidth() + buttonSpread, bottomToolbarPosY, buttonSize, buttonSize, "Graphics/GUI/hulk-button.png", "", gameEngine, 255, "Level 11 unit\nCost 100\n +11 Income");
	sendUnit11Button->setHoverImage("Graphics/GUI/hulk-hover-button.png");

	sendUnit12Button = new VortexButtonRectangle(sendUnit11Button->getPosition().x + sendUnit11Button->getWidth() + buttonSpread, bottomToolbarPosY, buttonSize, buttonSize, "Graphics/GUI/death-button.png", "", gameEngine, 255, "Level 12 unit\nCost 109\n +12 Income");
	sendUnit12Button->setHoverImage("Graphics/GUI/death-hover-button.png");
	
	upgradeToCannon = new VortexButtonRectangle(0, 0, buttonSize / 1.7f, buttonSize / 1.7f, "Graphics/GUI/UpgradeToCannon.png", "", gameEngine, 0, "Cannon tower\nCost 10");
	upgradeToCannon->setHoverImage("Graphics/GUI/UpgradeToCannon-hover.png");

	buttons.push_back(upgradeToCannon);
	buttons.push_back(buildButton);
	buttons.push_back(deleteTowerButton);
	buttons.push_back(sendUnit1Button);
	buttons.push_back(sendUnit2Button);
	buttons.push_back(sendUnit3Button);
	buttons.push_back(sendUnit4Button);
	buttons.push_back(sendUnit5Button);
	buttons.push_back(sendUnit6Button);
	buttons.push_back(sendUnit7Button);
	buttons.push_back(sendUnit8Button);
	buttons.push_back(sendUnit9Button);
	buttons.push_back(sendUnit10Button);
	buttons.push_back(sendUnit11Button);
	buttons.push_back(sendUnit12Button);

	

	building = false;
	deleting = false;
	playerLost = false;
	addedLoserText = false;

	showingTowerUpgrades = false;
	buildTimer = 400; // Upgrade button cannot be clicked before 400 ms has passed since it first appeared

	playerResources = 20;
	//playerResources = 2000;
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

	buttonPanel = new sf::RectangleShape(sf::Vector2f(toolbarPanelWidth, buttonSize + 5));
	buttonPanel->setFillColor(sf::Color::White);
	buttonPanel->setPosition(toolbarPanelPosX, bottomToolbarPosY);

	sf::Color outlineColor(0, 0, 0, 200);

	resourcePanel->setOutlineThickness(3);
	resourcePanel->setOutlineColor(outlineColor);
	levelPanel->setOutlineThickness(3);
	levelPanel->setOutlineColor(outlineColor);
	buttonPanel->setOutlineThickness(5);
	buttonPanel->setOutlineColor(sf::Color(50, 50, 50, 150));

	for (auto button : buttons) {
		guiObjects.push_back(button);
	}

	
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

	winText = new VortexText("YOU WIN!", *gameEngine->loadFont("Fonts/arial.ttf"), 70);
	winText->setColor(sf::Color::Transparent);
	winText->setStyle(sf::Text::Bold);
	winText->setPosition(WINDOWSIZEX / 2 - winText->getLocalBounds().width / 2, WINDOWSIZEY / 2 - lossText->getLocalBounds().height / 2);
	guiObjects.push_back(winText);
	
	currentLevel = 0;


	


	playerWon = false;

}

void GameGuiController::preloadAssets() {

}


GameGuiController::~GameGuiController() {
}


void GameGuiController::addPlayersSideTexts() {

	



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

	if (playerWon) {
		if (!addedWinText) {
			addedWinText = true;
			winText->setColor(sf::Color::Green);
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
		msSinceLastIncome += 10000;
		setPlayerResources(playerResources + playerIncome);
	}
	setTimer(msSinceLastIncome / 1000);

	msToNextLevel -= gameEngine->deltaTime.asMilliseconds();
	if (msToNextLevel <= 0) {
		msToNextLevel += 25000;
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

		else if (sendUnit3Button->isPressed && sendUnit3Button->hovering) {
			if (playerResources >= 28) {
				setPlayerResources(playerResources - 28);
				setPlayerIncome(playerIncome + 3);
				unitsToSpawn.push_back(3);
				hideTowerUpgrades();
			}
		}

		else if (sendUnit4Button->isPressed && sendUnit4Button->hovering) {
			if (playerResources >= 37) {
				setPlayerResources(playerResources - 37);
				setPlayerIncome(playerIncome + 4);
				unitsToSpawn.push_back(4);
				hideTowerUpgrades();
			}
		}
		else if (sendUnit5Button->isPressed && sendUnit5Button->hovering) {
			if (playerResources >= 46) {
				setPlayerResources(playerResources - 46);
				setPlayerIncome(playerIncome + 5);
				unitsToSpawn.push_back(5);
				hideTowerUpgrades();
			}
		}
		else if (sendUnit6Button->isPressed && sendUnit6Button->hovering) {
			if (playerResources >= 55) {
				setPlayerResources(playerResources - 55);
				setPlayerIncome(playerIncome + 6);
				unitsToSpawn.push_back(6);
				hideTowerUpgrades();
			}
		}
		else if (sendUnit7Button->isPressed && sendUnit7Button->hovering) {
			if (playerResources >= 64) {
				setPlayerResources(playerResources - 64);
				setPlayerIncome(playerIncome + 7);
				unitsToSpawn.push_back(7);
				hideTowerUpgrades();
			}
		}
		else if (sendUnit8Button->isPressed && sendUnit8Button->hovering) {
			if (playerResources >= 73) {
				setPlayerResources(playerResources - 73);
				setPlayerIncome(playerIncome + 8);
				unitsToSpawn.push_back(8);
				hideTowerUpgrades();
			}
		}
		else if (sendUnit9Button->isPressed && sendUnit9Button->hovering) {
			if (playerResources >= 82) {
				setPlayerResources(playerResources - 82);
				setPlayerIncome(playerIncome + 9);
				unitsToSpawn.push_back(9);
				hideTowerUpgrades();
			}
		}
		else if (sendUnit10Button->isPressed && sendUnit10Button->hovering) {
			if (playerResources >= 91) {
				setPlayerResources(playerResources - 91);
				setPlayerIncome(playerIncome + 10);
				unitsToSpawn.push_back(10);
				hideTowerUpgrades();
			}
		}
		else if (sendUnit11Button->isPressed && sendUnit11Button->hovering) {
			if (playerResources >= 100) {
				setPlayerResources(playerResources - 100);
				setPlayerIncome(playerIncome + 11);
				unitsToSpawn.push_back(11);
				hideTowerUpgrades();
			}
		}
		else if (sendUnit12Button->isPressed && sendUnit12Button->hovering) {
			if (playerResources >= 109) {
				setPlayerResources(playerResources - 109);
				setPlayerIncome(playerIncome + 12);
				unitsToSpawn.push_back(12);
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
	renderListSub.push_back(buttonPanel);
	
	for (auto currentRenderVector : guiObjects) {
		for (auto currentRenderObj : currentRenderVector->getRenderDrawable()) {
			renderListSub.push_back(currentRenderObj);
		}
	}

	// Render all tooltips on top
	for (auto currentButton : buttons) {
		for (auto currentRenderObj : currentButton->getTooltipDrawable()) {
			renderListSub.push_back(currentRenderObj);
		}
	}
	/*
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
	for (auto currentRenderObj : sendUnit3Button->getTooltipDrawable()) {
		renderListSub.push_back(currentRenderObj);
	}
	for (auto currentRenderObj : sendUnit4Button->getTooltipDrawable()) {
		renderListSub.push_back(currentRenderObj);
	}

	for (auto currentRenderObj : upgradeToCannon->getTooltipDrawable()) {
		renderListSub.push_back(currentRenderObj);
	}
	*/
	

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
	if (playerLost || playerWon) {
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
	if (playerLost || playerWon) {
		return;
	}
	playerIncome = newValue;
	incomeText->setString("Income: " + std::to_string(playerIncome));
	float textWidth = incomeText->getLocalBounds().width;
	incomeText->setPosition(WINDOWSIZEX - textWidth, resourceText->getPosition().y + resourceText->getLocalBounds().height + 10);
}

void GameGuiController::setTimer(int newValue) {
	if (playerLost || playerWon) {
		return;
	}
	timeText->setString("Time till income: " + std::to_string(newValue));
	float textWidth = timeText->getLocalBounds().width;
	timeText->setPosition(WINDOWSIZEX - textWidth, livesText->getPosition().y + livesText->getLocalBounds().height + 5);
}

void GameGuiController::setPlayerLives(int newValue) {
	if (playerLost || playerWon) {
		return;
	}
	numLives = newValue;
	livesText->setString("Lives remaining: " + std::to_string(newValue));
	float textWidth = livesText->getLocalBounds().width;
	livesText->setPosition(WINDOWSIZEX - textWidth, incomeText->getPosition().y + incomeText->getLocalBounds().height + 5);

	if (numLives <= 0) {
		playerLost = true;
		sendPlayerLossPacket();
	}
}

void GameGuiController::sendPlayerLossPacket() {


	if (gameEngine->networkHandler->connectedByTCP) {

		sf::Packet sendPacket;
		sf::Int32 typeID = VortexNetwork::packetId_MainGameLoss;

		sendPacket << typeID;

		gameEngine->networkHandler->sendTcpPacket(sendPacket);

		std::cout << "Loss Pakke sendt!\n";

	} else {
		std::cout << "JEG ER IKKE PA MP\n";
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