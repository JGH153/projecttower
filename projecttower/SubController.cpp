#include "SubController.h"


SubController::SubController(Vortex * gameEngine){

	this->gameEngine = gameEngine;
	currentRenderController = this;

}


SubController::~SubController()
{
}

void SubController::update() 
{

}

int SubController::getNextControllerID(){
	return nextControllerID;
}

void SubController::setNextControllerID(int ID){
	nextControllerID = ID;
}

SubController * SubController::getCurrentRenderController() {

	return currentRenderController;

}

/*
controllerFlag SubController::getNextControllerSequence()
{
	return controllerSequence;
}
*/