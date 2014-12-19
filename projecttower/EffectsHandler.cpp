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
	int effectWidth = 93 / 2;
	int effectHeight = 100 / 2;


	
	VortexAnimation* explosionEffect = new VortexAnimation(posX - (effectWidth / 2), posY - (effectHeight / 2), effectWidth, effectHeight, 30, gameEngine);
	explosionEffect->asembleSpritesheetAnimation("Graphics/explosion_sheet.png", 93, 100, 10, 4);

	gameEngine->effectsMutex.lock();
	currentEffects.push_back(explosionEffect);
	gameEngine->effectsMutex.unlock();
	
}

void EffectsHandler::showFreezingExplosion(int posX, int posY) {
	int effectWidth = 200 / 2;
	int effectHeight = 200 / 2;

	VortexAnimation* snowballExplosionEffect = new VortexAnimation(posX - (effectWidth / 2), posY - (effectHeight / 2), effectWidth, effectHeight, 30, gameEngine);
	snowballExplosionEffect->asembleSpritesheetAnimation("Graphics/iceexplosion_sheet.png", 100, 100, 5, 4);


	gameEngine->effectsMutex.lock();
	currentEffects.push_back(snowballExplosionEffect);
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