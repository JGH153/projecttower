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

#include "GlobalDefines.h"

class VortexAnimation : public RenderObject
{
public:
	VortexAnimation(float x, float y, int width, int height, float fps, Vortex * gameEngine);
	~VortexAnimation();

	void VortexAnimation::addFrame(sf::Texture * tex);
	void addFrame(std::string path);
	void assembleAnimation(std::string startPath, std::string filetype, int startNum, int endNum);
	void asembleSpritesheetAnimation(std::string path, int orgWidth, int orgHeight, sf::Vector2i moveDirection, int numFrmes);

	void update();
	std::vector<RenderData> getRenderData();

	void reset();

	bool playedOneTime;

	void setPos(float x, float y);
	void setSize(int width, int height);
	sf::Vector2f getPos();

	VortexSprite *  getDrawData();

private:

	float posX;
	float posY;
	int width;
	int height;

	float fps;
	int currentFrame;

	Vortex * gameEngine;
	
	sf::Time lastRunFrameTime;

	std::vector <VortexSprite> frames;
};

