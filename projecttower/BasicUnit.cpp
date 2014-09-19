#include "BasicUnit.h"


BasicUnit::BasicUnit(Vortex * gameEngine, int posX, int posY) : Unit(gameEngine){

	this->posX = posX;
	this->posY = posY;

	moveAnimation = new VortexAnimation(posX, posY, 32, 48, 13, gameEngine);
	moveAnimation->asembleSpritesheetAnimation("Graphics/ironman.png", 4);

}


BasicUnit::~BasicUnit()
{
}


void BasicUnit::update() {

	//std::cout << "Basic Unit" << std::endl;

	moveAnimation->update();

}