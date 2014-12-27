#pragma once

#include <SFML\Graphics.hpp>
#include <array>
#include <iostream>


namespace TileTypes {
	extern const int grass;
	extern const int dirt;
	extern const int water;
	extern const int wall;
	extern const int cave;
	extern const int tower;
}

//namespace zIndexLayers {
//	extern const int background;
//	extern const int tower;
//	extern const int projectile;
//	extern const int unit;
//}

enum class zIndexlayer : int { 
	background = 1,
	tower,
	projectile,
	unit
};


class node {
public:

	int x;
	int y;

	float disFromStart;
	float disFromTarget;
	float sum;
	node * parent;

	node(int x, int y, float disFromStart, float disFromTarget, node * parent) :
		x(x),
		y(y),
		disFromStart(disFromStart),
		disFromTarget(disFromTarget),
		parent(parent) {

		sum = disFromStart + disFromTarget;

	}



};

struct startEndStruct {
public:
	int startX;
	int startY;
	int endX;
	int endY;
	startEndStruct(int startX, int startY, int endX, int endY) :
		startX(startX), startY(startY), endX(endX), endY(endY) {
	}

};


int getDirectionIndex(sf::Vector2i direction);

const sf::Vector2i DIR_SOUTH	=	{ 0, 1 };
const sf::Vector2i DIR_WEST =		{ -1, 0 };
const sf::Vector2i DIR_EAST =		{ 1, 0 };
const sf::Vector2i DIR_NORTH	=	{ 0, -1 };

const int WINDOWSIZEX = 1280;
const int WINDOWSIZEY = 720;

//Maintain ratio based on resolution (16(+1):9) atm. +1 due to the middle column used for separation between players
const int GAMEMAPSIZEX = 49; 
const int GAMEMAPSIZEY = 27;

const int GAME_GRID_TILE_SIZE = (int)(WINDOWSIZEX / GAMEMAPSIZEX);

const int MAXFPS = 60;

const sf::Color UNABLETOBUILD(150, 0, 0, 200);
const sf::Color ABLETOBUILD(0, 150, 0, 200);


const std::array<sf::Vector2i, 4> DIRECTIONS = { DIR_SOUTH, DIR_WEST, DIR_EAST, DIR_NORTH };

enum {
	renderData_None = 0, 
	renderData_Sprite = 1,
	renderData_Text = 2
};

class VortexSprite;
class VortexText;

//not in use? 
struct RenderData {

	int dataType; //0 = none, 1 = sprite, 2 = text
	VortexSprite * sprite;
	VortexText * text;

	RenderData(VortexSprite * sprite) {
		this->sprite = sprite;
		dataType = renderData_Sprite;
	}
	//RenderData(VortexSprite &sprite) {
	//	this->sprite = &sprite;
	//	dataType = renderData_Sprite;
	//}
	RenderData(VortexText  * text) {
		this->text = text;
		dataType = renderData_Text;
	}
	//RenderData(sf::Text text) {
	//	this->text = &text;
	//	dataType = renderData_Text;
	//}

	void  operator = (VortexSprite * sprite) {
		this->sprite = sprite;
		dataType = renderData_Sprite;
	}
	void  operator = (VortexText  * text) {
		this->text = text;
		dataType = renderData_Text;
	}

	operator VortexSprite * () {
		return sprite;
	}
	operator VortexText  * () {
		return text;
	}


};

class RemovableObject;
//
//std::vector<RemovableObject * > RemovableObjectList;
