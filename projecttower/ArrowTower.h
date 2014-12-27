#pragma once

#include "Tower.h"

class ArrowTower : public Tower {
public:
	ArrowTower(Vortex * gameEngine, std::vector<Unit *> * enemyList, int posX, int posY, double gridTileSize, sf::Vector2i mapGroundTileIndex, std::vector<VortexParticleSystem*> * particleList);
	~ArrowTower();

	void update();
	std::vector<sf::Drawable *> getRenderDrawable();
	//VortexSprite *projectileSprite;

	void killYourself();


private:


	VortexSound fireSound;
	

};

