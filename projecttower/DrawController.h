#pragma once

#include <SFML\Window.hpp>
#include <SFML\Graphics.hpp>
#include <SFML\Audio.hpp>
#include <vector>
#include <iostream>

#include "Vortex.h"
#include "VortexParticleSystem.h"
#include "VortexAnimation.h"
#include "VortexSprite.h"
#include "VortexButton.h"

class DrawController {
public:
	DrawController(Vortex * gameEngine);
	~DrawController();

	void drawLoop();

private:

	Vortex * gameEngine;

};

