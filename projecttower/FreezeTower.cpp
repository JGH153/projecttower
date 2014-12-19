#include "FreezeTower.h"


FreezeTower::FreezeTower(Vortex * gameEngine, std::vector<Unit *> * enemyList, int posX, int posY, double gridTileSize, sf::Vector2i mapGroundTileIndex, std::vector<VortexParticleSystem *> * particleList, EffectsHandler* effectsHandler) : Tower(gameEngine, enemyList, posX, posY, mapGroundTileIndex, particleList) {

	damage = 1.f;
	range = 75;
	reloadTimeMS = 2000;
	projectileSpeed = 0.1f;
	splashRadius = 40;

	reloading = false;

	this->effectsHandler = effectsHandler;
	this->gridTileSize = gridTileSize;

	sf::Texture * texImageTile;
	texImageTile = gameEngine->loadImageToTexture("Graphics/Towers/FreezeReducedCanvas.png");

	towerSpriteOffsetX = 1.f;
	towerSpriteOffsetY = 23.f;

	width = gridTileSize;
	height = gridTileSize + towerSpriteOffsetY;
	towerSprite = new VortexSprite(gameEngine, "Graphics/Towers/FreezeReducedCanvas.png", posX - towerSpriteOffsetX, posY - towerSpriteOffsetY, width + 2, height);
	//projectileSpritePath = "Graphics/Projectiles/manyeffects_sheet.png";
	projectileSpritePath = "Graphics/Projectiles/frostbolt.png";

	towerId = 3;
}


FreezeTower::~FreezeTower() {
}


std::vector<sf::Drawable *> FreezeTower::getRenderDrawable() {

	auto returnList = towerSprite->getRenderDrawable();

	return returnList;

}



void FreezeTower::update() {


	for (int i = 0; i < projectiles.size(); i++) {
		if (projectiles[i]->destroyProjectile == true) {
			gameEngine->addRemovableObjectToList(projectiles[i]);
			projectiles[i] = nullptr;
			projectiles.erase(projectiles.begin() + i);
			i--;
		}
	}


	for (auto current : projectiles) {
		current->update();
	}


	if (reloadTimer.getElapsedTime().asMilliseconds() > reloadTimeMS) {
		reloading = false;
	}

	

	// If it is time to attack
	if (!reloading) {

		// If tower has a previous target, check if that target is still within range
		if (currentTarget != nullptr) {
			if (!targetWithinRange(currentTarget) || currentTarget->isDead()) {
				currentTarget = nullptr;
			}
		}


		// If tower has no target, find one
		if (currentTarget == nullptr) {
			currentTarget = findTarget();
		}
		// If it has a viable target by now, attack it
		if (currentTarget != nullptr) {

			//VortexAnimation* snowballProjectileEffect = new VortexAnimation(0, 0, 64/2, 64/2, 14, gameEngine);
			//snowballProjectileEffect->asembleSpritesheetAnimation(projectileSpritePath, 512, 0, 64, 64, 8, 6);

			auto sprite = new VortexSprite(gameEngine, projectileSpritePath, posX + width / 2, posY - towerSpriteOffsetY);

			auto projectile = new Projectile(gameEngine, posX + towerSprite->getSize().x / 2, posY, sprite, currentTarget, projectileSpeed, damage, splashRadius, enemyList, particleList, effectsHandler, 50);

			projectiles.push_back(projectile);
			reloading = true;
			reloadTimer.restart();
		}
	}
}

void FreezeTower::killYourself() {

	delete this;

}