#pragma once

#include <SFML\Window.hpp>
#include <SFML\Graphics.hpp>
#include <SFML\Audio.hpp>
#include <vector>
#include <iostream>

#include "VortexSprite.h"

//#define uint unsigned int
typedef unsigned int uint;


struct texElement{

	texElement(std::string path, sf::Texture * texture) : path(path), texture(texture){}

	std::string path;
	sf::Texture * texture;
};

struct soundElement{

	soundElement(std::string path, sf::SoundBuffer * sound) : path(path), sound(sound){}

	std::string path;
	sf::SoundBuffer * sound;

};

struct FontElement{

	FontElement(std::string path, sf::Font * font) : path(path), font(font){}

	std::string path;
	sf::Font * font;
};

//The game engine, uning SFML
class Vortex {
public:
	Vortex();
	~Vortex();

	void initVortex(int screenWidth, int screenHeight, std::string windowName, std::string iconPath, std::string defaultFontPath, bool fullscreen);

	sf::RenderWindow * getWindow();

	void drawClear();
	void drawDisplay();

	void frameStart();
	void frameEnd();

	VortexSprite loadImageToSprite(std::string path);
	sf::Texture * loadImageToTexture(std::string path);
	sf::SoundBuffer * loadSound(std::string path);
	sf::Music * openMusic(std::string path);
	sf::Font * loadFont(std::string path);

	sf::Texture checkForBackupImage(std::string path);

	sf::Vector2i getMousePosition();
	sf::Vector2f getMapPixelToCoords(sf::Vector2i point);

	

	sf::Font * getDefaultFont();

	sf::Time getTimeFromProgramStart();
	sf::Time getTimeFromFrameStart();
	

	void regEvents();
	std::vector<sf::Event> getWindowEvents();

	void closeApplication();
	

	bool running;

	bool eventKeyPressed= false;
	bool eventKeyReleased = false;

	bool eventMouseMove = false;

	bool eventMouseClicked = false;
	bool eventMouseReleased = false;

	bool eventMouseClickedLeft = false;
	bool eventMouseClickedRight = false;

	bool eventMouseReleasedLeft = false;
	bool eventMouseReleasedRight = false;

	bool windowInFocus = true;

	static void setSpriteSize(sf::Sprite * sprite, double w, double h);

	sf::Vector2i getWindowSize();

	sf::Clock totalTime;
	sf::Clock frameTime;

private:

	sf::Texture * checkForCopyOfTex(std::string path);
	sf::SoundBuffer * checkForCopyOfSound(std::string path);
	sf::Font * checkForCopyOfFont(std::string path);

	std::vector<sf::Event> eventList;

	std::vector<texElement *> textures;
	std::vector<soundElement *> sounds;
	std::vector<FontElement *> fonts;

	std::string windowName;
	sf::RenderWindow * mainWindow;

	sf::Font * defaultFont;


	

	

};

