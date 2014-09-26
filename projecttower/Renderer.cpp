#include "Renderer.h"


Renderer::Renderer(int screenWidth, int screenHeight, float fps, std::string windowName, std::string iconPath, bool fullscreen) {
	bool initError = false;
	this->fps = fps;

	sf::ContextSettings openGLSettings;
	openGLSettings.antialiasingLevel = 8;

	int windowSettings = sf::Style::Resize;
	windowSettings = sf::Style::None;

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



	this->windowName = windowName;
	loaded = initError ? false : true;
}


Renderer::~Renderer()
{
}

void Renderer::renderBG(){
	for (int x = 0; x < (WINDOWSIZEX / (int)bgSprite.getSize().x) + (int)bgSprite.getSize().x; x++){
		for (int y = 0; y < (WINDOWSIZEY / (int)bgSprite.getSize().y) + (int)bgSprite.getSize().y; y++){
			bgSprite.setPosition(x * (int)bgSprite.getSize().x, y * (int)bgSprite.getSize().y);
			getWindow()->draw(bgSprite);
		}
	}
}

void Renderer::renderTiles(){
	if (mapTiles.empty()) {
		return;
	}
	for (uint i = 0; i < mapTiles.size(); i++){

		getWindow()->draw(mapTiles[i]);

	}

}

struct sortinStructDistance{

	bool operator() (Unit * a, Unit * b) {

		return (a->posY + a->height < b->posY + b->height);

	}

} sortingInstanceDistance;

void Renderer::renderEntities() {
	//sorting units so the unit with the lowest base y is renderd first
	//std::sort(unitList.begin(), unitList.end(), sortingInstanceDistance);
	for (Unit * current : unitList) {
		current->render();
	}
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