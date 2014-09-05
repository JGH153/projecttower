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

class VortexAnimation
{
public:
	VortexAnimation(int x, int y, int width, int height, float fps, Vortex * gameEngine);
	~VortexAnimation();

	void addFrame(std::string path);
	void assembleAnimation(std::string startPath, std::string filetype, int startNum, int endNum);

	void update(float delta);

	void reset();

	bool playedOneTime;

	void setPos(float x, float y);
	void setSize(int width, int height);
	sf::Vector2f getPos();

private:

	int posX;
	int posY;
	int width;
	int height;

	float fps;
	int currentFrame;

	Vortex * gameEngine;
	
	sf::Time lastRunFrameTime;

	std::vector <VortexSprite> frames;
};

