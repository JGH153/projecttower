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



