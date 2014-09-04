#pragma once

#include <SFML\Window.hpp>
#include <SFML\Graphics.hpp>
#include <vector>
#include <iostream>

#include "Vortex.h"
#include "VortexParticleSystem.h"

int screenX = 800;
int screenY = 600;



















int main(int argc, char* argv[]){







	































	Vortex * gameEngine = new Vortex();
	gameEngine->initVortex(800, 600, "Main Window", "Graphics/sfml.png", "Fonts/arial.ttf");
	gameEngine->loadImageToSprite("Graphics/tile_1.png");
	sf::Texture texImage = gameEngine->loadImageToTexture("Graphics/tile_1.png");

	// create the particle system
	VortexParticleSystem particles(10000);

	// create a clock to track the elapsed time
	sf::Clock clock;





	sf::Font font = gameEngine->loadFont("Fonts/arial.ttf");

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







	int x, y;

	x = 20;
	y = 20;

	x = y = 2;

	std::vector<sf::Sprite *> sprites;

	for (int i = 0; i < x*y; i++){

		sprites.push_back(new sf::Sprite(texImage));
		sprites[i]->setScale(1.5f, 1.5f);
		//sprites[i]->setScale(100 / sprites[i].getLocalBounds().width, 100 / sprites[i].getLocalBounds().height);
		gameEngine->setSpriteSize(sprites[i], 100, 100);
		sprites[i]->setPosition(i % x * screenX / x, floor(i / y) * screenY / y);

	}

	while (gameEngine->running){

		gameEngine->regEvents();
		for each (sf::Event currentEvent in gameEngine->getWindowEvents()){

			if (currentEvent.type == sf::Event::Closed){

				gameEngine->closeApplication();
			}

		}


		gameEngine->drawClear();

		static int step = 0;

		step++;
		step = step % (x*y);

		//printf("%d\n", step);

		for (int j = 0; j < step; j++){

			gameEngine->drawToScreen(sprites[j]);

		}

		sf::CircleShape shape(50);
		shape.setPosition(0, 100);
		shape.setFillColor(sf::Color(100, 250, 50));
		gameEngine->drawToScreen(shape);






		// make the particle system emitter follow the mouse
		sf::Vector2i mouse = gameEngine->getMousePosition();
		//std::cout << mouse.x << " " << mouse.y << std::endl;
		//particles.setEmitter(window.mapPixelToCoords(mouse));
		particles.setEmitter(gameEngine->getMapPixelToCoords(mouse));

		// update it
		sf::Time elapsed = clock.restart();
		particles.update(elapsed);

		

		gameEngine->drawToScreen(text);

		gameEngine->drawToScreen(particles);

		/*
		for (int i = 0; i < x*y; i++)
		{
		mainWindow.draw(sprites[i]);
		}
		*/

		gameEngine->drawDisplay();

	}

	
}