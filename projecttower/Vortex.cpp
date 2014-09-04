#include "Vortex.h"


Vortex::Vortex(){

	running = true;

}


Vortex::~Vortex(){
}


void Vortex::initVortex(int screenWidth, int screenHeight, std::string windowName, std::string iconPath, std::string defaultFontPath){

	mainWindow = new sf::RenderWindow(sf::VideoMode(screenWidth, screenHeight), windowName);

	sf::Image image;
	if (!image.loadFromFile(iconPath)){
		std::cout << "FATAL iconPath";
		std::cin.get();
		closeApplication();
	}

	mainWindow->setIcon(image.getSize().x, image.getSize().y, image.getPixelsPtr());
	mainWindow->setFramerateLimit(60);

	this->windowName = windowName;

	defaultFont = loadFont(defaultFontPath);

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
void Vortex::drawToScreen(VortexParticleSystem particles){
	mainWindow->draw(particles);
}
void Vortex::drawToScreen(sf::Text text){
	mainWindow->draw(text);
}

void Vortex::drawDisplay(){

	mainWindow->display();

}



sf::Vector2i Vortex::getMousePosition(){
	return sf::Mouse::getPosition(*mainWindow);
}
sf::Vector2f Vortex::getMapPixelToCoords(sf::Vector2i point){
	return mainWindow->mapPixelToCoords(point);
}

sf::Sprite Vortex::loadImageToSprite(std::string path){

	sf::Texture image;
	if (!image.loadFromFile(path)){
		std::cout << "Unable to load image: " << path << std::endl;
		image = checkForBackupImage(path);
	}

	return sf::Sprite(image);

}

sf::Texture Vortex::loadImageToTexture(std::string path){

	sf::Texture image;
	if (!image.loadFromFile(path)){
		std::cout << "Unable to load image: " << path << std::endl;
		image = checkForBackupImage(path);
	}

	return image;

}

sf::Font Vortex::loadFont(std::string path){
	sf::Font font;
	if (!font.loadFromFile(path)){
		// error... return default
		std::cout << "Unable to load font: " << path << std::endl;
		return defaultFont;
	}

	return font;

}

sf::Font Vortex::getDefaultFont(){
	return defaultFont;
}

//Vortex::loadFont(std::string path){

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

