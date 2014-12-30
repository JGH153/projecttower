#include "ProgramController.h"


ProgramController::ProgramController(Vortex * gameEngine, int controllerID) : SubController(gameEngine, controllerID) {

	statedLoadingAssetsThread = false;


	initController();
	
	loadingController->setTotalToLoad(subControllers.size());

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
	loadingController = new LoadingController(gameEngine, LOADING_CONTROLLER_ID);
	subControllers.push_back(loadingController);
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

}

void ProgramController::onStop() {



}

void ProgramController::onStart() {



}

void ProgramController::loadSubControllerAssets(bool usingSubThreads) {

	std::cout << "Assets Loading Thread Online\n";

	//twice as slow using this...
	if (usingSubThreads){

		std::vector<std::thread> loadingThreads;

		for (int i = 0; i < subControllers.size(); i++) {

			loadingThreads.push_back(thread(&ProgramController::loadSpecificController, this, i));

		}

		for (int i = 0; i < subControllers.size(); i++) {

			loadingThreads[i].join();

		}

	} else {

		for (int i = 0; i < subControllers.size(); i++) {
			subControllers[i]->loadAssets();
			loadingController->setOneDone();
		}

	}


	setNewActiveController(MENU_CONTROLLER_ID);

	std::cout << "Assets Loading Thread DONE\n";

	controllerAssetsLoaded = true;

}


void ProgramController::loadSpecificController(int index) {

	std::cout << "Loading for index " << index << "\n";
	subControllers[index]->loadAssets();
	loadingController->setOneDone();

}


void ProgramController::setNewActiveController(int controllerID) {

	activeSubController = controllerID;
	currentRenderController = subControllers[getIndexOfController(activeSubController)];
	subControllers[getIndexOfController(activeSubController)]->setNextControllerID(activeSubController);
	subControllers[getIndexOfController(activeSubController)]->updateStaticRenderData = true;

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

	//look for change of controller
	if (subControllers[getIndexOfController(activeSubController)]->getNextControllerID() != subControllers[getIndexOfController(activeSubController)]->getMyControllerID()) {

		//std::cout << "changing\n";
		subControllers[getIndexOfController(activeSubController)]->onStop();
		setNewActiveController(subControllers[getIndexOfController(activeSubController)]->getNextControllerID());
		subControllers[getIndexOfController(activeSubController)]->onStart();
		//std::cout << "new ID: " << subControllers[getIndexOfController(activeSubController)] << std::endl;

	}

	//call update on current
	subControllers[getIndexOfController(activeSubController)]->update();

	//first time code
	if (!controllerAssetsLoaded && !statedLoadingAssetsThread) {
		statedLoadingAssetsThread = true;
		//loadAssets();
		assetsLoadingHandlingThread = thread(&ProgramController::loadSubControllerAssets, this, false);
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