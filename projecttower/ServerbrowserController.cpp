#include "ServerbrowserController.h"


ServerbrowserController::ServerbrowserController(Vortex * gameEngine, int controllerID) : SubController(gameEngine, controllerID) {
	nextControllerID = MENU_CONTROLLER_ID;

	doMultiplayer = false;

	sf::Texture * texBackgroundImage = gameEngine->loadImageToTexture("Graphics/menuBackground.jpg");
	backgroundImage = new VortexSprite(*texBackgroundImage);
	backgroundImage->setPosition(0, 0);
	backgroundImage->setSize(WINDOWSIZEX, WINDOWSIZEY);


	int centerX = gameEngine->getWindowSize().x / 2;
	int centerY = gameEngine->getWindowSize().y / 2;
	int buttonWidth = 180;
	int buttonHeight = 60;


	quitGameButton = new VortexButtonRectangle((buttonWidth / 2), WINDOWSIZEY - buttonHeight * 3, buttonWidth, buttonHeight, "Graphics/blackbutton.png", "Quit", gameEngine, 175);
	startSearchButton = new VortexButtonRectangle((buttonWidth / 2), quitGameButton->getPosition().y - buttonHeight * 1.2, buttonWidth, buttonHeight, "Graphics/blackbutton.png", "Start Broadcast Search", gameEngine, 175);

	quitGameButton->setHoverImage("Graphics/graybutton.png");
	startSearchButton->setHoverImage("Graphics/graybutton.png");

	guiObjects.push_back(quitGameButton);
	guiObjects.push_back(startSearchButton);



	//this->title = title;
	//font = *gameEngine->loadFont("Fonts/arial.ttf");
	//text.setFont(font);
	//text.setString(title);
	//text.setCharacterSize(28);
	//text.setColor(sf::Color::White);
	//text.setStyle(sf::Text::Bold);

	std::string tittleText = "Serverbrowser (your IP is: " + gameEngine->localIpAdress.toString() + ")";

	serverbrowserTittle = new VortexText(tittleText, *gameEngine->getDefaultFont(), 28);
	serverbrowserTittle->setPosition(sf::Vector2f(20.f, 20.f));
	
	guiObjects.push_back(serverbrowserTittle);


	

	startedBroadcastSearch = false;

}


ServerbrowserController::~ServerbrowserController() {
}

void ServerbrowserController::preloadAssets() {

}

void ServerbrowserController::update() {

	auto ipList = gameEngine->networkHandler->getIncomingBroadcastIpList();
	
	if (quitGameButton->isPressed && quitGameButton->hovering) {
		gameEngine->closeApplication();
	} else if (startSearchButton->isPressed && startSearchButton->hovering && !startedBroadcastSearch) {
		startedBroadcastSearch = true;
		gameEngine->networkHandler->startBroadcastSearch();
	}


	


	for (auto *current : guiObjects) {
		current->update();
	}



}

std::vector<std::vector<sf::Drawable *>> ServerbrowserController::getDynamicRenderData() {

	std::vector<std::vector<sf::Drawable *>> renderList;
	std::vector<sf::Drawable *> renderListSub;



	renderList.push_back(renderListSub);
	return renderList;

}
std::vector<std::vector<sf::Drawable *>> ServerbrowserController::getStaticRenderData() {

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

sf::View ServerbrowserController::getView() {
	return sf::View(sf::FloatRect(0, 0, WINDOWSIZEX, WINDOWSIZEY));
}

std::vector<SubController *> ServerbrowserController::getChildControllers() {

	return childControllers;

}