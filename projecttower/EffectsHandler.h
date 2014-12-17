#pragma once

#include "VortexAnimation.h"

class EffectsHandler {
public:
	EffectsHandler(Vortex* gameEngine);
	~EffectsHandler();

	void update();
	void showExplosion(int posX, int posY);
	std::vector<sf::Drawable*> getRenderDrawable();

private:
	std::vector<VortexAnimation*> currentEffects;
	
	Vortex* gameEngine;
};

