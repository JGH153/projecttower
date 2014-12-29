#include "VortexMusic.h"


VortexMusic::VortexMusic() : sf::Music(){



}

VortexMusic::VortexMusic(Vortex * gameEngine, std::string path) : sf::Music() {

	gameEngine->openMusicByPath(*this, path);


}


VortexMusic::~VortexMusic() {
}
