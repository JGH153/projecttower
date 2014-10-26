#pragma once

#include <SFML\Window.hpp>
#include <SFML\Graphics.hpp>
#include <SFML\Audio.hpp>
#include <vector>
#include <iostream>
#include <thread>

#include "Vortex.h"
#include "VortexLoader.h"
#include "VortexParticleSystem.h"
#include "VortexAnimation.h"
#include "VortexSprite.h"
#include "VortexButton.h"
#include "Renderer.h"
#include "GlobalDefines.h"

#include "ProgramController.h"

#include "VortexUseExample.h"

#include "RenderObject.h"

Renderer * renderer;
bool renderThreadOnline = false;
Vortex * gameEngine;

ProgramController * programController = nullptr;


void render() {

	renderer = new Renderer(WINDOWSIZEX, WINDOWSIZEY, 60.f, "Main Window", "Graphics/sfml.png", false);
	std::cout << "Render thread started" << std::endl;
	if (!renderer->loaded) {
		std::cout << "Error initializing renderer" << std::endl;
		std::cin.get();
	}

	std::cout << "Entering render loop" << std::endl;

	renderThreadOnline = true;

	float rotation = 360.f;

	while (programController == nullptr) {

		sf::sleep(sf::milliseconds(10));

	}

	renderer->topLevelRenderController = programController;

	float msToWait = 1000.f / MAXFPS;
	float lastRenderFrameTime = 0;
	sf::Clock renderFrameTime;


	sf::Clock oneSecTimeClock;
	int oneSecTime = 0;
	int numFramesSek = 0;

	renderer->initStaticBackground();
	while (gameEngine->running) {
//		std::cout << "THREAD" << std::endl;


		sf::Event mainEvent;
		while (renderer->getWindow()->pollEvent(mainEvent)) {
			gameEngine->pushEvent(mainEvent);

		}

		renderer->doRenderLoop();

		int frameTime = renderFrameTime.restart().asMilliseconds();

		oneSecTime += oneSecTimeClock.restart().asMilliseconds();
		numFramesSek++;
		//one sec

		if (oneSecTime > 1000) {
			oneSecTime = 0;
			std::cout << "FPS: " << numFramesSek << std::endl;
			numFramesSek = 0;
		}

		if (frameTime < msToWait) {
			sf::sleep(sf::milliseconds(msToWait - frameTime));
			renderFrameTime.restart();
		}
		



	}

	renderThreadOnline = false;

}

int main(int argc, char* argv[]){

	std::cout << "Creating new vortex" << std::endl;
	gameEngine = new Vortex();

	std::cout << "Starting render thread" << std::endl;
	std::thread renderThread(render);

	

	//wait for render thred to start
	while (!renderThreadOnline) {

		sf::sleep(sf::milliseconds(10));

	}

	std::cout << "Initing vortex" << std::endl;

	gameEngine->initVortex(renderer->getWindow(), "Fonts/arial.ttf");
	

	programController = new ProgramController(gameEngine);
	
	//Just a class here i hvae contaned all the exaples of how to use Vortex
	//VortexUseExample vortexUseExample(gameEngine);

	float minimumLogicFrameTimeInMilliseconds = 1000.f / MAXFPS; //30 fps
	

	sf::Clock oneSecTimeClock;
	int oneSecTime = 0;
	int numFramesSek = 0;



	std::cout << "Starting main loop" << std::endl;
	while (gameEngine->running) {
//		std::cout << "MAIN" << std::endl;



		gameEngine->frameStart();

		//vortexUseExample.update();

		//std::cout << gameEngine->getWindowEvents().size() << std::endl;

		for each (sf::Event currentEvent in gameEngine->getWindowEvents()){
			
		}

	/*	if (gameEngine->eventMouseClicked) {

			sf::Vector2i mouse = gameEngine->getMousePosition();
			auto mousePos = gameEngine->getMapPixelToCoords(mouse);

			std::cout << mousePos.x << " " << mousePos.y << std::endl;


		}*/
		
		//std::cout << "Updating program controller" << std::endl;
		programController->update();

		gameEngine->frameEnd();

		oneSecTime += oneSecTimeClock.restart().asMilliseconds();
		numFramesSek++;
		//one sec
		if (oneSecTime > 1000) {
			oneSecTime = 0;
			//std::cout << "Num logic pr sek: " << numFramesSek << std::endl;
			numFramesSek = 0;
		}

		// SLEEEP 
		if (gameEngine->getTimeFromFrameStart().asMilliseconds() < minimumLogicFrameTimeInMilliseconds){
			sf::sleep(sf::milliseconds(minimumLogicFrameTimeInMilliseconds - gameEngine->getTimeFromFrameStart().asMilliseconds()));
		}



	}

	//wait for render thread to finish
	while (renderThreadOnline) {

		sf::sleep(sf::milliseconds(10));

	}
	
	renderThread.join();
	return 0;

	
}