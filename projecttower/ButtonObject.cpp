#include "ButtonObject.h"

ButtonObject::ButtonObject() {

}

ButtonObject::ButtonObject(Pos position, sf::Texture *tex, sf::Texture *mouseOver, sf::Texture *clicked) {
	topLeft = position;
	texture = tex;
	mouseOverTexture = mouseOver;
	clickedTexture = clicked;
}