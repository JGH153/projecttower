#include "ExplosionPower.h"


ExplosionPower::ExplosionPower(Vortex * gameEngine, std::vector<Unit *> * enemyList, int posX, int posY) : GamePower(gameEngine, enemyList, posX, posY){

	powerAnimation = new VortexAnimation(0, 0, 256, 256, 80.f, gameEngine);
	powerAnimation->asembleSpritesheetAnimation("Graphics/Powers/Bomb/explotionAnimation.png", 0, 0, 256, 256, 49, 1);
	powerAnimation->setLoop(false);
	//powerAnimation->stop();
	powerAnimation->setPos(posX - (powerAnimation->getSize().x / 2), posY - (powerAnimation->getSize().y / 2));

	powerSoundeffect = VortexSound(gameEngine, "Sound/Powers/explosion.wav");
	powerSoundeffect.setVolume(40.f);

	damage = 120.f;

	activatePower();

}


ExplosionPower::~ExplosionPower() {

	powerSoundeffect.stop();
	delete powerAnimation;

}


void ExplosionPower::activatePower() {

	powerSoundeffect.play();

	std::lock_guard<std::mutex> unitLock(gameEngine->unitListMutex);

	for (int i = 0; i < unitList->size(); i++) {
		if (targetWithinRange(posX, posY, 100, unitList->at(i)) && !unitList->at(i)->isDead()) {
			
			unitList->at(i)->damage(damage);

		}
	}


}


std::vector<sf::Drawable *> ExplosionPower::getRenderDrawable() {

	auto returnList = powerAnimation->getRenderDrawable();

	return returnList;

}



void ExplosionPower::update() {

	powerAnimation->update();
	if (powerAnimation->playedOneTime) {
		powerReadyForDelete = true;
	}

}


void ExplosionPower::killYourself() {

	delete this;

}