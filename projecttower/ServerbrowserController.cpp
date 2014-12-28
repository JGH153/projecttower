#include "ServerbrowserController.h"


ServerbrowserController::ServerbrowserController(Vortex * gameEngine, int controllerID) : SubController(gameEngine, controllerID) {
	nextControllerID = MENU_CONTROLLER_ID;

	doMultiplayer = false;




	

	startedBroadcastSearch = false;
	lookingForClient = false;

}


ServerbrowserController::~ServerbrowserController() {
}

void ServerbrowserController::initController() {

}

void ServerbrowserController::loadAssets() {


	sf::Texture * texBackgroundImage = gameEngine->loadImageToTexture("Graphics/menuBackground.jpg");
	backgroundImage = new VortexSprite(*texBackgroundImage);
	backgroundImage->setPosition(0, 0);
	backgroundImage->setSize(WINDOWSIZEX, WINDOWSIZEY);


	int centerX = gameEngine->getWindowSize().x / 2;
	int centerY = gameEngine->getWindowSize().y / 2;
	int buttonWidth = 180;
	int buttonHeight = 60;


	quitGameButton = new VortexButtonRectangle((buttonWidth / 2), WINDOWSIZEY - buttonHeight * 3, buttonWidth, buttonHeight, "Graphics/blackbutton.png", "Quit", gameEngine, 175);
	startSearchButton = new VortexButtonRectangle((buttonWidth / 2), quitGameButton->getPosition().y - buttonHeight * 1.2, buttonWidth, buttonHeight, "Graphics/blackbutton.png", "Update serverbrowser", gameEngine, 175);
	startServerButton = new VortexButtonRectangle((buttonWidth / 2), startSearchButton->getPosition().y - buttonHeight * 1.2, buttonWidth, buttonHeight, "Graphics/blackbutton.png", "Start server", gameEngine, 175);
	joinLocalhostButton = new VortexButtonRectangle((buttonWidth / 2), startServerButton->getPosition().y - buttonHeight * 1.2, buttonWidth, buttonHeight, "Graphics/blackbutton.png", "Join Localhost", gameEngine, 175);

	quitGameButton->setHoverImage("Graphics/graybutton.png");
	startSearchButton->setHoverImage("Graphics/graybutton.png");
	startServerButton->setHoverImage("Graphics/graybutton.png");
	joinLocalhostButton->setHoverImage("Graphics/graybutton.png");

	guiObjects.push_back(quitGameButton);
	guiObjects.push_back(startSearchButton);
	guiObjects.push_back(startServerButton);
	guiObjects.push_back(joinLocalhostButton);


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

}


void ServerbrowserController::updateServerbrowser() {



	if (!startedBroadcastSearch) {
		startedBroadcastSearch = true;
		gameEngine->networkHandler->startBroadcastSearch();
	}


	gameEngine->networkHandler->showMeAsServer = lookingForClient;


	int buttonWidth = 180;
	int buttonHeight = 60;



	auto ipList = gameEngine->networkHandler->getIncomingBroadcastIpList();



	for each (auto currentButton in broadcastConnectButtons) {
		gameEngine->addRemovableObjectToList(currentButton);
	}
	broadcastConnectButtons.clear();


	for (int i = 0; i < ipList.size(); i++) {
		auto newButton = new VortexButtonRectangle(	(WINDOWSIZEX / 2) - (buttonWidth / 2), 
													40 + ((buttonHeight+10)*i), 
													buttonWidth, 
													buttonHeight, 
													"Graphics/blackbutton.png", 
													ipList[i].toString(),
													gameEngine, 
													175);
		newButton->setHoverImage("Graphics/graybutton.png");
		newButton->setValueString(ipList[i].toString());
		broadcastConnectButtons.push_back(newButton);
	}

}

void ServerbrowserController::setupConnection(sf::IpAddress targetIP) {

	if (lookingForClient){

		stopServer();

	}

	if (gameEngine->networkHandler->connectToServer(targetIP)) {

		gameEngine->networkHandler->stopBroadcastSearch();

		sf::Packet sendPacket;
		sf::Int32 ID = VortexNetwork::packetId_StartGame;

		sendPacket << ID;

		gameEngine->networkHandler->sendTcpPacket(sendPacket);

		std::cout << "Pakke sendt start game by client\n";

		nextControllerID = GAME_CONTROLLER_ID;

		

	}


}

void ServerbrowserController::update() {

	gameEngine->setMousePosView(gameView);

	for (auto *current : guiObjects) {
		current->update();
	}

	for (auto *current : broadcastConnectButtons) {
		current->update();

		if (gameEngine->eventMouseClickedLeft && current->hovering) {

			setupConnection(current->getValueString());
			std::cout << "Button pressed for IP: " << current->getValueString() << std::endl;

		}

	}

	
	if (gameEngine->eventMouseClickedLeft && quitGameButton->hovering) {

		gameEngine->closeApplication();

	} else if (gameEngine->eventMouseClickedLeft && startSearchButton->hovering) {

		updateServerbrowser();	

	} else if (gameEngine->eventMouseClickedLeft && startServerButton->hovering) {
		if (!lookingForClient) {
			
			startServer();

		} else {

			stopServer();
			
		}
	} else if (gameEngine->eventMouseClickedLeft && joinLocalhostButton->hovering) {

		if (gameEngine->networkHandler->connectedByTCP) {

			sf::Packet sendPacket;
			int ID = 5;
			std::string mainData = "Jeg er en mus";

			sendPacket << ID << mainData;

			gameEngine->networkHandler->sendTcpPacket(sendPacket);

			std::cout << "Pakke sendt\n";

		} else {

			setupConnection(sf::IpAddress::LocalHost);

		}

	}


	
	if (gameEngine->networkHandler->connectedByTCP) {

		if (gameEngine->networkHandler->newPacketsReady) {

			auto packets = gameEngine->networkHandler->getTcpPackets();

			for each (auto packet in packets) {

				sf::Int32 ID;
				std::string mainData;

				packet >> ID;
				
				if (ID != VortexNetwork::packetId_StartGame) {
					packet >> mainData;

					std::cout << "Pakke motatt: (" << ID << ") " << mainData << std::endl;

				} else {

					std::cout << "Pakke motatt: (" << ID << ") " << std::endl;
					nextControllerID = GAME_CONTROLLER_ID;

				}
	





				

			}

		}
			

	}



}

void ServerbrowserController::startServer() {

	lookingForClient = true;
	gameEngine->networkHandler->startOpenServerTCP();
	updateServerbrowser(); 


}

void ServerbrowserController::stopServer() {

	lookingForClient = false;
	gameEngine->networkHandler->stopOpenServerTCP();

}



std::vector<std::vector<sf::Drawable *>> ServerbrowserController::getDynamicRenderData() {

	std::vector<std::vector<sf::Drawable *>> renderList;
	std::vector<sf::Drawable *> renderListSub;

	for (auto *currentDrawableList : broadcastConnectButtons) {
		for (auto current : currentDrawableList->getRenderDrawable()) {
			renderListSub.push_back(current);
		}
	}


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