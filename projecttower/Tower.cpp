#include "Tower.h"


Tower::Tower(Vortex * gameEngine, std::vector<Unit *> * enemyList) : Entity(gameEngine) {

	
	this->enemyList = enemyList;

}


Tower::~Tower()
{
}

Unit * Tower::findTarget() {

	for (int i = 0; i < enemyList->size(); i++) {

		if (abs(enemyList->at(i)->posX - posX) < range / 2 && abs(enemyList->at(i)->posY - posY) < range / 2) {

			//if ((!enemyList->at(i)->dead) && (!enemyList->at(i)->deathAnimationActive))
				return enemyList->at(i);

		}

	}

	return nullptr;

}

//bool Tower::canAttack() {
//	timeSinceLastAttack = stopwatch.getElapsedTime();
//
//	//Tower is on cooldown and cannot attack
//	if (timeSinceLastAttack.asMilliseconds() < speed * 1000) {
//		return false;
//	}
//
//	//Tower can attack
//	stopwatch.restart();
//	return true;
//}
//
//bool Tower::attack() {
//	if (!canAttack()) {
//		return false;
//	}
//	std::cout << "DEBUG: Ima firin' mah lazor pewpew" << std::endl;
//	if (!target->takeDamageAndCheckIfDead(damage)) {
//		//If unit survived the attack, return false.
//		return false;
//	}
//	//Unit is dead, send true signal to remove it
//	return true;
//}

//void Tower::update() {
//
//	//std::cout << "TOWER" << std::endl;
//	//std::cout << gameEngine->getWindow()->getSize().x;
//
//	//gameEngine->getWindow()->draw(sprite);
//	//if (!target) {
//	//	return;
//	//}
//	//double xdist = abs(position.x - target->position.x);
//	//double ydist = abs(position.y - target->position.y);
//
//	////Target has moved out of range
//	//if ((xdist + xdist) * (ydist + ydist) > (range * range)) {
//	//	target = NULL;
//	//}
//}