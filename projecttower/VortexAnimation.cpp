#include "VortexAnimation.h"


VortexAnimation::VortexAnimation(float x, float y, int width, int height, float fps, Vortex * gameEngine){

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


void VortexAnimation::addFrame(sf::Texture * tex){

	VortexSprite image = VortexSprite(*tex);

	image.setPosition(posX, posY);
	image.setSize(width, height);
	//image.setColor(sf::Color(gameEngine->getRandInt(0, 255), gameEngine->getRandInt(0, 255), gameEngine->getRandInt(0, 255), 255));
	frames.push_back(image);


}

void VortexAnimation::addFrame(std::string path){

	VortexSprite image = gameEngine->loadImageToSprite(path);

	image.setPosition(posX, posY);
	image.setSize(width, height);
	
	frames.push_back(image);

}



std::vector<sf::Drawable *> VortexAnimation::getRenderDrawable() {

	return frames[currentFrame].getRenderDrawable();

}

void VortexAnimation::update(){

	sf::Time currentTime = gameEngine->getTimeFromProgramStart();

	//std::cout << "SIZE: " << frames.size();
	

	if (lastRunFrameTime.asMilliseconds() + (1000 / fps) < currentTime.asMilliseconds()){

		lastRunFrameTime = currentTime;

		//have to check first before currentFrame++ beacause if we use the normal approach it is possilbe for the renderer to render before 'out of frames' check is ran
		if (currentFrame+1 >= frames.size()) {
			currentFrame = 0;
			playedOneTime = true;
		} else {
			currentFrame++;
		}

		
	}
	
}

//VortexDrawObject * VortexAnimation::getDrawData() {
//
//	//return &frames[currentFrame];
//
//}


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

//assuming spritesheet have the same moveDirections (S, W, E, N)
void VortexAnimation::asembleSpritesheetAnimation(std::string path, int orgWidth, int orgHeight, sf::Vector2i moveDirection, int numFrmes) {

	//std::cout << orgWidth << " " << orgHeight << std::endl;
	//std::cin.get();

	int yPosSheet = getDirectionIndex(moveDirection);

	for (int x = 0; x < numFrmes; x++){

		sf::Texture * image = gameEngine->loadImageSubsetToTexture(path, sf::IntRect(orgWidth*x, orgHeight*yPosSheet, orgWidth, orgHeight));
		addFrame(image);

	}
	//sf::Texture * image = gameEngine->loadImageSubsetToTexture(path, sf::IntRect(0, 0, 32, 48));
	//addFrame(image);

}


void VortexAnimation::setPos(float x, float y){

	posX = x;
	posY = y;

	//std::cout << posX;

	for (VortexSprite &currentFrame : frames){

		currentFrame.setPosition(posX, posY);

	}


}

void VortexAnimation::killYourself() {

	delete this;

}