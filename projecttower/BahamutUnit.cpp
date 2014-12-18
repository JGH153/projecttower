#include "BahamutUnit.h"


BahamutUnit::BahamutUnit(Vortex * gameEngine, std::vector<std::vector<MapTile *>> * mapGroundTiles, int posX, int posY, int endPosX, int endPosY) : Unit(gameEngine, mapGroundTiles, posX, posY) {

	this->endPosX = endPosX;
	this->endPosY = endPosY;

	speed = 0.025f;
	width = 96 / 4;
	height = 96 / 4;
	maxHealth = 15.f; //+9
	offsetComponentsY = 15 + gameEngine->getRandInt(-5, 5);

	killReward = 2;


	moveDirection = DIRECTIONS[rand() % 4];

	currentMoveAnimationIndex = getDirectionIndex(moveDirection);

	for (int i = 0; i < DIRECTIONS.size(); i++){

		VortexAnimation * tempAni = new VortexAnimation(posX, posY, width, height, 13, gameEngine);
		tempAni->asembleSpritesheetAnimation("Graphics/Units/bahamut.png", 96, 96, DIRECTIONS[i], 4);
		moveAnimations.push_back(tempAni);

	}

	hitParticleColor = sf::Color(220, 20, 20);


	initUnit();
}


BahamutUnit::~BahamutUnit() {

}

std::vector<sf::Drawable *> BahamutUnit::getRenderDrawable() {
	std::vector<sf::Drawable*> temp = moveAnimations[currentMoveAnimationIndex]->getRenderDrawable();
	temp.push_back(healthBarBG);
	temp.push_back(healthBarFG);
	temp.push_back(healthBarFrame);
	return temp;
}



void BahamutUnit::update() {
	if (isDead() || reachedGoal){
		return;
	}
	
	updateMovement();

	sf::Vector2f offset(moveDirection.x * speed * gameEngine->deltaTime.asMilliseconds(), (moveDirection.y * speed * gameEngine->deltaTime.asMilliseconds()));

	posX += offset.x;
	posY += offset.y;
	moveHealthBar(offset);


	moveAnimations[currentMoveAnimationIndex]->setPos(posX, posY);


	moveAnimations[currentMoveAnimationIndex]->update();


	float percentageHP = currentHealth / maxHealth;
	if (percentageHP < 0) {
		percentageHP = 0;
	}
	healthBarFG->setSize(healthBarBG->getSize().x * percentageHP, healthBarFG->getSize().y);

	groundTilesChanged = false;
	towerRemoved = false;

}

void BahamutUnit::killYourself() {

	delete this;

}