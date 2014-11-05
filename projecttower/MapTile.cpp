#include "MapTile.h"


MapTile::MapTile(Vortex * gameEngine, int ID, double posX, double posY, double width, double height) {

	this->gameEngine = gameEngine;
	this->ID = ID;
	this->posX = posX;
	this->posY = posY;
	this->width = width;
	this->height = height;
	
	setLoadPathBasedOnCurrentID();
	
	tileSprite = VortexSprite(gameEngine, loadPath, posX, posY, width, height);

}

void MapTile::changeTileType(int newID) {

	this->ID = newID;

	setLoadPathBasedOnCurrentID();

	tileSprite = VortexSprite(gameEngine, loadPath, posX, posY, width, height);

}

void MapTile::setLoadPathBasedOnCurrentID() {

	if (ID == TileTypes::grass) {
		loadPath = "Graphics/grass_tile.png";
		//loadPath = "Graphics/grass.png";
	} else if (ID == TileTypes::dirt) {
		loadPath = "Graphics/dirt.png";
	} else if (ID == TileTypes::water) {
		loadPath = "Graphics/water.png";
	} else if (ID == TileTypes::wall) {
		loadPath = "Graphics/wall.png";
	} else if (ID == TileTypes::cave) {
		loadPath = "Graphics/cave.png";
	} else if (ID == TileTypes::tower) {
		//just tile displayed below a tower. Practise invisible
		loadPath = "Graphics/dirt.png";
	} else {
		//default
		loadPath = "Graphics/dirt.png";
	}

}

int MapTile::getTileTypeID() {
	return ID;
}


MapTile::~MapTile() {
}

std::vector<sf::Drawable *> MapTile::getRenderDrawable() {
	return tileSprite.getRenderDrawable();
}



void MapTile::update() {
}