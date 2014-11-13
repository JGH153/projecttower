#pragma once

#include <SFML\Window.hpp>
#include <SFML\Graphics.hpp>
#include <vector>
#include <deque>
#include <iostream>
#include <string>
#include <sstream>
#include <mutex>

#include "RemovableObject.h"

struct RemovableObjectContainer {

	sf::Clock remainingClock;
	RemovableObject * object;

	RemovableObjectContainer(RemovableObject * object) {
		this->object = object;
	}

};

class GarbageCollector {
public:
	GarbageCollector();
	~GarbageCollector();

	void add(RemovableObject * object);
	void update();

	int elementsInList();

	int getRemovableObjectListSize();

private:

	std::mutex garbageMutex;

	std::deque<RemovableObjectContainer> removableObjectListTemp;
	std::deque<RemovableObjectContainer> removableObjectList;

};

