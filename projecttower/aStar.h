#pragma once

#include "GlobalDefines.h"
#include "MapTile.h"
#include <deque>
#include <iostream>
#include <cmath>
#include <string>
using namespace std;

class aStar{
public:

	aStar(std::vector<std::vector<MapTile *>> map);
	~aStar();

	std::vector<std::vector<MapTile *>> map;
	int mapSizeX;
	int mapSizeY;

	bool nodeInLists(node * currentNode, deque<node*> * openNodes, deque<node*> * closedNodes);
	bool nodeAlreadyExplored(int xPos, int yPos, deque<node*> * openNodes, deque<node*> * closeNodes);
	bool outsideMap(int x, int y);
	void addNewAdjacentNodes(int nextIndex, deque<node*> * openNodes, deque<node*> * closedNodes, startEndStruct startAndEnd);
	int getNextByLowestSum(deque<node*> * openNodes);
	bool isAtEnd(deque<node*> * closedNodes, startEndStruct startAndEnd);
	void displayMap(deque< deque<char> > moveMap);
	deque<sf::Vector2i> getPathHome(deque<node*> * closedNodes, startEndStruct startAndEnd);
	deque<sf::Vector2i> findPath(startEndStruct startAndEnd);

};

