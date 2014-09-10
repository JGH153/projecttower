#include "VortexButton.h"


VortexButton::VortexButton(double x, double y, int w, int h, std::string imagePath, std::string title, Vortex * gameEngine){

	
	width = w;
	height = h;

	this->gameEngine = gameEngine;
	
	image = VortexSprite(gameEngine->loadImageToSprite(imagePath));
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

	
	setPosition(x, y);
	image.setSize(width, height);

}


VortexButton::~VortexButton(){

	

}

void VortexButton::setPosition(double x, double y){

	posX = x;
	posY = y;

	text.setPosition(posX, posY);
	image.setPosition(posX, posY);
	
	update(0);

}

sf::Vector2f VortexButton::getPosition(){

	return sf::Vector2f(posX, posY);

}


void VortexButton::update(float delta){

	if (gameEngine->eventMouseMove){
		if (mouseOver()){

			if (!mouseOverButton){

				mouseOverButton = true;
				image.setSize(width - 2, height - 2);
				image.setPosition(posX + 1, posY + 1);

				text.setPosition(posX + 1, posY + 1);
				text.setCharacterSize(text.getCharacterSize() - 1);

			}

		}else{

			if (mouseOverButton){

				mouseOverButton = false;
				image.setSize(width + 2, height + 2);
				image.setPosition(posX - 1, posY - 1);

				text.setPosition(posX - 1, posY - 1);
				text.setCharacterSize(text.getCharacterSize() + 1);

			}

		}

	}


	gameEngine->getWindow()->draw(image);
	gameEngine->getWindow()->draw(text);

}

bool VortexButton::buttonClicked(){

	if(gameEngine->eventMouseReleasedLeft)
		return mouseOver();

	return false;

}

bool VortexButton::hitPoint(sf::Vector2f point){
	return hitPoint(point.x, point.y);
}

bool VortexButton::hitPoint(double x, double y){

	if (x >= this->posX && x <= this->posX + this->width
		&& y >= this->posY && y <= this->posY + this->height){
		return true;
	}

	return false;
}


bool VortexButton::mouseOver(){

	sf::Vector2i mouse = gameEngine->getMousePosition();
	return hitPoint(gameEngine->getMapPixelToCoords(mouse));

}