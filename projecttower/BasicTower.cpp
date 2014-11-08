#include "BasicTower.h"


BasicTower::BasicTower(Vortex * gameEngine, std::vector<Unit *> * enemyList, int posX, int posY, double gridTileSize) : Tower(gameEngine, enemyList, posX, posY) {

	damage = 2.f;
	range = 200;
	reloadTimeMS = 500;
	projectileSpeed = 0.2f;

	reloading = false;

	this->gridTileSize = gridTileSize;

	/*this->posX = posX;
	this->posY = posY;*/

	//towerSprite = new VortexSprite("Graphics/button.png", posX, posY);

	sf::Texture * texImageTile;
	texImageTile = gameEngine->loadImageToTexture("Graphics/Towers/NormalReducedCanvas.png");
	sf::Texture * texArrow = gameEngine->loadImageToTexture("Graphics/Projectiles/Arrow.png");
	
	float towerSpriteOffsetX = 0.f;
	float towerSpriteOffsetY = 23.f;


	/*spritePos.x = posX - towerSpriteOffsetX;
	spritePos.y = posY - towerSpriteOffsetY;*/
	width = gridTileSize;
	height = gridTileSize + towerSpriteOffsetY;
	towerSprite = new VortexSprite(gameEngine, "Graphics/Towers/NormalReducedCanvas.png", posX - towerSpriteOffsetX, posY - towerSpriteOffsetY, width, height);
	projectileSprite = new VortexSprite(gameEngine, "Graphics/Projectiles/Arrow.png", posX + width / 2, posY - towerSpriteOffsetY, texArrow->getSize().x / 2, texArrow->getSize().y / 2);
}


BasicTower::~BasicTower() {
}


std::vector<sf::Drawable *> BasicTower::getRenderDrawable() {
	auto temp = towerSprite->getRenderDrawable();
	for (auto current : projectiles) {
		temp.push_back(current->projectileSprite);
	}
	return temp;
}



void BasicTower::update() {
	for (int i = 0; i < projectiles.size(); i++) {
		if (projectiles[i]->hasHitTarget() || projectiles[i]->target == nullptr || projectiles[i]->posX < 0 || projectiles[i]->posX > WINDOWSIZEX || projectiles[i]->posY < 0 || projectiles[i]->posX > WINDOWSIZEY) {
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

	// If tower has a previous target, check if that target is still within range
	if (currentTarget != nullptr) {
		if (!targetWithinRange(currentTarget)) {
			currentTarget = nullptr;
		}
	}

	if (!reloading) {
		// If tower has no target, find one
		if (currentTarget == nullptr) {
			currentTarget = findTarget();
		}
		// If it has a viable target by now, attack it
		if (currentTarget != nullptr) {
			//fire!
			//std::cout << "im firing my lazer" << std::endl;
			projectiles.push_back(new Projectile(gameEngine, posX, posY, projectileSprite, currentTarget, projectileSpeed, damage));
			reloading = true;
			reloadTimer.restart();
			
		}

	}

}