#pragma once
#include "Tower.h"
class FreezeTower : public Tower {
public:
	FreezeTower(Vortex * gameEngine, std::vector<Unit *> * enemyList, int posX, int posY, double gridTileSize, sf::Vector2i mapGroundTileIndex, std::vector<VortexParticleSystem *> * particleList, EffectsHandler* effectsHandler);

	~FreezeTower();

	void update();
	std::vector<sf::Drawable *> getRenderDrawable();

	void killYourself();
	int splashRadius;
};

