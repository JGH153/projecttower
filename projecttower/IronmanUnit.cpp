#include "IronmanUnit.h"


IronmanUnit::IronmanUnit(Vortex * gameEngine, std::vector<std::vector<MapTile *>> * mapGroundTiles, int posX, int posY, int endPosX, int endPosY) : Unit(gameEngine, mapGroundTiles, posX, posY) {

	int randNum = rand() % 10;

	this->endPosX = endPosX;
	this->endPosY = endPosY;

	maxspeed = 0.02f;
	maxspeed = 0.05f;
	speed = maxspeed;

	width = 32 / 2;
	height = 48 / 2;
	maxHealth = 6.f;
	offsetComponentsY = 15 + gameEngine->getRandInt(-5, 5);

	killReward = 1;


	moveDirection = DIRECTIONS[rand() % 4];

	currentMoveAnimationIndex = getDirectionIndex(moveDirection);

	for (int i = 0; i < DIRECTIONS.size(); i++){

		VortexAnimation * tempAni = new VortexAnimation(posX, posY, width, height, 13, gameEngine);
		tempAni->asembleSpritesheetAnimation("Graphics/Units/ironman.png", 32, 48, DIRECTIONS[i], 4);
		moveAnimations.push_back(tempAni);

	}


	hitParticleColor = sf::Color(220, 20, 20);
	

	initUnit();
	

}


IronmanUnit::~IronmanUnit(){

	

}



std::vector<sf::Drawable *> IronmanUnit::getRenderDrawable() {
	std::vector<sf::Drawable*> temp = moveAnimations[currentMoveAnimationIndex]->getRenderDrawable();
	return temp;
}


void IronmanUnit::update() {
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

	/*	OLD MOVEMENT CODE, for reference, i guess?
	if (isDead() || reachedGoal) {
		return;
	}

	if (pathToTarget.empty()) {
		/*
		int centerPosX = posX + width / 2;
		int centerPosY = posY + height / 2;
		*//*

		if (abs(posX - endPosX) * abs(posX - endPosX) + abs(posY - endPosY) * abs(posY - endPosY) <= 100 * 100) {
			reachedGoal = true;
			return;
		}

		findNewPath();
	}
	
	if (!pathToTarget.empty()) {
		if (groundTilesChanged) {
			if (mapGroundTiles->at(currentWaypointTarget.x).at(currentWaypointTarget.y)->getTileTypeID() == TileTypes::tower) {
				findNewPath();
			}
			else {
				for (auto pathPoint : pathToTarget) {
					if (mapGroundTiles->at(pathPoint.x).at(pathPoint.y)->getTileTypeID() == TileTypes::tower) {
						findNewPath();
						break;
					}
				}
			}
		}

		if (towerRemoved) {
			findNewPath();
		}
	}

	if (atCurrentWaypointTarget() && pathToTarget.size() > 0) {

		currentWaypointTarget = pathToTarget[pathToTarget.size() - 1];
		pathToTarget.pop_back();
		//std::cout << "popper \n";

	}


	auto currentWaypointTargetWorldCord = mapGroundTilePosToWorldPos(currentWaypointTarget.x, currentWaypointTarget.y);


	if (posX < currentWaypointTargetWorldCord.x && !atCurrentWaypointTargetX()) {
		moveDirection = DIR_EAST;
		currentMoveAnimationIndex = getDirectionIndex(moveDirection);
		//std::cout << "JUPP " << currentWaypointTargetWorldCord.x << " \n";
	}
	else if (posX > currentWaypointTargetWorldCord.x && !atCurrentWaypointTargetX()) {
		moveDirection = DIR_WEST;
		currentMoveAnimationIndex = getDirectionIndex(moveDirection);
	}
	else if (posY < currentWaypointTargetWorldCord.y  && !atCurrentWaypointTargetY()) {
		moveDirection = DIR_SOUTH;
		currentMoveAnimationIndex = getDirectionIndex(moveDirection);
	}
	else if (posY > currentWaypointTargetWorldCord.y  && !atCurrentWaypointTargetY()) {
		moveDirection = DIR_NORTH;
		currentMoveAnimationIndex = getDirectionIndex(moveDirection);
	}
	
	*/
	
	/*posX += moveDirection.x * speed * gameEngine->deltaTime.asMilliseconds();
	posY += moveDirection.y * speed * gameEngine->deltaTime.asMilliseconds();*/
	

//	std::cout << gameEngine->deltaTime.asMilliseconds() << std::endl;

	//DO NOT REMOVE!!!!
	//if (posX < 0 && moveDirection == DIR_WEST){
	//	moveDirection.x *= -1;
	//	posX = 0;
	//	currentMoveAnimationIndex = getDirectionIndex(moveDirection);
	//}
	//if (posX + width > gameEngine->getWindowSize().x  && moveDirection == DIR_EAST){
	//	moveDirection.x *= -1;
	//	posX = gameEngine->getWindowSize().x - width;
	//	currentMoveAnimationIndex = getDirectionIndex(moveDirection);
	//}

	//if (posY < 0 && moveDirection == DIR_NORTH){
	//	moveDirection.y *= -1;
	//	posY = 0;
	//	currentMoveAnimationIndex = getDirectionIndex(moveDirection);
	//}
	//if (posY + height > gameEngine->getWindowSize().y  && moveDirection == DIR_SOUTH){
	//	moveDirection.y *= -1;
	//	posY = gameEngine->getWindowSize().y - height;
	//	currentMoveAnimationIndex = getDirectionIndex(moveDirection);
	//}



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

void IronmanUnit::killYourself() {

	delete this;

}