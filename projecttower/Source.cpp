#include <SFML\Window.hpp>
#include <SFML\Graphics.hpp>
#include <vector>
#include <iostream>

int screenX = 800;
int screenY = 600;

sf::RenderWindow mainWindow(sf::VideoMode(screenX, screenY), "Greger world");

void setSpriteSize(sf::Sprite * sprite, double x, double y){

	sprite->setScale(x / sprite->getLocalBounds().width, y / sprite->getLocalBounds().height);

}

void drawToScreen(sf::Sprite sprite){

	mainWindow.draw(sprite);

}

void drawToScreen(sf::Sprite * sprite){

	mainWindow.draw(*sprite);

}


int main(int argc, char* argv[])
{
	int x, y;

	

	x = 20;
	y = 20;

	x = y = 2;


	

	sf::Texture image;
	if (!image.loadFromFile("tile_1.png"))
	{
		// What do when there is no image?!
	}

	std::vector<sf::Sprite *> sprites;

	for (int i = 0; i < x*y; i++){

		sprites.push_back(new sf::Sprite(image));
		sprites[i]->setScale(1.5f, 1.5f);
		//sprites[i]->setScale(100 / sprites[i].getLocalBounds().width, 100 / sprites[i].getLocalBounds().height);
		setSpriteSize(sprites[i], 100, 100);
		sprites[i]->setPosition(i % x * screenX / x, floor(i / y) * screenY / y);

	}

	while (mainWindow.isOpen()){

		sf::Event mainEvent;
		while (mainWindow.pollEvent(mainEvent)){

			if (mainEvent.type == sf::Event::Closed){

				mainWindow.close();
			}

			if (mainEvent.type == sf::Event::KeyPressed){

				if (mainEvent.key.code == sf::Keyboard::Escape){

					mainWindow.close();

					//sf::Mouse::setPosition(sf::Vector2i(10, 50));
					//sf::Mouse::setPosition(sf::Vector2i(10, 50), mainWindow);

					std::cout << "the escape key was pressed" << std::endl;
					std::cout << "control:" << mainEvent.key.control << std::endl;
					std::cout << "alt:" << mainEvent.key.alt << std::endl;
					std::cout << "shift:" << mainEvent.key.shift << std::endl;
					std::cout << "system:" << mainEvent.key.system << std::endl;

				}

			}

		}
		mainWindow.clear();

		static int step = 0;

		step++;
		step = step % (x*y);

		//printf("%d\n", step);

		for (int j = 0; j < step; j++)
		{
			drawToScreen(sprites[j]);
		}

		sf::CircleShape shape(50);
		shape.setPosition(0, 100);
		shape.setFillColor(sf::Color(100, 250, 50));
		mainWindow.draw(shape);

		/*
		for (int i = 0; i < x*y; i++)
		{
		mainWindow.draw(sprites[i]);
		}
		*/

		mainWindow.display();

	}

	
}