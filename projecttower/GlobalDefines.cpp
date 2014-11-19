#include "GlobalDefines.h"

int getDirectionIndex(sf::Vector2i direction){

	if (direction == DIR_SOUTH)
		return 0;
	else if (direction == DIR_WEST)
		return 1;
	else if (direction == DIR_EAST)
		return 2;
	else if (direction == DIR_NORTH)
		return 3;

	std::cout << "FUCK IN getDirectionIndex: " << direction.x << " " << direction.y << std::endl;
	return -1;

}

namespace TileTypes {
	const int grass = 1;
	const int dirt = 2;
	const int water = 3;
	const int wall = 4;
	const int cave = 5;
	const int tower = 6;
}

//namespace zIndexLayers {
//	const int background = 1;
//	const int tower = 2;
//	const int projectile = 3;
//	const int unit = 4;
//}


