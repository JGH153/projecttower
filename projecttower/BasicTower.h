#pragma once

#include "Tower.h"

class BasicTower : public Tower {
public:
	BasicTower(Vortex * gameEngine, std::vector<Unit *> * enemyList, int posX, int posY, double gridTileSize, sf::Vector2i mapGroundTileIndex);
	~BasicTower();

	void update();
	std::vector<sf::Drawable *> getRenderDrawable();
	//VortexSprite *projectileSprite;

	void killYourself();


private:

	

};

