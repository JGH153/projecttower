#pragma once

#include <vector>
#include "GlobalDefines.h"

//Forward (Unto) declaration (Halo 4 ref)
class VortexSprite;

class RenderObject {
public:
	RenderObject();
	~RenderObject();

	virtual void update() = 0;
	virtual std::vector<sf::Drawable *> getRenderDrawable() = 0;

protected:

	std::vector<RenderData> returnVector;

};

