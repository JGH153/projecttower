#include "VortexSound.h"

VortexSound::VortexSound(): sf::Sound() {
}

VortexSound::VortexSound(Vortex * gameEngine, std::string path) : sf::Sound() {

	setBuffer(*gameEngine->loadSound(path));

}


VortexSound::~VortexSound() {
}
