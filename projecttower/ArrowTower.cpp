#include "ArrowTower.h"


ArrowTower::ArrowTower(Vortex * gameEngine, std::vector<Unit *> * enemyList, int posX, int posY, double gridTileSize, sf::Vector2i mapGroundTileIndex, std::vector<VortexParticleSystem *> * particleList) : Tower(gameEngine, enemyList, posX, posY, mapGroundTileIndex, particleList) {

	damage = 2.f;
	damage = 8.f;
	range = 100;
	reloadTimeMS = 1000;
	projectileSpeed = 0.3f;

	reloading = false;

	this->gridTileSize = gridTileSize;

	sf::Texture * texImageTile;
	texImageTile = gameEngine->loadImageToTexture("Graphics/Towers/NormalReducedCanvas.png");
	
	towerSpriteOffsetX = 0.f;
	towerSpriteOffsetY = 23.f;

	width = gridTileSize;
	height = gridTileSize + towerSpriteOffsetY;
	towerSprite = new VortexSprite(gameEngine, "Graphics/Towers/NormalReducedCanvas.png", posX - towerSpriteOffsetX, posY - towerSpriteOffsetY, width, height);
	projectileSpritePath = "Graphics/Projectiles/Arrow.png";

	towerId = 1;



	fireSound = VortexSound(gameEngine, "Sound/sound1.wav");
	fireSound.setVolume(8.f);

}


ArrowTower::~ArrowTower() {
}


std::vector<sf::Drawable *> ArrowTower::getRenderDrawable() {

	auto returnList =  towerSprite->getRenderDrawable();

	return returnList;

}



void ArrowTower::update() {


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

			auto sprite =  new VortexSprite(gameEngine, projectileSpritePath, posX + width / 2, posY - towerSpriteOffsetY);
			auto projectile = new Projectile(gameEngine, posX + towerSprite->getSize().x / 2, posY, sprite, currentTarget, projectileSpeed, damage);
			
			projectiles.push_back(projectile);
			reloading = true;
			reloadTimer.restart();

			
			fireSound.play();

			//std::cout << "playing sound?";

		}
	}
}

void ArrowTower::killYourself() {

	delete this;

}