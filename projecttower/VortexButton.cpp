#include "VortexButton.h"

VortexButton::VortexButton(double x, double y, std::string imagePath, std::string title, Vortex * gameEngine){
	this->gameEngine = gameEngine;
	image = VortexSprite(gameEngine->loadImageToSprite(imagePath));
	posX = x;
	posY = y;
	this->title = title;

	font = *gameEngine->loadFont("Fonts/arial.ttf");
	// select the font
	text.setFont(font); // font is a sf::Font
	// set the string to display
	text.setString(title);
	// set the character size
	text.setCharacterSize(28); // in pixels, not points!
	// set the color
	text.setColor(sf::Color::Red);
	// set the text style
	text.setStyle(sf::Text::Bold | sf::Text::Underlined);

}


VortexButton::~VortexButton(){

}


sf::Vector2f VortexButton::getPosition(){

	return sf::Vector2f(posX, posY);

}

int VortexButton::getWidth(){
	return width;
}

int VortexButton::getHeight(){
	return height;
}



bool VortexButton::buttonClicked(){
	if (gameEngine->eventMouseClickedLeft){
		sf::Vector2i mouse = gameEngine->getMousePosition();
		return hitPoint(gameEngine->getMapPixelToCoords(mouse));
	}
	return false;
}