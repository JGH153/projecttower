#pragma once

#include <SFML\Window.hpp>
#include <SFML\Graphics.hpp>
#include <vector>
#include <iostream>

#include "Vortex.h"
#include "VortexLoader.h"
#include "VortexParticleSystem.h"
#include "VortexAnimation.h"

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



	gameEngine->drawClear();
	VortexAnimation * testAnimation = new VortexAnimation(300, 300, 112, 170, 24, gameEngine);
	//testAnimation->addFrame("Graphics/tile_1.png", gameEngine->getWindow());
	//testAnimation->addFrame("Graphics/testAnimation/Boss8_black_hole2_1.png");
	//testAnimation->addFrame("Graphics/testAnimation/Boss8_black_hole2_2.png");
	//testAnimation->addFrame("Graphics/testAnimation/Boss8_black_hole2_3.png");
	//testAnimation->addFrame("Graphics/testAnimation/Boss8_black_hole2_4.png");
	//testAnimation->addFrame("Graphics/testAnimation/Boss8_black_hole2_5.png");
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
	
	for (int i = 0; i < 30; i++){

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

	std::vector<sf::Sprite *> sprites;

	for (int i = 0; i < x*y; i++){

		sprites.push_back(new sf::Sprite(texImage));
		sprites[i]->setScale(1.5f, 1.5f);
		//sprites[i]->setScale(100 / sprites[i].getLocalBounds().width, 100 / sprites[i].getLocalBounds().height);
		gameEngine->setSpriteSize(sprites[i], 100, 100);
		sprites[i]->setPosition(i % x * screenX / x, floor(i / y) * screenY / y);

	}

	while (gameEngine->running){

		gameEngine->frameStart();

		
		for each (sf::Event currentEvent in gameEngine->getWindowEvents()){

			if (currentEvent.type == sf::Event::Closed){

				gameEngine->closeApplication();
			}

		}


		//static int step = 0;

		//step++;
		//step = step % (x*y);

		////printf("%d\n", step);

		//for (int j = 0; j < step; j++){

		//	gameEngine->getWindow()->draw(*sprites[j]);

		//}

		//sf::CircleShape shape(50);
		//shape.setPosition(0, 100);
		//shape.setFillColor(sf::Color(100, 250, 50));
		//gameEngine->getWindow()->draw(shape);


		for (int i = 0; i < animations.size(); i++){
			animations[i]->update(0);
		}




		// make the particle system emitter follow the mouse
		sf::Vector2i mouse = gameEngine->getMousePosition();
		//std::cout << mouse.x << " " << mouse.y << std::endl;
		//particles.setEmitter(window.mapPixelToCoords(mouse));
		particles.setEmitter(gameEngine->getMapPixelToCoords(mouse));

		// update it
		sf::Time elapsed = clock.restart();
		particles.update(elapsed);

		//testAnimation->update(0);

		gameEngine->getWindow()->draw(text);

		gameEngine->getWindow()->draw(particles);

		/*
		for (int i = 0; i < x*y; i++)
		{
		mainWindow.draw(sprites[i]);
		}
		*/

		gameEngine->frameEnd();

	}

	
}