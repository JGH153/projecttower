#pragma once
#include "Unit.h"
class ChineseUnit : public Unit {
public:
	ChineseUnit(Vortex * gameEngine, std::vector<std::vector<MapTile *>> * mapGroundTiles, int posX, int posY, int endPosX, int endPosY);
	~ChineseUnit();

	void update();
	std::vector<sf::Drawable *> getRenderDrawable();
	void findNewPath();

	void killYourself();
};

