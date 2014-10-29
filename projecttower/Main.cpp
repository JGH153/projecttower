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


int main(int argc, char* argv[]){

	std::cout << "Creating new vortex and Renderer" << std::endl;

	Vortex * gameEngine = new Vortex();
	Renderer * renderer = new Renderer(gameEngine, WINDOWSIZEX, WINDOWSIZEY, 60.f, "Gregers Spill", "Graphics/sfml.png", false);

	std::cout << "Starting render thread" << std::endl;
	//starting new thread caling renderer->renderMainLoop();
	std::thread renderThread(&Renderer::renderMainLoop, renderer);

	//wait for render thread to start
	while (!renderer->renderThreadOnline) {

		sf::sleep(sf::milliseconds(10));

	}

	std::cout << "Initing vortex" << std::endl;
	gameEngine->initVortex(renderer->getWindow(), "Fonts/arial.ttf");
	
	//Seting up controllers (an loading all the data like sprites and textures into memory)
	ProgramController * programController = new ProgramController(gameEngine, -1);
	renderer->topLevelRenderController = programController;
	
	//Just a class here i hvae contaned all the exaples of how to use Vortex
	//VortexUseExample vortexUseExample(gameEngine);

	float minimumLogicFrameTimeInMilliseconds = 1000.f / (MAXFPS / 2); //30 fps
	

	sf::Clock oneSecTimeClock;
	int oneSecTime = 0;
	int numFramesSek = 0;



	std::cout << "Starting main loop" << std::endl;
	while (gameEngine->running) {

		gameEngine->frameStart();

		for each (sf::Event currentEvent in gameEngine->getWindowEvents()){
			
		}

		programController->update();

		gameEngine->frameEnd();

		oneSecTime += oneSecTimeClock.restart().asMilliseconds();
		numFramesSek++;
		//one sec, only preformed once each sec
		if (oneSecTime > 1000) {
			oneSecTime = 0;
			std::cout << "Num logic pr sek: " << numFramesSek << std::endl;
			numFramesSek = 0;
		}

		// SLEEEP 
		if (gameEngine->getTimeFromFrameStart().asMilliseconds() < minimumLogicFrameTimeInMilliseconds){
			sf::sleep(sf::milliseconds(minimumLogicFrameTimeInMilliseconds - gameEngine->getTimeFromFrameStart().asMilliseconds()));
		}



	}

	//wait for render thread to finish
	while (renderer->renderThreadOnline) {

		sf::sleep(sf::milliseconds(10));

	}
	
	renderThread.join();
	return 0;

	
}