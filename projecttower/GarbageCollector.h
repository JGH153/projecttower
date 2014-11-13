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

	int remainingCycles;
	RemovableObject * object;

	RemovableObjectContainer(RemovableObject * object, int remainingCycles) {
		this->object = object;
		this->remainingCycles = remainingCycles;
	}

};

class GarbageCollector {
public:
	GarbageCollector();
	~GarbageCollector();

	void add(RemovableObject * object);
	void update();

	int elementsInList();

	std::mutex garbageMutex;

private:


	std::deque<RemovableObjectContainer> removableObjectList;

};

