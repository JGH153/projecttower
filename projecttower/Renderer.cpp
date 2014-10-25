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


void Renderer::doRenderLoop() {

	drawClear();

	SubController * tempControllerPointer = topLevelRenderController;


	//ask top lvl controller to tell render if it has a active sub controller. if so, ask it if it has an sub controller. repeat untill getCurrentRenderController returns itself
	while (tempControllerPointer != tempControllerPointer->getCurrentRenderController()) {

		tempControllerPointer = tempControllerPointer->getCurrentRenderController();

	}


	//make the sub controller render itself
	if (tempControllerPointer != nullptr) {
		//tempControllerPointer->render();

		std::vector<VortexSprite *> renderList = tempControllerPointer->getRenderSprites();

		for (VortexSprite * currentRenderObj : renderList) {

			//currentRenderObj->update();
			//currentRenderObj->render();
			mainWindow->draw(*currentRenderObj);

		}



	}

	drawDisplay();

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