#include "SelectionGizmo.h"


SelectionGizmo::SelectionGizmo(Vortex * gameEngine, int posX, int posY) : Entity(gameEngine, posX, posY) {
	sf::Texture *temp = gameEngine->loadImageToTexture("Graphics/GUI/Selection/SelectionNWSmall.png");

	for (int i = 0; i < 4; i++) {
		selectionSprites.push_back(new VortexSprite(gameEngine, "Graphics/GUI/Selection/SelectionNWSmall.png", posX, posY, temp->getSize().x, temp->getSize().y));
		selectionSprites[i]->rotate(i * 90);
	}
}


SelectionGizmo::~SelectionGizmo() {

}

//Dont understand how we are supposed to use this function......
std::vector<sf::Drawable*> SelectionGizmo::getRenderDrawable() {
	std::vector<sf::Drawable *> returnable;
	for (int i = 0; i < selectionSprites.size(); i++) {
		returnable.push_back(selectionSprites[i]);
	}
	return returnable;
}

void SelectionGizmo::update() {

}

void SelectionGizmo::killYourself() {

	delete this;

}