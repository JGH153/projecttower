#pragma once

class VortexSprite;

class RenderObject {
public:
	RenderObject();
	~RenderObject();

	virtual void update() = 0;
	virtual void render() = 0;
	virtual VortexSprite * getRenderSprite() = 0;

};

