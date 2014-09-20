#pragma once
#include "Unit.h"
class BasicUnit : public Unit {
public:
	BasicUnit(Vortex * gameEngine, int posX, int posY);
	~BasicUnit();

	void update();


private:

	std::vector<VortexAnimation *> moveAnimations;
	int currentMoveAnimationIndex;


};

