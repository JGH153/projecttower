#include "Vortex.h"


Vortex::Vortex(){

	running = true;
	garbageCollectorThreadOnline = false;

}


Vortex::~Vortex(){
}




void Vortex::initVortex(sf::RenderWindow * mainWindow, std::string defaultFontPath) {
	this->mainWindow = mainWindow;
	//display avalible videomodes for fullscreen and current

	/*auto deskMode = sf::VideoMode::getDesktopMode();

	std::cout << "Mode (Desktop) " << deskMode.width << "-" << deskMode.height << "-" << deskMode.bitsPerPixel << " is valid" << std::endl;


	std::cout << std::endl;

	for each (auto Mode in sf::VideoMode::getFullscreenModes()){ 

		std::cout << "Mode (fullscreen) " << Mode.width << "-" << Mode.height << "-" << Mode.bitsPerPixel << " is valid" << std::endl;

	}*/
	defaultFont = loadFont(defaultFontPath);

	totalTime.restart();

	randomNumberGenerator = std::default_random_engine(time(NULL));

	pathFinder = new PathFinder();

	networkHandler = new VortexNetwork(54000, 54001);

	localIpAdress = sf::IpAddress::getLocalAddress();


}







void Vortex::frameStart(){

	printMutex.lock();

	while (pristList.size() != 0) {

		auto current = pristList[pristList.size() - 1];
		pristList.pop_back();;
		std::cout << current;

	}

	printMutex.unlock();

	deltaTime = getTimeFromProgramStart() - lastRenderTime;
	lastRenderTime = getTimeFromProgramStart();
	auto timePri = frameTime.restart();

	

	regEvents();

}

void Vortex::frameEnd(){



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

	std::lock_guard<std::mutex> assetsGuard(assetsLoadMutex);

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

	std::lock_guard<std::mutex> assetsGuard(assetsLoadMutex);

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

	std::lock_guard<std::mutex> assetsGuard(assetsLoadMutex);

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

		sounds.push_back(new soundElement(path, sound));

	}

	return sound;

}

void Vortex::preloadSound(std::string path) {

	loadSound(path);

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

	std::lock_guard<std::mutex> assetsGuard(assetsLoadMutex);

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


void Vortex::setMousePosView(sf::View gameView) {
	currentMousePosView = gameView;
}


sf::Vector2f Vortex::getMousePositionRelativeToSetView() {

	auto mouseFirst = sf::Mouse::getPosition(*mainWindow);

	return mainWindow->mapPixelToCoords(sf::Mouse::getPosition(*mainWindow), currentMousePosView);

}

sf::Vector2i Vortex::getMousePositionRelativeToSetViewInt() {

	auto cordD = getMousePositionRelativeToSetView();

	sf::Vector2i returnPoint;
	returnPoint.x = cordD.x;
	returnPoint.y = cordD.y;

	return returnPoint;
}





sf::Vector2i Vortex::getMousePosition(){
	return sf::Mouse::getPosition(*mainWindow);
}

sf::Vector2i Vortex::getMousePositionRelativeToWindow() {
	return sf::Mouse::getPosition(*mainWindow);
}

sf::Vector2f Vortex::getMousePositionRelativeToViewFloat(sf::View gameView) {

	auto mouseFirst = sf::Mouse::getPosition(*mainWindow);

	return mainWindow->mapPixelToCoords(sf::Mouse::getPosition(*mainWindow), gameView);

}

sf::Vector2i Vortex::getMousePositionRelativeToView(sf::View gameView) {

	auto cordD = getMousePositionRelativeToViewFloat(gameView);

	sf::Vector2i returnPoint;
	returnPoint.x= cordD.x;
	returnPoint.y = cordD.y;

	return returnPoint;
}


sf::Vector2f Vortex::getMapPixelToCoords(sf::Vector2i point){
	return mainWindow->mapPixelToCoords(point);
}

sf::Vector2f Vortex::getMousePositionLocal() {
	sf::Vector2i mouse = getMousePosition();
	return getMapPixelToCoords(mouse);
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

void Vortex::pushEvent(sf::Event mainEvent) {

	pendingEventsMutex.lock();

	pendingEventList.push_back(mainEvent);

	pendingEventsMutex.unlock();

}

void Vortex::regEvents(){

	eventList.clear();

	pendingEventsMutex.lock();

	for (sf::Event currentEvent : pendingEventList) {

		eventList.push_back(currentEvent);

	}

	pendingEventList.clear();

	pendingEventsMutex.unlock();

	//reset evry event bool exept the eventMousePressed events
	eventKeyPressed = false;
	eventKeyReleased = false;

	eventMouseMove = false;

	eventMouseClicked = false;
	eventMouseReleased = false;
	
	eventMouseClickedLeft = false;
	eventMouseClickedRight = false;

	eventMouseReleasedLeft = false;
	eventMouseReleasedRight = false;

	eventMouseWheelScroll = false;
	eventMouseWheelScrollUp = false;
	eventMouseWheelScrollDown = false;

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

			eventMousePressedLeft = false;
			eventMousePressedRight = false;
			eventMousePressed = false;

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
			eventMousePressed = true;

			if (currentEvent.mouseButton.button == sf::Mouse::Left){
				eventMouseClickedLeft = true;
				eventMousePressedLeft = true;
			}
			if (currentEvent.mouseButton.button == sf::Mouse::Right){
				eventMouseClickedRight = true;
				eventMousePressedRight = true;
			}

		}

		if (currentEvent.type == sf::Event::MouseButtonReleased){

			eventMouseReleased = true;
			eventMousePressed = false;

			if (currentEvent.mouseButton.button == sf::Mouse::Left){
				eventMouseReleasedLeft = true;
				eventMousePressedLeft = false;
			}
			if (currentEvent.mouseButton.button == sf::Mouse::Right){
				eventMouseReleasedRight = true;
				eventMousePressedRight = false;
			}

		}

		if (currentEvent.type == sf::Event::MouseWheelMoved) {

			//positive is up, negative is down)
			int wheelDelta = currentEvent.mouseWheel.delta;

			eventMouseWheelScroll = true;

			if (wheelDelta > 0) {

				eventMouseWheelScrollUp = true;

			} else if(wheelDelta < 0) {

				eventMouseWheelScrollDown = true;

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



int Vortex::getRandInt(int min, int max) {

	//random number between 0 and 1
	//std::uniform_real_distribution<int> distribution(min, max);

	//return distribution(randomNumberGenerator);
	return min + (rand() % (int)(max - min + 1));

}

float Vortex::getRandFloat(float min, float max) {

	std::uniform_real_distribution<float> distribution(min, max);

	return distribution(randomNumberGenerator);

}

double Vortex::getRandDouble(double min, double max) {

	std::uniform_real_distribution<double> distribution(min, max);

	return distribution(randomNumberGenerator);

}


void Vortex::closeApplication(){
	running = false;

}

sf::RenderWindow * Vortex::getWindow() {
	return mainWindow;
}


void Vortex::handleGarbageCollector() {

	std::cout << "GarbageCollector thread started" << std::endl;

	garbageCollectorThreadOnline = true;

	float msToWait = 1000.f / (MAXFPS/2); //30 fps
	float lastRenderFrameTime = 0;
	sf::Clock renderFrameTime;

	sf::Clock oneSecTimeClock;
	int oneSecTime = 0;
	int numFramesSek = 0;

	std::cout << "Entering GarbageCollector loop" << std::endl;

	while (this->running || objectHandler.elementsInList() > 0) {


		objectHandler.update();




		int frameTime = renderFrameTime.restart().asMilliseconds();


		oneSecTime += oneSecTimeClock.restart().asMilliseconds();
		numFramesSek++;
		//one sec, only preformed once each sec
		if (oneSecTime > 1000) {
			oneSecTime = 0;
			//std::cout << "Num garbage fps: " << numFramesSek << " Num to del: " << objectHandler.getRemovableObjectListSize() << std::endl;
			numFramesSek = 0;
		}

		if (frameTime < msToWait) {
			//std::cout << "SStart\n";
			sf::sleep(sf::milliseconds(msToWait - frameTime));
			renderFrameTime.restart();
			//std::cout << "SEnd\n";
		}


	}

	//std::cout << "DONE2\n";

	garbageCollectorThreadOnline = false;

	

}

void Vortex::addRemovableObjectToList(RemovableObject * object) {
	objectHandler.add(object);

}



void Vortex::print(std::string printText) {

	std::lock_guard<std::mutex> lock(printMutex);

	pristList.push_back(printText);

}