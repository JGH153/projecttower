#pragma once

#include "Unit.h"

#include "Entity.h"

#include "VortexSound.h"


class GamePower : public Entity {
public:
	GamePower(Vortex * gameEngine, std::vector<Unit *> * enemyList, int posX, int posY);
	~GamePower();

	bool isDone();

protected:

	bool powerReadyForDelete;

	std::vector<Unit *> * unitList;
	VortexAnimation * powerAnimation;
	VortexSound powerSoundeffect;

	virtual void activatePower() = 0;

	bool targetWithinRange(float posX, float posY, float range, Unit *testSubject);

private:


};

