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
	bool usingPower;
	int powerID;

	//std::vector<RenderObject *> getRenderObjectList();

	bool mouseOverSomeButton(sf::View resetToView);

	void initController();
	void loadAssets();

	void setPlayerResources(int newValue);
	void setPlayerIncome(int newValue);
	void setTimer(int newValue);
	void setPlayerLives(int newValue);
	int getPlayerResources();
	
	int bottomToolbarPosY;
	std::vector<int> unitsToSpawn;
	int numLives;
	void showTowerUpgrades(sf::Vector2i towerPosition);
	void hideTowerUpgrades();
	bool showingTowerUpgrades;
	void setCurrentLevel(int newLevel);
	void setNextLevelTime(int newValue);

	VortexButtonRectangle * upgradeToCannon;
	VortexButtonRectangle * upgradeToFreeze;
	int playerResources;
	int buildTimer;
	int currentLevel;

	bool playerWon;

	void addPlayersSideTexts();

private:
	std::mutex guiMutex;
	std::vector<RenderObject *> guiObjects;
	VortexButtonRectangle * buildButton;
	VortexButtonRectangle * deleteTowerButton;
	VortexButtonRectangle * sendUnit1Button;
	VortexButtonRectangle * sendUnit2Button;
	VortexButtonRectangle * sendUnit3Button;
	VortexButtonRectangle * sendUnit4Button;
	VortexButtonRectangle * sendUnit5Button;
	VortexButtonRectangle * sendUnit6Button;
	VortexButtonRectangle * sendUnit7Button;
	VortexButtonRectangle * sendUnit8Button;
	VortexButtonRectangle * sendUnit9Button;
	VortexButtonRectangle * sendUnit10Button;
	VortexButtonRectangle * sendUnit11Button;
	VortexButtonRectangle * sendUnit12Button;
	
	VortexText* resourceText;
	VortexText* incomeText;
	VortexText* timeText;
	VortexText* livesText;
	VortexText* lossText;
	VortexText* winText;
	VortexText* levelText;
	VortexText* levelTimerText;

	


	VortexButtonRectangle * powerButtonBomb;



	sf::RectangleShape* resourcePanel;
	sf::RectangleShape* levelPanel;
	sf::RectangleShape* buttonPanel;
	std::vector<VortexButtonRectangle*> buttons;
	std::vector<VortexButtonRectangle*> buttonsPowers;

	int playerIncome;
	
	int msSinceLastIncome;
	int msToNextLevel;
	bool playerLost;
	bool addedLoserText;
	bool addedWinText;

	void sendPlayerLossPacket() ;
	void doUpdatePowerButtons();
	
	
	
};

