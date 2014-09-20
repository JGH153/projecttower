#include "Vortex.h"


Vortex::Vortex(){

	running = true;

}


Vortex::~Vortex(){
}


sf::RenderWindow * Vortex::getWindow(){

	return mainWindow;

}

void Vortex::initVortex(int screenWidth, int screenHeight, std::string windowName, std::string iconPath, std::string defaultFontPath, bool fullscreen){

	sf::ContextSettings openGLSettings;
	openGLSettings.antialiasingLevel = 8;

	int windowSettings = sf::Style::Resize;

	//windowSettings = sf::Style::None;
	windowSettings = sf::Style::None;

	if (fullscreen){

		auto bestRes = sf::VideoMode::getFullscreenModes();

		screenWidth = bestRes[0].width;
		screenHeight = bestRes[0].height;

		windowSettings = windowSettings | sf::Style::Fullscreen;

	}


	//display avalible videomodes for fullscreen and current

	/*auto deskMode = sf::VideoMode::getDesktopMode();

	std::cout << "Mode (Desktop) " << deskMode.width << "-" << deskMode.height << "-" << deskMode.bitsPerPixel << " is valid" << std::endl;


	std::cout << std::endl;

	for each (auto Mode in sf::VideoMode::getFullscreenModes()){

		std::cout << "Mode (fullscreen) " << Mode.width << "-" << Mode.height << "-" << Mode.bitsPerPixel << " is valid" << std::endl;

	}*/



	
	mainWindow = new sf::RenderWindow(sf::VideoMode(screenWidth, screenHeight), windowName, windowSettings, openGLSettings);

	sf::Image image;
	if (!image.loadFromFile(iconPath)){
		std::cout << "FATAL iconPath";
		std::cin.get();
		closeApplication();
	}

	mainWindow->setIcon(image.getSize().x, image.getSize().y, image.getPixelsPtr());
	mainWindow->setFramerateLimit(60);
	//mainWindow->setTitle("GREGER ER KUL");
	//mainWindow->setMouseCursorVisible(false);



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

	auto timePri = frameTime.restart();
	//std::cout << timePri.asMilliseconds() << std::endl;
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

	image = checkForCopyOfTex(path, sf::IntRect(0,0,0,0));

	if (image == nullptr){

		image = new sf::Texture;
		if (!image->loadFromFile(path)){
			std::cout << "Unable to load image: " << path << std::endl;
			image = &checkForBackupImage(path);
		}

		textures.push_back(new texElement(path, image, sf::IntRect(0, 0, 0, 0)));

	}

	return image;

}


sf::Texture * Vortex::loadImageSubsetToTexture(std::string path, sf::IntRect rec){

	sf::Texture * image;

	image = checkForCopyOfTex(path, rec);

	if (image == nullptr){

		image = new sf::Texture;
		if (!image->loadFromFile(path, rec)){
			std::cout << "Unable to load image: " << path << std::endl;
			image = &checkForBackupImage(path);
		}

		textures.push_back(new texElement(path, image, rec));

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


sf::Texture * Vortex::checkForCopyOfTex(std::string path, sf::IntRect rec){

	for each (texElement * currentElement in textures){

		if (currentElement->path == path && currentElement->rec == rec){
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




		if (currentEvent.type == sf::Event::Closed){

			closeApplication();

		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)){

			closeApplication();

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

