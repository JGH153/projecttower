#pragma once
#include <SFML\Audio.hpp>
#include <vector>
#include <iostream>
#include <string>

#include "Vortex.h"

class Vortex;

class VortexSound : public sf::Sound{
public:
	VortexSound();
	VortexSound(Vortex * gameEngine, std::string path);
	~VortexSound();
};

