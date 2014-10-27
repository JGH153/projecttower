#pragma once
#include "VortexConvexButton.h"


VortexConvexButton::VortexConvexButton(int x, int y, std::vector<sf::Vector2f> vertices, std::string imageSource, std::string title, Vortex * gameEngine) : VortexButton(x, y, imageSource, title, gameEngine){
	shape.setTexture(image.getTexture());

	float lowestX = 999999999.0f;
	float highestX = 0.0f;

	float lowestY = 999999999.0f;
	float highestY = 0.0f;

	shape.setPointCount(vertices.size());
	// Determine BB size

	for (uint i = 0; i < vertices.size(); i++) {
		shape.setPoint(i, vertices[i]);
		if (vertices[i].x < lowestX) {
			lowestX = vertices[i].x;
		}
		else if (vertices[i].x > highestX) {
			highestX = vertices[i].x;
		}

		if (vertices[i].y < lowestY) {
			lowestY = vertices[i].x;
		}
		else if (vertices[i].y > highestY) {
			highestY = vertices[i].x;
		}
	}

	width = lowestX - highestX;
	height = lowestY - highestY;

	shape.setFillColor(sf::Color(255, 255, 255, 255));

	setPosition(posX, posY);

}


VortexConvexButton::~VortexConvexButton()
{
}

bool VortexConvexButton::hitPoint(sf::Vector2f point){
	return hitPoint(point.x, point.y);
}

std::vector<sf::Drawable *> VortexConvexButton::getRenderDrawable() {
	std::vector<sf::Drawable *> returnVector2;
	returnVector2.push_back(&shape);
	returnVector2.push_back(&text);
	return returnVector2;
}

// Winding number test for a point in a polygon
bool VortexConvexButton::hitPoint(double x, double y) {
	int wn = 0;    // the  winding number counter
	sf::Vector2f mouse(x, y);


	// Loop through all edges of the polygon
	for (int i = 0; i < shape.getPointCount(); i++) {
		//If the point y pos is greater or equal to the mouse y pos
		if (shape.getPoint(i).y <= mouse.y) {
			//And it is not the last point of the shape
			if (i < shape.getPointCount() - 1) {
				//And the next point is greater in y than the mouse y pos
				if (shape.getPoint(i + 1).y > mouse.y) {
					//Check if the mouse point is left or right of the line between the two points
					if (isLeft(shape.getPoint(i), shape.getPoint(i + 1), mouse) > 0) {
						++wn;
					}
				}
				//If it is the last vertex point in the shape.
			}
			else {
				//Use the line between the last point and the first point.
				if (shape.getPoint(0).y > mouse.y) {
					if (isLeft(shape.getPoint(i), shape.getPoint(0), mouse) > 0) {
						++wn;
					}
				}
			}
		}
		else {
			if (i < shape.getPointCount() - 1) {
				if (shape.getPoint(i + 1).y <= mouse.y) {
					if (isLeft(shape.getPoint(i), shape.getPoint(i + 1), mouse) < 0) {
						--wn;
					}
				}
			}
			else {
				if (shape.getPoint(0).y <= mouse.y) {
					if (isLeft(shape.getPoint(i), shape.getPoint(0), mouse) < 0) {
						--wn;
					}
				}
			}
		}
	}
	return (wn != 0);
}

// Tests if a point is Left|On|Right of an infinite line.
//    Input:  three points P0, P1, and P2
//    Return: >0 for P2 left of the line through P0 and P1
//            =0 for P2  on the line
//            <0 for P2  right of the line
int VortexConvexButton::isLeft(sf::Vector2f P0, sf::Vector2f P1, sf::Vector2f P2) {
	return ((P1.x - P0.x) * (P2.y - P0.y) - (P2.x - P0.x) * (P1.y - P0.y));
}

void VortexConvexButton::update(){

}

void VortexConvexButton::setPosition(sf::Vector2f newPosition) {
	posX = newPosition.x;
	posY = newPosition.y;
	image.setPosition(newPosition);
	shape.setPosition(newPosition);
	newPosition.x += shape.getGlobalBounds().width / 2 - text.getGlobalBounds().width / 2;
	newPosition.y += shape.getGlobalBounds().height / 2;
	text.setPosition(newPosition);
}
void VortexConvexButton::setPosition(double x, double y) {
	setPosition(sf::Vector2f(x, y));
}