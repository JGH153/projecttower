#pragma once

#include <SFML\Graphics.hpp>
#include <array>
#include <iostream>



int getDirectionIndex(sf::Vector2i direction);

const sf::Vector2i DIR_SOUTH	=	{ 0, 1 };
const sf::Vector2i DIR_WEST =		{ -1, 0 };
const sf::Vector2i DIR_EAST =		{ 1, 0 };
const sf::Vector2i DIR_NORTH	=	{ 0, -1 };

const int WINDOWSIZEX = 1000;
const int WINDOWSIZEY = 600;


const std::array<sf::Vector2i, 4> DIRECTIONS = { DIR_SOUTH, DIR_WEST, DIR_EAST, DIR_NORTH };
