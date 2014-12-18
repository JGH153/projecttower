#pragma once

#include "Unit.h"
class IndianaJonesUnit : public Unit {
public:
	IndianaJonesUnit(Vortex * gameEngine, std::vector<std::vector<MapTile *>> * mapGroundTiles, int posX, int posY, int endPosX, int endPosY);
	~IndianaJonesUnit();

	void update();
	std::vector<sf::Drawable *> getRenderDrawable();
	void findNewPath();

	void killYourself();
};

