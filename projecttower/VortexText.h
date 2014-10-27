#pragma once

#include <SFML\Window.hpp>
#include <SFML\Graphics.hpp>
#include <vector>
#include <iostream>
#include <string>

//#include "Vortex.h"
#include "RenderObject.h"
#include "GlobalDefines.h"

class VortexText : public sf::Text, public RenderObject {
public:
	VortexText();
	VortexText(const std::string &string, const sf::Font &font, unsigned int characterSize);
	~VortexText();

	void update();
	std::vector<sf::Drawable *> getRenderDrawable();

};

