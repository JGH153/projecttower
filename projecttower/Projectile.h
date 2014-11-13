#pragma once
#include "Unit.h"
#include <math.h>       /* atan2 */

class Projectile : public Entity {

public:
	Projectile(Vortex *gameEngine, int posX, int posY, VortexSprite *projectileSprite, Unit *target, float speed, float damage);
	~Projectile();

	void update();
	bool checkIfHitTarget();
	std::vector<sf::Drawable*> getRenderDrawable();
	VortexSprite *projectileSprite;
	Unit *target;
	bool destroyProjectile;

	void killYourself();
	
private:
	Vortex *gameEngine;
	float damage;
	float speed;

	void updatePos();
	
};

