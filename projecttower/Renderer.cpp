#include "Renderer.h"


Renderer::Renderer(int screenWidth, int screenHeight, float fps, std::string windowName, std::string iconPath, bool fullscreen) {
	bool initError = false;
	this->fps = fps;

	sf::ContextSettings openGLSettings;
	openGLSettings.antialiasingLevel = 1;

	int windowSettings = sf::Style::Resize;
	windowSettings = sf::Style::Default;

	if (fullscreen){

		auto bestRes = sf::VideoMode::getFullscreenModes();

		screenWidth = bestRes[0].width;
		screenHeight = bestRes[0].height;

		windowSettings = windowSettings | sf::Style::Fullscreen;

	}

	mainWindow = new sf::RenderWindow(sf::VideoMode(screenWidth, screenHeight), windowName, windowSettings, openGLSettings);

	sf::Image image;
	if (!image.loadFromFile(iconPath)){
		std::cout << "FATAL iconPath";
		std::cin.get();
		initError = true;
	}

	mainWindow->setIcon(image.getSize().x, image.getSize().y, image.getPixelsPtr());

	/*sf::View view(sf::FloatRect(200, 200, 300, 200));
	view.setRotation(20);
	mainWindow->setView(view);*/


	this->windowName = windowName;
	loaded = initError ? false : true;
}


Renderer::~Renderer()
{
}

void Renderer::handleStaticBackground() {
	SubController * tempControllerPointer = topLevelRenderController;
	//ask top lvl controller to tell render if it has a active sub controller. if so, ask it if it has an sub controller. repeat untill getCurrentRenderController returns itself
	while (tempControllerPointer != tempControllerPointer->getCurrentRenderController()) {
		tempControllerPointer = tempControllerPointer->getCurrentRenderController();
	}
	if (tempControllerPointer != nullptr) {
		//only update of controller has updated the static assets (like changing lvl)
		if (tempControllerPointer->updateStaticRenderData) {

			staticRenderListList = tempControllerPointer->getStaticRenderData();
			tempControllerPointer->updateStaticRenderData = false;

		}
	}
}


void Renderer::doRenderLoop() {

	//sf::Clock tidTaker;
	//sf::Time t1, t2, t3;

	handleStaticBackground();

	drawClear();

	SubController * tempControllerPointer = topLevelRenderController;


	//ask top lvl controller to tell render if it has a active sub controller. if so, ask it if it has an sub controller. repeat untill getCurrentRenderController returns itself
	while (tempControllerPointer != tempControllerPointer->getCurrentRenderController()) {

		tempControllerPointer = tempControllerPointer->getCurrentRenderController();

	}

	//t1 = tidTaker.getElapsedTime();


	//make the sub controller render itself
	if (tempControllerPointer != nullptr) {
		//tempControllerPointer->render();

		auto renderList = tempControllerPointer->getDynamicRenderData();

		//t2 = tidTaker.getElapsedTime();

		//std::cout << "size: " << renderList.size() << " (" << renderList.size()*sizeof(RenderData) << ")\n";

		//RTEMEBER STAIC OBJECTS ARE ALWAYS IN THE BACGROUND
		for (RenderData currentRenderObj : staticRenderListList) {
			if (currentRenderObj.dataType == renderData_Sprite) {
				mainWindow->draw(*currentRenderObj.sprite);
			}
			else if (currentRenderObj.dataType == renderData_Text) {
				mainWindow->draw(*currentRenderObj.text);
			}
		}

		for (RenderData currentRenderObj : renderList) {

			if (currentRenderObj.dataType == renderData_Sprite) {
				mainWindow->draw(*currentRenderObj.sprite);
			}
			else if (currentRenderObj.dataType == renderData_Text) {
				mainWindow->draw(*currentRenderObj.text);
			}
			

		}

		//t3 = tidTaker.getElapsedTime();



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