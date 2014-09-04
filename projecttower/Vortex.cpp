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

		std::cout << "Unable to load file " << path << std::endl;
		std::cin.get();
		exit(1);
		// What do when there is no image?!
	}

	return sf::Sprite(image);

}

sf::Texture  Vortex::loadImageToTexture(std::string path){

	sf::Texture image;
	if (!image.loadFromFile(path)){

		std::cout << "Unable to load file " << path << std::endl;
		std::cin.get();
		exit(1);
		// What do when there is no image?!
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