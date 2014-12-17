#pragma once
#include <vector>
#include <queue>
#include "GlobalDefines.h"
//#include "MapTile.h"			// Include loop fuckery, maptile includes Vortex.h, and Vortex.h includes this file (PathFinder.h)
//#include "SFML\System.hpp"
class PathFinder
{
public:
	PathFinder();
	~PathFinder();
	std::vector<std::vector<sf::Vector2i>> makeBreadthFirstDirectionMap(std::vector<std::vector<int>> map, sf::Vector2i goalPoint, sf::Vector2i exitDirection);
	//std::vector<std::vector<sf::Vector2i>> makeBreadthFirstDirectionMap(std::vector<std::vector<MapTile *>> map, sf::Vector2i goalPoint, sf::Vector2i exitDirection);

	std::vector<std::vector<sf::Vector2i>> breadthFirstDirectionMap;
private:
	//std::vector<std::vector<int>> translateMapFromTilesToInt(std::vector<std::vector<MapTile *>> map);
};