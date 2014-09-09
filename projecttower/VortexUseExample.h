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

class VortexUseExample
{
public:
	VortexUseExample(Vortex * gameEngine);
	~VortexUseExample();

	void update();

	sf::Texture * texImage;
	VortexParticleSystem * particles;
	sf::Font * font;
	sf::Text text;

	VortexAnimation * testAnimation;
	std::vector<VortexAnimation *> animations;

	VortexSprite * sprit;

	VortexButton * testButton;

	sf::SoundBuffer buffer;
	sf::Sound sound;

	sf::Music music;

	Vortex * gameEngine;

	sf::Clock clock;

};

