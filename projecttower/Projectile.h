#pragma once
#include "Unit.h"
#include <math.h>       /* atan2 */

class Projectile : public Entity {

public:
	Projectile(Vortex *gameEngine, int posX, int posY, VortexSprite *projectileSprite, Unit *target, float speed, float damage);
	Projectile(Vortex *gameEngine, int posX, int posY, VortexSprite *projectileSprite, Unit *target, float speed, float damage, int radius, std::vector<Unit *> * enemyList, std::vector<VortexParticleSystem *> * particleList);
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
	

	void updatePos();
	std::vector<Unit *> * enemyList;
	std::vector<VortexParticleSystem *> * particleList;
};

