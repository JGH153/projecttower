#pragma once
#include "Unit.h"
class IronmanUnit : public Unit {
public:
	IronmanUnit(Vortex * gameEngine, std::vector<std::vector<MapTile *>> * mapGroundTiles, int posX, int posY, int endPosX, int endPosY);
	~IronmanUnit();

	void update();
	void render();
	std::vector<sf::Drawable *> getRenderDrawable();
	void findNewPath();

	void killYourself();


private:

	std::vector<VortexAnimation *> moveAnimations;
	int currentMoveAnimationIndex;


};

