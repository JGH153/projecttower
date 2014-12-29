#pragma once

#include <SFML\Window.hpp>
#include <SFML\Graphics.hpp>
#include <vector>
#include <iostream>
#include <string>
#include <sstream>

#include "RenderObject.h"
#include "RemovableObject.h"

#include "Vortex.h"
//#include "VortexSprite.h"
#include "VortexAnimation.h"
#include "EffectsHandler.h"
#include "VortexSound.h"

//#include "GameGuiController.h"

class Entity : public RenderObject, public RemovableObject {
public:
	Entity(Vortex * gameEngine, int posX, int posY);
	~Entity();


	sf::Vector2f getPos();
	sf::Vector2i getSize();
	

	void setPos(float posX, float posY);
	void setPos(sf::Vector2f pos);
	void setSize(int width, int height);
	
	
	//virtual void update();

	float posX;
	float posY;

	int width;
	int height;

protected:

	

	Vortex * gameEngine;

};

