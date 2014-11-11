#include "Tower.h"


Tower::Tower(Vortex * gameEngine, std::vector<Unit *> * enemyList, int posX, int posY, sf::Vector2i mapGroundTileIndex) : Entity(gameEngine, posX, posY) {

	
	this->enemyList = enemyList;
	this->mapGroundTileIndex = mapGroundTileIndex;

}


Tower::~Tower()
{
}

Unit * Tower::findTarget() {
	Unit *closestEnemy = nullptr;

	gameEngine->unitListMutex.lock();

	for (int i = 0; i < enemyList->size(); i++) {
		//wat? funker egentlig dette bra eller er det noen som har drukket for mye karsk?
		//if (abs(enemyList->at(i)->posX - posX) < range / 2 && abs(enemyList->at(i)->posY - posY) < range / 2) { 
		//	if ((!enemyList->at(i)->dead) && (!enemyList->at(i)->deathAnimationActive))
		//		return enemyList->at(i);
		if (targetWithinRange(enemyList->at(i))) {
			// If there is no target set the first one found in range as a potential target, as best target
			if (closestEnemy == nullptr) {
				closestEnemy = enemyList->at(i);
			}
			// If the new target is closer than the other target, pick it in favor
			else if (newTargetCloser(closestEnemy, enemyList->at(i))) {
				closestEnemy = enemyList->at(i);
			}
		}
	}

	gameEngine->unitListMutex.unlock();

	return closestEnemy;

}

bool Tower::newTargetCloser(Unit *previousBest, Unit *newPotential) {
	float oldUnitDistX = abs(posX - previousBest->posX);
	float oldUnitDistY = abs(posX - previousBest->posY);
	float oldUnitDist = (oldUnitDistX * oldUnitDistX) + (oldUnitDistY * oldUnitDistY);

	float newUnitDistX = abs(posX - newPotential->posX);
	float newUnitDistY = abs(posX - newPotential->posY);
	float newUnitDist = (newUnitDistX * newUnitDistX) + (newUnitDistY * newUnitDistY);

	// If the distance between tower and the new unit is less than the previous best, return true
	if (oldUnitDist < newUnitDist) {
		return false;
	}
	return true;
}

bool Tower::targetWithinRange(Unit *testSubject) {
	float xdist = abs(posX - testSubject->posX);
	float ydist = abs(posX - testSubject->posY);
	
	//Target out of range
	if ((xdist * xdist) + (ydist * ydist) > (range * range)) {
		return false;
	}
	return true;
}

VortexSprite* Tower::getTowerSprite() {
	return towerSprite;
}

sf::Vector2i Tower::getMapGroundTileIndex() {

	return mapGroundTileIndex;

}