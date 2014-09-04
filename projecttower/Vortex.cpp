#include "Vortex.h"


Vortex::Vortex(){

	running = true;

}


Vortex::~Vortex(){
}


void Vortex::initVortex(int screenWidth, int screenHeight, std::string windowName){

	mainWindow = new sf::RenderWindow(sf::VideoMode(screenWidth, screenHeight), windowName);
	this->windowName = windowName;

}


void Vortex::drawClear(){

	mainWindow->clear();

}

void Vortex::drawToScreen(sf::Sprite sprite){
	mainWindow->draw(sprite);
}
void Vortex::drawToScreen(sf::Sprite * sprite){
	mainWindow->draw(*sprite);
}
void Vortex::drawToScreen(sf::CircleShape circle){
	mainWindow->draw(circle);
}

void Vortex::drawDisplay(){

	mainWindow->display();

}


sf::Sprite Vortex::loadImageToSprite(std::string path){

	sf::Texture image;
	if (!image.loadFromFile(path)){
		image = checkForBackupImage(path);
	}

	return sf::Sprite(image);

}

sf::Texture  Vortex::loadImageToTexture(std::string path){

	sf::Texture image;
	if (!image.loadFromFile(path)){
		image = checkForBackupImage(path);
	}

	return image;

}

/**
* If the original texture/sprite/image could not be loaded, the program
* will try to load a default image which is clearly visible.
*
* @param  path	the directory of the original image, used for error msg
*/
sf::Texture Vortex::checkForBackupImage(std::string path) {
	//std::cout << "Unable to load file: " << path << std::endl;
	sf::Texture image;
	std::string backup = "Graphics/errorImage.jpg";
	if (!image.loadFromFile(backup)) {
		std::cout << "UNHANDLED EXEPTION: Unable to load backup file: " << backup << std::endl;
		std::cout << "Press enter to close application" << std::endl;
		std::cin.get();
		exit(1);
	}
	return image;
}

void Vortex::regEvents(){

	eventList.clear();

	sf::Event mainEvent;
	while (mainWindow->pollEvent(mainEvent)){
		eventList.push_back(mainEvent);
	}


}

std::vector<sf::Event> Vortex::getWindowEvents(){

	return eventList;

}


void Vortex::setSpriteSize(sf::Sprite * sprite, double x, double y){

	sprite->setScale(x / sprite->getLocalBounds().width, y / sprite->getLocalBounds().height);

}



void Vortex::closeApplication(){

	running = false;
	mainWindow->close();

}

