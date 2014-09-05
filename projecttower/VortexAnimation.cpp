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

	VortexSprite image = gameEngine->loadImageToSprite(path);

	image.setPosition(posX, posY);
	image.setSize(width, height);
	frames.push_back(image);

}

void VortexAnimation::update(float delta){

	sf::Time currentTime = gameEngine->getTimeFromProgramStart();

	//std::cout << "SIZE: " << frames.size();
	

	if (lastRunFrameTime.asMilliseconds() + (1000 / fps) < currentTime.asMilliseconds()){

		lastRunFrameTime = currentTime;

		currentFrame++;

		if (currentFrame >= frames.size()){
			currentFrame = 0;
			playedOneTime = true;
		}

	}


	gameEngine->getWindow()->draw(frames[currentFrame]);

	

}

void VortexAnimation::assembleAnimation(std::string startPath, std::string filetype, int startNum, int endNum){
	
	std::string path = "";

	for (int i = startNum; i <= endNum; i++){

		path.clear();

		std::stringstream ss;
		ss << i;

		path = startPath + ss.str() + filetype;

		addFrame(path);


	}
	

}
