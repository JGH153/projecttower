#include "ReaperUnit.h"

// Last unit. For sudden death, to end game
ReaperUnit::ReaperUnit(Vortex * gameEngine, std::vector<std::vector<MapTile *>> * mapGroundTiles, int posX, int posY, int endPosX, int endPosY, int currentLevel) : Unit(gameEngine, mapGroundTiles, posX, posY) {

	this->endPosX = endPosX;
	this->endPosY = endPosY;

	speed = 0.07f + currentLevel * 0.002;
	width = 50 / 2;
	height = 48 / 2;
	maxHealth = currentLevel * 15;
	offsetComponentsY = 15 + gameEngine->getRandInt(-5, 5);

	killReward = 13;


	moveDirection = DIRECTIONS[rand() % 4];

	currentMoveAnimationIndex = getDirectionIndex(moveDirection);

	for (int i = 0; i < DIRECTIONS.size(); i++){

		VortexAnimation * tempAni = new VortexAnimation(posX, posY, width, height, 13, gameEngine);
		tempAni->asembleSpritesheetAnimation("Graphics/Units/reaper.png", 50, 48, DIRECTIONS[i], 4);
		moveAnimations.push_back(tempAni);

	}

	hitParticleColor = sf::Color(220, 20, 20);


	initUnit();
}


ReaperUnit::~ReaperUnit() {

}

std::vector<sf::Drawable *> ReaperUnit::getRenderDrawable() {
	std::vector<sf::Drawable*> temp = moveAnimations[currentMoveAnimationIndex]->getRenderDrawable();
	return temp;
}

void ReaperUnit::update() {
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

void ReaperUnit::killYourself() {

	delete this;

}

