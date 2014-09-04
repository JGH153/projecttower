#include "ButtonObject.h"

ButtonObject::ButtonObject() {

}

ButtonObject::ButtonObject(Pos position, sf::Texture *tex, sf::Texture *mouseOver, sf::Texture *clicked) {
	pos = position;
	texture = tex;
	mouseOverTexture = mouseOver;
	clickedTexture = clicked;
}