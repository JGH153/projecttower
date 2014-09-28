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



void render() {

	renderer = new Renderer(WINDOWSIZEX, WINDOWSIZEY, 60.f, "Main Window", "Graphics/sfml.png", false);
	std::cout << "Render thread started" << std::endl;
	if (!renderer->loaded) {
		std::cout << "Error initializing renderer" << std::endl;
		std::cin.get();
	}

	std::cout << "Entering render loop" << std::endl;

	renderThreadOnline = true;

	while (gameEngine->running) {
//		std::cout << "THREAD" << std::endl;


		sf::Event mainEvent;
		while (renderer->getWindow()->pollEvent(mainEvent)) {
			gameEngine->pushEvent(mainEvent);

		}
		

		renderer->drawClear();

		//renderer->renderBG();

		

		renderer->renderTiles();
		renderer->renderEntities();
		renderer->renderObjects();
		//renderer->drawGUI();

		renderer->drawDisplay();
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
	

	ProgramController * programController = new ProgramController(gameEngine, renderer);
	
	//Just a class here i hvae contaned all the exaples of how to use Vortex
	//VortexUseExample vortexUseExample(gameEngine);

	int minimumLogicFrameTimeInMilliseconds = 1;


	std::cout << "Starting main loop" << std::endl;
	while (gameEngine->running) {
//		std::cout << "MAIN" << std::endl;

		gameEngine->frameStart();

		//vortexUseExample.update();

		//std::cout << gameEngine->getWindowEvents().size() << std::endl;

		for each (sf::Event currentEvent in gameEngine->getWindowEvents()){
			
		}

		if (gameEngine->eventMouseClicked) {

			sf::Vector2i mouse = gameEngine->getMousePosition();
			auto mousePos = gameEngine->getMapPixelToCoords(mouse);

			std::cout << mousePos.x << " " << mousePos.y << std::endl;


		}
		
		//std::cout << "Updating program controller" << std::endl;
		programController->update();

		gameEngine->frameEnd();

		// If the last frame was shorter than 1 millisecond, sleep for 1 millisecond
		if (gameEngine->getTimeFromFrameStart().asMilliseconds() < minimumLogicFrameTimeInMilliseconds){
			sf::sleep(sf::milliseconds(minimumLogicFrameTimeInMilliseconds));
		}
	}

	//wait for render thred to finish
	while (renderThreadOnline) {

		sf::sleep(sf::milliseconds(10));

	}
	
	renderThread.join();
	return 0;

	
}