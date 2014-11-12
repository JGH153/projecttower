#include "BasicUnit.h"


BasicUnit::BasicUnit(Vortex * gameEngine, std::vector<std::vector<MapTile *>> * mapGroundTiles, int posX, int posY) : Unit(gameEngine, mapGroundTiles, posX, posY) {

	int randNum = rand() % 10;

	if (randNum < 8){
		speed = 0.02f + gameEngine->getRandFloat(0.01f, 0.02f);
		width = 32/2;
		height = 48/2;
		maxHealth = 30.f;
	}else{
		speed = 0.04f + gameEngine->getRandFloat(0.01f, 0.08f);
		width = 96/4;
		height = 96/4;
		maxHealth = 40.f;
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

	
	

	initUnit();
	

}


BasicUnit::~BasicUnit(){

	/*for (auto current : moveAnimations) {
		delete current;
	}*/

}



std::vector<sf::Drawable *> BasicUnit::getRenderDrawable() {
	std::vector<sf::Drawable*> temp = moveAnimations[currentMoveAnimationIndex]->getRenderDrawable();
	temp.push_back(healthBarBG);
	temp.push_back(healthBarFG);
	temp.push_back(healthBarFrame);
	return temp;
}



void BasicUnit::update() {

	if (isDead()) {
		return;
	}

	if (pathToTarget.size() == 0) {

		atWaypointTarget = false;

		//std::cout << "Astart starter " << std::endl;

		aStar aStarPath = aStar(*mapGroundTiles);
		startEndStruct startStop = startEndStruct(4, 14, 21, 14);
		pathToTarget = aStarPath.findPath(startStop);

		//std::cout << "printer vei med lengde: " << pathToTarget.size() << std::endl;

		for each (auto current in pathToTarget) {
			//std::cout << "x: " << current.x << " y: " << current.y << std::endl;
		}

		//std::cin.get();

		if (pathToTarget.size() > 0) {

			currentWaypointTarget = pathToTarget[pathToTarget.size() - 1];
			pathToTarget.pop_back();
			//std::cout << "popper \n";

		} else {

			std::cout << "No Path \n";

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
	} else if (posX > currentWaypointTargetWorldCord.x && !atCurrentWaypointTargetX()) {
		moveDirection = DIR_WEST;
		currentMoveAnimationIndex = getDirectionIndex(moveDirection);
	} else if (posY < currentWaypointTargetWorldCord.y  && !atCurrentWaypointTargetY()) {
		moveDirection = DIR_SOUTH;
		currentMoveAnimationIndex = getDirectionIndex(moveDirection);
	} else if (posY > currentWaypointTargetWorldCord.y  && !atCurrentWaypointTargetY()) {
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



	//std::lock_guard<std::mutex> unitLock(gameEngine->unitListMutex);
	sf::Vector2f offset(moveDirection.x * speed * gameEngine->deltaTime.asMilliseconds(), moveDirection.y * speed * gameEngine->deltaTime.asMilliseconds());

	posX += offset.x;
	posY += offset.y;
	moveHealthBar(offset);




	//Locking a loced mutex
	//try {
	//	std::lock_guard<std::mutex> unitLock(gameEngine->unitListMutex);
	//} catch (const std::system_error& e) {
	//	std::cout << "Caught system_error with code :" << e.code() << "\n"
	//		<< " meaning: " << e.what() << '\n';
	//	std::cin.get();
	//}

	moveAnimations[currentMoveAnimationIndex]->setPos(posX, posY);

	//std::cout << "Basic Unit" << std::endl;

	moveAnimations[currentMoveAnimationIndex]->update();


	float percentageHP = currentHealth / maxHealth;
	if (percentageHP < 0) {
		percentageHP = 0;
	}
	healthBarFG->setSize(healthBarBG->getSize().x * percentageHP, healthBarFG->getSize().y);

	//damage(0.25f);
}