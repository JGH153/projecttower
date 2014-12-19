#include "IfritUnit.h"


IfritUnit::IfritUnit(Vortex * gameEngine, std::vector<std::vector<MapTile *>> * mapGroundTiles, int posX, int posY, int endPosX, int endPosY) : Unit(gameEngine, mapGroundTiles, posX, posY) {

	this->endPosX = endPosX;
	this->endPosY = endPosY;

	maxspeed = 0.065f;
	speed = maxspeed;

	width = 48 / 2;
	height = 48 / 2;
	maxHealth = 123.f; //+17
	offsetComponentsY = 15 + gameEngine->getRandInt(-5, 5);

	killReward = 10;


	moveDirection = DIRECTIONS[rand() % 4];

	currentMoveAnimationIndex = getDirectionIndex(moveDirection);

	for (int i = 0; i < DIRECTIONS.size(); i++){

		VortexAnimation * tempAni = new VortexAnimation(posX, posY, width, height, 13, gameEngine);
		tempAni->asembleSpritesheetAnimation("Graphics/Units/ifrit.png", 80, 80, DIRECTIONS[i], 4);
		moveAnimations.push_back(tempAni);

	}

	hitParticleColor = sf::Color(220, 20, 20);


	initUnit();
}


IfritUnit::~IfritUnit() {

}

std::vector<sf::Drawable *> IfritUnit::getRenderDrawable() {
	std::vector<sf::Drawable*> temp = moveAnimations[currentMoveAnimationIndex]->getRenderDrawable();
	return temp;
}

void IfritUnit::update() {
	if (isDead() || reachedGoal){
		return;
	}

	if (slowtimer > 0) {
		slowtimer -= gameEngine->deltaTime.asMilliseconds();

		if (slowtimer <= 0) {
			speed = maxspeed;
			slowed = false;
		}
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

void IfritUnit::killYourself() {

	delete this;

}
