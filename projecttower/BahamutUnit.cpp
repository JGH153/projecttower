#include "BahamutUnit.h"


BahamutUnit::BahamutUnit(Vortex * gameEngine, std::vector<std::vector<MapTile *>> * mapGroundTiles, int posX, int posY, int endPosX, int endPosY) : Unit(gameEngine, mapGroundTiles, posX, posY) {

}


BahamutUnit::~BahamutUnit() {
}
