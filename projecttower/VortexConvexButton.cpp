#include "VortexConvexButton.h"


VortexConvexButton::VortexConvexButton(std::vector<sf::Vector2f> vertices, std::string idleImage, std::string hoverImage, std::string title, Vortex * gameEngine) {
	
	this->gameEngine = gameEngine;
	mouseOverButton = false;
	buttonPressed = false;

	this->idleImage = gameEngine->loadImageToTexture(idleImage);
	this->hoverImage = (hoverImage != "") ? gameEngine->loadImageToTexture(hoverImage) : nullptr;

	shape.setTexture(gameEngine->loadImageToTexture(idleImage));
	this->title = title;
	font = *gameEngine->loadFont("Fonts/arial.ttf");

	float lowestX = 999999999.0f;
	float highestX = 0.0f;

	float lowestY = 999999999.0f;
	float highestY = 0.0f;

	shape.setPointCount(vertices.size());
	for (uint i = 0; i < vertices.size(); i++) {
		shape.setPoint(i, vertices[i]);

		//Determine the best possible center
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

	float midX = ((highestX - lowestX) / 2) - (title.size() / 2);
	float midY = (highestY - lowestY) / 2;
	text.setPosition(midX, midY);
	
	// select the font
	text.setFont(font); // font is a sf::Font

	// set the string to display
	text.setString(title);

	// set the character size
	text.setCharacterSize(20); // in pixels, not points!

	// set the color
	text.setColor(sf::Color::Blue);

	// set the text style
	text.setStyle(sf::Text::Bold | sf::Text::Underlined);

	
	
	shape.setFillColor(sf::Color(255, 255, 255, 255));

}


VortexConvexButton::~VortexConvexButton()
{
}

void VortexConvexButton::update(float delta) {

	if (gameEngine->eventMouseMove) {
		if (mouseOver()) {
			//std::cout << "Mouse over button" << std::endl;
			if (!mouseOverButton){
				mouseOverButton = true;
				shape.setOutlineThickness(3.0f);
				shape.setFillColor(sf::Color(225, 225, 225, 255));
				shape.setOutlineColor(sf::Color(215, 215, 215, 255));
				if (hoverImage != nullptr) {
					shape.setTexture(hoverImage);
				}
			}
			

		} else {
			//std::cout << "Mouse not over button" << std::endl;
			if (mouseOverButton){
				mouseOverButton = false;
				shape.setOutlineThickness(0.0f);
				shape.setFillColor(sf::Color(255, 255, 255, 255));
				if (hoverImage != nullptr) {
					shape.setTexture(idleImage);
				}
			}
			
		}
	} 
	if (gameEngine->eventMouseClickedLeft && mouseOver() && !buttonPressed) {
		buttonPressed = true;
		shape.setOutlineThickness(4.0f);
		shape.setFillColor(sf::Color(150, 150, 150, 255));
		shape.setOutlineColor(sf::Color(255, 255, 255, 255));
	} 
	if (gameEngine->eventMouseReleasedLeft && buttonPressed) {
		shape.setOutlineThickness(3.0f);
		shape.setFillColor(sf::Color(255, 255, 255, 255));
		shape.setOutlineColor(sf::Color(215, 215, 215, 255));
		if (mouseOver()) {
			shape.setFillColor(sf::Color(225, 225, 225, 255));
			buttonPressed = false;
			executeButton();
		}
	}


	gameEngine->getWindow()->draw(shape);
	//gameEngine->getWindow()->draw(text);

}

void VortexConvexButton::executeButton() {
	//HEY MR BUTTON, DO STUFF!

}

bool VortexConvexButton::hitPoint(sf::Vector2f point){
	return hitPoint(point.x, point.y);
}

// Winding number test for a point in a polygon
bool VortexConvexButton::hitPoint(float x, float y) {
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
			} else {
				//Use the line between the last point and the first point.
				if (shape.getPoint(0).y > mouse.y) {
					if (isLeft(shape.getPoint(i), shape.getPoint(0), mouse) > 0) {
						++wn;
					}
				}
			}
		} else {     
			if (i < shape.getPointCount() - 1) {
				if (shape.getPoint(i + 1).y <= mouse.y) {
					if (isLeft(shape.getPoint(i), shape.getPoint(i + 1), mouse) < 0) {
						--wn;
					}
				}
			} else {
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


bool VortexConvexButton::mouseOver(){

	sf::Vector2i mouse(gameEngine->getMousePosition().x, gameEngine->getMousePosition().y);
	return hitPoint(gameEngine->getMapPixelToCoords(mouse));

}