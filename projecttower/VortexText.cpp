#include "VortexText.h"


VortexText::VortexText() : sf::Text() {
}


VortexText::~VortexText() {
}

VortexText::VortexText(const std::string &string, const sf::Font &font, unsigned int characterSize) : sf::Text(string, font, characterSize) {



}


void VortexText::update() {


}


std::vector<RenderData>  VortexText::getRenderData() {

	std::vector<RenderData> returnVector;
	returnVector.push_back(RenderData(this));
	return returnVector;

}