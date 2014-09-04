#pragma once

#include <SFML\Window.hpp>
#include <SFML\Graphics.hpp>
#include <vector>
#include <iostream>

#include "Vortex.h"

int screenX = 800;
int screenY = 600;


int main(int argc, char* argv[]){

	Vortex * gameEngine = new Vortex();
	gameEngine->initVortex(800, 600, "Main Window");
	gameEngine->loadImageToSprite("Graphics/tile_1.png");
	sf::Texture texImage = gameEngine->loadImageToTexture("Graphics/tile_1.png");





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

		/*
		for (int i = 0; i < x*y; i++)
		{
		mainWindow.draw(sprites[i]);
		}
		*/

		gameEngine->drawDisplay();



















		//sf::Event mainEvent;
		//while (mainWindow.pollEvent(mainEvent)){

		//	if (mainEvent.type == sf::Event::Closed){

		//		mainWindow.close();
		//	}

		//	if (mainEvent.type == sf::Event::KeyPressed){

		//		if (mainEvent.key.code == sf::Keyboard::Escape){

		//			mainWindow.close();

		//			//sf::Mouse::setPosition(sf::Vector2i(10, 50));
		//			//sf::Mouse::setPosition(sf::Vector2i(10, 50), mainWindow);

		//			std::cout << "the escape key was pressed" << std::endl;
		//			std::cout << "control:" << mainEvent.key.control << std::endl;
		//			std::cout << "alt:" << mainEvent.key.alt << std::endl;
		//			std::cout << "shift:" << mainEvent.key.shift << std::endl;
		//			std::cout << "system:" << mainEvent.key.system << std::endl;

		//		}

		//	}

		//}
		//mainWindow.clear();

		//static int step = 0;

		//step++;
		//step = step % (x*y);

		////printf("%d\n", step);

		//for (int j = 0; j < step; j++)
		//{
		//	drawToScreen(sprites[j]);
		//}

		//sf::CircleShape shape(50);
		//shape.setPosition(0, 100);
		//shape.setFillColor(sf::Color(100, 250, 50));
		//mainWindow.draw(shape);

		///*
		//for (int i = 0; i < x*y; i++)
		//{
		//mainWindow.draw(sprites[i]);
		//}
		//*/

		//mainWindow.display();

	}

	
}