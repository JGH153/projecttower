#include "GameObject.h"

GameObject::GameObject() {

}


GameObject::GameObject(Pos position) {
	topLeft = position;
	width = 0;
	height = 0;
}

GameObject::GameObject(Pos position, double w, double h) {
	topLeft = position;
	width = w;
	height = h;
}