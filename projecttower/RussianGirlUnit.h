#pragma once
#include "Unit.h"
class RussianGirlUnit : public Unit {
public:
	RussianGirlUnit(Vortex * gameEngine, std::vector<std::vector<MapTile *>> * mapGroundTiles, int posX, int posY, int endPosX, int endPosY);
	~RussianGirlUnit();

	void update();
	std::vector<sf::Drawable *> getRenderDrawable();
	void findNewPath();

	void killYourself();
};

