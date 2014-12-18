#include "SubController.h"


SubController::SubController(Vortex * gameEngine, int controllerID) {

	this->gameEngine = gameEngine;
	currentRenderController = this;
	updateStaticRenderData = true;

	nextControllerID = controllerID;

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

bool SubController::requestingUpdateStaticRenderData() {

	if (updateStaticRenderData)
		return true;

	for (auto currentController : childControllers) {
		if (currentController->updateStaticRenderData) {
			return true;
		}
	}

	return false;

}

/*
controllerFlag SubController::getNextControllerSequence()
{
	return controllerSequence;
}
*/