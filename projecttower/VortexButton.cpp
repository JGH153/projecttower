#include "VortexButton.h"


VortexButton::VortexButton(int x, int y, int w, int h, std::string imagePath, std::string title, Vortex * gameEngine){

	posX = x;
	posY = y;
	width = w;
	height = h;

	this->gameEngine = gameEngine;

	image = VortexSprite(gameEngine->loadImageToSprite(imagePath));
	this->title = title;

	image.setPosition(posX, posY);
	image.setSize(width, height);


	font = gameEngine->loadFont("Fonts/arial.ttf");


	// select the font
	text.setFont(font); // font is a sf::Font

	text.setPosition(posX, posY);

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


void VortexButton::update(float delta){


	for each (sf::Event currentEvent in gameEngine->getWindowEvents()){

		if (currentEvent.type == sf::Event::MouseMoved){

			sf::Vector2i mouse = gameEngine->getMousePosition();
			if (hitPoint(gameEngine->getMapPixelToCoords(mouse))){

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

	}


	gameEngine->getWindow()->draw(image);
	gameEngine->getWindow()->draw(text);

}

bool VortexButton::hitPoint(sf::Vector2f point){
	return hitPoint(point.x, point.y);
}

bool VortexButton::hitPoint(int x, int y){

	


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