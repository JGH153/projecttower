#pragma once


#include <SFML\Window.hpp>
#include <SFML\Graphics.hpp>
#include <SFML\Audio.hpp>
#include <vector>
#include <iostream>

#include "Vortex.h"
#include "VortexLoader.h"
#include "VortexParticleSystem.h"
#include "VortexAnimation.h"
#include "VortexSprite.h"
#include "VortexButton.h"

class GameGuiController
{
public:
	GameGuiController(Vortex * gameEngine);
	~GameGuiController();

	void update();

	Vortex * gameEngine;
};

