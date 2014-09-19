#include "ProgramController.h"


ProgramController::ProgramController(Vortex * gameEngine){

	this->gameEngine = gameEngine;
	// Strict order! Or the IDs will be pointless
	// Refer to the IDs defined in SubController.h
	subControllers.push_back(new MenuController(gameEngine));
	subControllers.push_back(new GameController(gameEngine));
	activeSubController = 0;
}


ProgramController::~ProgramController(){



}

// Run the current subController and if it has decided that nother subcontroller should be running, run that one instead and set the active controller id both here and in the running controller
void ProgramController::update(){
	subControllers[activeSubController]->update();
	activeSubController = subControllers[activeSubController]->getNextControllerID();
	subControllers[activeSubController]->setNextControllerID(activeSubController);
}