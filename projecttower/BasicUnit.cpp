#include "BasicUnit.h"


BasicUnit::BasicUnit(Vortex * gameEngine, std::vector<std::vector<MapTile *>> * mapGroundTiles, int posX, int posY, int endPosX, int endPosY) : Unit(gameEngine, mapGroundTiles, posX, posY) {

	int randNum = rand() % 10;

	this->endPosX = endPosX;
	this->endPosY = endPosY;

	if (randNum < 8){
		//speed = 0.02f + gameEngine->getRandFloat(0.01f, 0.02f);
		speed = 0.02f;
		width = 32/2;
		height = 48/2;
		maxHealth = 30.f;
		offsetComponentsY = 15 + gameEngine->getRandInt(-5, 5);

		killReward = 1;
	}else{
		//speed = 0.04f + gameEngine->getRandFloat(0.01f, 0.08f);
		speed = 0.04f;
		width = 96/4;
		height = 96/4;
		maxHealth = 40.f;
		offsetComponentsY = 15 + gameEngine->getRandInt(-5, 5);

		killReward = 2;
	}


	moveDirection = DIRECTIONS[rand() % 4];

	currentMoveAnimationIndex = getDirectionIndex(moveDirection);

	for (int i = 0; i < DIRECTIONS.size(); i++){

		VortexAnimation * tempAni = new VortexAnimation(posX, posY, width, height, 13, gameEngine);
		if (randNum < 8) {
			tempAni->asembleSpritesheetAnimation("Graphics/ironman.png", 32, 48, DIRECTIONS[i], 4);
		}
		else{
			tempAni->asembleSpritesheetAnimation("Graphics/bahamut.png", 96, 96, DIRECTIONS[i], 4);
		}
		moveAnimations.push_back(tempAni);

	}

	hitParticleColor = sf::Color(220, 20, 20);
	

	initUnit();
	

}


BasicUnit::~BasicUnit(){

	for (auto current : moveAnimations) {
		gameEngine->addRemovableObjectToList(current);
	}

}



std::vector<sf::Drawable *> BasicUnit::getRenderDrawable() {
	std::vector<sf::Drawable*> temp = moveAnimations[currentMoveAnimationIndex]->getRenderDrawable();
	temp.push_back(healthBarBG);
	temp.push_back(healthBarFG);
	temp.push_back(healthBarFrame);
	return temp;
}

void BasicUnit::findNewPath() {
	atWaypointTarget = false;
	int footPosX = posX + width / 2;
	int footPosY = posY + height;

	aStar aStarPath = aStar(*mapGroundTiles);
	//startEndStruct startStop = startEndStruct(4, 13, 21, 13);
	startEndStruct startStop = startEndStruct(footPosX / 25, footPosY / 25, endPosX / 25, endPosY / 25);
	pathToTarget = aStarPath.findPath(startStop);

	if (pathToTarget.size() > 0) {

		currentWaypointTarget = pathToTarget[pathToTarget.size() - 1];
		pathToTarget.pop_back();

	}
	else {

		//std::cout << "No Path \n";

	}
}


void BasicUnit::update() {

	if (isDead() || reachedGoal) {
		return;
	}

	if (pathToTarget.empty()) {
		int centerPosX = posX + width / 2;
		int centerPosY = posY + height / 2;

		if (abs(centerPosX - endPosX) * abs(centerPosX - endPosX) + abs(centerPosY - endPosY) * abs(centerPosY - endPosY) <= 100 * 100) {
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

void BasicUnit::killYourself() {

	delete this;

}