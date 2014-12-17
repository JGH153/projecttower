#include "EffectsHandler.h"


EffectsHandler::EffectsHandler(Vortex * gameEngine) {
	this->gameEngine = gameEngine;
	
}


EffectsHandler::~EffectsHandler() {

}

void EffectsHandler::update() {
	if (currentEffects.empty()) {
		return;
	}

	for (int i = 0; i < currentEffects.size(); i++) {
		//printf("%d\n", currentEffects[i]->frames.size());
		currentEffects[i]->update();
		
		if (currentEffects[i]->playedOneTime) {
			
			gameEngine->effectsMutex.lock();

			gameEngine->addRemovableObjectToList(currentEffects[i]);
			currentEffects.erase(currentEffects.begin() + i);

			gameEngine->effectsMutex.unlock();
			i--;
		}
	}


}

void EffectsHandler::showExplosion(int posX, int posY) {
	VortexAnimation* explosionEffect = new VortexAnimation(posX - (93 / 2), posY - (100 / 2), 93, 100, 30, gameEngine);
	explosionEffect->asembleSpritesheetAnimation("Graphics/explosion_sheet.png", 93, 100, 10, 4);

	gameEngine->effectsMutex.lock();
	currentEffects.push_back(explosionEffect);
	gameEngine->effectsMutex.unlock();
}

std::vector<sf::Drawable *> EffectsHandler::getRenderDrawable() {
	std::vector<sf::Drawable*> temp;
	for (auto effect : currentEffects) {
		for (auto drawable : effect->getRenderDrawable()) {
			temp.push_back(drawable);
		}
		
	}
	return temp;
}