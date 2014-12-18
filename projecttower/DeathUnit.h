#pragma once
#include "Unit.h"
class DeathUnit : public Unit {
public:
	DeathUnit(Vortex * gameEngine, std::vector<std::vector<MapTile *>> * mapGroundTiles, int posX, int posY, int endPosX, int endPosY);
	~DeathUnit();

	void update();
	std::vector<sf::Drawable *> getRenderDrawable();
	void findNewPath();

	void killYourself();
};

