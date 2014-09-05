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
