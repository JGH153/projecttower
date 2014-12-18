#include "Renderer.h"


Renderer::Renderer(Vortex * gameEngine, int screenWidth, int screenHeight, float fps, std::string windowName, std::string iconPath, bool fullscreen) {
	bool initError = false;
	this->fps = fps;

	this->gameEngine = gameEngine;

	renderThreadOnline = false;

	

	

	topLevelRenderController = nullptr;

	
	

	this->screenWidth = screenWidth;
	this->screenHeight = screenHeight;
	this->windowName = windowName;
	this->iconPath = iconPath;
	this->fullscreen = fullscreen;

	


	this->windowName = windowName;
	loaded = initError ? false : true;
}


Renderer::~Renderer()
{
}

void Renderer::handleStaticBackground() {

	SubController * mainControllerPointer = topLevelRenderController;
	std::vector<SubController *> controllerRenderList;


	//ask top lvl controller to tell render if it has a active sub controller. if so, ask it if it has an sub controller. repeat untill getCurrentRenderController returns itself
	while (mainControllerPointer != mainControllerPointer->getCurrentRenderController()) {

		mainControllerPointer = mainControllerPointer->getCurrentRenderController();

	}

	//if no update
	if (!mainControllerPointer->requestingUpdateStaticRenderData())
		return;

	//std::cout << "oppdaterer static\n";


	staticRenderList.clear();

	controllerRenderList.push_back(mainControllerPointer);


	for each (auto currentController in  mainControllerPointer->getChildControllers()) {
		controllerRenderList.push_back(currentController);
	}


	for (int currentControllerID = 0; currentControllerID < controllerRenderList.size(); currentControllerID++) {

		std::vector<std::vector < sf::Drawable * >> tempStaticRenderList;

		if (controllerRenderList[currentControllerID] != nullptr) {
			//only update of controller has updated the static assets (like changing lvl)

			tempStaticRenderList = controllerRenderList[currentControllerID]->getStaticRenderData();
			controllerRenderList[currentControllerID]->updateStaticRenderData = false;


		}

		staticRenderList.push_back(tempStaticRenderList);

	}

	

	//SubController * tempControllerPointer = topLevelRenderController;
	////ask top lvl controller to tell render if it has a active sub controller. if so, ask it if it has an sub controller. repeat untill getCurrentRenderController returns itself
	//while (tempControllerPointer != tempControllerPointer->getCurrentRenderController()) {
	//	tempControllerPointer = tempControllerPointer->getCurrentRenderController();
	//}
	//if (tempControllerPointer != nullptr) {
	//	//only update of controller has updated the static assets (like changing lvl)
	//	if (tempControllerPointer->updateStaticRenderData) {

	//		staticRenderList = tempControllerPointer->getStaticRenderData();
	//		tempControllerPointer->updateStaticRenderData = false;

	//	}
	//}
}

void Renderer::renderMainLoop() {

	std::cout << "Render thread started" << std::endl;

	sf::ContextSettings openGLSettings;
	openGLSettings.antialiasingLevel = 1;

	int windowSettings = sf::Style::Resize;
	windowSettings = sf::Style::Default;

	if (fullscreen) {

		auto bestRes = sf::VideoMode::getFullscreenModes();

		screenWidth = bestRes[0].width;
		screenHeight = bestRes[0].height;

		windowSettings = windowSettings | sf::Style::Fullscreen;

	}

	mainWindow = new sf::RenderWindow(sf::VideoMode(screenWidth, screenHeight), windowName, windowSettings, openGLSettings);

	sf::Image image;
	if (!image.loadFromFile(iconPath)) {
		std::cout << "FATAL iconPath";
		std::cin.get();
	}

	mainWindow->setIcon(image.getSize().x, image.getSize().y, image.getPixelsPtr());

	if (!loaded) {
		std::cout << "Error initializing renderer" << std::endl;
		std::cin.get();
	}

	std::cout << "Entering render loop" << std::endl;

	renderThreadOnline = true;

	while (topLevelRenderController == nullptr) {

		sf::sleep(sf::milliseconds(10));

	}




	float msToWait = 1000.f / MAXFPS;
	float lastRenderFrameTime = 0;
	sf::Clock renderFrameTime;


	sf::Clock oneSecTimeClock;
	int oneSecTime = 0;
	int numFramesSek = 0;

	mainWindow->setFramerateLimit(MAXFPS);
	

	while (gameEngine->running) {

		sf::Event mainEvent;
		while (getWindow()->pollEvent(mainEvent)) {
			gameEngine->pushEvent(mainEvent);

		}

		doRenderLoop();

		int frameTime = renderFrameTime.restart().asMilliseconds();


		oneSecTime += oneSecTimeClock.restart().asMilliseconds();
		numFramesSek++;
		//one sec, only preformed once each sec
		if (oneSecTime > 1000) {
			oneSecTime = 0;
			//std::cout << "Num render fps: " << numFramesSek << std::endl;
			numFramesSek = 0;
		}

		if (frameTime < msToWait) {
			sf::sleep(sf::milliseconds(msToWait - frameTime));
			renderFrameTime.restart();
		}




	}

	renderThreadOnline = false;


}


void Renderer::doRenderLoop() {

	//sf::Clock tidTaker;
	//sf::Time t1, t2, t3;

	handleStaticBackground();

	drawClear();

	SubController * mainControllerPointer = topLevelRenderController;
	std::vector<SubController *> controllerRenderList;


	//ask top lvl controller to tell render if it has a active sub controller. if so, ask it if it has an sub controller. repeat untill getCurrentRenderController returns itself
	while (mainControllerPointer != mainControllerPointer->getCurrentRenderController()) {

		mainControllerPointer = mainControllerPointer->getCurrentRenderController();

	}

	controllerRenderList.push_back(mainControllerPointer);

	for each (auto currentController in  mainControllerPointer->getChildControllers()) {
		controllerRenderList.push_back(currentController);
	}


	//t1 = tidTaker.getElapsedTime();

	//for each (auto currentController in controllerRenderList) {
	for (int currentControllerID = 0; currentControllerID < controllerRenderList.size(); currentControllerID++) {



		//make the sub controller render itself
		if (controllerRenderList[currentControllerID] != nullptr) {
			//tempControllerPointer->render();

			int currentLayer = 0;
			bool staticDone = false;
			bool dynamicDone = false;

			mainWindow->setView(controllerRenderList[currentControllerID]->getView());

		


			auto dynamicRenderList = controllerRenderList[currentControllerID]->getDynamicRenderData();
			//t2 = tidTaker.getElapsedTime();

			//std::cout << "size: " << renderList.size() << " (" << renderList.size()*sizeof(RenderData) << ")\n";

			//REMEBER STATIC OBJECTS ARE ALWAYS IN THE BACKGROUND

			while (!staticDone || !dynamicDone) {

				if (staticRenderList[currentControllerID].size() > currentLayer) {

					auto currentRenderList = staticRenderList[currentControllerID][currentLayer];

					//gameEngine->backgroundListMutex.lock();
					//gameEngine->groundTileListMutex.lock();
					//gameEngine->renderObjectsListMutex.lock();
					//gameEngine->unitListMutex.lock();
					//gameEngine->towerListMutex.lock();
					//gameEngine->towerProjectileMutex.lock();

					for (auto currentRenderObj : currentRenderList) {

						mainWindow->draw(*currentRenderObj);

					}

					//gameEngine->backgroundListMutex.unlock();
					//gameEngine->groundTileListMutex.unlock();
					//gameEngine->renderObjectsListMutex.unlock();
					//gameEngine->unitListMutex.unlock();
					//gameEngine->towerListMutex.unlock();
					//gameEngine->towerProjectileMutex.unlock();

				} else {
					staticDone = true;
				}


				if (dynamicRenderList.size() > currentLayer) {

					auto currentRenderList = dynamicRenderList[currentLayer];

					//gameEngine->backgroundListMutex.lock();
					//gameEngine->groundTileListMutex.lock();
					//gameEngine->renderObjectsListMutex.lock();
					//gameEngine->unitListMutex.lock();
					//gameEngine->towerListMutex.lock();
					//gameEngine->towerProjectileMutex.lock();

					for (auto currentRenderObj : currentRenderList) {
						
						mainWindow->draw(*currentRenderObj);

					}

					//gameEngine->backgroundListMutex.unlock();
					//gameEngine->groundTileListMutex.unlock();
					//gameEngine->renderObjectsListMutex.unlock();
					//gameEngine->unitListMutex.unlock();
					//gameEngine->towerListMutex.unlock();
					//gameEngine->towerProjectileMutex.unlock();

				} else {
					dynamicDone = true;
				}


				currentLayer++;

			}

			//t3 = tidTaker.getElapsedTime();



		}

		

	}

	
	drawDisplay();



	//std::cout << "T1: " << t1.asMilliseconds() << " T2: " << t2.asMilliseconds() << " T3: " << t3.asMilliseconds() << std::endl;

}


sf::RenderWindow * Renderer::getWindow(){

	return mainWindow;

}


void Renderer::drawClear(){

	mainWindow->clear();

}

void Renderer::drawDisplay(){

	mainWindow->display();

}