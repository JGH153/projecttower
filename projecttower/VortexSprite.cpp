#include "VortexSprite.h"


VortexSprite::VortexSprite() : sf::Sprite(){


}

VortexSprite::VortexSprite(const sf::Texture &texture) : sf::Sprite(texture){
	

}


VortexSprite::~VortexSprite()
{
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


std::vector<sf::Drawable *> VortexSprite::getRenderDrawable() {

	std::vector<sf::Drawable *> returnVector2;
	returnVector2.push_back(this);
	return returnVector2;

}