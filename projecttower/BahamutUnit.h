#pragma once
#include "Unit.h"

class BahamutUnit : public Unit {
public:
	BahamutUnit(Vortex * gameEngine, std::vector<std::vector<MapTile *>> * mapGroundTiles, int posX, int posY, int endPosX, int endPosY);
	~BahamutUnit();

	void update();
	std::vector<sf::Drawable *> getRenderDrawable();
	

	void killYourself();
};

