#pragma once

#include "PathFinder.h"


PathFinder::PathFinder()
{
}


PathFinder::~PathFinder()
{
}
/*
// Overload to let you send the MapTile type map
std::vector<std::vector<sf::Vector2i>> PathFinder::makeBreadthFirstDirectionMap(std::vector<std::vector<MapTile *>> map, sf::Vector2i goalPoint, sf::Vector2i exitDirecion) {
	std::vector<std::vector<sf::Vector2i>> resultMap;
	std::vector<std::vector<int>> translatedMap;

	resultMap = makeBreadthFirstDirectionMap(translatedMap, goalPoint, exitDirecion);
	return resultMap;
}
*/
// Working backwards from the goalPoint, expand every tile on the map and mark a direction on it pointing to where it was expanded from
std::vector<std::vector<sf::Vector2i>> PathFinder::makeBreadthFirstDirectionMap(std::vector<std::vector<int>> map, sf::Vector2i goalPoint, sf::Vector2i exitDirecion) {
	std::vector<std::vector<sf::Vector2i>> resultMap;

	int width, height;
	width = map.size();
	height = map[0].size();
	std::queue<sf::Vector2i> nodesToExplore;

	nodesToExplore.push(goalPoint);

	// Fill resultmap with 0,0 vectors (invalid directions)
	for (int x = 0; x < width; x++) {
		std::vector<sf::Vector2i> column;
		for (int y = 0; y < height; y++) {
			column.push_back(sf::Vector2i(0, 0));
		}
		resultMap.push_back(column);
	}

	resultMap[goalPoint.x][goalPoint.y] = exitDirecion;

	// Work through the queue
	while (nodesToExplore.size() != 0){
		sf::Vector2i currentNode = nodesToExplore.front();
		nodesToExplore.pop();
		// Check all possible surrounding nodes
		for (auto direction : DIRECTIONS) {
			sf::Vector2i expandNode = currentNode + direction;
			if (expandNode.x < 0 || expandNode.x > width || expandNode.y < 0 || expandNode.y > height){
				// Out of bounds
				continue;
			}
			else {
				// Within bounds, check type
				int nodeType = map[expandNode.x][expandNode.y];
				if (nodeType == TileTypes::grass || nodeType == TileTypes::dirt || nodeType == TileTypes::cave){
					// Check if not already expanded
					if (resultMap[expandNode.x][expandNode.y] == sf::Vector2i(0, 0)){						
						// Result is the direction opposite of the one you took to get to this node
						resultMap[expandNode.x][expandNode.y] = direction * -1;
						// Push new node to queue
						nodesToExplore.push(expandNode);
					}
				}
			}
		}
	}
	/*
	for (int x = 0; x < width; x++) {
		std::vector<sf::Vector2i> column;
		for (int y = 0; y < height; y++) {
//			std::cout << map[x][y];
			if (resultMap[x][y] == sf::Vector2i(0, 0)){
				std::cout << "0";
			}
			else {
				std::cout << "1";
			}
		}
		std::cout << std::endl;
	}
	*/
	return resultMap;
}

/*
std::vector<std::vector<int>> PathFinder::translateMapFromTilesToInt(std::vector<std::vector<MapTile *>> map){
	std::vector<std::vector<int>> resultMap;
	int width, height;
	width = map.size();
	height = map[0].size();

	for (int x = 0; x < width; x++) {
		std::vector<int> column;
		for (int y = 0; y < height; y++) {
			column[y] = map[x][y]->getTileTypeID();
		}
		resultMap.push_back(column);
	}
	return resultMap;
}
*/