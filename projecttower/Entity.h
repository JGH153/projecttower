#pragma once

#include <SFML\Window.hpp>
#include <SFML\Graphics.hpp>
#include <vector>
#include <iostream>
#include <string>
#include <sstream>

#include "RenderObject.h"

#include "Vortex.h"
#include "VortexSprite.h"
#include "VortexAnimation.h"

#include "GameGuiController.h"

class Entity : public RenderObject {
public:
	Entity(Vortex * gameEngine);
	~Entity();

	
	//virtual void update();

protected:

	Vortex * gameEngine;

};

