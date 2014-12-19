#include "Unit.h"


Unit::Unit(Vortex * gameEngine, std::vector<std::vector<MapTile *>> * mapGroundTiles, int posX, int posY) : Entity(gameEngine, posX, posY) {

	this->gameEngine = gameEngine;
	this->mapGroundTiles = mapGroundTiles;

	zIndex = zIndexlayer::projectile;

	offsetComponentsY = 0.f;

	groundTilesChanged = false;
	reachedGoal = false;
	towerRemoved = false;

	slowtimer = 0;
	slowed = false;
}


Unit::~Unit()
{
	delete healthBarBG;
	delete healthBarFG;
	delete healthBarFrame;

	for (auto current : moveAnimations) {
		gameEngine->addRemovableObjectToList(current);
	}

}

void Unit::initUnit() {

	
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

void Unit::updateMovement(){
	if (isDead() || reachedGoal){
		return;
	}

	if (firstTimeRun){
		updateDirection();
		firstTimeRun = false;
	}

	if (atTileCentre()){
		if (atTargetTile()){
			reachedGoal = true;
			return;
		}
		updateDirection();
	}
}

void Unit::updateDirection(){
	sf::Vector2i positionInMapTileSpace = WorldPosToMapGroundTilePos(posX, posY);
	auto newDirection = gameEngine->pathFinder->navigationMap[positionInMapTileSpace.x][positionInMapTileSpace.y];
	if (newDirection == sf::Vector2i(0, 0)){
		steppedOnBadTile = true;
	}
	else {
		steppedOnBadTile = false;
	}
	if (steppedOnBadTile){
		if (!directionFlipped){
			moveDirection *= -1;
			directionFlipped = true;
		}
	}
	else{
		moveDirection = newDirection;
		directionFlipped = false;
	}
	currentMoveAnimationIndex = getDirectionIndex(moveDirection);
	
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

void Unit::slowUnit(int slowPercentage, int slowtime) {
	if (slowtime > slowtimer) {
		slowtimer = slowtime;
	}
	if (!slowed) {
		slowed = true;
		speed = speed * (float)(100 - slowPercentage) / 100.f;
	}
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

bool Unit::atTileCentre(){
	float range = 5.f; //px?
	
	sf::Vector2f distanceFromCenter = sf::Vector2f(fmod(posX, 25.f), fmod(posY, 25.f));
	if (abs(distanceFromCenter.x) <= range && abs(distanceFromCenter.y) <= range){
		return true;
	}
	return false;
}
bool Unit::atTargetTile(){
	float range = 5.f; //px?

	if (abs(posX - endPosX) <= range && abs(posY - endPosY) <= range){
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

std::vector<sf::Drawable *> Unit::getHealthbarDrawable() {
	std::vector<sf::Drawable*> temp;
	temp.push_back(healthBarBG);
	temp.push_back(healthBarFG);
	temp.push_back(healthBarFrame);
	return temp;
}