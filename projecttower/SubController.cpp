#include "SubController.h"


SubController::SubController(Vortex * gameEngine){

	this->gameEngine = gameEngine;

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

/*
controllerFlag SubController::getNextControllerSequence()
{
	return controllerSequence;
}
*/