#pragma once
#include "Unit.h"
class HulkUnit : public Unit {
public:
	HulkUnit(Vortex * gameEngine, std::vector<std::vector<MapTile *>> * mapGroundTiles, int posX, int posY, int endPosX, int endPosY);
	~HulkUnit();

	void update();
	std::vector<sf::Drawable *> getRenderDrawable();
	void findNewPath();

	void killYourself();
};

