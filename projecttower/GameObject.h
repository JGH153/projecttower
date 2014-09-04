#pragma once
#include "Pos.h"
#include <SFML\Graphics.hpp>

class GameObject {
public:
	GameObject();
	GameObject(Pos position);
	Pos pos;

};