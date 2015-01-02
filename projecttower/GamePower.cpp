#include "GamePower.h"


GamePower::GamePower(Vortex * gameEngine, std::vector<Unit *> * enemyList, int posX, int posY) : Entity(gameEngine, posX, posY) {

	powerReadyForDelete = false;
	unitList = enemyList;

}


GamePower::~GamePower() {
}

bool GamePower::isDone() {

	return powerReadyForDelete;

}


bool GamePower::targetWithinRange(float posX, float posY, float range, Unit *testSubject) {
	float xdist = abs(posX - testSubject->posX);
	float ydist = abs(posY - testSubject->posY);

	//Target out of range
	if ((xdist * xdist) + (ydist * ydist) > (range * range)) {
		return false;
	}
	return true;
}