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

int screenX = 800;
int screenY = 600;


int main(int argc, char* argv[]){

	/*

	Add list:
	Vortex events for keyboard
	VortexButton - Hover


	*/

	Vortex * gameEngine = new Vortex();
	gameEngine->initVortex(800, 600, "Main Window", "Graphics/sfml.png", "Fonts/arial.ttf");
	gameEngine->loadImageToSprite("Graphics/tile_1.png");
	sf::Texture * texImage = gameEngine->loadImageToTexture("Graphics/tile_1.png");

	ProgramController * programController = new ProgramController(gameEngine);

	// create the particle system
	VortexParticleSystem particles(50000);

	// create a clock to track the elapsed time
	sf::Clock clock;


	//hehe


	sf::Font font = *gameEngine->loadFont("Fonts/arial.ttf");

	sf::Text text;

	// select the font
	text.setFont(font); // font is a sf::Font

	text.setPosition(150, 150);

	// set the string to display
	text.setString("Hello world");

	// set the character size
	text.setCharacterSize(28); // in pixels, not points!

	// set the color
	text.setColor(sf::Color::Red);

	// set the text style
	text.setStyle(sf::Text::Bold | sf::Text::Underlined);



	gameEngine->drawClear();
	VortexAnimation * testAnimation = new VortexAnimation(300, 300, 112, 170, 24, gameEngine);
	testAnimation->assembleAnimation("Graphics/testAnimation/Boss8_black_hole2_", ".png", 1, 53);
	gameEngine->drawDisplay();

	///std::cin.get();


	std::vector<VortexAnimation *> animations;
	
	int x, y;

	x = 0;
	y = 0;

	int width = 112;
	int height = 170;
	int border = 10;
	
	for (uint i = 0; i < 30; i++){

		VortexAnimation * temp = new VortexAnimation(x, y, width, height, 25, gameEngine);
		temp->assembleAnimation("Graphics/testAnimation/Boss8_black_hole2_", ".png", 1, 53);
		animations.push_back(temp);

		x += width + border;
		if (x > gameEngine->getWindow()->getSize().x + width){
			x = 0;
			y += height + border;
		}



	}


	

	x = 20;
	y = 20;

	x = y = 2;

	std::vector<VortexSprite *> sprites;

	for (int i = 0; i < x*y; i++){

		sprites.push_back(new VortexSprite(*texImage));
		sprites[i]->setScale(1.5f, 1.5f);
		//sprites[i]->setScale(100 / sprites[i].getLocalBounds().width, 100 / sprites[i].getLocalBounds().height);
		gameEngine->setSpriteSize(sprites[i], 100, 100);
		sprites[i]->setPosition(i % x * screenX / x, floor(i / y) * screenY / y);

	}


	VortexSprite sprit(*texImage);


	VortexButton testButton(400, 400, 150, 55, "Graphics/button.png", "En knapp", gameEngine);
	




	sf::SoundBuffer buffer = *gameEngine->loadSound("Sound/sound1.wav");
	sf::Sound sound;
	//sound.setPosition(sf::Vector3f(0.f, 0.f, 0.f));
	sound.setBuffer(buffer);
	//sound.setLoop(true);
	sound.play();

	sf::Music music;
	if (!music.openFromFile("Sound/gameMusic.wav"))
		return -1; // error
	music.play();

	music.setPitch(1.5);
	music.setVolume(100);

	while (gameEngine->running){

		gameEngine->frameStart();

		programController->update();

		sf::Vector2i mouse = gameEngine->getMousePosition();

		if (testButton.buttonCliced()){
			std::cout << "KNAPP TREYKKET" << std::endl;
			testButton.setPosition(rand() % gameEngine->getWindowSize().x, rand() % gameEngine->getWindowSize().y);
		}
		
		
		for each (sf::Event currentEvent in gameEngine->getWindowEvents()){
			
			

			if (currentEvent.type == sf::Event::Closed){

				gameEngine->closeApplication();

			}

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)){

				gameEngine->closeApplication();

			}

			
		}


		for (uint i = 0; i < animations.size(); i++){
			animations[i]->update(0);
		}

		particles.setEmitter(gameEngine->getMapPixelToCoords(mouse));

		// update it
		sf::Time elapsed = clock.restart();
		particles.update(elapsed);

		gameEngine->getWindow()->draw(text);

		testButton.update(0);

		gameEngine->getWindow()->draw(particles);

		gameEngine->getWindow()->draw(sprit);


		gameEngine->frameEnd();

	}

	
}