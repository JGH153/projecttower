#pragma once

#include "Tower.h"

class BasicTower : public Tower {
public:
	BasicTower(Vortex * gameEngine, std::vector<Unit *> * enemyList, int posX, int posY);
	~BasicTower();

	void update();
	std::vector<sf::Drawable *> getRenderDrawable();

private:

	VortexSprite * towerSprite;

};

