#include "Vortex.h"


Vortex::Vortex(){

	running = true;

}


Vortex::~Vortex(){
}


sf::RenderWindow * Vortex::getWindow(){

	return mainWindow;

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

	totalTime.restart();

}


void Vortex::drawClear(){

	mainWindow->clear();

}

void Vortex::drawDisplay(){

	mainWindow->display();

}



void Vortex::frameStart(){

	frameTime.restart();
	drawClear();
	regEvents();

}

void Vortex::frameEnd(){

	drawDisplay();

}



VortexSprite Vortex::loadImageToSprite(std::string path){


	//sf::Texture * image;

	//image = checkForCopyOfTex(path);

	//if (image == nullptr){

	//	image = new sf::Texture;
	//	if (!image->loadFromFile(path)){
	//		std::cout << "Unable to load image: " << path << std::endl;
	//		image = &checkForBackupImage(path);
	//	}

	//	textures.push_back(new texElement(path, image));

	//}


	return VortexSprite(*loadImageToTexture(path));

}

sf::Texture * Vortex::loadImageToTexture(std::string path){

	sf::Texture * image;

	image = checkForCopyOfTex(path);

	if (image == nullptr){

		image = new sf::Texture;
		if (!image->loadFromFile(path)){
			std::cout << "Unable to load image: " << path << std::endl;
			image = &checkForBackupImage(path);
		}

		textures.push_back(new texElement(path, image));

	}

	return image;

}

sf::SoundBuffer * Vortex::loadSound(std::string path){

	sf::SoundBuffer * sound;

	sound = checkForCopyOfSound(path);

	if (sound == nullptr){

		sound = new sf::SoundBuffer;
		if (!sound->loadFromFile(path)){
			// error... return default
			std::cout << "Unable to load SoundBuffer: " << path << std::endl;
			std::cin.get();
			exit(0);
		}

	}

	return sound;

}

//NOT WORKING!!!!
sf::Music * openMusic(std::string path){

	//no factory pattern, streaming form disk/SSD

	sf::Music * music = new sf::Music();
	if (!music->openFromFile(path)){
		// error... return default
		std::cout << "Unable to load Music: " << path << std::endl;
		std::cin.get();
		exit(0);
	}

	return music;

}


sf::Font * Vortex::loadFont(std::string path){

	sf::Font * font;

	font = checkForCopyOfFont(path);

	if (font == nullptr){

		font = new sf::Font();
		if (!font->loadFromFile(path)){
			// error... return default
			std::cout << "Unable to load font: " << path << std::endl;
			return defaultFont;
		}

	}

	return font;

}


sf::Texture * Vortex::checkForCopyOfTex(std::string path){

	for each (texElement * currentElement in textures){

		if (currentElement->path == path){
			//std::cout << "Found duplicate: " << path << std::endl;
			return currentElement->texture;

		}

		//std::cout << currentElement->path;
	}

	return nullptr;

}

sf::SoundBuffer * Vortex::checkForCopyOfSound(std::string path){

	for each (soundElement * currentElement in sounds){

		if (currentElement->path == path){
			//std::cout << "Found duplicate: " << path << std::endl;
			return currentElement->sound;

		}

		//std::cout << currentElement->path;
	}

	return nullptr;

}

sf::Font * Vortex::checkForCopyOfFont(std::string path){

	for each (FontElement * currentElement in fonts){

		if (currentElement->path == path){
			//std::cout << "Found duplicate: " << path << std::endl;
			return currentElement->font;

		}

		//std::cout << currentElement->path;
	}

	return nullptr;

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


sf::Vector2i Vortex::getMousePosition(){
	return sf::Mouse::getPosition(*mainWindow);
}
sf::Vector2f Vortex::getMapPixelToCoords(sf::Vector2i point){
	return mainWindow->mapPixelToCoords(point);
}



sf::Font * Vortex::getDefaultFont(){
	return defaultFont;
}



sf::Time Vortex::getTimeFromProgramStart(){

	return totalTime.getElapsedTime();

}
sf::Time Vortex::getTimeFromFrameStart(){

	return frameTime.getElapsedTime();

}

sf::Vector2i Vortex::getWindowSize(){

	return sf::Vector2i(mainWindow->getSize().x, mainWindow->getSize().y);

}



//Vortex::loadFont(std::string path){



void Vortex::regEvents(){

	eventList.clear();

	sf::Event mainEvent;
	while (mainWindow->pollEvent(mainEvent)){
		eventList.push_back(mainEvent);
	}

	eventKeyPressed = false;
	eventKeyReleased = false;

	eventMouseMove = false;

	eventMouseClicked = false;
	eventMouseReleased = false;
	
	eventMouseClickedLeft = false;
	eventMouseClickedRight = false;

	eventMouseReleasedLeft = false;
	eventMouseReleasedRight = false;

	for each (sf::Event currentEvent in getWindowEvents()){

		if (currentEvent.type == sf::Event::KeyPressed){
			eventKeyPressed = true;
		}
		if (currentEvent.type == sf::Event::KeyReleased){
			eventKeyReleased = true;
		}

		if (currentEvent.type == sf::Event::LostFocus){
			//myGame.pause();
			windowInFocus = false;
		}

		if (currentEvent.type == sf::Event::GainedFocus){
			//myGame.resume();
			windowInFocus = true;
		}

		if (currentEvent.type == sf::Event::MouseMoved){

			eventMouseMove = true;

		}
		
		if (currentEvent.type == sf::Event::MouseButtonPressed){

			eventMouseClicked = true;

			if (currentEvent.mouseButton.button == sf::Mouse::Left){
				eventMouseClickedLeft = true;
			}
			if (currentEvent.mouseButton.button == sf::Mouse::Right){
				eventMouseClickedRight = true;
			}

		}

		if (currentEvent.type == sf::Event::MouseButtonReleased){

			eventMouseReleased = true;

			if (currentEvent.mouseButton.button == sf::Mouse::Left){
				eventMouseReleasedLeft = true;
			}
			if (currentEvent.mouseButton.button == sf::Mouse::Right){
				eventMouseReleasedRight = true;
			}

		}

		

	}


}

std::vector<sf::Event> Vortex::getWindowEvents(){

	return eventList;

}


void Vortex::setSpriteSize(sf::Sprite * sprite, double w, double h){

	sprite->setScale(w / sprite->getLocalBounds().width, h / sprite->getLocalBounds().height);

}



void Vortex::closeApplication(){

	running = false;
	mainWindow->close();

}

