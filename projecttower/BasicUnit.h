#pragma once
#include "Unit.h"
class BasicUnit : public Unit {
public:
	BasicUnit(Vortex * gameEngine, std::vector<std::vector<MapTile *>> * mapGroundTiles, int posX, int posY, int endPosX, int endPosY);
	~BasicUnit();

	void update();
	void render();
	std::vector<sf::Drawable *> getRenderDrawable();
	void findNewPath();

	void killYourself();


private:

	std::vector<VortexAnimation *> moveAnimations;
	int currentMoveAnimationIndex;


};

