#include "VortexAnimation.h"


VortexAnimation::VortexAnimation(int x, int y, int width, int height, float fps, Vortex * gameEngine){

	posX = x;
	posY = y;
	this->width = width;
	this->height = height;

	this->fps = fps;

	currentFrame = 0;

	this->gameEngine = gameEngine;

}


VortexAnimation::~VortexAnimation(){
}


void VortexAnimation::addFrame(std::string path){

	sf::Sprite image = gameEngine->loadImageToSprite(path);

	image.setPosition(posX, posY);
	Vortex::setSpriteSize(&image, width, height);
	frames.push_back(image);

}

void VortexAnimation::update(float delta){



	//std::cout << "SIZE: " << frames.size();
	gameEngine->getWindow()->draw(frames[currentFrame]);
	currentFrame++;


	if (currentFrame >= frames.size())
		currentFrame = 0;

}
