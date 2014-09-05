#pragma once
#include "Pos.h"
#include <SFML\Graphics.hpp>

class GameObject {
public:
	GameObject();
	GameObject(Pos position);
	GameObject(Pos position, double w, double h);
	Pos topLeft;
	double width;
	double height;
};