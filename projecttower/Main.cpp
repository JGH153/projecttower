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


	//hehe


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

		sprites.push_back(new VortexSprite(texImage));
		sprites[i]->setScale(1.5f, 1.5f);
		//sprites[i]->setScale(100 / sprites[i].getLocalBounds().width, 100 / sprites[i].getLocalBounds().height);
		gameEngine->setSpriteSize(sprites[i], 100, 100);
		sprites[i]->setPosition(i % x * screenX / x, floor(i / y) * screenY / y);

	}


	VortexSprite sprit(texImage);


	VortexButton testButton(400, 400, 150, 55, "Graphics/button.png", "En knapp", gameEngine);
	




	sf::SoundBuffer buffer;
	if (!buffer.loadFromFile("Sound/sound1.wav"))
		return -1;

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
	music.setVolume(50);

	bool windowInFocus = true;

	while (gameEngine->running){

		gameEngine->frameStart();

		sf::Vector2i mouse = gameEngine->getMousePosition();
		
		for each (sf::Event currentEvent in gameEngine->getWindowEvents()){
			
			if (windowInFocus){

				if (currentEvent.type == sf::Event::Closed){

					gameEngine->closeApplication();
				}

				if (currentEvent.type == sf::Event::MouseButtonReleased){

					if (currentEvent.mouseButton.button == sf::Mouse::Left){
						std::cout << "Up" << std::endl;

						if (testButton.hitPoint(gameEngine->getMapPixelToCoords(mouse)))
							std::cout << "KNAPP TREYKKET" << std::endl;

					}

				}

				if (currentEvent.type == sf::Event::MouseMoved){

					//sound.setPosition(sf::Vector3f(mouse.x, 0.f, 0.f));

				}

				if (currentEvent.type == sf::Event::MouseButtonPressed){

					if (currentEvent.mouseButton.button == sf::Mouse::Left){

						std::cout << "Down" << std::endl;
						std::cout << "mouse x: " << currentEvent.mouseButton.x << std::endl;
						std::cout << "mouse y: " << currentEvent.mouseButton.y << std::endl;

					}
				}

			}else{

				std::cout << "No Focus" << std::endl;

			}

			if (currentEvent.type == sf::Event::LostFocus){
				//myGame.pause();
				windowInFocus = false;
			}

			if (currentEvent.type == sf::Event::GainedFocus){
				//myGame.resume();
				windowInFocus = true;
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
		
		//std::cout << mouse.x << " " << mouse.y << std::endl;
		//particles.setEmitter(window.mapPixelToCoords(mouse));
		particles.setEmitter(gameEngine->getMapPixelToCoords(mouse));

		

		// update it
		sf::Time elapsed = clock.restart();
		particles.update(elapsed);

		//testAnimation->update(0);

		gameEngine->getWindow()->draw(text);

		testButton.update(0);

		gameEngine->getWindow()->draw(particles);

		gameEngine->getWindow()->draw(sprit);
		

		/*
		for (int i = 0; i < x*y; i++)
		{
		mainWindow.draw(sprites[i]);
		}
		*/

		gameEngine->frameEnd();

	}

	
}