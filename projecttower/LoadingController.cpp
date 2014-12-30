#include "LoadingController.h"



LoadingController::LoadingController(Vortex * gameEngine, int controllerID) : SubController(gameEngine, controllerID) {
	nextControllerID = controllerID;

	sf::Texture * texBackgroundImage = gameEngine->loadImageToTexture("Graphics/loadingBG.jpg");
	backgroundImage = new VortexSprite(*texBackgroundImage);
	backgroundImage->setPosition(0, 0);
	backgroundImage->setSize(WINDOWSIZEX, WINDOWSIZEY);

	int centerX = gameEngine->getWindowSize().x / 2;
	int centerY = gameEngine->getWindowSize().y / 2;

	int offsetY = 55;


	loadingText = new VortexText("Loading", *gameEngine->getDefaultFont(), 32);
	loadingText->setColor(sf::Color::Black);

	sf::FloatRect textRect = loadingText->getLocalBounds();

	loadingText->setPosition(sf::Vector2f(centerX - (textRect.width / 2), centerY - (textRect.height / 2) - offsetY));

	guiObjects.push_back(loadingText);


	int totalLoading = 0;
	int numLoadingDone = 0;


}


LoadingController::~LoadingController() {
}

void LoadingController::initController() {
	//std::cout << "NOPE IN LoadingController::initController\n";
}

void LoadingController::loadAssets() {
	//std::cout << "NOPE IN LoadingController::loadAssets\n";
}

void LoadingController::onStop() {



}

void LoadingController::onStart() {



}

void LoadingController::update() {


	for (auto *current : guiObjects) {
		current->update();
	}



}


void LoadingController::setTotalToLoad(int total) {

	totalLoading = total;

}
void LoadingController::setOneDone() {

	//std::cout << "New progress is " << numDone << std::endl;

	guiMutex.lock();

	if (numLoadingDone < totalLoading) {
		numLoadingDone++;
	} else {
		std::cout << "Too many loading done in LoadingController::setOneDone" << std::endl;
	}

	std::string newText = "Loading " + std::to_string(numLoadingDone) + "/" + std::to_string(totalLoading);
	loadingText->setString(newText);

	updateStaticRenderData = true;

	guiMutex.unlock();

}

std::vector<std::vector<sf::Drawable *>> LoadingController::getDynamicRenderData() {

	std::vector<std::vector<sf::Drawable *>> renderList;
	std::vector<sf::Drawable *> renderListSub;



	renderList.push_back(renderListSub);
	return renderList;

}
std::vector<std::vector<sf::Drawable *>> LoadingController::getStaticRenderData() {

	std::vector<std::vector<sf::Drawable *>> renderList;

	std::vector<sf::Drawable *> renderListSub;


	//Add static objects to be rendered into the return list
	guiMutex.lock();
	renderListSub.push_back(backgroundImage);

	for (auto currentRenderVector : guiObjects) {
		for (auto currentRenderObj : currentRenderVector->getRenderDrawable()) {
			renderListSub.push_back(currentRenderObj);
		}
	}
	guiMutex.unlock();

	renderList.push_back(renderListSub);

	return renderList;
}

sf::View LoadingController::getView() {
	return sf::View(sf::FloatRect(0, 0, WINDOWSIZEX, WINDOWSIZEY));
}

std::vector<SubController *> LoadingController::getChildControllers() {

	return childControllers;

}