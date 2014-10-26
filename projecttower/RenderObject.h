#pragma once

#include <vector>

//Forward (Unto) declaration (Halo 4 ref)
class VortexSprite;

class RenderObject {
public:
	RenderObject();
	~RenderObject();

	virtual void update() = 0;
	virtual std::vector<VortexSprite *> getRenderSprites() = 0;

};

