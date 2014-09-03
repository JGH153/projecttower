#include <SFML\Window.hpp>
#include <SFML\Graphics.hpp>
#include <vector>


int main(int argc, char* argv[])
{
	int x, y;
	int screenX, screenY;

	

	x = 20;
	y = 20;
	screenX = 800;
	screenY = 600;

	sf::RenderWindow mainWindow(sf::VideoMode(screenX, screenY), "Greger world");

	sf::Texture image;
	if (!image.loadFromFile("tile_1.png"))
	{
		// What do when there is no image?!
	}

	std::vector<sf::Sprite> sprites;

	for (int i = 0; i < x*y; i++)
	{
		sprites.push_back(sf::Sprite(image));
		sprites[i].move(i % x * screenX / x, floor(i / y) * screenY / y);
	}

	while (mainWindow.isOpen())
	{
		sf::Event mainEvent;
		while (mainWindow.pollEvent(mainEvent))
		{
			if (mainEvent.type == sf::Event::Closed)
			{
				mainWindow.close();
			}
		}
		mainWindow.clear();

		static int step = 0;

		step++;
		step = step % (x*y);

		printf("%d\n", step);

		for (int j = 0; j < step; j++)
		{
			mainWindow.draw(sprites[j]);
		}


		/*
		for (int i = 0; i < x*y; i++)
		{
		mainWindow.draw(sprites[i]);
		}
		*/

		mainWindow.display();

	}

	
}