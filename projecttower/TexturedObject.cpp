#include "TexturedObject.h"

TexturedObject::TexturedObject() {
	texture = NULL;
}

TexturedObject::TexturedObject(sf::Texture *tex) {
	texture = tex;
}

TexturedObject::TexturedObject(Pos position, sf::Texture *tex) {
	topLeft = position;
	texture = tex;
}