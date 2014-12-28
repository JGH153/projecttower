#pragma once

#include <SFML\Window.hpp>
#include <SFML\Graphics.hpp>
#include <vector>
#include <iostream>
#include <string>
#include <sstream>

#include "VortexLoader.h"
#include "Vortex.h"
#include "VortexSprite.h"
#include "RemovableObject.h"

#include "GlobalDefines.h"

class VortexAnimation : public RenderObject, public RemovableObject
{
public:
	VortexAnimation(float x, float y, int width, int height, float fps, Vortex * gameEngine);
	~VortexAnimation();

	void addFrame(sf::Texture * tex);
	void addFrame(std::string path);
	void addFrame(VortexSprite* sprite);

	void assembleAnimation(std::string startPath, std::string filetype, int startNum, int endNum);
	void asembleSpritesheetAnimation(std::string path, int orgWidth, int orgHeight, sf::Vector2i moveDirection, int numFrames);
	void asembleSpritesheetAnimation(std::string path, int offsetX, int offsetY, int orgWidth, int orgHeight, int numFrmesX, int numFrmesY, sf::Color appendColor = sf::Color(255, 255, 255, 200));
	

	void update();
	std::vector<sf::Drawable *> getRenderDrawable();

	void reset();

	bool playedOneTime;

	void setPos(float x, float y);
	void setSize(int width, int height);
	sf::Vector2f getPos();

	VortexSprite *  getDrawData();
	

	void killYourself();
	int currentFrame;
	std::vector <VortexSprite> frames;

private:

	float posX;
	float posY;
	int width;
	int height;

	float fps;
	sf::Time fpsMS;
	

	Vortex * gameEngine;


	sf::Clock animationUpdateClock;
	sf::Time accumulatedTime;

	
};

