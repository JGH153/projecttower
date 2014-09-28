#pragma once

#include <SFML\Window.hpp>
#include <SFML\Graphics.hpp>
#include <vector>
#include <iostream>
#include <string>
#include <sstream>

#include "Vortex.h"
#include "SubController.h"

class MenuController : public SubController {

public:
	MenuController(Vortex * gameEngine);
	~MenuController();

	void update();
	void render() {};

	std::vector<RenderObject *> getRenderObjectList();

private:
	VortexSprite testSprite;

};

