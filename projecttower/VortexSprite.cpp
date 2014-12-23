#include "VortexSprite.h"


VortexSprite::VortexSprite() : sf::Sprite(){


}

VortexSprite::VortexSprite(const sf::Texture &texture, sf::IntRect spriteRec, sf::IntRect texRec) : sf::Sprite(texture, texRec) {

	setPosition(spriteRec.left, spriteRec.top);
	setSize(spriteRec.width, spriteRec.height);

}

VortexSprite::VortexSprite(Vortex * gameEngine, std::string path, float posX, float posY, double width, double height) : sf::Sprite() {

	setTexture(*gameEngine->loadImageToTexture(path));
	setPosition(posX, posY);
	setSize(width, height);


}

//create sprite using image size as sprite size
VortexSprite::VortexSprite(Vortex * gameEngine, std::string path, float posX, float posY) : sf::Sprite() {

	auto tex = gameEngine->loadImageToTexture(path);
	setTexture(*tex);
	setPosition(posX, posY);
	setSize(tex->getSize().x, tex->getSize().y);


}

VortexSprite::VortexSprite(const sf::Texture &texture) : sf::Sprite(texture){


}

VortexSprite::VortexSprite(sf::Texture* texture, float posX, float posY, double width, double height) : sf::Sprite(*texture){
	setPosition(posX, posY);
	setSize(width, height);

}


VortexSprite::~VortexSprite(){


	
}

void VortexSprite::killYourself() {

	delete this;

}

void VortexSprite::setSize(double w, double h){

	setScale(w / getLocalBounds().width, h / getLocalBounds().height);

}

void VortexSprite::setSize(sf::Vector2f newSize){

	setScale(newSize.x / getLocalBounds().width, newSize.y / getLocalBounds().height);

}

sf::Vector2f VortexSprite::getSize(){

	return sf::Vector2f(getGlobalBounds().width, getGlobalBounds().height);

}


void VortexSprite::update() {


}

bool VortexSprite::hitPoint(sf::Vector2f point) {
	return hitPoint(point.x, point.y);
}

bool VortexSprite::hitPoint(double x, double y) {

	if (x >= getPosition().x && x <= getPosition().x + getSize().x
		&& y >= getPosition().y && y <= getPosition().y + getSize().y) {
		return true;
	}

	return false;
}


std::vector<sf::Drawable *> VortexSprite::getRenderDrawable() {

	std::vector<sf::Drawable *> returnVector2;
	returnVector2.push_back(this);
	return returnVector2;

}