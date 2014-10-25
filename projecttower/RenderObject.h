#pragma once

//Forward (Unto) declaration (Halo 4 ref)
class VortexSprite;

class RenderObject {
public:
	RenderObject();
	~RenderObject();

	virtual void update() = 0;
	virtual VortexSprite * getRenderSprite() = 0;

};

