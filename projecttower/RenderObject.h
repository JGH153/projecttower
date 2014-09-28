#pragma once
class RenderObject {
public:
	RenderObject();
	~RenderObject();

	virtual void update() = 0;
	virtual void render() = 0;
};

