#include "ProgramController.h"


ProgramController::ProgramController(Vortex * gameEngine, int controllerID) : SubController(gameEngine, controllerID) {

	
	
	

	initController();
	

	setNewActiveController(LOADING_CONTROLLER_ID);
	

}


ProgramController::~ProgramController(){



}

void ProgramController::initController() {

	std::cout << "INITING CONTROLLERS\n";

	//gameEngine->loadImageToTexture("lol");

	// Strict order! Or the IDs will be pointless
	// Refer to the IDs defined in SubController.h
	//LoadingController
	subControllers.push_back(new LoadingController(gameEngine, LOADING_CONTROLLER_ID));
	subControllers[subControllers.size() - 1]->setNextControllerID(LOADING_CONTROLLER_ID);
	// Menu controller
	subControllers.push_back(new MenuController(gameEngine, MENU_CONTROLLER_ID));
	subControllers[subControllers.size() - 1]->setNextControllerID(MENU_CONTROLLER_ID);
	// Singleplayer game controller
	subControllers.push_back(new GameController(gameEngine, GAME_CONTROLLER_ID));
	subControllers[subControllers.size() - 1]->setNextControllerID(GAME_CONTROLLER_ID);
	// serverbrower controller
	subControllers.push_back(new ServerbrowserController(gameEngine, SERVERBROWSER_CONTROLLER_ID));
	subControllers[subControllers.size() - 1]->setNextControllerID(SERVERBROWSER_CONTROLLER_ID);
	

	for (int i = 0; i < subControllers.size(); i++) {

		subControllers[i]->initController();

	}

	

	controllerInitialized = true;

}

void ProgramController::loadAssets() {

	std::cout << "LOADING CONTROLLERS ASSETS\n";

	for (int i = 0; i < subControllers.size(); i++) {

		subControllers[i]->loadAssets();

	}

	setNewActiveController(MENU_CONTROLLER_ID);

	controllerAssetsLoaded = true;

}


void ProgramController::setNewActiveController(int controllerID) {

	activeSubController = controllerID;
	currentRenderController = subControllers[getIndexOfController(activeSubController)];

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
	subControllers[getIndexOfController(activeSubController)]->update();

	//std::cout << "Getting new active controller" << std::endl;
	activeSubController = subControllers[getIndexOfController(activeSubController)]->getNextControllerID();

	//std::cout << "Something something darkside" << std::endl;
	subControllers[getIndexOfController(activeSubController)]->setNextControllerID(activeSubController);
	currentRenderController = subControllers[getIndexOfController(activeSubController)];

	if (!controllerAssetsLoaded) {
		loadAssets();
	}

}


int ProgramController::getIndexOfController(int controllerID) {

	for (int i = 0; i < subControllers.size(); i ++ ) {

		if (subControllers[i]->getMyControllerID() == controllerID) {
			return i;
		}

	}

	std::cout << "FATAL CONTROLLER ID NOT FOUND("<<controllerID<<")\n";
	std::cin.get();

	return -1;


}


std::vector<SubController *> ProgramController::getChildControllers() {

	return childControllers;

}