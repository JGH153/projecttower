#pragma once

#include "Tower.h"

class CannonTower : public Tower {
public:
	CannonTower(Vortex * gameEngine, std::vector<Unit *> * enemyList, int posX, int posY, double gridTileSize, sf::Vector2i mapGroundTileIndex, std::vector<VortexParticleSystem*> * particleList);
	~CannonTower();

	void update();
	std::vector<sf::Drawable *> getRenderDrawable();

	void killYourself();
	int splashRadius;
	
};

