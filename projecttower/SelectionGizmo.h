#pragma once
#include "Entity.h"

class SelectionGizmo : public Entity {
public:
	SelectionGizmo(Vortex * gameEngine, int posX, int posY);
	~SelectionGizmo();

	std::vector<sf::Drawable *> SelectionGizmo::getRenderDrawable();
	std::vector<VortexSprite*> selectionSprites;

	void update();

private:
	
};

