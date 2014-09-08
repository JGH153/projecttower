#include "ProgramController.h"


ProgramController::ProgramController(Vortex * gameEngine){

	this->gameEngine = gameEngine;

	menuController = new MenuController(gameEngine);
	gameController = new GameController(gameEngine);

	activeSubControllerID = 1;

}


ProgramController::~ProgramController(){



}

void ProgramController::update(){

	if (menuController->programControllerNewActionID == 2){
		activeSubControllerID = 2;
	}


	if (activeSubControllerID == 1){
		menuController->update();
	}else if(activeSubControllerID == 2){
		gameController->update();
	}

}
