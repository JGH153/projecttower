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

Renderer * renderer;
bool runmuthafucka = true;

void render() {
	renderer = new Renderer(WINDOWSIZEX, WINDOWSIZEY, 60.f, "Main Window", "Graphics/sfml.png", false);
	std::cout << "Render thread started" << std::endl;
	if (!renderer->loaded) {
		std::cout << "Error initializing renderer" << std::endl;
		std::cin.get();
	}

	std::cout << "Entering render loop" << std::endl;
	while (runmuthafucka) {
		std::cout << "THREAD" << std::endl;
		renderer->drawClear();

		//renderer->renderBG();
		renderer->renderTiles();
		renderer->renderEntities();
		//renderer->drawGUI();

		renderer->drawDisplay();
	}
}

int main(int argc, char* argv[]){

	/*
	Add list:
	VortexButton - Hover
	VortexButton - No image/hover or no text

	Tower and unit as base classes 

	NB! 
	All new classes that will do ANY rendering needs to take the game engine as constructor parameter and hava a update function


	*/

	std::cout << "Starting render thread" << std::endl;
	std::thread renderThread(render);

	std::cout << "Creating new vortex" << std::endl;
	Vortex * gameEngine = new Vortex();
	

	//Let the thread init the renderer before initing vortex
	sf::sleep(sf::milliseconds(1000));
	std::cout << "Initing vortex" << std::endl;

	gameEngine->initVortex(renderer->getWindow(), "Fonts/arial.ttf");
	

	ProgramController * programController = new ProgramController(gameEngine, renderer);
	
	//Just a class here i hvae contaned all the exaples of how to use Vortex
	//VortexUseExample vortexUseExample(gameEngine);

	std::cout << "Starting main loop" << std::endl;
	while (gameEngine->running){
		std::cout << "MAIN" << std::endl;

		gameEngine->frameStart();

		//vortexUseExample.update();

		for each (sf::Event currentEvent in gameEngine->getWindowEvents()){

		}
		
		//std::cout << "Updating program controller" << std::endl;
		programController->update();

		gameEngine->frameEnd();

	}

	
}