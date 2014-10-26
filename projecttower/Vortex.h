#pragma once

#include <SFML\Window.hpp>
#include <SFML\Graphics.hpp>
#include <SFML\Audio.hpp>
#include <vector>
#include <iostream>

#include <thread>         // std::thread
#include <mutex> // std::mutex

#include "VortexSprite.h"
#include "GlobalDefines.h"

//#define uint unsigned int
typedef unsigned int uint;


struct texElement{

	//if rec = 0,0,0,0 then you use orginale size

	texElement(std::string path, sf::Texture * texture, sf::IntRect rec) : path(path), texture(texture), rec(rec){}

	std::string path;
	sf::Texture * texture;
	sf::IntRect rec;
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

	void initVortex(sf::RenderWindow * mainWindow, std::string defaultFontPath);


	void frameStart();
	void frameEnd();

	VortexSprite loadImageToSprite(std::string path);
	sf::Texture * loadImageToTexture(std::string path);

	sf::Texture * loadImageSubsetToTexture(std::string path, sf::IntRect rec);

	sf::SoundBuffer * loadSound(std::string path);
	sf::Music * openMusic(std::string path);
	sf::Font * loadFont(std::string path);

	sf::Texture checkForBackupImage(std::string path);

	sf::Vector2i getMousePosition();
	sf::Vector2f getMapPixelToCoords(sf::Vector2i point);
	sf::Vector2f getMousePositionLocal();

	

	sf::Font * getDefaultFont();

	sf::Time getTimeFromProgramStart();
	sf::Time getTimeFromFrameStart();
	


	void pushEvent(sf::Event mainEvent);

	void regEvents();
	std::vector<sf::Event> getWindowEvents();

	void closeApplication();
	

	bool running;

	bool eventKeyPressed= false;
	bool eventKeyReleased = false;

	bool eventMouseMove = false;

	bool eventMouseClicked = false;
	bool eventMousePressed = false; //mouse button is down (pressed)
	bool eventMouseReleased = false;

	bool eventMouseClickedLeft = false;
	bool eventMouseClickedRight = false;

	bool eventMousePressedLeft = false;
	bool eventMousePressedRight = false;

	bool eventMouseReleasedLeft = false;
	bool eventMouseReleasedRight = false;

	bool windowInFocus = true;

	static void setSpriteSize(sf::Sprite * sprite, double w, double h);

	sf::Vector2i getWindowSize();
	sf::RenderWindow * getWindow();

	sf::Clock totalTime;
	sf::Clock frameTime;
	sf::Time lastRenderTime;
	sf::Time deltaTime;

private:

	sf::Texture * checkForCopyOfTex(std::string path, sf::IntRect rec);
	sf::SoundBuffer * checkForCopyOfSound(std::string path);
	sf::Font * checkForCopyOfFont(std::string path);


	std::vector<sf::Event>  pendingEventList;
	std::vector<sf::Event> eventList;

	std::vector<texElement *> textures;
	std::vector<soundElement *> sounds;
	std::vector<FontElement *> fonts;

	sf::Font * defaultFont;
	sf::RenderWindow * mainWindow;


	std::mutex pendingEventsMutex;

};

