#pragma once


#include <SFML\Window.hpp>
#include <SFML\Graphics.hpp>
#include <SFML\Audio.hpp>
#include <vector>
#include <iostream>

#include "Vortex.h"
#include "SubController.h"
#include "VortexButtonRectangle.h"
#include "VortexConvexButton.h"

class GameGuiController : public SubController{
public:
	GameGuiController(Vortex * gameEngine, int controllerID);
	~GameGuiController();

	void update();
	std::vector<std::vector<sf::Drawable *>> getDynamicRenderData();
	std::vector<std::vector<sf::Drawable *>> getStaticRenderData();
	sf::View getView();
	std::vector<SubController *> getChildControllers();

	bool building;
	bool deleting;

	//std::vector<RenderObject *> getRenderObjectList();

	bool mouseOverSomeButton(sf::View resetToView);

	void preloadAssets();
	void setPlayerResources(int newValue);
	void setPlayerIncome(int newValue);
	void setTimer(int newValue);
	int getPlayerResources();
	
	int bottomToolbarPosY;
	std::vector<int> unitsToSpawn;

private:
	std::mutex guiMutex;
	std::vector<RenderObject *> guiObjects;
	VortexButtonRectangle * buildButton;
	VortexButtonRectangle * deleteTowerButton;
	VortexButtonRectangle * sendUnit1Button;
	VortexButtonRectangle * sendUnit2Button;
	VortexText* resourceText;
	VortexText* incomeText;
	VortexText* timeText;
	sf::RectangleShape* resourcePanel;
	std::vector<VortexButtonRectangle*> buttons;

	int playerIncome;
	int playerResources;
	int msSinceLastIncome;
};

