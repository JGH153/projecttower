#include "ProgramController.h"


ProgramController::ProgramController(Vortex * gameEngine, int controllerID) : SubController(gameEngine, controllerID) {

	// Strict order! Or the IDs will be pointless
	// Refer to the IDs defined in SubController.h
	// Menu controller
	subControllers.push_back(new MenuController(gameEngine, MENU_CONTROLLER_ID));
	subControllers[subControllers.size() - 1]->setNextControllerID(MENU_CONTROLLER_ID);
	// Singleplayer game controller
	subControllers.push_back(new GameController(gameEngine, GAME_CONTROLLER_ID));
	subControllers[subControllers.size() - 1]->setNextControllerID(GAME_CONTROLLER_ID);
	// Network game client
	subControllers.push_back(new NetworkGameClient(gameEngine, NETWORK_GAME_CLIENT_ID));
	subControllers[subControllers.size() - 1]->setNextControllerID(NETWORK_GAME_CLIENT_ID);
	// Network game server
	subControllers.push_back(new NetworkGameServer(gameEngine, NETWORK_GAME_SERVER_ID));
	subControllers[subControllers.size() - 1]->setNextControllerID(NETWORK_GAME_SERVER_ID);

	activeSubController = MENU_CONTROLLER_ID;
	//activeSubController = GAME_CONTROLLER_ID;
	currentRenderController = subControllers[activeSubController];

}


ProgramController::~ProgramController(){



}

void ProgramController::preloadAssets() {

}


sf::View ProgramController::getView() {
	return sf::View(sf::FloatRect(0, 0, WINDOWSIZEX, WINDOWSIZEY));
}

std::vector<std::vector<sf::Drawable *>> ProgramController::getStaticRenderData() {

	std::vector<std::vector<sf::Drawable *>> renderList;

	std::vector<sf::Drawable *> renderListSub;
	renderList.push_back(renderListSub);
	return renderList;
}


std::vector<std::vector<sf::Drawable *>> ProgramController::getDynamicRenderData() {

	std::vector<std::vector<sf::Drawable *>> renderList;

	std::vector<sf::Drawable *> renderListSub;
	renderList.push_back(renderListSub);
	return renderList;
}

// Run the current subController and if it has decided that nother subcontroller should be running, run that one instead and set the active controller id both here and in the running controller
void ProgramController::update(){
	//std::cout << "Starting active sub controller update - " << activeSubController << std::endl;
	subControllers[activeSubController]->update();

	//std::cout << "Getting new active controller" << std::endl;
	activeSubController = subControllers[activeSubController]->getNextControllerID();

	//std::cout << "Something something darkside" << std::endl;
	subControllers[activeSubController]->setNextControllerID(activeSubController);
	currentRenderController = subControllers[activeSubController];
}

std::vector<SubController *> ProgramController::getChildControllers() {

	return childControllers;

}