#include "SubController.h"


SubController::SubController(Vortex * gameEngine, int controllerID) {

	this->gameEngine = gameEngine;
	currentRenderController = this;
	updateStaticRenderData = true;
	controllerInitialized = false;
	controllerAssetsLoaded = false;

	nextControllerID = controllerID;
	myControllerID = controllerID;

}


SubController::~SubController()
{
}

void SubController::update() 
{

}

int SubController::getMyControllerID() {

	return myControllerID;

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

//void SubController::startController() {
//
//	if (!controllerInitialized) {
//
//		initController();
//		loadAssets();
//
//	}
//
//}

/*
controllerFlag SubController::getNextControllerSequence()
{
	return controllerSequence;
}
*/