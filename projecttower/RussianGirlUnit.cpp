#include "RussianGirlUnit.h"


RussianGirlUnit::RussianGirlUnit(Vortex * gameEngine, std::vector<std::vector<MapTile *>> * mapGroundTiles, int posX, int posY, int endPosX, int endPosY) : Unit(gameEngine, mapGroundTiles, posX, posY) {

	this->endPosX = endPosX;
	this->endPosY = endPosY;

	speed = 0.04f;
	width = 32 / 2;
	height = 48 / 2;
	maxHealth = 25.f;
	offsetComponentsY = 15 + gameEngine->getRandInt(-5, 5);

	killReward = 3;


	moveDirection = DIRECTIONS[rand() % 4];

	currentMoveAnimationIndex = getDirectionIndex(moveDirection);

	for (int i = 0; i < DIRECTIONS.size(); i++){

		VortexAnimation * tempAni = new VortexAnimation(posX, posY, width, height, 13, gameEngine);
		tempAni->asembleSpritesheetAnimation("Graphics/russiangirl.png", 32, 48, DIRECTIONS[i], 4);
		moveAnimations.push_back(tempAni);

	}

	hitParticleColor = sf::Color(220, 20, 20);


	initUnit();
}


RussianGirlUnit::~RussianGirlUnit() {

}

std::vector<sf::Drawable *> RussianGirlUnit::getRenderDrawable() {
	std::vector<sf::Drawable*> temp = moveAnimations[currentMoveAnimationIndex]->getRenderDrawable();
	temp.push_back(healthBarBG);
	temp.push_back(healthBarFG);
	temp.push_back(healthBarFrame);
	return temp;
}

void RussianGirlUnit::findNewPath() {
	atWaypointTarget = false;
	int footPosX = posX + width / 2;
	int footPosY = posY + height;

	aStar aStarPath = aStar(*mapGroundTiles);
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


void RussianGirlUnit::update() {

	if (isDead() || reachedGoal) {
		return;
	}

	if (pathToTarget.empty()) {

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

void RussianGirlUnit::killYourself() {

	delete this;

}