#include "Unit.h"


Unit::Unit(Vortex * gameEngine, std::vector<std::vector<MapTile *>> * mapGroundTiles, int posX, int posY) : Entity(gameEngine, posX, posY) {

	this->gameEngine = gameEngine;
	this->mapGroundTiles = mapGroundTiles;

	zIndex = zIndexlayer::projectile;

	offsetComponentsY = 0.f;

}


Unit::~Unit()
{
	//gameEngine->addRemovableObjectToList(healthBarBG);
	//gameEngine->addRemovableObjectToList(healthBarFG);
	//gameEngine->addRemovableObjectToList(healthBarFrame);

	delete healthBarBG;
	delete healthBarFG;
	delete healthBarFrame;

	//std::cout << "BYE";
}

void Unit::initUnit() {

	atWaypointTarget = true;

	this->currentHealth = maxHealth;

	int scaleFactorX = 12;
	int scaleFactorY = 8;
	int healthBarWidth = 266 / scaleFactorX;
	int healthBarHeight = 65 / scaleFactorY;
	int healthBarPosX = posX - healthBarWidth / 4;
	int healthBarPosY = posY - healthBarHeight;

	healthBarBG = new VortexSprite(gameEngine, "Graphics/GUI/HealthBar/HealthBarBG.gif", healthBarPosX, healthBarPosY, healthBarWidth, healthBarHeight);
	healthBarFG = new VortexSprite(gameEngine, "Graphics/GUI/HealthBar/HealthBarFG.gif", healthBarPosX, healthBarPosY, healthBarWidth, healthBarHeight);
	healthBarFrame = new VortexSprite(gameEngine, "Graphics/GUI/HealthBar/HealthBarFrame.png", healthBarPosX, healthBarPosY, healthBarWidth, healthBarHeight);

}


bool Unit::hitPoint(sf::Vector2f point) {
	return hitPoint(point.x, point.y);
}

bool Unit::hitPoint(double x, double y) {

	if (x >= this->posX && x <= this->posX + this->width
		&& y >= this->posY && y <= this->posY + this->height) {
		return true;
	}

	return false;
}

void Unit::damage(float damage) {
	if (isDead()) {
		return;
	}
	currentHealth -= damage;
	
	
	//std::cout << health << std::endl;

}

bool Unit::isDead() {

	if (currentHealth <= 0.f) {
		return true;
	}

	return false;

}

//bool Unit::takeDamageAndCheckIfDead(int damage) {
//	hp -= damage;
//	if (hp <= 0) {
//		return true;	//Returns true if unit is dead. Delete unit and remove it from vector in GameController.
//	}
//	
//	std::cout << "My hp: " << hp << std::endl; //DEBUG
//	return false;	//Unit still alive. Dont do shit.
//}

//void Unit::update() {
//
//	std::cout << "UNIT" << std::endl;
//
//}

bool Unit::atCurrentWaypointTarget() {

	float range = 10.f; //px?

	auto currentWaypointTargetWorldCord = mapGroundTilePosToWorldPos(currentWaypointTarget.x, currentWaypointTarget.y);

	//std::cout << abs(currentWaypointTargetWorldCord.x - posX) << " | " << abs(currentWaypointTargetWorldCord.y - posY) << std::endl;

	if (abs(currentWaypointTargetWorldCord.x - posX) < range / 2 && abs(currentWaypointTargetWorldCord.y - posY) < range / 2) {
		//std::cout << "YESS\n";
		return true;
	}

	return false;

}

bool Unit::atCurrentWaypointTargetX() {

	float range = 10.f; //px?

	auto currentWaypointTargetWorldCord = mapGroundTilePosToWorldPos(currentWaypointTarget.x, currentWaypointTarget.y);

	if (abs(currentWaypointTargetWorldCord.x - posX) < range / 2) {
		//std::cout << "YESS\n";
		return true;
	}

	return false;

}

bool Unit::atCurrentWaypointTargetY() {

	float range = 10.f; //px?

	auto currentWaypointTargetWorldCord = mapGroundTilePosToWorldPos(currentWaypointTarget.x, currentWaypointTarget.y);

	if (abs(currentWaypointTargetWorldCord.y - posY) < range / 2) {
		//std::cout << "YESS\n";
		return true;
	}

	return false;

}

sf::Vector2f Unit::mapGroundTilePosToWorldPos(int x, int y) {
	int gridTileSize = 25;
	return sf::Vector2f(x*gridTileSize, y*gridTileSize);


}

sf::Vector2i Unit::WorldPosToMapGroundTilePos(double x, double y) {
	double gridTileSize = 25.0;
	return sf::Vector2i(x/gridTileSize, y/gridTileSize);

}

void Unit::moveHealthBar(sf::Vector2f offset) {

	healthBarBG->move(offset);
	healthBarFG->move(offset);
	healthBarFrame->move(offset);
}