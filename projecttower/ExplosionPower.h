#pragma once

#include "GamePower.h"

class ExplosionPower : public GamePower {
public:
	ExplosionPower(Vortex * gameEngine, std::vector<Unit *> * enemyList, int posX, int posY);
	~ExplosionPower();

	float damage;

	void update();
	std::vector<sf::Drawable *> getRenderDrawable();
	void killYourself();

	void activatePower();

};

