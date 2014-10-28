#include "ProgramController.h"


ProgramController::ProgramController(Vortex * gameEngine) : SubController(gameEngine) {

	// Strict order! Or the IDs will be pointless
	// Refer to the IDs defined in SubController.h
	subControllers.push_back(new MenuController(gameEngine));
	subControllers.push_back(new GameController(gameEngine));
	activeSubController = MENU_CONTROLLER_ID;
	//activeSubController = GAME_CONTROLLER_ID;
	currentRenderController = subControllers[activeSubController];

}


ProgramController::~ProgramController(){



}

std::vector<sf::Drawable *> ProgramController::getStaticRenderData() {

	std::vector<sf::Drawable *> renderList;
	return renderList;
}


std::vector<sf::Drawable *> ProgramController::getDynamicRenderData() {

	std::vector<sf::Drawable *> renderList;
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