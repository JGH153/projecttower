#pragma once
#include "Unit.h"
#include <math.h>       /* atan2 */

class Projectile : public Entity {

public:
	Projectile(Vortex *gameEngine, int posX, int posY, VortexSprite *projectileSprite, Unit *target, float speed, float damage);
	Projectile(Vortex *gameEngine, int posX, int posY, VortexSprite *projectileSprite, Unit *target, float speed, float damage, int radius, std::vector<Unit *> * enemyList, std::vector<VortexParticleSystem *> * particleList, EffectsHandler* effectsHandler);
	Projectile(Vortex *gameEngine, int posX, int posY, VortexAnimation* projectileSprites, Unit *target, float speed, float damage, int radius, std::vector<Unit *> * enemyList, std::vector<VortexParticleSystem *> * particleList, EffectsHandler* effectsHandler, int slowPercentage);
	Projectile(Vortex *gameEngine, int posX, int posY, VortexSprite* projectileSprites, Unit *target, float speed, float damage, int radius, std::vector<Unit *> * enemyList, std::vector<VortexParticleSystem *> * particleList, EffectsHandler* effectsHandler, int slowPercentage);

	~Projectile();

	void update();
	bool checkIfHitTarget();
	std::vector<sf::Drawable*> getRenderDrawable();
	VortexSprite *projectileSprite;
	Unit *target;
	bool destroyProjectile;

	void killYourself();
	sf::Color hitParticleColor;
	int radius;
	
private:
	Vortex *gameEngine;
	float damage;
	float speed;
	int slowPercentage;

	EffectsHandler* effectsHandler;
	bool animatedProjectile;

	void updatePos();
	std::vector<Unit *> * enemyList;
	std::vector<VortexParticleSystem *> * particleList;
	VortexAnimation* projectileSprites;
};

