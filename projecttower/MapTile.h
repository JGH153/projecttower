#pragma once

#include <SFML\Window.hpp>
#include <SFML\Graphics.hpp>
#include <vector>
#include <iostream>
#include <string>
#include <sstream>

#include "RenderObject.h"

#include "GlobalDefines.h"

#include "Vortex.h"
#include "VortexSprite.h"
#include "VortexAnimation.h"

class MapTile : RenderObject {
public:
	MapTile(Vortex * gameEngine, int ID, double posX, double posY, double width, double height);
	~MapTile();

	void changeTileType(int newID);

	void update();
	void render();
	std::vector<sf::Drawable *> getRenderDrawable();

	int getTileTypeID();

private:

	int ID;
	Vortex * gameEngine;
	double posX;
	double posY;
	double width;
	double height;

	VortexSprite tileSprite;

	std::string loadPath;

	void setLoadPathBasedOnCurrentID();

};

