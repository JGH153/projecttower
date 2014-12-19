#include "VortexAnimation.h"


VortexAnimation::VortexAnimation(float x, float y, int width, int height, float fps, Vortex * gameEngine){

	posX = x;
	posY = y;
	this->width = width;
	this->height = height;

	this->fps = fps;

	currentFrame = 0;

	this->gameEngine = gameEngine;
	playedOneTime = false;

}


VortexAnimation::~VortexAnimation(){

}


void VortexAnimation::addFrame(sf::Texture * tex){

	VortexSprite image = VortexSprite(*tex);

	image.setPosition(posX, posY);
	image.setSize(width, height);
	frames.push_back(image);


}

void VortexAnimation::addFrame(std::string path){

	VortexSprite image = gameEngine->loadImageToSprite(path);

	image.setPosition(posX, posY);
	image.setSize(width, height);
	
	frames.push_back(image);

}

void VortexAnimation::addFrame(VortexSprite* sprite) {

	frames.push_back(*sprite);

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

	int yPosSheet = getDirectionIndex(moveDirection);

	for (int x = 0; x < numFrmes; x++){

		sf::Texture * image = gameEngine->loadImageSubsetToTexture(path, sf::IntRect(orgWidth*x, orgHeight*yPosSheet, orgWidth, orgHeight));
		addFrame(image);

	}
}

// Used for cannon ball explosion
void VortexAnimation::asembleSpritesheetAnimation(std::string path, int orgWidth, int orgHeight, int numFrmesX, int numFrmesY) {
	sf::IntRect rect;

	for (int y = 0; y < numFrmesY; y++) {

		for (int x = 0; x < numFrmesX; x++) {
			rect = sf::IntRect(orgWidth*x, orgHeight*y, orgWidth, orgHeight);

			sf::Texture* texture = gameEngine->loadImageSubsetToTexture(path, rect);
			VortexSprite* image = new VortexSprite(texture, posX, posY, width, height);
			//sf::Color barelyTransparent(255, 255, 255, 230);
			//image->setColor(barelyTransparent);


			addFrame(image);
		}

	}
}

// Used for freeze tower projectile
void VortexAnimation::asembleSpritesheetAnimation(std::string path, int offsetX, int offsetY, int orgWidth, int orgHeight, int numFrmesX, int numFrmesY) {

	sf::IntRect rect;

	for (int y = 0; y < numFrmesY; y++) {

		for (int x = 0; x < numFrmesX; x++) {
			rect = sf::IntRect(orgWidth*x + offsetX, orgHeight*y + offsetY, orgWidth, orgHeight);

			sf::Texture* texture = gameEngine->loadImageSubsetToTexture(path, rect);
			VortexSprite* image = new VortexSprite(texture, posX, posY, width, height);
			


			addFrame(image);
		}

	}
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