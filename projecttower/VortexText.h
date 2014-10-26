#pragma once

#include <SFML\Window.hpp>
#include <SFML\Graphics.hpp>
#include <vector>
#include <iostream>

//#include "Vortex.h"
#include "RenderObject.h"
#include "GlobalDefines.h"

class VortexText : public sf::Text, public RenderObject {
public:
	VortexText();
	~VortexText();

	void update();
	std::vector<RenderData> getRenderData();

};

