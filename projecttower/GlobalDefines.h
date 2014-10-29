#pragma once

#include <SFML\Graphics.hpp>
#include <array>
#include <iostream>



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