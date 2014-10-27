#pragma once

#include <SFML\Window.hpp>
#include <SFML\Graphics.hpp>
#include <vector>
#include <iostream>
#include <string>
#include <sstream>

#include "Vortex.h"
#include "SubController.h"
#include "BasicUnit.h"

class MenuController : public SubController {

public:
	MenuController(Vortex * gameEngine);
	~MenuController();

	void update();
	std::vector<RenderData> getDynamicRenderData();
	std::vector<RenderData> getStaticRenderData();

	std::vector<RenderObject *> getRenderObjectList();

private:
	std::mutex guiMutex;
	std::vector<RenderObject *> guiObjects;

};

