#pragma once
#include "Unit.h"
class ReaperUnit : public Unit {
public:
	ReaperUnit(Vortex * gameEngine, std::vector<std::vector<MapTile *>> * mapGroundTiles, int posX, int posY, int endPosX, int endPosY, int currentLevel);
	~ReaperUnit();

	void update();
	std::vector<sf::Drawable *> getRenderDrawable();
	void findNewPath();

	void killYourself();
};

