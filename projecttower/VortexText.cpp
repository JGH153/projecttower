#include "VortexText.h"


VortexText::VortexText() : sf::Text() {
}


VortexText::~VortexText() {
}

VortexText::VortexText(const std::string &string, const sf::Font &font, unsigned int characterSize) : sf::Text(string, font, characterSize) {



}


void VortexText::update() {


}


std::vector<sf::Drawable *> VortexText::getRenderDrawable() {

	std::vector<sf::Drawable *> returnVector2;
	returnVector2.push_back(this);
	return returnVector2;

}