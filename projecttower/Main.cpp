#pragma once

#include <SFML\Window.hpp>
#include <SFML\Graphics.hpp>
#include <SFML\Audio.hpp>
#include <vector>
#include <iostream>

#include "Vortex.h"
#include "VortexLoader.h"
#include "VortexParticleSystem.h"
#include "VortexAnimation.h"
#include "VortexSprite.h"
#include "VortexButton.h"

#include "ProgramController.h"

#include "VortexUseExample.h"

int main(int argc, char* argv[]){

	/*
	Add list:
	VortexButton - Hover
	VortexButton - No image/hover or no text

	Tower and unit as base classes 

	NB! 
	All new classes that will do ANY rendering needs to take the game engine as constructor parameter and hava a update function


	*/

	Vortex * gameEngine = new Vortex();
	gameEngine->initVortex(1000, 600, 60.f, "Main Window", "Graphics/sfml.png", "Fonts/arial.ttf", false);

	ProgramController * programController = new ProgramController(gameEngine);

	//Just a class here i hvae contaned all the exaples of how to use Vortex
	VortexUseExample vortexUseExample(gameEngine);


	while (gameEngine->running){

		gameEngine->frameStart();

		//vortexUseExample.update();

		for each (sf::Event currentEvent in gameEngine->getWindowEvents()){

		}

		programController->update();

		gameEngine->frameEnd();

	}

	
}