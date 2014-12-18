#pragma once
#include "Unit.h"
class IronmanUnit : public Unit {
public:
	IronmanUnit(Vortex * gameEngine, std::vector<std::vector<MapTile *>> * mapGroundTiles, int posX, int posY, int endPosX, int endPosY);
	~IronmanUnit();

	void update();
	std::vector<sf::Drawable *> getRenderDrawable();

	void killYourself();
};

