#pragma once
#include <SFML\Audio.hpp>
#include <vector>
#include <iostream>
#include <string>

#include "Vortex.h"

class Vortex;

class VortexMusic : public sf::Music {
public:
	VortexMusic();
	VortexMusic(Vortex * gameEngine, std::string path);
	~VortexMusic();
};

