#pragma once
#include "Unit.h"
class BasicUnit : public Unit {
public:
	BasicUnit(Vortex * gameEngine, std::vector<std::vector<MapTile *>> * mapGroundTiles, int posX, int posY, float maxHealth);
	~BasicUnit();

	void update();
	void render();
	std::vector<sf::Drawable *> getRenderDrawable();


private:

	std::vector<VortexAnimation *> moveAnimations;
	int currentMoveAnimationIndex;


};

