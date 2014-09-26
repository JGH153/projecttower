#pragma once

#include <SFML\Window.hpp>
#include <SFML\Graphics.hpp>
#include <vector>
#include <iostream>
#include <string>
#include <sstream>



#include "Vortex.h"
#include "VortexSprite.h"
#include "VortexAnimation.h"

#include "GameGuiController.h"

class Entity{
public:
	Entity(Vortex * gameEngine);
	~Entity();

	virtual void update() = 0;
	virtual void render() = 0;
	//virtual void update();

protected:

	Vortex * gameEngine;

};

