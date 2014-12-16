#pragma once
#include "VortexButtonRectangle.h"

VortexButtonRectangle::VortexButtonRectangle(double x, double y, int w, int h, std::string imagePath, std::string title, Vortex * gameEngine) : VortexButton(x, y, gameEngine) {
	width = w;
	height = h;
	isPressed = false;
	hidden = false;
	image = new VortexSprite(gameEngine->loadImageToSprite(imagePath));
	setIdleImage(imagePath);
	hoverImage = nullptr;
	pressedImage = nullptr;
	image->setSize(width, height);

	this->title = title;
	font = *gameEngine->loadFont("Fonts/arial.ttf");
	text.setFont(font);
	text.setString(title);
	text.setCharacterSize(28);
	text.setColor(sf::Color::White);
	text.setStyle(sf::Text::Bold);

	setPosition(posX, posY);
	tooltipText = nullptr;
	tooltipBackground = nullptr;
}

VortexButtonRectangle::VortexButtonRectangle(double x, double y, int w, int h, std::string imagePath, std::string title, Vortex * gameEngine, int opacity) : VortexButton(x, y, gameEngine) {
	width = w;
	height = h;
	if (opacity <= 0){
		hidden = true;
	}
	image = new VortexSprite(gameEngine->loadImageToSprite(imagePath));
	setIdleImage(imagePath);
	hoverImage = nullptr;
	pressedImage = nullptr;
	image->setColor(sf::Color(255, 255, 255, opacity));
	image->setSize(width, height);

	this->title = title;
	font = *gameEngine->loadFont("Fonts/arial.ttf");
	text.setFont(font);
	text.setString(title);
	text.setCharacterSize(28);
	text.setColor(sf::Color::White);
	text.setStyle(sf::Text::Bold);

	setPosition(posX, posY);
	tooltipText = nullptr;
	tooltipBackground = nullptr;
}

VortexButtonRectangle::VortexButtonRectangle(double x, double y, int w, int h, std::string imagePath, std::string title, Vortex * gameEngine, int opacity, std::string tooltipText) : VortexButton(x, y, gameEngine) {
	width = w;
	height = h;
	if (opacity <= 0){
		hidden = true;
	}
	image = new VortexSprite(gameEngine->loadImageToSprite(imagePath));
	setIdleImage(imagePath);
	hoverImage = nullptr;
	pressedImage = nullptr;
	image->setColor(sf::Color(255, 255, 255, opacity));
	image->setSize(width, height);

	this->title = title;
	font = *gameEngine->loadFont("Fonts/arial.ttf");
	text.setFont(font);
	text.setString(title);
	text.setCharacterSize(28);
	text.setColor(sf::Color::White);
	text.setStyle(sf::Text::Bold);

	setPosition(posX, posY);
	tooltipBackground = nullptr;

	this->tooltipText = new VortexText(tooltipText, *gameEngine->loadFont("Fonts/arial.ttf"), 20);
	this->tooltipText->setColor(sf::Color::Transparent);
	this->tooltipText->setStyle(sf::Text::Bold);
	this->tooltipText->setPosition(0, 0);

	tooltipBackground = new sf::RectangleShape(sf::Vector2f(this->tooltipText->getLocalBounds().width, this->tooltipText->getLocalBounds().height + 6));
	tooltipBackground->setFillColor(sf::Color::Transparent);
	tooltipBackground->setPosition(0, 0);
}

VortexButtonRectangle::~VortexButtonRectangle()
{
}

void VortexButtonRectangle::killYourself() {

	delete this;

}

void VortexButtonRectangle::update(){
	
	if (hidden) {
		hovering = false;
		isPressed = false;
		return;
	}

	if (mouseOver() && !hovering){
		if (hoverImage != nullptr){
			image->setTexture(*hoverImage);
		}
		hovering = true;
		if (this->tooltipText != nullptr) {
			tooltipBackground->setFillColor(sf::Color(25, 25, 25, 200));
			this->tooltipText->setColor(sf::Color::White);
		}
	}
	else if (!mouseOver() && hovering){
		if (hoverImage != nullptr){
			image->setTexture(*idleImage);
		}
		
		hovering = false;
		if (this->tooltipText != nullptr) {
			tooltipBackground->setFillColor(sf::Color::Transparent);
			this->tooltipText->setColor(sf::Color::Transparent);
		}
	}

	

	if (gameEngine->eventMouseClickedLeft) {
		if (buttonClicked() && !isPressed){
			if (pressedImage != nullptr){
				image->setTexture(*pressedImage);
			}
			isPressed = true;
		}
	}

	if (gameEngine->eventMouseReleasedLeft) {
		if (!buttonClicked() && isPressed){
			if (pressedImage != nullptr){
				image->setTexture(*idleImage);
			}
			isPressed = false;
		}
	}

	if (hovering && tooltipText != nullptr) {

		int tooltipPostX = gameEngine->getMousePositionRelativeToWindow().x;
		int tooltipPostY = gameEngine->getMousePositionRelativeToWindow().y;

		//prevent tooltip goint out of screen (currently only at bottom)
		if (tooltipPostY + tooltipBackground->getLocalBounds().height > WINDOWSIZEY) {
			tooltipPostY = WINDOWSIZEY - tooltipBackground->getLocalBounds().height;
		}

		tooltipText->setPosition(tooltipPostX, tooltipPostY);
		tooltipBackground->setPosition(tooltipPostX, tooltipPostY);
		
	}
	
}

std::vector<sf::Drawable *> VortexButtonRectangle::getRenderDrawable() {

	std::vector<sf::Drawable *> drawData;
	drawData.push_back(image);
	drawData.push_back(&text);

	return drawData;
}

std::vector<sf::Drawable *> VortexButtonRectangle::getTooltipDrawable() {

	std::vector<sf::Drawable *> drawData;

	if (tooltipText != nullptr) {

		drawData.push_back(tooltipBackground);
		drawData.push_back(tooltipText);
	}

	return drawData;
}

void VortexButtonRectangle::setIdleImage(sf::Texture * newImage){
	delete idleImage;
	idleImage = newImage;
}
void VortexButtonRectangle::setHoverImage(sf::Texture * newImage){
	if (hoverImage != nullptr){
		delete hoverImage;
	}
	hoverImage = newImage;
}
void VortexButtonRectangle::setPressedImage(sf::Texture * newImage){
	if (pressedImage != nullptr){
		delete pressedImage;
	}
	pressedImage = newImage;
}

void VortexButtonRectangle::setIdleImage(std::string imagePath){
	delete idleImage;
	idleImage = gameEngine->loadImageToTexture(imagePath);
}
void VortexButtonRectangle::setHoverImage(std::string imagePath){
	if (hoverImage != nullptr){
		delete hoverImage;
	}
	hoverImage = gameEngine->loadImageToTexture(imagePath);
}
void VortexButtonRectangle::setPressedImage(std::string imagePath){
	if (pressedImage != nullptr){
		delete pressedImage;
	}
	pressedImage = gameEngine->loadImageToTexture(imagePath);
}


bool VortexButtonRectangle::hitPoint(sf::Vector2f point){
	return hitPoint(point.x, point.y);
}

bool VortexButtonRectangle::hitPoint(double x, double y){

	if (x >= this->posX && x <= this->posX + this->width
		&& y >= this->posY && y <= this->posY + this->height){
		return true;
	}

	return false;
}

void VortexButtonRectangle::setPosition(sf::Vector2f newPosition){
	posX = newPosition.x;
	posY = newPosition.y;
	int buttonWidth = this->getWidth();
	int buttonHeight = this->getHeight();
	float textWidth = text.getLocalBounds().width;
	float textHeight = text.getLocalBounds().height;
	//Text has a bit empty transparent space above, so dividing height by 2 makes it look like it isnt centered
	sf::Vector2f textPos(newPosition.x + (buttonWidth / 2 - textWidth / 2), newPosition.y + (buttonHeight / 2 - textHeight / 1.2)); 
	

	text.setPosition(textPos);
	image->setPosition(newPosition);
}

void VortexButtonRectangle::setPosition(double x, double y){
	setPosition(sf::Vector2f(x, y));
}