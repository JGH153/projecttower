#include "BasicUnit.h"


BasicUnit::BasicUnit(Vortex * gameEngine, int posX, int posY) : Unit(gameEngine){

	this->posX = posX;
	this->posY = posY;

	//
	int randNum = rand() % 10;

	if (randNum < 8){
		speed = 0.04f;
		width = 32;
		height = 48;
	}else{
		speed = 0.08f;
		width = 96/2;
		height = 96/2;
	}


	moveDirection = DIRECTIONS[rand() % 4];

	currentMoveAnimationIndex = getDirectionIndex(moveDirection);

	for (int i = 0; i < DIRECTIONS.size(); i++){

		VortexAnimation * tempAni = new VortexAnimation(posX, posY, width, height, 13, gameEngine);
		if (randNum < 8) {
			tempAni->asembleSpritesheetAnimation("Graphics/ironman.png", width, height, DIRECTIONS[i], 4);
		}
		else{
			tempAni->asembleSpritesheetAnimation("Graphics/bahamut.png", 96, 96, DIRECTIONS[i], 4);
		}
		moveAnimations.push_back(tempAni);

	}

	

	

}


BasicUnit::~BasicUnit(){



}

std::vector<VortexSprite *> BasicUnit::getRenderSprites() {
	return moveAnimations[currentMoveAnimationIndex]->getRenderSprites();
}



void BasicUnit::update() {

	posX += moveDirection.x * speed * gameEngine->deltaTime.asMilliseconds();
	posY += moveDirection.y * speed * gameEngine->deltaTime.asMilliseconds();

//	std::cout << gameEngine->deltaTime.asMilliseconds() << std::endl;

	if (posX < 0 && moveDirection == DIR_WEST){
		moveDirection.x *= -1;
		currentMoveAnimationIndex = getDirectionIndex(moveDirection);
	}
	if (posX + width > gameEngine->getWindowSize().x  && moveDirection == DIR_EAST){
		moveDirection.x *= -1;
		currentMoveAnimationIndex = getDirectionIndex(moveDirection);
	}

	if (posY < 0 && moveDirection == DIR_NORTH){
		moveDirection.y *= -1;
		currentMoveAnimationIndex = getDirectionIndex(moveDirection);
	}
	if (posY + height > gameEngine->getWindowSize().y  && moveDirection == DIR_SOUTH){
		moveDirection.y *= -1;
		currentMoveAnimationIndex = getDirectionIndex(moveDirection);
	}


	moveAnimations[currentMoveAnimationIndex]->setPos(posX, posY);

	//std::cout << "Basic Unit" << std::endl;

	moveAnimations[currentMoveAnimationIndex]->update();

}